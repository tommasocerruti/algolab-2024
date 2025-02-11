#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0;
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

void solve(){
  int n, m, s, p; std::cin >> n >> m >> s >> p;
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  std::map<edge_desc, int> caps;
  std::vector<edge_desc> edges;
  edge_desc e;
  for (int i = 0; i < m; i++){
    int u, v, c, d; std::cin >> u >> v >> c >> d;
    e = boost::add_edge(u, v, G).first; 
    weights[e] = d;
    caps[e] = c;
    edges.push_back(e);
  }
  std::vector<int> dist_map(n);
  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));
  
  graph GS(n);
  edge_adder adder(GS);
  for (auto edge : edges){
    int u = boost::source(edge, G), v = boost::target(edge, G);
    if (dist_map[u] + weights[edge] == dist_map[v]) adder.add_edge(u, v, caps[edge]);
    if (dist_map[v] + weights[edge] == dist_map[u]) adder.add_edge(v, u, caps[edge]);
  }
  
  long flow = boost::push_relabel_max_flow(GS, s, p);
  
  std::cout << flow << '\n';
}

int main(){
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int t; std::cin >> t;
  while(t--) solve();
}