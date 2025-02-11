#include <bits/stdc++.h>

void solve(){
  long n, m, x, k; std::cin >> n >> m >> x >> k;
  std::vector<std::vector<std::pair<int, int>>> graph(n);
  for (int i = 0; i < m; i++){
    int u, v, p; std::cin >> u >> v >> p;
    graph[u].push_back({v, p});
  }
  int end_v = -1;
  for (int i = 0; i < n; i++) if (graph[i].size() == 0) end_v = i;
  std::vector<std::vector<long>> dp(n, std::vector<long>(k + 1, -1));
  for (int i = 0; i < n; i++) dp[i][0] = 0;
  for (int j = 1; j <= k; j++){
    for (int i = 0; i < n; i++){
      if (i == end_v) dp[i][j] = dp[0][j];
      for (auto &move : graph[i]) dp[i][j] = std::max(dp[i][j], dp[move.first][j - 1] + move.second);
    }
  }
  for (int s = 0; s <= k; s++){
    if (dp[0][s] >= x) {
      std::cout << s << '\n';
      return;
    }
  }
  std::cout << "Impossible\n";
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) solve();
}