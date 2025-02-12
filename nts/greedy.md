## Greedy

### Main Points
Sometimes, locally optimal choices result in a globally optimal solution (greedy algorithm).  
However, choices that seem best at a particular moment may not always be optimal.  

A greedy approach typically involves:
1. Modeling: Realize that the task requires constructing an optimal set.
2. Greedy Choice: Given already chosen elements c1, ..., ck-1, decide how to choose ck based on a local optimality criterion.
3. Proof of Correctness: Show that elements obtained this way result in a globally optimal set (often challenging).
4. Efficient Implementation: Make the greedy choice as efficient as possible.

Key elements to solve such problems include sorting and priority queues.  
Example:  
- The knapsack problem with integer values is NP-complete (solved with DP), while the fractional knapsack problem is greedy.  
- The job scheduling problem (to maximize the number of compatible jobs) can be solved greedily by sorting by finishing time.