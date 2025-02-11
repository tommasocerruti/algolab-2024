#include <bits/stdc++.h>

void solve(){
  int n, m, k, d;
  std::cin >> n >> m >> k >> d;
  std::vector<std::vector<std::vector<int>>> patts(n);
  for (int i = 0; i < m; i++){
    std::vector<int> patt(k);
    for (int j = 0; j < k; j++) std::cin >> patt[j];
    patts[patt[k - 1]].push_back(patt);
  }
  std::vector<std::vector<int>> dp(n, std::vector<int>(d, INT_MAX));
  for (int j = 0; j < int(patts[0].size()); j++) dp[0][j] = k;
  for (int i = 1; i < n; i++){
    for (int j = 0; j < int(patts[i].size()); j++){
      for (int jp = 0; jp < int(patts[i - 1].size()); jp++){
        if (dp[i - 1][jp] == INT_MAX) continue;
        for (int k1 = 0; k1 <= k; k1++){
          if (std::equal(patts[i][j].begin(), patts[i][j].begin() + k1, patts[i - 1][jp].begin() + k - k1)
            && *std::min_element(patts[i][j].begin() + k1, patts[i][j].end()) >= i){
            dp[i][j] = std::min(dp[i][j], dp[i - 1][jp] + k - k1);
          }
        }
      }
    }
  }
  int best = *std::min_element(dp[n - 1].begin(), dp[n - 1].end());
  if (best == INT_MAX) std::cout << "Impossible!\n";
  else std::cout << best << '\n';
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) solve();
}