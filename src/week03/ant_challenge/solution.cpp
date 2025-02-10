#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

void solve(){
  int n, m, s, a, b;
  std::cin >> n >> m >> s >> a >> b;
  std::vector<weighted_graph> graphs(s + 1, weighted_graph(n));
  std::vector<weight_map> weights(s + 1);
  for (int i = 0; i <= s; i++) weights[i] = boost::get(boost::edge_weight, graphs[i]);
  edge_desc e;
  for (int i = 0; i < m; i++){
    int from, to; std::cin >> from >> to;
    for (int j = 0; j < s; j++){
      int weight; std::cin >> weight;
      e = boost::add_edge(from, to, graphs[j]).first; 
      weights[j][e] = weight;
    }
  }

  int trash;
  std::vector<std::vector<edge_desc>> mst(s);
  for (int i = 0; i < s; i++){
    std::cin >> trash;
    boost::kruskal_minimum_spanning_tree(graphs[i], std::back_inserter(mst[i]));
    for (auto edge : mst[i]){
      e = boost::add_edge(boost::source(edge, graphs[i]), boost::target(edge, graphs[i]), graphs[s]).first; 
      weights[s][e] = weights[i][edge];
    }
  }
  std::vector<int> dist_map(n);
  boost::dijkstra_shortest_paths(graphs[s], a,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, graphs[s]))));
  std::cout << dist_map[b] << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) solve();
}