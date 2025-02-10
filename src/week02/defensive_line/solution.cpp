#include <bits/stdc++.h>

void solve(){
  int n, m, k; std::cin >> n >> m >> k;
  std::vector<int> def(n);
  for (int i = 0; i < n; i++) std::cin >> def[i];
  std::vector<int> lens(n + 1, -1);
  int left = 0;
  int sum = 0;
  for (int right = 0; right < n; right++){
    sum += def[right];
    while (sum > k) sum -= def[left++];
    if (sum == k) lens[right + 1] = right - left + 1;
  }
  std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
  for (int i = 1; i <= m; i++) dp[i][0] = -1;
  for (int i = 1; i <= m; i++){
    for (int j = 1; j <= n; j++){
      dp[i][j] = dp[i][j - 1];
      int len = lens[j];
      if (len > 0 && dp[i - 1][j - len] != -1)
        dp[i][j] = std::max(dp[i][j], dp[i - 1][j - len] + len); 
    }
  }
  int sol = dp[m][n];
  if (sol == -1) std::cout << "fail\n";
  else std::cout << sol << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) solve();
}