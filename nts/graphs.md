## Introduction to Graph Algorithms

### Main Points
The Boost Graph Library (BGL) provides efficient implementations of common graph algorithms.  
We will make the complexity analysis considering n as the number of vertices and m as the number of edges.

-> Shortest path:
 - Using Dijkstra's algorithm we can compute the shortest paths between all the nodes in a graph.
 - We are given a template containing the following functions:
   int dijkstra_dist(const weighted_graph &G, int s, int t); Which returns the minimum distance between s and t (by returning index t of the distance map of s).
   int dijkstra_path(const weighted_graph &G, int s, int t, std::vector<vertex_desc> &path); Which does the same but also stores within path all the shortest paths to all the vertices.
 - They both use boost:dijkstra_shortest_paths that runs in O(m + nlogn).

-> Minimum spanning tree:
 - Using Kruskal's algorithm we can compute the MST of a graph (even with negative edges), i.e. a subset of its edges that connects all vertices with the minimum total edge weight, without forming any cycle.
 - We are given a template that computes the mst and stores the weight of the edges in a vector.
 - It uses boost::kruskal_minimum_spanning_tree that runs in O(mlogm)

-> Maximum cardinality matching:
 - Using Edmond's algorithm we can compute the maximum matching of a graph, i.e. the set of edges so that no vertex is covered by more than one edge.
 - The matching is not always perfect, it is when the matching size == n/2, else some vertices are not covered.
 - We are given a template containing int maximum_matching(const graph &G) that given a graph, computes the maximum matching and returns the matching size.
 - It uses boost::edmonds_maximum_cardinality_matching that runs in O(4mn).

-> Strongly connected components:
 - Using Tarjan's algorithm we can compute the SCC of a directed graph, i.e. the maximal subset of vertices such that all the vertices in the component are pairwise reachable.
 - We are given a template that calculates the SCC and determines whether there is a universal vertex, i.e. only one SCC.
 - It uses boost::strong_components that runs in O(m + n).

-> Connected components:
 - Basically the same as SCC but for undirected graphs.
 - We are given a template containing that finds all the connected components of a graph.
 - It uses boost::connected_components that runs in O(m + n).

-> Biconnected components:
 - A biconnected graph is an undirected graph that is connected and remains connected even if a vertex is removed. A biconnected component is any maximal subgraph of G that is biconnected.
 - We are not given a template, but this is a template to calculate it:
    std::vector<int> component_map(boost::num_edges(G)); // Component IDs for each edge
    std::map<edge_desc, int> edge_to_component;          // Mapping of edges to components
    int num_components = boost::biconnected_components(G, boost::make_iterator_property_map(component_map.begin(), boost::get(boost::edge_index, G)));
 - We can find the bridges of the graph by a simple edge iteration and check if a biconnected component has only one edge, in such a case that edge is a bridge.
    std::vector<int> edge_count(num_components, 0);
    for (int comp : component_map) edge_count[comp]++;
    for (auto e : boost::make_iterator_range(edges(G))) {
    int comp_id = component_map[boost::get(boost::edge_index, G, e)];
    if (edge_count[comp_id] == 1) std::cout << "Edge (" << boost::source(e, G) << ", " << boost::target(e, G) << ") is a bridge.\n";
 - It uses boost::biconnected_components that runs in O(m + n)

-> Articulation points:
 - Any vertex part of two or more biconnected components, that therefore when removed, leads to a disconnected graph.
 - We are not given a template, but this is a template to calculate it (easy to find in the documentation):
    std::vector<int> articulation_points;
    boost::articulation_points(G, std::back_inserter(articulation_points));
 - It uses boost::articulation_points that runs in O(m + n)

-> Bipartite graph:
 - A graph is bipartite if the vertices can be split in two subsets such that all edges have an extremity in each.
 - We are not given a template. The function is boost::is_bipartite that runs in O(m + n).