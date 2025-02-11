#include <iostream>
#include <vector>
#include <map>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor                       vertex_desc;

void solve(){
  int w, h; std::cin >> w >> h;
  int n = 0;
  std::map<std::pair<int, int>, int> nodes;
  for (int i = 0; i < h; i++){
    for (int j = 0; j < w; j++){
      char c; std::cin >> c;
      if (c == '.') nodes[{i, j}] = n++;
    }
  }
  graph G(n);
  for (auto node : nodes){
    std::pair<int, int> pos = node.first;
    int index = node.second;
    int i = pos.first, j = pos.second;
    if (nodes.count({i - 1, j}) > 0) boost::add_edge(index, nodes[{i - 1, j}], G);
    if (nodes.count({i + 1, j}) > 0) boost::add_edge(index, nodes[{i + 1, j}], G);
    if (nodes.count({i, j - 1}) > 0) boost::add_edge(index, nodes[{i, j - 1}], G);
    if (nodes.count({i, j + 1}) > 0) boost::add_edge(index, nodes[{i, j + 1}], G);
  }
  std::vector<vertex_desc> mate_map(n);
  boost::edmonds_maximum_cardinality_matching(G, boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  int matching_size = boost::matching_size(G, boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));

  if (matching_size * 2 == n) std::cout << "yes\n";
  else std::cout << "no\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int n;std::cin >> n;
  while (n--) solve();
}