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
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};

struct booking{int s, t, d, a, p;};

void solve(){
  int N, S; std::cin >> N >> S;
  std::vector<int> initial(S);
  int maxf = 0;
  for (int i = 0; i < S; i++){ 
    int l; std::cin >> l;
    initial[i] = l;
    maxf += l;
  }
  std::vector<booking> bookings(N);
  for (int i = 0; i < N; i++){
    int s, t, d, a, p; std::cin >> s >> t >> d >> a >> p;
    bookings[i] = {s - 1, t - 1, d, a, p};
  }
  const int start = 0, end = 100000;
  const int maxp = 100;
  std::vector<std::set<int>> times(S);
  std::vector<std::unordered_map<int, int>> indices(S);
  int index = 0;
  for (int i = 0; i < S; i++){
    times[i].insert(start);
    indices[i][start] = index++;
    times[i].insert(end);
    indices[i][end] = index++;
  }
  for (int i = 0; i < N; i++){
    booking B = bookings[i];
    if (B.d != start){ 
      times[B.s].insert(B.d);
      indices[B.s][B.d] = index++;
    }
    if (B.a != end){ 
      times[B.t].insert(B.a);
      indices[B.t][B.a] = index++;
    }
  }
  
  graph G(index);
  edge_adder adder(G);
  auto src = boost::add_vertex(G);
  auto tgt = boost::add_vertex(G);
  
  for (int i = 0; i < S; i++){
    adder.add_edge(src, indices[i][start], initial[i], 0);
    auto t1 = times[i].begin(), t2 = times[i].begin();
    t2++;
    while (t2 != times[i].end()){
      adder.add_edge(indices[i][*t1], indices[i][*t2], maxf, maxp*(*t2 - *t1));
      t1++; t2++;
    }
    adder.add_edge(indices[i][end], tgt, maxf, 0);
  }
  for (int i = 0; i < N; i++){
    booking B = bookings[i];
    int si = indices[B.s][B.d];
    int ti = indices[B.t][B.a];
    adder.add_edge(si, ti, 1, maxp*(B.a - B.d) - B.p);
  }
  boost::successive_shortest_path_nonnegative_weights(G, src, tgt);
  int profit = maxp*maxf*end - boost::find_flow_cost(G);
  std::cout << profit << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t; std::cin >> t;
  while(t--) solve();
}