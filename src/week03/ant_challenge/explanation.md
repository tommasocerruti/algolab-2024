#### Explanation
In this problem, multiple species of ants contribute to building a network between a source and a target node in a forest. Each species can only use specific paths, forming a unique graph.  
The task is to find the shortest path from the source to the target if all species collaborate.

Approach:
1. Build a graph for each species with their respective paths and weights.
2. Compute the MST (Minimum Spanning Tree) for each species, as ants can only traverse these edges.
3. Merge all MSTs into a combined graph (hence have an array of s + 1 graphs).
4. Use Dijkstra’s algorithm on the combined graph to find the shortest path between the source and target.