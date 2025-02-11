#### Topic
Dynamic programming

#### Explanation

Story summarised:
There are n cities with n-1 roads between them, structured like a tree. To save a city we need to repair either itself or at least one of its neighbours cities. However each city has a different cost, and we want to find the minimum cost to save every city.

Approach: 
Note: multiple approaches are tempting, such as a min vector cover or a min cost max flow, however due to the cost being on the vertices (cities) and being different, we need to go with a DP approach.
- We define a struct city that attributes three states to each node: 
* fix: the minimum cost of repairing such node having the other nodes in the below tree saved.
* save: the minimum cost of covering the node without repairing it, hence having at least of its children repaired.
* ignore: the minimum cost of neither repairing this one or covering one of its children (below they are repaired but the current one no).
- We read the graph and the costs, and perform a dfs on the nodes that returns the city value of the root, where the solution to the problem will be stored in the cost to save it.
- We then calculate the three states for each node. For each neighbour:
   - save_sum increases by the cost of saving it (without necessarily repairing it)
   - ignore_sum increases by the cost of not saving it (neither fixing it or saving it)
   - min_fix_diff storing the overall minimum difference to change one of its children from saved to fixed
- After iterating through its neighbours we can compute the values:
   - fix_cost = costs[node] + ignore_sum; meaning selecting this and so the children could be not saved
   - save_cost = std::min(fix_cost, save_cost + min_selected_diff); meaning if fixing this is cheaper do it, else we can take the cost of saving the children while fixing the least expensive.
   - ignore_cost = std::min(fix_cost, save_sum); meaning if fixing this is cheaper do it, else do not care about covering this node and take the cost of just covering the children (since ignore does not care just about the current, but below they are saved).