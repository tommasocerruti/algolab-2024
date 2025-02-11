#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;

void solve(int n){
  std::vector<K::Point_2> pts;
  pts.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    pts.push_back(K::Point_2(x, y));
  }
  Triangulation t;
  t.insert(pts.begin(), pts.end());
  int m;
  std::cin >> m;
  for (int i = 0; i < m; i++){
    int x, y;
    std::cin >> x >> y;
    auto p = t.nearest_vertex(K::Point_2(x, y))->point();
    std::cout << long(CGAL::squared_distance(p, K::Point_2(x, y))) << std::endl;
  }
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n; std::cin >> n;
  while (n != 0){ 
    solve(n);
    std::cin >> n;
  }
}