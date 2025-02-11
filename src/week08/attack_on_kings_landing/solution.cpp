#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor                       vertex;

void solve(){
  int n, m, b, p, d; std::cin >> n >> m >> b >> p >> d;
  std::vector<int> barracks(b);
  for (int i = 0; i < b; i++) std::cin >> barracks[i];
  std::unordered_map<int, int> plazas;
  for (int i = 0; i < p; i++){ 
    int ind; std::cin >> ind;
    plazas[ind] = n + i;
  }
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  edge_desc e;
  std::vector<edge_desc> edges;
  for (int i = 0; i < m; i++){
    int x, y, l; std::cin >> x >> y >> l;
    e = boost::add_edge(x, y, G).first; 
    weights[e] = l;
    edges.push_back(e);
  }
  std::vector<bool> reachable(n, false);
  for (int i = 0; i < b; i++){
    std::vector<long> dist_map(n);
    boost::dijkstra_shortest_paths(G, barracks[i],
     boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));
    for (int i = 0; i < n; i++) if (dist_map[i] <= d) reachable[i] = true;
  }
  
  graph Gr(n + p);
  std::vector<vertex> mate_map(n + p);
  for (auto edge : edges){
    int u = boost::source(edge, G);
    int v = boost::target(edge, G);
    if (!reachable[u] || !reachable[v]) continue;
    add_edge(u, v, Gr);
    if (plazas.find(u) != plazas.end()) add_edge(plazas[u], v, Gr);
    if (plazas.find(v) != plazas.end()) add_edge(plazas[v], u, Gr);
  }
  boost::edmonds_maximum_cardinality_matching(Gr, boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, Gr)));
  int ms = boost::matching_size(Gr, boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, Gr)));
  std::cout << ms << std::endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) solve();
}