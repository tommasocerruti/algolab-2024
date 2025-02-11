#include <bits/stdc++.h>

void solve(){
  int n; std::cin >> n;
  std::vector<int> bombs(n);
  for (int i = 0; i < n; i++) std::cin >> bombs[i];
  for (int j = 0; j <= (n - 3)/2; j++){
    bombs[2*j + 1] = std::min(bombs[2*j + 1], bombs[j] - 1);
    bombs[2*j + 2] = std::min(bombs[2*j + 2], bombs[j] - 1);
  }
  std::sort(bombs.begin(), bombs.end());
  for (int i = 1; i <= n; i++){
    if (bombs[i - 1] < i){
      std::cout << "no\n";
      return;
    }
  }
  std::cout << "yes\n";
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) solve();
}