#include <bits/stdc++.h>
typedef std::vector<int> VI;
typedef std::vector<VI> VVI;
typedef std::vector<VVI> VVVI;
typedef std::vector<VVVI> VVVVI;

struct fq{int f1, f2, f3;};
int n, k, m; 

int distinct(fq f, int m){
  if (m == 2) return std::unordered_set<int>({0, f.f1, f.f2}).size() - 1;
  else return std::unordered_set<int>({0, f.f1, f.f2, f.f3}).size() - 1;
}

int solve(int curr, VVVVI& dp, VI& fighters, fq& north, fq& south, int diff){
  if (curr == -1) return 0;
  if (diff > 12) return INT_MIN;
  int encn = north.f1*5 + north.f2;
  int encs = south.f1*5 + south.f2;
  int diffp = diff + 12;
  int value = dp[curr][encn][encs][diffp];
  if (value != -1) return value;
  int nextf = fighters[curr];
  fq nnorth = {nextf, north.f1, north.f2};
  fq ssouth = {nextf, south.f1, south.f2};
  int best = 0;
  int north_exc = 1000*distinct(nnorth, m) - pow(2, std::abs(diff + 1));
  int south_exc = 1000*distinct(ssouth, m) - pow(2, std::abs(diff - 1));
  if (north_exc > 0) best = north_exc + solve(curr - 1, dp, fighters, nnorth, south, diff + 1);
  if (south_exc > 0) best = std::max(best, south_exc + solve(curr - 1, dp, fighters, north, ssouth, diff - 1));
  dp[curr][encn][encs][diffp] = best;
  return best;
}

void solve(){
  std::cin >> n >> k >> m;
  VI fighters(n);
  for (int i = n - 1; i >= 0; i--){
    int x; std::cin >> x;
    fighters[i] = x + 1;
  }
  fq north = {0, 0, 0};
  fq south = {0, 0, 0};
  VVVVI dp(n, VVVI(25, VVI(25, VI(25, -1))));
  std::cout << solve(n - 1, dp, fighters, north, south, 0) << '\n';
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin>>t;
  while(t--) solve();
}