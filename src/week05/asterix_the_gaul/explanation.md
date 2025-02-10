#### Explanation
Panoramix is at distance D from Asterix, while the Romans need T seconds to reach Panoramix.  
Asterix has a list of n possible moves, each consisting of a distance d executed in time t.  
Asterix can perform each movement at most once, and he can take at most m sips from a magic potion. Each sip allows him to cover an additional distance, s_j for each move.

We need to output the minimum number of sips needed for Asterix to reach Panoramix in less than T time, if it's not possible, output "captured".  
It is valid to go beyond D, which makes it tempting to solve this greedily. However, such an approach fails because it cannot satisfy both T and D constraints simultaneously, and the boost is moves dependent.  
This is a subset-sum-like and knapsack-like problem. Since n is small (n < 30) and D is very large (D < 2^50), we use Split and List.

Approach:
- Store the moves and the sips, and try to solve(*) it without sips first (if we succed, we stop).
- Binary search the minimum number of potions that solves the problem (we need to add the potion effect to all the moves, and subtract it after our trial).

*To solve the problem:
- we split the input in half (split and list)
- we find all the combinations of moves(**) within the split range having total time less than T (and if greater or equal than D, return true since that solved the problem already)
- if we didn't find a solution within the two split range, we use binary search (upperbound) to look for them but before this we need to
	1. Sort the subset2 of moves in decreasing order of time
	2. Use dominance compression to pre-process the moves so that for each t we have the best d (right to left propagating rightest best distance, since sorted in descending order of time)
	3. For every move in subset1, define the key, i.e. the minimum value that is satisfactory to solve the problem
	4. Find the upper bound of the subset2 regarding key, i.e. the highest time taking move so that the condition of time is satisfied
	5 Check if also the condition of distance is satisfied (if yes, we found a solution)

*To find all the combinations we use bitmasks:
- we find all the bitmasks for the range end-beg
- for each bitmask, every element belonging to it gets added (with the offset of the beg index)
- if such a combination satisfies our constraints of both time and distance, it's a solution, only time it is to be added to the subsums, else we don't care