#### Explanation
You and a friend alternately pick coins from the ends of a line (you starting). 
The goal is to calculate the maximum guaranteed win, assuming both play optimally, which means assuming both you and your friend play optimally (you try to maximize you and he tries to minimize yours).  
Looking for the local optimal solution doesn't work because choosing the current best coin doesn't guarantee choosing the best in the next turn.  

We define the DP state as DP[i][j], representing the maximum value achievable when coins from i to j are left.  
Base case: When only one coin is left, if the total number of coins is even, DP[i][i] = 0 (since your friend picks it). Otherwise, DP[i][i] = coin[i].  
Recurrence:
- Their turn: DP[i][j] = min(DP[i+1][j], DP[i][j-1])
- Your turn: DP[i][j] = max(DP[i+1][j] + coins[i], DP[i][j-1] + coins[j])
