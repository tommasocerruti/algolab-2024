
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
  int e,w,m,d,p,l; std::cin>>e>>w>>m>>d>>p>>l;
  graph G(2*(e + w));
  edge_adder adder(G);
  int src = boost::add_vertex(G), srcl = boost::add_vertex(G), srcr = boost::add_vertex(G);
  int tgt = boost::add_vertex(G), tgtl = boost::add_vertex(G), tgtr = boost::add_vertex(G);
  for (int i = 0; i < e; i++){ 
    adder.add_edge(srcl, i, l, 0);
    adder.add_edge(srcr, i, INT_MAX, 0);
    adder.add_edge(srcr, i + e + w, INT_MAX, 0);
  }
  for (int i = 0; i < w; i++){
    adder.add_edge(i + e, tgtl, l, 0);
    adder.add_edge(i + e, tgtr, INT_MAX, 0);
    adder.add_edge(i + 2*e + w, tgtr, INT_MAX, 0);
  }
  for (int i = 0; i < m; i++){
    int u, v, r; std::cin>>u>>v>>r;
    adder.add_edge(u, e + v, 1, r);
  }
  for (int i = 0; i < d; i++){
    int u, v, r; std::cin>>u>>v>>r;
    adder.add_edge(u + e + w, 2*e + w + v, 1, r);
  }
  if (std::max(e, w)*l > p){
    std::cout << "No schedule!\n";
    return;    
  }
  adder.add_edge(src, srcl, l*e, 0); adder.add_edge(src, srcr, p - l*e, 0);
  adder.add_edge(tgtl, tgt, l*w, 0); adder.add_edge(tgtr, tgt, p - l*w, 0);
  int flow = boost::push_relabel_max_flow(G, src, tgt);
  if (flow != p){ 
    std::cout << "No schedule!\n";
    return;
  }
  boost::successive_shortest_path_nonnegative_weights(G, src, tgt);
  int risk = boost::find_flow_cost(G);
  std::cout << risk << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t; std::cin >> t;
  while(t--) solve();
}