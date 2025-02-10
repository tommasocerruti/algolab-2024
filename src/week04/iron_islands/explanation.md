#### Explanation
The goal is to attack a subset of islands given k men soldiers. These n islands are structured like a tree, we have a spike at the centre and then b waterways, i.e. sets of continuously adjacent islands.
We need to plan a valid plan that attacks the most number of islands, where each island requires a determined amount of soldiers. A valid plan is a plan that:
- attacks adjacent islands.
- uses all available soldiers (exactly all, k).
- does not send more soldiers than needed (exactly the value required by the island, ni).
- does not pass twice through the same island.
The last condition has many implications, in particular a valid plan cannot involve more than two waterways. This means that there are two types of solutions:
- case 1: the best plan involves only one waterway, which can be tackled using SW (the longest continuous sequence that sums up to exactly k).
- case 2: the best plan involves two waterways, which can be tackled using two sum on all possible paths (which are identified by: waterway index w, partial sum of men par_sum, number of islands included nr_islands).

The paths get created while we read the waterways using partial sums.
Note that for the two sum approach we need to sort these paths in ascending order, first by par_sum since this is the value that needs to match the total number of men to have a valid plan, second by the number of islands to have the best plan.
We therefore point to the start and the end of the array, and we move these pointers as we calculate their respective total sum (take care to remove the spike since present in both the paths).
If the sum is equal to k we (potentially) update the best valid solution, and we go up.
If the sum is lower/greater than k we go up/down.