#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 P;
typedef K::Segment_2 S;

void solve(int n){
  std::vector<P> points(n);
  long le, bo, ri, to; std::cin >> le >> bo >> ri >> to;
  for (int i = 0; i < n; i++){
    int x, y; std::cin >> x >> y;
    points[i] = P(x, y);
  }
  Triangulation t(points.begin(), points.end());
  std::vector<double> die_time_sqrd;
  for (auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); v++){
    P p = v->point();
    double die_dist = std::min({std::abs(p.x() - le), std::abs(p.x() - ri), std::abs(p.y() - bo), std::abs(p.y() - to)});
    double die_dist_sqrd = std::numeric_limits<long>::max();
    auto ec = t.incident_edges(v);
    if (ec != nullptr){
      do {
        if (t.is_infinite(ec)) continue;
        double curr = t.segment(ec).squared_length()/4;
        die_dist_sqrd = std::min(die_dist_sqrd, curr);
      } while(++ec != t.incident_edges(v));
    }
    die_time_sqrd.push_back(std::min(die_dist - 0.5, std::sqrt(die_dist_sqrd) - 0.5));
  }
  std::sort(die_time_sqrd.begin(), die_time_sqrd.end());
  auto sqrt_and_ceil = [](double t){return std::ceil(std::sqrt(t));};
  auto t0 = sqrt_and_ceil(die_time_sqrd[0]);
  auto t1 = sqrt_and_ceil(die_time_sqrd[n/2]);
  auto t2 = sqrt_and_ceil(die_time_sqrd[n - 1]);
  std::cout << t0 << ' ' << t1 << ' ' << t2 << '\n';
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  while (n > 0){
    solve(n);
    std::cin >> n;
  }
}