#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph;

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it;

class edge_adder {
 graph &G;
 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G);
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0;
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;
    w_map[rev_e] = -cost;
  }
};

void solve(){
  int n, m; std::cin >> n >> m;
  std::vector<int> caps(n - 1);
  int posc = 0;
  for (int i = 0; i < n - 1; i++){
    int c; std::cin >> c;
    caps[i] = c;
    posc += c;
  }
  graph G(n*2);
  edge_adder adder(G); 
  int src = boost::add_vertex(G);
  int tgt = boost::add_vertex(G);
  adder.add_edge(src, 0, caps[0], 0);
  adder.add_edge(src, n, 100 - caps[0], 0);
  adder.add_edge(0, 1, caps[0], 128);
  adder.add_edge(n, n + 1, 100 - caps[0], 0);
  for (int i = 1; i < n - 1; i++){
    adder.add_edge(i, i + 1, caps[i], 128);
    adder.add_edge(n + i, n + i + 1, 100 - caps[i], 0);
    if (caps[i - 1] > caps[i]) adder.add_edge(i, n + i, caps[i - 1] - caps[i], 0);
    if (caps[i - 1] < caps[i]) adder.add_edge(n + i, i, caps[i] - caps[i - 1], 0);
  }
  adder.add_edge(n - 1, tgt, caps[n - 2], 0);
  adder.add_edge(2*n - 1, tgt, 100 - caps[n - 2], 0);
  for (int i = 0; i < m; i++){
    int a, b, d; std::cin >> a >> b >> d;
    adder.add_edge(a, b, 1, (b - a)*128 - d);
  }
  boost::successive_shortest_path_nonnegative_weights(G, src, tgt);
  int cost = 128*posc - boost::find_flow_cost(G);
  std::cout << cost << '\n';
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) solve();
}