#include <iostream>
#include <vector>
#include <unordered_set>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor                       vertex_desc;

void solve(){
  int n, c, f; std::cin >> n >> c >> f;
  std::vector<std::unordered_set<std::string>> hobbies(n, std::unordered_set<std::string>(c));
  for (int i = 0; i < n; i++){
    for (int j = 0; j < c; j++){
      std::string hobby;
      std::cin >> hobby;
      hobbies[i].insert(hobby);
    }
  }
  graph G(n);
  for (int i = 0; i < n; i++){
    for (int j = i + 1; j < n; j++){
      int count = 0;
      for (auto &hobby : hobbies[j]){
        if (hobbies[i].count(hobby) > 0)
          count++;
      }
      if (count > f) boost::add_edge(i, j, G);
    }
  }
  std::vector<vertex_desc> mate_map(n);
  boost::edmonds_maximum_cardinality_matching(G,boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  int matching_size = boost::matching_size(G, boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  if (matching_size == (n/2)) std::cout << "not optimal\n";
  else std::cout << "optimal\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t; std::cin >> t;
  while (t--) solve();
}