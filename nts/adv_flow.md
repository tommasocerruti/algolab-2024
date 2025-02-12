## Advanced Flow algorithms

a. Bipartite Matchings (Problem 1)
Some introductory concepts:
- Maximum matching MM (already seen): largest set of disjoint edges.
- Bipartite graphs BP (already seen): a graph so that its vertices can be split in two disjoint sets of vertices U and V such that edges connect vertices only from U to V.
- Maximum independent set MaxIS: largest set of vertices so that no two vertices are adjacent to each other.
- Minimum vector cover MinVC: minimum set of vertices so that every edge in the graph is incident to at least one vertex.
It can be proven that MaxIS and MinVC are complementary! (V / MaxIS = MinVC).
Unfortunately the problem is NP-complete for general graphs :( Buuut it is much simpler on bipartite graphs! :)
There is a theorem that proves that for a bipartite graph, the number of edges in a maximum matching equals to the number of vertices in a MinVC.
From this we can also calculate the MaxIS by taking the difference between the number of vertices and the matching size (since equal to MinVC).
Note: we can solve this even with flows, since it will be equal to the maximum matching.

b. Flows with Costs - MinCostMaxFlow (Problem 2 & Problem 3)
Now other than the capacities, we also have edge costs that, opposite from the flow, we want to minimise.
But we want to minimise it after we maximise the flow, so among all maximum flows, we want to find the flow that also minimises the cost.
There are two algorithms available in BGL:
1. cycle_cancelling(), that is slower but handles negative costs O(C*(nm)), good for m, n <= 600
2. successive_shortest_path_nonnegative_weights(), faster but works for non-negative O(f*(m + nlogn), good for m, n <= 1000
Note: the complexity is critical, really critical. Sometimes you might need to restructure the graph more efficiently to avoid TLE!
For this we have a code snippet that can easily help to implement it.
Sometimes we need to find the MaxCost, and for this we can either
- negate the costs so that the maximum becomes the minimum, and use the slower algorithm (slower but easier to implement).
- if given the maximum cost, take the difference between that and the actual cost, use the faster algorithm and then consider this offset for the return value (faster but harder to implement).

c. Minimum Cuts (Problem 4)
- The minimum cut consists in finding a set of edges whose sum of capacities is minimal so that one vertex can be disconnected from the graph.
- It is proven that the maximum flow between two vertices equals the minimum cut between them!
- This turns out to be very useful because we can calculate:
    * the minimum cut between the source and the target by computing the max flow between them.
    * the minimum cut to disconnect one vertex from the others, that corresponds to the minimum max flow between node 0 and all the other nodes.
    * this does not exactly mean disconnect one vertex from the graph, but rather finding the cheapest cut to separate the graph in two so that the two vertices belong to distinct graphs.
    * to find the cheapest node to remove would mean just to find the node that has the cheapest sum of incoming and outgoing flow.
Note: for both BM and MC, we can then find what is the matching and what is the cut by going through the residual graph. However, it is not required (very likely)...
