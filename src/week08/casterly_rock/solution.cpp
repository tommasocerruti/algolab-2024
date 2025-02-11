#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef long IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

long conversion(const CGAL::Quotient<ET>& x){
  double a = std::ceil(CGAL::to_double(x));
  while (a+1 >= x) a -= 1;
  while (a < x) a += 1;
  return long(a);
}

void solve(){
  int n, m; long s; std::cin >> n >> m >> s;
  std::vector<std::pair<int, int>> nobles(n);
  std::vector<std::pair<int, int>> commons(m);
  Program lp (CGAL::SMALLER, false, 0, false, 0); 
  long sumxn = 0, sumyn = 0, sumxc = 0, sumyc = 0;
  const int a = 0, b = 1, c = 2;
  for (int i = 0; i < n; i++) {
    int x, y; std::cin >> x >> y;
    nobles[i] = {x, y};
    sumxn += x; sumyn += y;
    lp.set_a(a, i, x); lp.set_a(b, i, y); lp.set_a(c, i, 1);
    lp.set_b(i, 0);
  }
  for (int i = 0; i < m; i++) {
    int x, y; std::cin >> x >> y;
    commons[i] = {x, y};
    sumxc += x; sumyc += y;
    lp.set_a(a, n+i, -x); lp.set_a(b, n+i, -y); lp.set_a(c, n+i, -1);
    lp.set_b(n+i, 0);
  }
  lp.set_l(a, true, 1); lp.set_u(a, true, 1);
  Solution sol = CGAL::solve_linear_program(lp, ET());
  if (sol.is_infeasible()){ 
    std::cout << "Y\n";
    return;
  }
  if (s != -1){
    lp.set_a(b, n+m, sumyc - sumyn);
    lp.set_a(c, n+m, m - n);
    lp.set_b(n+m, s - (sumxc - sumxn));
    sol = CGAL::solve_linear_program(lp, ET());
    if (sol.is_infeasible()){ 
      std::cout << "B\n";
      return;
    }
  }
  int eq = n+m+1;
  const int a1 = 3, b1 = 4, c1 = 5, r = 6;
  lp.set_a(a1, eq, 1);
  lp.set_a(b, eq, 1);
  lp.set_b(eq++, 0);
  lp.set_a(a1, eq, -1);
  lp.set_a(b, eq, -1);
  lp.set_b(eq++, 0);
  lp.set_l(b1, true, 1);
  lp.set_u(b1, true, 1);
  for (int i = 0; i < n; i++){
    lp.set_a(a1, eq, nobles[i].first);
    lp.set_a(c1, eq, 1);
    lp.set_a(r, eq, -1);
    lp.set_b(eq++, -nobles[i].second);
    lp.set_a(a1, eq, -nobles[i].first);
    lp.set_a(c1, eq, -1);
    lp.set_a(r, eq, -1);
    lp.set_b(eq++, nobles[i].second);
  }
  for (int i = 0; i < m; i++){
    lp.set_a(a1, eq, commons[i].first);
    lp.set_a(c1, eq, 1);
    lp.set_a(r, eq, -1);
    lp.set_b(eq++, -commons[i].second);
    lp.set_a(a1, eq, -commons[i].first);
    lp.set_a(c1, eq, -1);
    lp.set_a(r, eq, -1);
    lp.set_b(eq++, commons[i].second);
  }
  lp.set_c(r, 1);
  sol = CGAL::solve_linear_program(lp, ET());
  if (sol.is_infeasible()) std::cout << "Y\n";
  std::cout << conversion(sol.objective_value()) << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) solve();
}