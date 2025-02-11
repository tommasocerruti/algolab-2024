#### Topic
Greedy sort + Recursive DFS

#### Explanation

Story summarised:
- Imagine a “tree” structure with the root at the surface (node 0). [we can understand this by having only edges going down and having distinct paths, differentiating it from a DAG]
- Each chamber has some gold that is “ticking down” at a rate of 1 coin per second until it’s emptied. [even though we are given the guarantee that there will always be some gold]
- You can only travel each tunnel at most once each way. [which still allows us to explore all the subtrees]
- You must plan a full route from the surface, through every chamber, collecting gold, and then return back to the surface, to maximize what you collect. [since we are guaranteed to gain every time positive amount of gold]
-> "a best-route problem on a tree, with a time penalty that reduces the value of unvisited nodes over time"

Approach:
- We define two structs:
   edge_t used to create the tree (by creating an adjacency list graph), including the length of the edge and the vertex reached.
   path_t used to define the paths that for a current nodes includes: galleons (#galleons taken), chambers (#chambers visited), return_time (time taken to explore the subtree below and come back to the current).
- We define a sorter:
   Sorting by the paths that waste less galleons, which practically means the product between the number of chambers in the subtree that are "ticking down" and the total length, equivalent to the time.
- We read the galleons and the graph (make sure to include +1 for the source, and use appropriate types, like long instead of int)
- The result is returned by the function call solve(0, galleons, graph).galleons, indicating the galleons of the path starting from 0 that will lead to the maximum number of galleons.
- solve returns hence the best path statistics starting from the current:
   * base case: if the current is a leaf, then we return {galleons in the leaf, 1 chamber (the leaf), 0 time (since cannot explore further)}.
   * recurrence case: 
        - we store all the paths, so we iterate in the outgoing edges from the current and for each one we solve it
        - for each one we push it to the paths: the galleons of the path - (the length of the edge)*(chambers of the subtree), which removes to the subtree the ones that will tick down when we will explore it, the same chambers and return time +2*len.
        - we sort them with our sorter, so that we have the most convenient first
        - we iterate again the paths and keep track of the total galleons, chambers and return_time, that will be the one we return. In particular
              - we add to the total galleons the galleons of each path minus the product between the path chambers and the total time, indicating the ticking down due to waiting to go back.
		(note: while the first offset is due to the time to go back up to the path, this is to wait the other paths)
              - we add to the total chambers/return_time the current chambers and return_time
        - we return the total statistics we counted incrementing the tot_galleons with the galleons of the current and the tot_chambers by one indicating the one just added