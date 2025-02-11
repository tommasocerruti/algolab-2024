#include <bits/stdc++.h>

struct city_t{long fix, save, ignore;};

city_t cost(int curr, std::vector<std::vector<int>>& graph, std::vector<int>& costs){
  if (graph[curr].size() == 0) return {costs[curr], costs[curr], 0};
  long savec = 0, ignorec = 0, mindiff = INT_MAX;
  for (int neigh : graph[curr]){
    auto city = cost(neigh, graph, costs);
    savec += city.save;
    ignorec += city.ignore;
    mindiff = std::min(mindiff, city.fix - city.save);
  }
  long fixr = costs[curr] + ignorec;
  long saver = std::min(savec + mindiff, fixr);
  long ignorer = std::min(fixr, savec);
  return {fixr, saver, ignorer};
}

void solve(){
  int n; std::cin >> n;
  std::vector<std::vector<int>> graph(n);
  std::vector<int> costs(n);
  for (int i = 0; i < n - 1; i++){
    int u, v; std::cin >> u >> v;
    graph[u].push_back(v);
  }
  for (int i = 0; i < n; i++) std::cin >> costs[i];
  std::cout << cost(0, graph, costs).save << '\n';
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) solve();
}