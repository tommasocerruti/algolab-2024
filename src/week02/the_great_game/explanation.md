#### Explanation
The game is a two-player turn-based game played on a directed graph, since the board allows only for moves going forward (there can be multiple paths forward from the same position), which makes the board as directed acyclic graph (DAG). 

The dp procedure to solve this is therefore:
1. Storing the moves in an adjacency list graph (consider that they are 1-index based)
2. Initialising the dp states:
	- mini(n + 1, MAX_N), where mini[i] = min #moves to finish the game after mini plays at position i. We set the values to MAX_N so to pick the first neighbour instead (lower than than that).
	- maxi(n + 1, -1); where maxi[i] = max #moves to finish the game after maxi plays at position i. We set the values to -1 so to pick the first neighbour instead (higher than that).
3. Base case: mini[n] = maxi[n] = 0, since the game finishes when you arrive at the last position (n)
4. Recurrence case: iterating right to left, for every neighbour of such position:
	- mini[i] = std::min(mini[i], maxi[v] + 1), because we want to select the minimum number of moves starting from the future node given that in the next turn the other player will choose the worst.
	- maxi[i] = std::max(maxi[i], mini[v] + 1), because we want to select the maximum number of moves starting from the future node given that in the next turn the other player will choose the best.
5. The solution is a comparison between the min #moves from the starting position of the respective Red and Black marbles.
	- mini[r] < mini[b] --> 0 (S won)
	- mini[r] > mini[b] --> 1 (M won)
	- mini[r] == mini[b] --> (if the total number of moves is odd, it means S plays the last move before M) mini[r] % 2 == 1 --> 0, else 1