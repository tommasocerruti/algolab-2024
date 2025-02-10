#### Explanation
There are n boats, each defined by a length l and the position p of the ring that holds the boat.  
No two boats can overlap (but they can barely touch), and the ring should be inside the length of the boat.  
We need to output the maximum number of boats that can fit.  

This problem is identical to the event scheduling problem (greedily solved by sorting events by their finishing time) and it is one of the most common greedy problems.  
Key steps:
1. Defining the boat struct: length l, position of the ring p, first_begin and first_end denoting the leftest possible position of the boat, and max_end denoting the rightest possible position.
2. Sort the boats by their ending position (for the greedy approach).
3. For each boat, check if it can fit at its earliest position (first_begin):
   * If possible increment the count of boats, and modify the prev variable keeping track of the leftest free spot
   * If not possible, we adjust the position of the current boat and push it back if it would be possible (we cannot consider it already since we might have another boat ending first)  