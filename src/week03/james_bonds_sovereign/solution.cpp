#include <iostream>
#include <vector>

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

void solve(){
  int n, m, k; std::cin >> n >> m >> k;
  VI coins(n);
  for (int i = 0; i < n; i++) std::cin >> coins[i];
  VVI dp(n, VI(n, 0));
  
  if (n % m == k) for (int i = 0; i < n; i++) dp[i][i] = coins[i];
  for (int i = n - 2; i >= 0; i--){
    for (int j = i; j < n; j++){
      bool your_turn = ((n - j + i - 1) % m == k);
      if (your_turn) dp[i][j] = std::max(dp[i + 1][j] + coins[i], dp[i][j - 1] + coins[j]);
      else dp[i][j] = std::min(dp[i + 1][j], dp[i][j - 1]);
    }
  }
  std::cout << dp[0][n - 1] << '\n';
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) solve();
}