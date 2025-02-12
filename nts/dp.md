
## Dynamic Programming

### Main Points
Sometimes, to find the optimal solution, we need to try all possible states.  
Computing these states is computationally expensive, so we use dynamic programming (DP) to avoid re-computation of already visited states.
The main idea however should not be to come up directly with the states since they are often very complicated.
We should think of how to solve the problem after splitting it into many subproblems.
We start with one dimension, with the essence of the problem, and gradually increase the dimensions of the solutions in case we cannot solve the problem.

*Few words about how we can end up with the solution of James Bond problem in an easy way:*

We first need to think about how to subdivide the big problem into small subproblems.
In this case, we have to deal with n coins, and an obvious subproblem is to reduce the number of coins taken into consideration.
Hence the first attempted solution is dp(n), where dp[i] = "maximum earning when we are left with the coins from i".
However, we soon realise that there are many different cases where we can be left with coins from i, indicating up to what j coin we are left with.
Hence the second attempted solution is dp(nxn), where dp[i][j] = "maximum earning when we are left with the coins from i to j".
We note that some cases in the states are impossible, in particular when i > j, since we assuming the index of the coin we are starting from is less than the one we are ending with, but we do not care we just leave it 0.
We then want to find the base case to start with, which is the subset of sub-problems that we already know the solution of, which in this case is when i = j, since when there is only on coin left, player k either picks it (if it's his turn) or not.
We then realise that the solution lies in dp[0][n - 1], that is when we consider all the coins. Therefore the order of population should be towards that value, hence from top to bottom and from left to right.
While we populate we choose the values based on if it's kth player turn, where we try to maximise (pick the coin that leads to the highest outcome value), or if it's not, where we pick the coin that leads to the lowest outcome value, without adding it.