#### Explanation

There are some defenders with variable defence value, and some attackers with fixed attack value.
For an attack to be valid: no more than one attacker can attack a defender, the strength of the attack must be the same as the defence, and the defensive line must be contiguous.
Find the maximum number of defenders beaten.
1. Precompute the length of valid segments ending at each position (using sliding window)
2. Use DP to pick the disjoint sets:
- dp[i][j] = "the maximum number of defenders taken down while using at most i attackers within the first j defenders"
- base case: dp[i][0] = -1, since it is invalid for an attacker to attack an empty set of defenders
While we iterate to fill the dp table we have two options:
- option A: skip the jth defender
- option B: if there is a sequence ending at j (len > 0) and the attack is valid (not to many attackers, i.e. dp[i - 1][j - len] != -1), then we can consider the best of these two (skipping or using this and the previous dp[i - 1][j - len] != -1)

Find the maximum number of defenders taken down using at most k attackers. Each attack must be contiguous.  
1. Precompute the length of valid segments ending at each position (using sliding window).  
2. Use DP to pick disjoint sets.