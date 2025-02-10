#include <bits/stdc++.h>

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

void solve() {
  int n, m, r, b; std::cin >> n >> m >> r >> b;
  VVI t(n);
  for (int i = 0; i < m; i++){
    int u, v; std::cin >> u >> v;
    t[u].push_back(v);
  }
  VI mini(n + 1, INT_MAX);
  VI maxi(n + 1, 0);
  maxi[n] = mini[n] = 0;
  for (int i = n - 1; i >= 0; i--){
    for (int k : t[i]){
      maxi[i] = std::max(maxi[i], mini[k] + 1);
      mini[i] = std::min(mini[i], maxi[k] + 1);
    }
  }
  int sherlock = mini[r];
  int moriarty = mini[b];
  if (sherlock < moriarty) std::cout << "0\n";
  else if (sherlock > moriarty) std::cout << "1\n";
  else std::cout << (sherlock % 2 == 1 ? "0\n":"1\n");
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) solve();
}