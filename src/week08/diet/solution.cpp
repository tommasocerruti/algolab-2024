#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int floor_to_int(const CGAL::Quotient<CGAL::Gmpz> &x){
 int a = std::floor(CGAL::to_double(x));
 while (a > x) a -= 1;
 while (a+1 <= x) a += 1;
 return a;
}

void solve(int n, int m){
  
  Program lp(CGAL::SMALLER, true, 0, false, 0);
  for (int i = 0; i < n; i++){
    int imin, imax; std::cin >> imin >> imax;
    lp.set_b(i, imax); lp.set_b(i + n, -imin);
  }
  for (int j = 0; j < m; j++){
    int price; std::cin >> price;
    for (int i = 0; i < n; i++){
      int val; std::cin >> val;
      lp.set_a(j, i, val);
      lp.set_a(j, i + n, -val);
    }
    lp.set_c(j, price);
  }
  Solution s = CGAL::solve_linear_program(lp, ET());
  if (s.is_unbounded()) std::cout << "unbounded" << std::endl;
  else if (s.is_infeasible()) std::cout << "No such diet." << std::endl;
  else std::cout << floor_to_int(s.objective_value()) << std::endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int n, m;
  std::cin >> n >> m;
  while (n != 0 || m != 0){
    solve(n, m);
    std::cin >> n >> m;
  }
}