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

typedef std::tuple<int, int, K::FT> Edge;
typedef std::vector<Edge> EdgeV;
typedef K::Point_2 P;
typedef std::pair<P, int> IPoint;

int num_families(int k, std::vector<int>& num_size){
  if (k == 1) return num_size[1];
  if (k == 2) return num_size[2] + num_size[1]/2;
  if (k == 3){
    int c12 = std::min(num_size[1], num_size[2]);
    int a12 = (num_size[1]-c12)/3 + (num_size[2]-c12)/2;
    return num_size[3] + c12 + a12;
  }
  else{
    int c13 = std::min(num_size[1], num_size[3]);
    int a13_2 = (num_size[1]-c13)/2 + (num_size[3]-c13);
    int a123 = (num_size[2] + a13_2)/2;
    return num_size[4] + c13 + a123;
  }
}

void solve() {
  int n, k; long f0, s0;
  std::cin >> n >> k >> f0 >> s0;
  std::vector<IPoint> points;
  points.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x, y; std::cin >> x >> y;
    points.emplace_back(K::Point_2(x, y), i);
  }
  Delaunay t;
  t.insert(points.begin(), points.end());
  EdgeV edges;
  edges.reserve(3*n);
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
  std::vector<int> num_size(4 + 1, 0);
  num_size[1] = n;
  std::vector<int> sizes(n, 1);
  int n_components = n;
  long f = -1, s = 0;
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
    int c1 = uf.find_set(std::get<0>(*e));
    int c2 = uf.find_set(std::get<1>(*e));
    long dist = std::get<2>(*e);
    if (f == -1 && dist >= s0) f = num_families(k, num_size);
    if (c1 != c2) {
      if (num_families(k, num_size) >= f0) s = dist;
      int s1 = sizes[c1], s2 = sizes[c2];
      uf.link(c1, c2);
      int c3 = uf.find_set(c1);
      sizes[c3] = s1 + s2;
      num_size[std::min(k, s1)]--;
      num_size[std::min(k, s2)]--;
      num_size[std::min(k, s1 + s2)]++;
      if (--n_components == 0) break;
    }
  }
  if (f == -1) f = 1;
  std::cout << s << ' ' << f << '\n';
}
  
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t; std::cin >> t;
  while (t--) solve();
}