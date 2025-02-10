#### Explanation
The solution is very similar to burning coins, the only thing differing is that multiple players are involved and we care just about the kth player.

Our dp approach is the following:
- State: dp[i][j] = "maximum earning value when coins from i to j are left".
- Initialisation: all 0, since there are some impossible positions where the earnings must be zero.
- Base case: dp[i][i] = coin[i] if it's player's k turn, 0 else (since the other players are picking the coin).
- Solution: dp[0][n - 1] = "maximum earning value when coins from 0 to n-1 are left" = "maximum earning value when all coins are left" = "maximum earning".
- Recurrence direction: from top to bottom, from left to right (so to to match with the last value being our solution).
- Recurrence equation: 
	* dp[i][j] = std::max(coins[i] + dp[i + 1][j], coins[j] + dp[i][j - 1]) when it's kth player turn (we pick the coin that leads to the maximum, and consider the coin)
	* dp[i][j] = std::min(dp[i + 1][j], dp[i][j - 1]) when it's someone else turn (we pick the coin that leads to the minimum, without considering it)
Note: to find whose turn is it we need to
- Find how many coins were picked up to the current move: p = #picked = #total - #left = n - (j - i + 1)
- Find who is currently picking it: turn = p % m. If turn = k, it's kth player turn.
