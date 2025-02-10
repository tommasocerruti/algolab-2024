#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;

double floor_to_double(const K::FT& x){
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void solve(int n){
  long a, b, c, d;
  std::cin >> a >> b >> c >> d;
  R ray = R(P(a,b), P(c,d));
  S best;
  bool hits = false;
  std::vector<S> segs(n);
  for (int i = 0; i < n; i++){
    std::cin >> a >> b >> c >> d;
    S seg = S(P(a, b), P(c,d)); 
    segs[i] = seg;
  }
  std::random_shuffle(segs.begin(), segs.end());
  for (int i = 0; i < n; i++){
    auto o = hits ? CGAL::intersection(segs[i], best):CGAL::intersection(segs[i], ray);
    if (o){
      hits = true;
      if (const P* op = boost::get<P>(&*o)) best = S(ray.source(), *op);
      else if (const S* os = boost::get<S>(&*o)) best = S(ray.source(), os->source());
    }
  }
  if (!hits) std::cout << "no\n";
  else std::cout << long(floor_to_double(best.end().x())) << ' ' << long(floor_to_double(best.end().y())) << '\n';
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int n; std::cin >> n;
  while (n != 0){
    solve(n);
    std::cin >> n;
  }
}