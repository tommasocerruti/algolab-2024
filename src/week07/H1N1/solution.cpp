#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <bits/stdc++.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel    K;
typedef CGAL::Triangulation_vertex_base_2<K>                   Vb;
typedef CGAL::Triangulation_face_base_with_info_2<int, K>      Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef K::Point_2                                             P;

void solve(int n) {
  std::vector<P> points(n);
  for (int i = 0; i < n; ++i) {
    int x, y; std::cin >> x >> y;
    points[i] = P(x, y);
  }
  Delaunay t;
  t.insert(points.begin(), points.end());
  int index = 1;
  for (auto f = t.finite_faces_begin(); f != t.finite_faces_end(); f++) f->info() = index++;
  std::vector<std::vector<std::pair<int, double>>> graph(index);
  for (auto f = t.finite_faces_begin(); f != t.finite_faces_end(); f++){
    int u = f->info();
    for (int i = 0; i < 3; i++){
      auto fn = f->neighbor(i);
      int v = (t.is_infinite(fn) ? 0:fn->info());
      auto p1 = f->vertex((i + 1) % 3)->point();
      auto p2 = f->vertex((i + 2) % 3)->point();
      double dist = CGAL::squared_distance(p1, p2);
      graph[u].push_back({v, dist});
      if (v == 0) graph[v].push_back({u, dist});
    }
  }
  std::vector<double> bottleneck(index, -1);
  std::priority_queue<std::pair<double, int>> pq;
  pq.push({DBL_MAX, 0});
  while (!pq.empty()){
    auto [val, u] = pq.top(); 
    pq.pop();
    if (bottleneck[u] != -1) continue;
    bottleneck[u] = val;
    for (auto neigh : graph[u]){
      int v = neigh.first;
      double dis = neigh.second;
      if (bottleneck[v] == -1) pq.push({std::min(dis, val), v});
    }
  }
  int m; std::cin >> m;
  for (int i = 0; i < m; i++){
    int x, y; double d; std::cin >> x >> y >> d;
    P person(x, y);
    P closest = t.nearest_vertex(person)->point();
    auto fzone = t.locate(person);
    int zone = (t.is_infinite(fzone) ? 0:fzone->info());
    if (CGAL::squared_distance(person, closest) < d || bottleneck[zone] < 4*d) std::cout << 'n';
    else std::cout << 'y';
  }
  std::cout << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n; std::cin >> n;
  while (n != 0){
    solve(n);
    std::cin >> n;
  }
}