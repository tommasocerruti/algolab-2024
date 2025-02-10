#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,boost::no_property, boost::property<boost::edge_weight_t, int> > graph;
typedef boost::property_map<graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor          vertex_desc;

void solve(){
  int n, m, k, x, y;
  std::cin >> n >> m >> k >> x >> y;
  graph G(n + k);
  weight_map weights = boost::get(boost::edge_weight, G);
  std::vector<edge_desc> rivers;
  edge_desc e;
  for (int i = 0; i < m; i++){
    int u, v, w, d;
    std::cin >> u >> v >> w >> d;
    e = boost::add_edge(u, v, G).first; 
    weights[e] = w;
    if (d == 1) rivers.push_back(e);
  }
  std::vector<int> dist_map(n + k, INT_MAX);
  boost::dijkstra_shortest_paths(G, x, boost::distance_map(boost::make_iterator_property_map(dist_map.begin(), boost::get(boost::vertex_index, G))));
  for (int i = 0; i < k; i++){
    int sn = n + i;
    for (auto edge : rivers){
      int u = boost::source(edge, G), v = boost::target(edge, G), c = weights[edge];
      e = boost::add_edge(sn, v, G).first; 
      weights[e] = c + dist_map[u];
      e = boost::add_edge(sn, u, G).first; 
      weights[e] = c + dist_map[v];
    }
    boost::dijkstra_shortest_paths(G, sn, boost::distance_map(boost::make_iterator_property_map(dist_map.begin(), 
      boost::get(boost::vertex_index, G))));
  }
  std::cout << dist_map[y] << std::endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) solve();
}