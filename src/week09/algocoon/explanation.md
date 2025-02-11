#### Explanation
There are n figures (nodes), and in total these figures have m limbs (edges) that hold the statue together.
We have to split the statue in two with our friend, and we will pay for the limbs that we break of our part, and she will pay for hers.
The objective is to minimise our cost, so what we do is finding the mincut to disconnect the graph.
There is no source or sink, we just want to get the mincut, so we take as reference node 0 and calculate the mincut for every other node, in both directions, and store the cheapest.
Note: 
- We need both directions since calculating the flow from 0 to i gives the cost of separating node 0 and the nodes it can reach from node i and the rest of the graph, while i to 0 the opposite.
- A full O(n^2) comparison (calculating flows between all pairs of nodes) would redundantly evaluate many of the same cuts, as the minimum cut for a subset of the graph depends only on the edges crossing the partition boundary.