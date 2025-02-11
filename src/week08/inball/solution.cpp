#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

double floor_to_double(const CGAL::Quotient<ET>& x){
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void solve(){
  int n; std::cin >> n;
  while (n > 0){
    int d; std::cin >> d;
    Program lp (CGAL::SMALLER, false, 0, false, 0);
    for (int i = 0; i < n; i++){
      long norm = 0;
      for (int j = 0; j < d; j++){
        int aij; std::cin >> aij;
        lp.set_a(j, i, aij);
        norm += aij*aij;
      }
      lp.set_a(d, i, std::sqrt(norm));
      int b; std::cin >> b;
      lp.set_b(i, b);
    }
    lp.set_l(d, true, 0);
    lp.set_c(d, -1);
    Solution sol = CGAL::solve_linear_program(lp, ET());
    if (sol.is_infeasible()) std::cout << "none\n";
    else if (sol.is_unbounded()) std::cout << "inf\n";
    else std::cout << floor_to_double(-sol.objective_value()) << '\n';
    std::cin >> n; 
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  solve();
}