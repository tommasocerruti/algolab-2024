#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

void solve(){
  int n, tat; std::cin >> n >> tat;
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  edge_desc e;
  std::vector<std::vector<int>> costs(n, std::vector<int>(n, 0));
  for (int i = 0; i < n - 1; i++){
    for (int j = i + 1; j < n; j++){
      int d; std::cin >> d;
      e = boost::add_edge(i, j, G).first;
      weights[e] = d;
      costs[i][j] = d;
      costs[j][i] = d;
    }
  }
  std::vector<edge_desc> mst_edges;
  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst_edges));
  std::vector<std::vector<bool>> edge_in_mst(n, std::vector<bool>(n, false));
  std::vector<std::vector<int>> mst(n);
  int mst_cost = 0;
  for (auto edge : mst_edges){
    int u = boost::source(edge, G), v = boost::target(edge, G), d = weights[edge];
    edge_in_mst[u][v] = edge_in_mst[v][u] = true;
    mst[u].push_back(v);
    mst[v].push_back(u);
    mst_cost += d;
  }
  std::vector<std::vector<int>> most_expensive(n, std::vector<int>(n, 0));
  for (int u = 0; u < n; u++){
    std::stack<int> stk;
    std::vector<bool> visited(n, false);
    stk.push(u);
    while (!stk.empty()){
      int v = stk.top();
      stk.pop();
      visited[v] = true;
      for (int k : mst[v]){
        if (visited[k]) continue;
        stk.push(k);
        most_expensive[u][k] = std::max(most_expensive[u][v], costs[v][k]);
      }
    }
  }
  int best_add = INT_MAX;
  for (int i = 0; i < n - 1; i++){
    for (int j = i + 1; j < n; j++){
      if (edge_in_mst[i][j]) continue;
      best_add = std::min(best_add, costs[i][j] - most_expensive[i][j]);
    }
  }
  std::cout << mst_cost + best_add << std::endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) solve();
}