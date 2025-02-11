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

void solve() {
  int n; std::cin >> n;
  auto is_white = [](int i, int j){return (i + j) % 2 == 0;};
  auto ind = [&](int i, int j){return i*n + j;};
  graph G(n*n);
  edge_adder adder(G);
  const vertex_desc src = boost::add_vertex(G);
  const vertex_desc tgt = boost::add_vertex(G);
  std::vector<std::pair<int, int>> dirs = {{1, 2}, {-1, 2}, {1, -2}, {-1, -2}, {2, 1}, {-2, 1}, {2, -1}, {-2, -1}};
  int pres, tot = 0;
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      std::cin >> pres;
      if (pres == 0) continue;
      tot++;
      if (!is_white(i, j)){
        adder.add_edge(ind(i, j), tgt, 1);
        continue;
      }
      adder.add_edge(src, ind(i, j), 1);
      for (auto &dir : dirs){
        int i_new = i + dir.first;
        int j_new = j + dir.second;
        if (i_new >= 0 && i_new < n && j_new >= 0 && j_new < n) adder.add_edge(ind(i, j), ind(i_new, j_new), 1);
      }
    }
  }
  int flow = boost::push_relabel_max_flow(G, src, tgt);
  std::cout << tot - flow << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) solve();
}