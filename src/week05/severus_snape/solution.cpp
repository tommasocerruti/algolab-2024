#include <bits/stdc++.h>

struct A {long p, h;};
struct B {long w;};

typedef std::vector<long> VL;
typedef std::vector<VL> VVL;
typedef std::vector<VVL> VVVL;

void solve(){
  int n, m; long a, b, P, H, W;
  std::cin >> n >> m >> a >> b >> P >> H >> W;
  std::vector<A> potsA(n);
  std::vector<B> potsB(m);
  for (int i = 0; i < n; i++){
    long p, h; std::cin >> p >> h;
    potsA[i] = {p, h};
  }
  for (int i = 0; i < m; i++){
    long w; std::cin >> w;
    potsB[i] = {w};
  }
  auto sortb = [](B b1, B b2){return b1.w > b2.w;};
  std::sort(potsB.begin(), potsB.end(), sortb);
  VVVL dp(n + 1, VVL(n + 1, VL(H + 1, LONG_MIN)));
  for (int h = 0; h <= H; h++){
    for (int i = 1; i <= n; i++){
      dp[i][1][h] = dp[i - 1][1][h];
      if (potsA[i - 1].h >= h){
        dp[i][1][h] = std::max(dp[i][1][h], potsA[i - 1].p);
      }
    }
  }
  for (int j = 2; j <= n; j++){
    for (int h = 0; h <= H; h++){
      for (int i = j; i <= n; i++){
        long prev_h = std::max(h - potsA[i - 1].h, 0L);
        dp[i][j][h] = std::max(dp[i - 1][j][h], potsA[i - 1].p + dp[i - 1][j - 1][prev_h]);
      }
    }
  }
  
  int num_pots_a = -1;
  int num_pots_b = 0;
  for (long curr_w = 0; num_pots_b < m; num_pots_b++){
    curr_w += potsB[num_pots_b].w;
    if (curr_w >= W){
      long neg_p = (num_pots_b + 1) * b;
      for (int j = 1; j <= n; j++){
        if (curr_w - j * a < W)
          break;
        if (dp[n][j][H] >= P + neg_p){
          num_pots_a = j;
          std::cout << num_pots_a + num_pots_b + 1<< std::endl;
          return;
        }
      }
    }
  }
  
  if (num_pots_a == -1) std::cout << -1 << std::endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t; std::cin >> t;
  while(t--) solve();
}