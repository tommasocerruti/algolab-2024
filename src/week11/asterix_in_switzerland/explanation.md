#### Topic
Maximum Flow

#### Explanation

Story summarised:
- We have n different provinces each with a balance bi that can be either positive or negative.
- We then have m debts between this provinces where a debt i j d means that province i is in debt with j for d.
- A set of provinces X is called free-standing if the total balance of the provinces in i is greater than their debt towards the provinces outside of the set (n \ X).

Approach:
- Note:  - this problem can be considered a Jewish problem, meaning a problem that has a very easy solution, but difficult to come up with.
         - it is a "yes/no" answer, not a "which set" one. This implies that calculating all the sets is not necessary (and also would pass only test 1).
         - among the most feasible approaches there is max flow (no cost since we are not interested in the maximum win).
- We distinct the provinces with a positive and negative balance, the positive ones we connect the source to them with the value of the balance, while the negative ones to the sink (with positive sign).
- While we add the edge between the source and the positive balance province, we keep track of the total balance, which will be our only positive asset.
- We then add the edges for the debts between the nodes.
- The negative asset will be due to the debts towards the ones excluded from the set, where the profit will be subject to the threshold of the capacities of the edges towards the negative balance provinces.