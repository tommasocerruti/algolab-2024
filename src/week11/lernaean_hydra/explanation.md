#### Topic
DP

#### Explanation

Story summarised:
There are n heads that we need to eradicate, the problem is that the hydra has this crazy thing that heads regrow like wtf. But thankfully sis Athene gives us m eradication patterns, composed of k heads, that if we follow we will be able to cut off head k-1.
However there is another constraint, that we cannot cut a head already eradicated, and an head is eradicated also if all the heads with index less than that were previously eradicated. :(
We need to save the world so we cannot just loose so much energy on this joke, so we try to minimise the number of cuts in such a way that (if possible) we eradicate all heads off.

Approach:
The first thing to notice is that we want to store all the patterns based on the last head, since it will lead to the cut, hence we define a VVVI that stores for each head j (out of n), all the eradication patterns (just vectors), ending with such head.
Then we divide the subproblems into: minimum cuts to eradicate head i (...but we realise it does not work alone, and we need...) using the jth possible cut.
So our dp of size n x d (where d is the guarantee of maximum patterns ending with that head) initialised to INT_MAX indicates such a state, and the base case is the pattern on the first head (that by default is k cuts).
So for every head (i - 0 to n) we try every pattern (j - 0 to patterns[i].size()) and we need to check for every previous pattern (l - 0 to patterns[i-1]):
- first if such pattern was used (in other words, if dp[i-1][l] = INT_MAX we continue)
- then we iterate k1 - 0 to k, to find the overlaps we can use to avoid cutting again
- and for this we need to check:
   - if std::equal(patterns[i][j].begin(), patterns[i][j].begin() + k1, patterns[i - 1][l].begin() + k - k1; meaning if the first k1 cuts of the current pattern match with the last k1 cuts of the previous one
   - if *std::min_element(patterns[i][j].begin() + k1, patterns[i][j].end()) >= i; meaning if the cuts that we do now do not include any head less than i
- if this is possible, we update dp[i][j] = std::min(dp[i][j], dp[i-1][l]+k-k1)
- then the solution is stored in the patterns that cuts the last head with the least number of cuts, which is *std::min_element(dp[n - 1].begin(), dp[n - 1].end())
- we need to still check if this is different from INT_MAX since it would mean that the cut is impossible