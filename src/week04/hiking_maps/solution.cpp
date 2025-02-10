#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <iostream>
#include <algorithm>
typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Line_2 L;
typedef K::Triangle_2 T;

void solve(){
  int m, n;
  std::cin >> m >> n;
  std::vector<P> points(m);
  for (int i = 0; i < m; i++){
    int x, y;
    std::cin >> x >> y;
    points[i] = P(x, y);
  }
  std::vector<std::vector<int>> tr_covers_lg(n)
  for (int i = 0; i < n; i++){
    int x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6;
    std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4 >> x5 >> y5 >> x6 >> y6;
    L l1 = L(P(x1, y1), P(x2, y2));
    L l2 = L(P(x3, y3), P(x4, y4));
    L l3 = L(P(x5, y5), P(x6, y6));
    auto i1 = CGAL::intersection(l1, l2);
    auto i2 = CGAL::intersection(l2, l3);
    auto i3 = CGAL::intersection(l3, l1);
    const P* v1 = boost::get<P>(&*i1));
    const P* v2 = boost::get<P>(&*i2));
    const P* v3 = boost::get<P>(&*i3));
    T tr = T(*v1, *v2, *v3);
    std::vector<bool> contains(m, false);
    for (int i = 0; i < m; i++) if (tr.has_on_bounded_side(points[i])) contains[i] = true;
    for (int i = 0; i < m - 1; i++) if (contains[i] && contains[i + 1]) tr_covers_leg[n].push_back(i);
  }
  std::vector<int> covered(m, 0);
  int l = 0, best = n;
  bool all_covered;
  for (int v : tr_covers_lg[0]) covered[v]++;
  for (int r = 1; r < n; r++){
    all_covered = false;
    for (int cover : covered)
      if (cover == 0) all_covered = false;
    if (all_covered){
      while (all_covered){
        best = std::min(best, r - l);
      }
    }
  }
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int c; std::cin >> c;
  while(c--) solve();
}