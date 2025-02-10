#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <vector>

typedef  CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef  CGAL::Min_circle_2_traits_2<K>  Traits;
typedef  CGAL::Min_circle_2<Traits>      Min_circle;

long ceil_to_long(const K::FT& x){
  double a = std::ceil(CGAL::to_double(x));
  while (a-1 >= x) a -= 1;
  while (a < x) a += 1;
  return long(a);
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int n;
  std::cin >> n;
  while (n > 0){
    std::vector<K::Point_2> P;
    while (n > 0){
      long x, y;
      std::cin >> x >> y;
      P.push_back(K::Point_2(x, y));
      n--;
    }
    Min_circle mc(P.begin(), P.end(), true);
    Traits::Circle c = mc.circle();
    std::cout << ceil_to_long(CGAL::sqrt(c.squared_radius())) << '\n';
    std::cin >> n;
  }
}