#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef K::Point_2 P;
typedef K::Circle_2 C;

struct beer_t{int x, y, s, a;};
struct stadium_t{int x, y, d, u;};
struct contour_t{int x, y; long rs;};

int n, m, c; 

double floor_to_double(const CGAL::Quotient<ET>& x){
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void compute_costs(std::vector<beer_t>& beers, std::vector<stadium_t>& stadiums, std::vector<std::vector<int>>& revenues){
  Program lp (CGAL::SMALLER, true, 0, false, 0);
  auto var = [&](int beer, int stadium){return beer*m + stadium;};
  int eq = 0;
  for (int i = 0; i < n; i++){
    for (int j = 0; j < m; j++){
      lp.set_a(var(i, j), eq, 1);
    }
    lp.set_b(eq++, beers[i].s);
  }
  for (int j = 0; j < m; j++){
    for (int i = 0; i < n; i++){
      lp.set_a(var(i, j), eq, 1);
    }
    lp.set_b(eq++, stadiums[j].d);
    for (int i = 0; i < n; i++){
      lp.set_a(var(i, j), eq, -1);
    }
    lp.set_b(eq++, -stadiums[j].d);    
  }
  for (int j = 0; j < m; j++){
    for (int i = 0; i < n; i++){
      lp.set_a(var(i, j), eq, beers[i].a);
    }
    lp.set_b(eq++, 100*stadiums[j].u);
  }
  for (int i = 0; i < n; i++){
    for (int j = 0; j < m; j++){
      lp.set_c(var(i, j), -revenues[i][j]);
    }
  }
  Solution sol = CGAL::solve_linear_program(lp, ET());
  if (sol.is_infeasible()) std::cout << "no\n";
  else std::cout << long(floor_to_double(-sol.objective_value()/100)) << '\n';
}

void update_costs(std::vector<beer_t>& beers, std::vector<stadium_t>& stadiums,
  std::vector<std::vector<int>>& revenues, std::vector<contour_t>& contours){
  std::vector<C> circles;
  circles.reserve(c);
  for (int i = 0; i < c; i++){
    circles.emplace_back(C(P(contours[i].x, contours[i].y), contours[i].rs));
  }
  std::vector<std::unordered_set<int>> bc(n), sc(m);
  for (int i = 0; i < n; i++){
    P point = P(beers[i].x, beers[i].y);
    for (int k = 0; k < c; k++){
      if (circles[k].has_on_bounded_side(point)) bc[i].insert(k);
    }
  }
  for (int j = 0; j < m; j++){
    P point = P(stadiums[j].x, stadiums[j].y);
    for (int k = 0; k < c; k++){
      if (circles[k].has_on_bounded_side(point)) sc[j].insert(k);
    }
  }
  for (int i = 0; i < n; i++){
    for (int j = 0; j < m; j++){
      int tot = bc[i].size() + sc[j].size();
      for (int v : bc[i]){
        if (sc[j].find(v) != sc[j].end()) tot -= 2;
      }
      revenues[i][j] = revenues[i][j]*100 - tot;
    }
  }
}

void solve(){
  std::cin >> n >> m >> c;
  std::vector<beer_t> beers;
  std::vector<stadium_t> stadiums;
  std::vector<contour_t> contours;
  std::vector<std::vector<int>> revenues(n, std::vector<int>(m));
  for (int i = 0; i < n; i++){
    int x, y, s, a; std::cin >> x >> y >> s >> a;
    beers.push_back({x, y, s, a});
  }
  for (int i = 0; i < m; i++){
    int x, y, d, u; std::cin >> x >> y >> d >> u;
    stadiums.push_back({x, y, d, u});
  }
  for (int i = 0; i < n; i++){
    for (int j = 0; j < m; j++){
      int r; std::cin >> r;
      revenues[i][j] = r;
    }
  }
  for (int i = 0; i < c; i++){
    int x, y; long r; std::cin >> x >> y >> r;
    contours.push_back({x, y, r*r});
  }
  update_costs(beers, stadiums, revenues, contours);
  compute_costs(beers, stadiums, revenues);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t; std::cin >> t;
  while (t--) solve();
}