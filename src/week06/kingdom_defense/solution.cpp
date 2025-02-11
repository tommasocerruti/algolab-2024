#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <iostream>

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
  int L, P;
  std::cin >> L >> P;
  graph G(L + 2);
  edge_adder adder(G);
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  long flow_needed = 0;
  for (int i = 0; i < L; i++){
    long g, d;
    std::cin >> g >> d;
    adder.add_edge(v_source, i + 2, g);
    adder.add_edge(i + 2, v_sink, d);
    flow_needed += d;
  }
  for (int j = 0; j < P; j++){
    int f, t;
    long c, C;
    std::cin >> f >> t >> c >> C;
    long diff = C - c;
    adder.add_edge(f + 2, t + 2, diff);
    adder.add_edge(v_source, t + 2, c);
    adder.add_edge(f + 2, v_sink, c);
    flow_needed += c;
  }
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  if (flow == flow_needed) std::cout << "yes\n";
  else std::cout << "no\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t; std::cin >> t;
  while(t--) solve();
}