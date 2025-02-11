#### Topic
Min Cut

#### Explanation

Story summarised:
Given a set of n nodes each with a particular convenience score sj, we want to find (if it exits) a subset S of nodes that have no outgoing edges (semi dead-end) that maximises the sum of the total convenience score.

Approach:
We remember there is a one to one correspondence between the minimum cut and maximum flow.
We connect the source with all the nodes with positive convenience score, so that given sj > 0, the cost of cutting node j (meaning to exclude node j from our set S) is sj, not cutting it means instead to include it in S.
We connect to the target all the nodes with negative convenience score, so that given sj < 0, the cost of cutting node j (meaning to include node j into our set S) is -sj, not cutting it means instead to include it with the target (exclude it from S)
We then connect together all the nodes with infinite capacity, so that if two nodes are connected, we make sure to cut them both (given u->v, wherever u goes, also v has to go to), otherwise we would have to pay infinite cost.
By choosing the Min Cut, we effectively choose to minimise the penalty (given by excluding a positive or including a negative).
So while we add the edges, we count the overall total positive score by summing the positive values.
The result is within the difference of the total positive and the penalty (the flow = mincut), which if non-positive makes it impossible to solve.