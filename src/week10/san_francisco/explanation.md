#### Topic
Dynamic programming

#### Explanation

Story summarised:
- We are playing a single player game where a board with n positions (directed graph with n nodes) has different m tunnels (m paths) each giving some pts. 
- We start from node 0, and there is a node ("end-hole") that has no outgoing edges, and we should make the ball go back to the starting node 0.
- Our goal is to see if we can achieve at least x points by traversing edges up to k, where each edge gives some points p.
- We want to find the minimum number of moves from 0 to k that achieves a score greater or equal than x, or determine it is “Impossible”.

Approach:
- We read the possible moves in an adjacency list graph representation, and we then iterate through it to find the end-hole, and keep record of its index.
- We set up a 2D DP table: dp[i][j] = best score if we start from node i with j moves available. Note: #moves left is better than #moves done! Also we should populate dp[i][j] at the j, i step.
- Base case: at j = 0, no points can be collected (when no moves are left): dp[i][0] = 0 for all i.
- When filling for j > 0, if i is the end hole, dp[i][j] = dp[0][j], otherwise, we look at all edges e and take the best one: dp[i][j] = std::max(dp[i][j], dp[e.to][j-1] + e.p), 
  meaning best points at the destination with one move less remaining plus current, or we already found a better one.
- After filling for all j from 1 to k, we find the smallest j for which dp[0][j] >= x, i.e. the lowest number of moves so that we make (more or) the points needed. If none is found, output “Impossible”.