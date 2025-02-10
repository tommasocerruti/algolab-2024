#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;

void solve(int n){
  long a, b, c, d;
  std::cin >> a >> b >> c >> d;
  R ray = R(P(a,b), P(c,d));
  bool hits = false;
  while(!hits && n > 0){
    std::cin >> a >> b >> c >> d;
    S seg = S(P(a, b), P(c,d));
    if (CGAL::do_intersect(ray, seg)) hits = true;
    n--;
  }
  while(n > 0){
    std::cin >> a >> b >> c >> d;
    n--;
  }
  std::cout << (hits ? "yes\n":"no\n");
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int n; std::cin >> n;
  while (n != 0){
    solve(n);
    std::cin >> n;
  }
}