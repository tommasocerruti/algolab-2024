#### Explanation
Determine the minimum distance between two nodes a and b while ensuring the path crosses exactly k rivers (special marked edges).  

Approach:
1. Represent the graph, that is weighted and undirected, using an adjacency list and store edges that cross rivers in a separate structure, where rivers[i] = [{j, c1}, {k, c2}], meaning from node i you can cross a river going to node j at the cost c1 and going to node k at cost c2 (or just use a vector of edges).
2. Perform Dijkstra's algorithm from node a to compute distances to all nodes.
3. We create a virtual node for every river we need to cross, that has an edge to all those nodes that are reached traversing a river, with cost equal to traversing that river.
So from virtual node k, dist[j] practically means the distance corresponding to the shortest path from the source node to node j while crossing at least k rivers.
4. After adding k virtual nodes, the distance to the target node corresponds to the distance of the shortest path to the target node starting from the last virtual node so that we traversed k rivers.