#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

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
  int n, m; std::cin >> n >> m;
  graph G(n);
  edge_adder adder(G);
  vertex_desc src = boost::add_vertex(G);
  vertex_desc tgt = boost::add_vertex(G);
  int totp = 0;
  for (int i = 0; i < n; i++){
    int s; std::cin >> s;
    if (s >= 0){
      totp += s;
      adder.add_edge(src, i, s);
    }
    else adder.add_edge(i, tgt, -s);
  }
  for (int i = 0; i < m; i++){
    int u, v; std::cin >> u >> v;
    adder.add_edge(u, v, INT_MAX);
  }
  int score = totp - boost::push_relabel_max_flow(G, src, tgt);
  if (score > 0) std::cout << score << '\n';
  else std::cout << "impossible\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t; std::cin >> t;
  while(t--) solve();
}