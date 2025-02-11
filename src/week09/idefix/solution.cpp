#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef K::Point_2 P;
typedef std::tuple<int,int,K::FT> Edge;
typedef std::vector<Edge> EdgeV;
typedef std::pair<K::Point_2,int> IPoint;

void solve() {
  int n, m, k; long s; std::cin >> n >> m >> s >> k;
  std::vector<IPoint> points;
  points.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x, y; std::cin >> x >> y;
    points.emplace_back(P(x, y), i);
  }
  Delaunay t;
  t.insert(points.begin(), points.end());
  EdgeV edges_ext;
  edges_ext.reserve(m);
  std::vector<int> sizes(n, 0);
  for (int i = 0; i < m; i++) {
    int x, y; std::cin >> x >> y;
    auto v = t.nearest_vertex(P(x, y));
    K::FT dis  = 4*CGAL::squared_distance(v->point(), P(x, y));
    if (dis <= s) sizes[v->info()]++;
    edges_ext.emplace_back(v->info(), n + i, dis);
  }
  EdgeV edges;
  edges.reserve(3*n + m);
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    int i1 = e->first->vertex((e->second+1)%3)->info();
    int i2 = e->first->vertex((e->second+2)%3)->info();
    if (i1 > i2) std::swap(i1, i2);
    edges.emplace_back(i1, i2, t.segment(e).squared_length());
  }
  std::sort(edges.begin(), edges.end(),
      [](const Edge& e1, const Edge& e2) -> bool {
        return std::get<2>(e1) < std::get<2>(e2);
            });
  boost::disjoint_sets_with_storage<> uf(n);
  int n_components = n;
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
    int c1 = uf.find_set(std::get<0>(*e));
    int c2 = uf.find_set(std::get<1>(*e));
    K::FT dis = std::get<2>(*e);
    if (dis <= s && c1 != c2) {
      int s1 = sizes[c1], s2 = sizes[c2];
      uf.link(c1, c2);
      int c3 = uf.find_set(c1);
      sizes[c3] = s1 + s2;
      if (--n_components == 1) break;
    }
    if (dis > s) break;
  }
  long a = *std::max_element(sizes.begin(), sizes.end());
  
  std::vector<long> sizes_q(n + m, 0);
  for (int i = 0; i < m; i++){ 
    edges.push_back(edges_ext[i]);
    sizes_q[n + i] = 1;
  }
  std::sort(edges.begin(), edges.end(),
    [](const Edge& e1, const Edge& e2) -> bool {
      return std::get<2>(e1) < std::get<2>(e2);
          });
  boost::disjoint_sets_with_storage<> uf_ext(n + m);
  n_components = n + m;
  K::FT q = 4*s;
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
    int c1 = uf_ext.find_set(std::get<0>(*e));
    int c2 = uf_ext.find_set(std::get<1>(*e));
    if (c1 != c2) {
      int s1 = sizes_q[c1], s2 = sizes_q[c2];
      uf_ext.link(c1, c2);
      int c3 = uf_ext.find_set(c1);
      sizes_q[c3] = s1 + s2;
      if (s1 + s2 >= k){
        q = std::get<2>(*e);
        break;
      }
    }
  }
  std::cout << a << ' ' << q << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
  std::size_t t;
  for (std::cin >> t; t > 0; --t) solve();
}