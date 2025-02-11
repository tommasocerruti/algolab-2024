#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel    K;
typedef int                                                    Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef std::pair<K::Point_2,Index>                            IPoint;
typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

struct student{int m, c, g;};

void solve() {
  int F, M, C, G, d, s;
  std::cin >> F >> M >> C >> G >> d >> s;
  std::vector<student> students(s);
  std::vector<IPoint> points;
  points.reserve(s);
  for (int i = 0; i < s; ++i){
    int x, y, m, c, g;
    std::cin >> x >> y >> m >> c >> g;
    points.emplace_back(K::Point_2(x, y), i);
    students[i] = {m, c, g};
  }
  Delaunay t;
  t.insert(points.begin(), points.end());
  std::vector<int> best_rate(s, -1);
  for (int i = 0; i < d; i++){
    int x, y, f;
    std::cin >> x >> y >> f;
    int ind = t.nearest_vertex(K::Point_2(x, y))->info();
    if (best_rate[ind] == -1 || best_rate[ind] > f) best_rate[ind] = f;
  }
  Program lp (CGAL::SMALLER, true, 0, true, 24);
  const int fc = 0, mc = 1, cc = 2, gc = 3;
    lp.set_b(fc, F); lp.set_b(mc, -M); lp.set_b(cc, -C); lp.set_b(gc, -G);

  for (int i = 0; i < s; i++){
    if (best_rate[i] != -1){
      lp.set_a(i, fc, best_rate[i]);
      lp.set_a(i, mc, -students[i].m);
      lp.set_a(i, cc, -students[i].c);
      lp.set_a(i, gc, -students[i].g);
    }
  }
  Solution sol = CGAL::solve_linear_program(lp, ET());
  if (sol.is_infeasible()) std::cout << "H\n";
  else std::cout << "L\n";
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t; std::cin >> t;
  while(t--) solve();
}