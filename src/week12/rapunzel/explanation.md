#### Topic
SW with PQ on a tree

#### Explanation

Story summarised:
- Rapunzel hair, braided with n hair ties, forms strands connecting the ties in a tree-like structure.
- The prince wants to climb a rope of length m that reaches the ground but he is sensitive to brightness change, and the difference between the maximum and minimum brightness along the rope (its contrast) must not exceed k.
- Rapunzel needs to determine the starting hair ties of all climbable ropes, or conclude "Abort mission" if no safe ropes exist.

Approach: 
- We declare 3 vectors of integers and 3 vectors of bools that we will need to solve the problem:
   * int - brights(n) [with brightnesses], prev(n, -1) [representing the tree by previous indices], parents(n) [with the ancestors used in the dfs going up]
   * bool - leaf(n, true) [if leaf], safe(n, false) [if solution], visited(n, false) [to skip revisiting]
- We read the brights and as we read the pair we modify prev and leaf
- We iterate the nodes and if it's a leaf we visit:
   * instantiate two priority queues both as max heap but one stores the min since we would put the negative brightness, storing {brightness, index}
   * enter a for loop where j = 0 indicates the level of the visit, curr = i indicates the current node (we do j++ and curr = prev[curr] to update)
   * we set parent[j] = curr to remember the 4th ancestor of i to be curr
   * we do a lazy removal of the pq removing the top just if outdated (i.e. while pq.top().second + m <= j)
   * if (j + 1 >= m) we can check if if its safe (i.e. if (pq_max.top().first + pq_min.top().first <= k), we would put safe[curr] = true)
   * we then check if visited[parent[j + 1 - m] (the first possible valid value) is visited then it would be redundant to go on, else we set it to visited