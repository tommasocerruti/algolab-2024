#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Gmpq.h>

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

int ceil_to_int(const CGAL::Quotient<CGAL::Gmpz> &x){
 double a = std::ceil(CGAL::to_double(x));
 while (a+1 >= x) a -= 1;
 while (a < x) a += 1;
 return a;
}

void testcases(){
  const int X = 0; 
  const int Y = 1;
  const int Z = 2;
  Program lp;
  int p, a, b;
  while(true) {
    std::cin >> p;
    if(p == 0) {
      return;
    } 
    else{
      std::cin >> a >> b;
      if(p == 1) {
        lp = Program(CGAL::SMALLER, true, 0, false, 0); 
        lp.set_a(X, 0,  1); lp.set_a(Y, 0, 1); lp.set_b(0, 4);
        lp.set_a(X, 1, 4); lp.set_a(Y, 1, 2); lp.set_b(1, a * b);
        lp.set_a(X, 2, -1); lp.set_a(Y, 2, 1); lp.set_b(2, 1);
        lp.set_c(X, a); lp.set_c(Y, -b);
      } 
      else{
        lp = Program(CGAL::SMALLER, false, 0, true, 0); 
        lp.set_a(X, 0,  -1); lp.set_a(Y, 0, -1); lp.set_a(Z, 0, 0); lp.set_b(0, 4);
        lp.set_a(X, 1, -4); lp.set_a(Y, 1, -2); lp.set_a(Z, 1, -1); lp.set_b(1, a * b);
        lp.set_a(X, 2, 1); lp.set_a(Y, 2, -1); lp.set_a(Z, 2, 0); lp.set_b(2, 1);
        lp.set_c(X, a); lp.set_c(Y, b); lp.set_c(Z, 1);          
      }
    } 
    
    Solution s = CGAL::solve_linear_program(lp, ET());
    if(s.is_unbounded()) std::cout << "unbounded" << std::endl;
    else if(s.is_infeasible()) std::cout << "no" << std::endl;
    else {
      auto val = s.objective_value();
      if (p == 1) std::cout << floor_to_int(-val) << std::endl;
      else std::cout << ceil_to_int(val) << std::endl;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  testcases();
}