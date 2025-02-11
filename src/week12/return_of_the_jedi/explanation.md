#### Topic
Second best MST

#### Explanation

Story summarised:
- The Rebels need a robust warp network to ensure secure communication between all planets. Each planet is assigned a unique number based on its importance. The network needs to satisfy two conditions:
   - All planets must be connected either directly or indirectly.
   - The total cost of constructing the warp network must be minimized.
- Princess Leia uses Kruskal’s algorithm to find the cheapest warp network, which forms a Minimum Spanning Tree (MST). 
- However, R2-D2 suspects that Emperor Palpatine might exploit this predictable network, and proposes to calculate the cost of the second best MST, which is slightly different from Leia's MST and still connects all planets.
- The second best MST is defined as the cheapest MST that differs from the original MST by at least one edge.

Approach: 
- Read the graph (both using BGL and using a separate costs matrix)
- Construct the MST (both using BGL and using a ajdacency list, an edge presence matrix, and the total mst cost)
- For every pair of nodes u, v find the most expensive edge on the unique path between them in the MST:
   - For each node u perform dfs
   - For each node v in the stack, iterate through the neighbours k and if not seen find most_expensive[u][k] which is either the new edge (costs[v][k]) or the most expensive between u v (most_expensive[u][v])
- Iterate through all the edges (like when reading) and look for the best edge to add:
   - The edge u to v that is not in the mst and that minimises cost[u][v] - most_expensive[u][v] (since to remove the loop between u and v we will remove the most expensive edge)
- The second best MST has a cost of the mst plus the smallest cost increased

