#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef CGAL::Gmpq IT;
typedef CGAL::Gmpq ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

struct P{int x, y;};

double floor_to_long(const CGAL::Quotient<ET>& x){
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return long(a);
}

void solve(){
  long n, m, h, w; std::cin >> n >> m >> h >> w;
  std::vector<P> newp, oldp;
  Program lp (CGAL::SMALLER, true, 1, false, 0); 
  for (int i = 0; i < n; i++){
    int x, y; std::cin >> x >> y;
    newp.push_back({x, y});
  }
  for (int i = 0; i < m; i++){
    int x, y; std::cin >> x >> y;
    oldp.push_back({x, y});
  }
  int eq = 0;
  for (int i = 0; i < n - 1; i++){
    for (int j = i + 1; j < n; j++){
      long xc = 2*std::abs(newp[i].x - newp[j].x);
      long yc = 2*std::abs(newp[i].y - newp[j].y); 
      lp.set_a(i, eq, 1); lp.set_a(j, eq, 1);
      lp.set_b(eq++, std::max(IT(xc, w), IT(yc, h)));
    }
  }
  for (int i = 0; i < n; i++){
    IT worst = IT(INT_MAX, 1);
    for (int j = 0; j < m; j++){
      long xc = 2*std::abs(newp[i].x - oldp[j].x) - w;
      long yc = 2*std::abs(newp[i].y - oldp[j].y) - h; 
      worst = std::min(worst, std::max(IT(xc, w), IT(yc, h)));
    }
    lp.set_u(i, true, worst);
  }
  for (int i = 0; i < n; i++) lp.set_c(i, -2*(h + w));
  Solution sol = CGAL::solve_linear_program(lp, ET());
  std::cout << -floor_to_long(sol.objective_value()) << '\n'; 
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
  int t; std::cin >> t;
  while(t--) solve();
}
