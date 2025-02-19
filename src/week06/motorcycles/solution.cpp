#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>
#include <bits/stdc++.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Gmpq slope;

struct moto{int i; long y0; slope s;};

void solve(){
  int n; std::cin >> n;
  std::vector<moto> motos;
  for (int i = 0; i < n; i++){
    long y0, x1, y1; std::cin >> y0 >> x1 >> y1;
    slope s = slope(y1 - y0, x1);
    motos.push_back({i, y0, s});
  }
  std::vector<bool> forever(n, true);
  auto sort_motos = [](moto m1, moto m2){return m1.y0 > m2.y0;};
  std::sort(motos.begin(), motos.end(), sort_motos);
  slope min_slope = motos[0].s;
  for (int i = 1; i < n; i++){
    moto curr = motos[i];
    if (CGAL::abs(curr.s) <= CGAL::abs(min_slope)) min_slope = curr.s;
    else if (curr.s > min_slope) forever[curr.i] = false;
  }
  min_slope = motos[n - 1].s;
  for (int i = n - 2; i >= 0; i--){
    moto curr = motos[i];
    if (CGAL::abs(curr.s) < CGAL::abs(min_slope) || (CGAL::abs(curr.s) == CGAL::abs(min_slope) && curr.s > min_slope)) min_slope = curr.s;
    else if (curr.s < min_slope) forever[curr.i] = false;
  }
  for (int i = 0; i < n; i++) if (forever[i]) std::cout << i << ' ';
  std::cout << std::endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) solve();
}