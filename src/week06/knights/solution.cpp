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
  int m, n, k, C;
  std::cin >> m >> n >> k >> C;
  auto ind_in = [&](int i, int j){return i*m + j;};
  auto ind_out = [&](int i, int j){return ind_in(i, j) + m*n;};
  graph G(2*m*n);
  edge_adder adder(G);
  const vertex_desc src = boost::add_vertex(G);
  const vertex_desc tgt = boost::add_vertex(G);
  for (int i = 0; i < n; i++){
    for (int j = 0; j < m; j++){
      adder.add_edge(ind_in(i, j), ind_out(i, j), C);
      int num_exits = 0;
      if (i == 0) num_exits++;
      else adder.add_edge(ind_out(i, j), ind_in(i - 1, j), 1);
      if (i == n - 1) num_exits++;
      else adder.add_edge(ind_out(i, j), ind_in(i + 1, j), 1);
      if (j == 0) num_exits++;
      else adder.add_edge(ind_out(i, j), ind_in(i, j - 1), 1);
      if (j == m - 1) num_exits++;
      else adder.add_edge(ind_out(i, j), ind_in(i, j + 1), 1);
      if (num_exits > 0) adder.add_edge(ind_out(i, j), tgt, num_exits);
    }
  }
  for (int i = 0; i < k; i++){
    int i_n, j_n; std::cin >> j_n >> i_n;
    adder.add_edge(src, ind_in(i_n, j_n), 1);
  }
  int saved = boost::push_relabel_max_flow(G, src, tgt);
  std::cout << saved << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int t; std::cin >> t;
  while(t--) solve();
}