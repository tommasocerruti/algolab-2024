#### Explanation
There are n intersections (nodes), m roads (edges), b barracks (intersections from which infinite troops can leave), p plazas (special kind of intersection), and d distance (maximum that can be travelled by troops).
We want to build as many safe roads as possible, where a safe road is a road where the two respective intersections joined have build on such road a barricade.
Typically regular intersections allow at most one road to construct the barricade, but for a plaza is at most two.
Hence we can solve this problem using dijkstra + edmonds:
- Read the graph (weighted and undirected, so to be changed the definition) and store the edges separately as well in a vector of pairs
- Store which are barracks and plazas
- Use dijkstra from each barrack and track down all the nodes that are reachable (i.e. dist_map[i] <= d)
- Use the reachable array and the roads to instantiate another graph (unweighted and undirected), adding one node more for the plazas (since they allow one more barricade)
- The size of the maximum matching corresponds to the maximum number of barricades to be built