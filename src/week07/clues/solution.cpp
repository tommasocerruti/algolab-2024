#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <bits/stdc++.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel    K;
typedef std::pair<int, bool>                                   Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef K::Point_2                                             P;
typedef Delaunay::Vertex_handle                                vertex;

bool is_valid(Delaunay t, K::FT dis){
  for (auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v){
    v->info() = {0, false};
  }
  Delaunay green, blue;
  int comp = 1;
  for (auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v){
    if (v->info().first == 0){
      v->info() = {comp, false};
      std::stack<vertex> stk;
      stk.push(v);
      while (!stk.empty()){
        auto val = stk.top();
        stk.pop();
        auto neigh = t.incident_vertices(val);
        do{
          if (!t.is_infinite(neigh) && CGAL::squared_distance(neigh->point(), val->point()) <= dis){
            if (neigh->info() == val->info()) return false;
            if (neigh->info().first == 0){
              neigh->info() = {comp, !val->info().second};
              stk.push(neigh);
            }
          }
        } while(++neigh != t.incident_vertices(val));
      }
      comp++;
    }
    if (v->info().second) green.insert(v->point());
    else blue.insert(v->point());
  }
  auto violates = [&](Delaunay t, K::FT dis){
    for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e)
      if (t.segment(*e).squared_length() <= dis)
        return true;
    return false;
  };
  return !violates(green, dis) && !violates(blue, dis);
}

void solve(){
  int n, m;
  K::FT r;
  std::cin >> n >> m >> r;
  std::vector<P> points;
  points.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    points.emplace_back(P(x, y));
  }
  Delaunay t;
  t.insert(points.begin(), points.end());
  K::FT r_squared = r*r;
  
  bool validity = is_valid(t, r_squared);
  
  for (int i = 0; i < m; i++){
    P holmes, watson;
    std::cin >> holmes >> watson;
    if (validity){
      if (CGAL::squared_distance(holmes, watson) <= r_squared){
        std::cout << 'y';
        continue;
      }
      auto holmes_nearest = t.nearest_vertex(holmes);
      auto watson_nearest = t.nearest_vertex(watson);
      if (holmes_nearest->info().second == watson_nearest->info().second &&
        CGAL::squared_distance(holmes, holmes_nearest->point()) <= r_squared &&
        CGAL::squared_distance(watson, watson_nearest->point()) <= r_squared){
          std::cout << 'y';
          continue;
        }
    }
    std::cout << 'n';
  }
  std::cout << '\n';
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t; std::cin >> t;
  while(t--) solve();
}