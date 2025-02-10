#### Explanation
There are different potions that affect Harry's power, happiness, and wit.  
- Potions of type A make him gain power pi and happiness hi, but lose a fixed amount of wit a.
- Potions of type B make him gain wit wi, but lose a fixed amount of power b.  

The goal is to find the minimum number (if possible) of drinks needed for Harry to satisfy requirements of at least P power, H happiness, and W wit.  

1. Use a greedy approach for potions B, as they affect only one variable, by sorting them from most powerful to weakest (i.e. decreasing order of wit).
2. Use dynamic programming for potions A, as they affect multiple variables.  

The procedure to populate the DP table is:
* state definition: dp[i][j][h] = maximum power achievable with the first i potions, using exactly j potions, with at least happiness h.
* state initialisation: LONG_MIN, since then we are summing values and we might get positive values despite that should be impossible.
* base case: using only one potion A, for every happiness level, iterate the starting potion, hence iterating h from 0 to H, i from 1 to n, and fixing j = 1. We want to initialise it to the highest value, so as we go on, if we find a potion satisfying the h level but giving more power choose that one.
* recurrence case: we increase the number of potions use, hence iterating j from 2 to n, h from 0 to H, i from j to n. We have two options: skip the current potion (dp[i - 1][j][h]) or take it, which means using one potion less where the total is leading to happiness h - pots_a[i - 1]. This because to reach the same level of happiness but using the current potion, we need to use the best result leading to prev_h that is without taking that potion (prev_h = std::max(0, pots_a[i - 1].h)). Overall it is therefore dp[i][j][h] = std::max(dp[i - 1][j][h], dp[i - 1][j - 1][prev_h] + potions_a[i].p)

We then greedily pick the potions B. We increment the respective total wit, and if we reach/overcome W, the threshold we want, we calculate the negative power given by those potions. We then iterate j from 1 to n to look for the minimum j (number of potions A used) so that using those potions across all of them (i = n) that have H happiness (h = H) we have enough power (dp[n][j][H] >= P + neg_pow, where neg_pow is given by the number of potions B used).
As soon as we find a valid one, it's the best one since they have decreasing wit but same lowering of power. If we finish that we do not find it, it means we cannot reach it.
