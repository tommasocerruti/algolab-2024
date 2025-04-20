## Split and List

### Main Points
When a greedy approach does not work, brute force is often the fallback. However, brute force can be optimized using:
1. **Dynamic Programming**: Useful when `k` (the bound of the states) is relatively small.
2. **Split and List**: Useful when `n` (the number of items) is small.  

The idea of Split and List is to split the input in half, work on the two halves separately, and use binary search to merge the results.

Example:  
Given a set (S = {s_1, ..., s_n}), is there a subset (S' subset of S) such that {sum}(S') = k?  
If `k` is small, use DP. For large `k` and small `n`, brute force is feasible, but for the last tests we need the split and list optimisation.  
