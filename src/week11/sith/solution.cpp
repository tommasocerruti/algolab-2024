#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel    K;
typedef int                                                    Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef std::pair<K::Point_2,Index>                            IPoint;

void solve() {
  int n, r; std::cin >> n >> r;
  std::vector<IPoint> points;
  points.reserve(n);
  for (int i = 0; i < n; i++) {
    int x, y; std::cin >> x >> y;
    points.emplace_back(K::Point_2(x, y), i);
  }
  int left = 2, right = n/2;
  long rs = pow(r, 2);
  while (left <= right){
    int mid = left + (right - left)/2;
    Delaunay t;
    t.insert(points.begin() + mid, points.end());
    boost::disjoint_sets_with_storage<> uf(n);
    std::vector<int> sizes(n, 1);
    for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
      Index i1 = e->first->vertex((e->second+1)%3)->info();
      Index i2 = e->first->vertex((e->second+2)%3)->info();
      Index c1 = uf.find_set(i1);
      Index c2 = uf.find_set(i2);
      long dist = t.segment(e).squared_length();
      if (c1 != c2 && dist <= rs){
        int s1 = sizes[c1], s2 = sizes[c2];
        uf.link(c1, c2);
        Index c3 = uf.find_set(i1);
        sizes[c3] = s1 + s2;
      }
    }
    int best = *std::max_element(sizes.begin(), sizes.end());
    if (best >= mid) left = mid + 1;
    else right = mid - 1;
  }
  std::cout << left - 1 << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t; std::cin >> t;
  while (t--) solve();
}