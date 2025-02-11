#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel      K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K>     Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef std::pair<K::Point_2,int> IPoint;

struct Event{K::FT value; int type;};
auto sort_events = [](Event e1, Event e2){
  if (e1.value == e2.value) return e1.type < e2.type;
  return e1.value < e2.value;
};

void solve() {
  int n, h; K::FT s; std::cin >> n >> s >> h;
  std::vector<IPoint> points; points.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x, y; std::cin >> x >> y;
    points.emplace_back(K::Point_2(x, y), i);
  }
  Delaunay t;
  t.insert(points.begin(), points.end());
  auto get_face_radius = [&](Delaunay::Face_handle f){
    if (t.is_infinite(f)) return K::FT(LONG_MAX);
    return K::Circle_2(f->vertex(0)->point(), f->vertex(1)->point(), f->vertex(2)->point()).squared_radius();
  };
  int a_2 = 0, a_3 = 0, a_s = 0, a_max = 0;
  K::FT min_rad_a2 = K::FT(LONG_MAX);
  std::vector<Event> events;
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); e++){
    auto v1 = e->first->vertex((e->second+1)%3);
    auto v2 = e->first->vertex((e->second+2)%3);
    auto midpoint = CGAL::midpoint(v1->point(), v2->point());
    int nearest = t.nearest_vertex(midpoint)->info();
    auto f1 = e->first;
    auto f2 = t.mirror_edge(*e).first;
    K::FT f1_rad = get_face_radius(f1);
    K::FT f2_rad = get_face_radius(f2);
    K::FT min_radius, max_radius = std::max(f1_rad, f2_rad);
    if (nearest != v1->info() && nearest != v2->info()) min_radius = std::min(f1_rad, f2_rad);
    else min_radius = t.segment(*e).squared_length()/4;
    if (min_radius <= s && max_radius >= s) a_s++;
    events.push_back({min_radius, 0});
    events.push_back({max_radius, 1});
    if (min_radius == min_rad_a2) a_2++;
    else if (min_radius < min_rad_a2){
      min_rad_a2 = min_radius;
      a_2 = 1;
    }
  }
  K::FT min_rad_a3 = K::FT(LONG_MAX);
  for (auto f = t.finite_faces_begin(); f != t.finite_faces_end(); f++){
    K::FT radius = get_face_radius(f);
    if (radius == min_rad_a3) a_3++;
    else if (radius < min_rad_a3){
      min_rad_a3 = radius;
      a_3 = 1;
    }
  }
  int curr = 0;
  std::sort(events.begin(), events.end(), sort_events);
  for (auto event : events){
    if (event.type == 0) curr++;
    else curr--;
    a_max = std::max(a_max, curr);
  }
  std::cout << a_2 << ' ' << a_3 << ' ' << a_s << ' ' << a_max << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t; std::cin >> t;
  while (t--) solve();
}