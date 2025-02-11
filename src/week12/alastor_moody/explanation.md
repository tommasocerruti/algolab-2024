#### Topic
MaxFlow with Dijkstra

#### Explanation

Story summarised:
Given n locations connected with m bidirectional flyways we want to go from location s to location p with as many friends as possible, however we all must take the same amount of time. What is the maximum number of friends to satisfy this condition?
(Each flyways is characterised by the maximum people that can traverse it and the duration it takes).

Approach:
- We can easily view the location as nodes and the flyways as bidirectional edges that we can store also separately in a vector of tuple<int, int, int, int>.
- We construct the first graph where we can use dijkstra algorithm to find the dist_map to each node starting from s, using the distances as weights (considering both directions, also in the next graph).
- We construct the second graph where we add the edges only if they belong to the shortest path, i.e. given an edge u to v with distance d, if dist_map[u] + d == dist_map[v] (if yes add the edge with also the capacity c).
- Run max flow that will give us the result.

Note: there is an alternative approach that uses MinCostMaxFlow, basically pushing one unit to find the minimum cost to arrive to the destination, and using binary search to find the highest value of flow that maintains such a cost. 
However it is x10 slower as we need to reinstantiate every time a new graph in order to adapt the amount of flow from the super source.