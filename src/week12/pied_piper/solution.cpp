#include <bits/stdc++.h>

void solve(){
  long n, m; std::cin >> n >> m;
  std::vector<std::vector<std::pair<long, long>>> G(n);
  std::vector<std::vector<std::pair<long, long>>> G_inv(n);
  for (int i = 0; i < m; i++){
    long u, v, f; std::cin >> u >> v >> f;
    G[u].push_back({v, f});
    G_inv[v].push_back({u, f});
  }
  std::vector<std::vector<long>> dp(n, std::vector<long>(n, -1));
  for (auto next : G[0]) dp[next.first][0] = next.second;
  for (auto next : G_inv[0]) dp[0][next.first] = next.second;
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      if (dp[i][j] == -1) continue;
      for (auto edge : G[i]){
        if (edge.first > j || edge.first == n - 1)
          dp[edge.first][j] = std::max(dp[edge.first][j], dp[i][j] + edge.second);
      }
      for (auto edge : G_inv[j]){
        if (edge.first > i || edge.first == n - 1)
          dp[i][edge.first] = std::max(dp[i][edge.first], dp[i][j] + edge.second);
      }
    }
  }
  std::cout << dp[n - 1][n - 1] << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) solve();
}