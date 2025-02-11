#include <iostream>
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
typedef boost::graph_traits<graph>::vertex_descriptor           vertex_desc;
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

void solve() {
  int N, M, S; std::cin >> N >> M >> S;
  graph G(N + M + S);
  edge_adder adder(G);
  const vertex_desc src = boost::add_vertex(G);
  const vertex_desc tgt = boost::add_vertex(G);
  for (int i = 0; i < S; i++){
    int l; std::cin >> l;
    adder.add_edge(M + N + i, tgt, l, 0);
  }
  for (int i = 0; i < M; i++){
    int s; std::cin >> s;
    adder.add_edge(i, M + N + s - 1, 1, 0);
  }
  for (int i = 0; i < N; i++){
    adder.add_edge(src, M + i, 1, 0);
    for (int j = 0; j < M; j++){
      int b; std::cin >> b;
      adder.add_edge(M + i, j, 1, 100-b);
    }
  }
  int sold = boost::push_relabel_max_flow(G, src, tgt);
  boost::successive_shortest_path_nonnegative_weights(G, src, tgt);
  int profit = 100*sold - boost::find_flow_cost(G);
  std::cout << sold << ' ' << profit << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t; std::cin >> t;
  while (t--) solve();
}