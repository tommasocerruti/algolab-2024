#include <bits/stdc++.h>

struct path_t{long chambs, galls, rettime;};
auto sort_paths = [](path_t& p1, path_t& p2){return p1.chambs*p2.rettime > p2.chambs*p1.rettime;};

path_t dig(int curr, std::vector<int>& galls, std::vector<std::vector<std::pair<int, int>>>& graph){
  if (graph[curr].size() == 0) return {1, galls[curr], 0};
  std::vector<path_t> paths;
  for (std::pair<int, int>& neigh : graph[curr]){
    path_t path = dig(neigh.first, galls, graph);
    paths.push_back({path.chambs, path.galls - path.chambs*neigh.second, path.rettime + 2*neigh.second});
  }
  std::sort(paths.begin(), paths.end(), sort_paths);
  long tot_chambs = 0, tot_galls = 0, tot_rettime = 0;
  for (path_t& path : paths){
    tot_galls += path.galls - path.chambs*tot_rettime;
    tot_rettime += path.rettime;
    tot_chambs += path.chambs;
  }
  return {tot_chambs + 1, tot_galls + galls[curr], tot_rettime};
}

void solve(){
  int n; std::cin >> n;
  std::vector<int> galls(n + 1);
  for (int i = 0; i < n; i++) std::cin >> galls[i];
  std::vector<std::vector<std::pair<int, int>>> graph(n + 1);
  for (int i = 0; i < n; i++){
    int u, v, l; std::cin >> u >> v >> l;
    graph[u].push_back({v, l});
  }
  std::cout << dig(0, galls, graph).galls << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) solve();
}