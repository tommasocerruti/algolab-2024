#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;

void solve(){
  int n, m;
  std::cin >> n >> m;
  graph G(n);
  for (int i = 0; i < m; i++){
    int src, tgt;
    std::cin >> src >> tgt;
    boost::add_edge(src, tgt, G);
  }
  std::map<edge_desc, int> edm; 
  int bc = boost::biconnected_components(G, boost::make_assoc_property_map(edm));

  std::vector<int> counts(bc, 0);
  for (const auto& pair : edm) counts[pair.second]++;
    
  int k = 0;
  std::set<std::pair<int, int>> bridges;
  for (const auto& pair : edm){
    if (counts[pair.second] == 1){
      k++;
      int src = boost::source(pair.first, G);
      int tgt = boost::target(pair.first, G);
      bridges.insert(std::make_pair(std::min(src, tgt), std::max(src, tgt)));
    }
  }
  
  std::cout << k << std::endl;
  for (const auto& bridge : bridges)
    std::cout << bridge.first << " " << bridge.second << std::endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) solve();
}