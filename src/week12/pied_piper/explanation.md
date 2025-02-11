#### Topic
Dynamic programming

#### Explanation

Story summarised:
There are n squares with m one directions streets, each street has some rats and we want to find the maximum number of rats that a valid path can achieve. 
A valid path is a path that:
- starts from square 0, goes to square n-1, and returns back to square 0
- does not pass twice through the same square (except for square 0)
- changes direction only one time (after arriving to n-1)

Approach:
- We want to optimise the number of rats captured with a valid path, that is having a monotonically increasing path from 0 towards n-1 and one monotonically decreasing back to 0 passing through distinct squares.
- We store the moves as an adjacency list graph, and we store two of them, to facilitate the return:
     - graph, where graph[u] = {{v, f}, ...} that is going from u to v collecting f rats
     - graph_inv, where graph_inv[v] = {{u, f}, ...} that is going to v from u collecting f rats
- The correct state is dp[i][j] = maximum rats going from 0 to i and back from j to 0 (all initialised to 0, where 0 indicates the invalidity of a path)
     - note: first attempt is to have dp_f[j] = maximum rats going from 0 to j (on forward path) and dp_b[j] = maximum rats going from j to 0, however we need to merge them together to avoid redundant square usages.
     - base case: dp[j][0] with all the outgoing paths from 0, and dp[0][j] with all the ingoing paths to 0
     - populate condition: if dp[i][j] != 0 since else it would mean the path to reach there is invalid
     - recurrence: at each step populate the table both in the forward path and backward path, imposing an ordering to avoid to use the same square in both paths (this is the most unnatural step):
	  - when populating the forward path, hence edges from graph[i] check if edge.first > j to use it, since if the forward path goes beyond j we ensure we have not been there.
	  - when populating the backward path, hence edges from graph_inv[j] check if edge.first > i to use, since if the backward path does not go beyond i we ensure we have not been there.
          - or if in both condition edge.first = n-1 it is valid since it's the turn-around point
	  - to check if we should pick the path we should take the maximum of the destination and the current with the path to the destination (ex: std::max(dp[edge.first][j], dp[i][j] + edge.second))
     - solution is stored for the path going from 0 to n-1 and from n-1 back to 0: dp[n-1][n-1], and is achieved iterating for(int i = 0; i < n; i++) for(int j = 0; j < n; j++);.