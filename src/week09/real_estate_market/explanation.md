#### Explanation
There are N buyers, each that submits bids for each of the M houses but can buy only one. What complicates the problem is that each house belongs to one state out of S different states, where each state has individual restrictions on how many houses can be sold there.
We can divide this problem into different layers:
L1 - source to buyers, where capacity = 1 (each buyer can buy at most one house) and cost = 0 (no benefit from which buyer buys)
L2 - buyers to houses, where capacity = 1 (each buyer has only one bid per house) and cost = -bid (since we want to maximise it)
L3 - houses to states, where capacity = 1 (each house can be bought by at most once buyer) and cost = 0 (no benefit from which house is bought)
L4 - states to sink, where capacity = threshold (the limit of how many states can be sold in that state) and cost = 0 (no benefit from which state is involved
This approach successfully solves the problem, but it's too slow for the last test because of cycle_cancelling that works for negative edges but it is slower.
In order to use the positive edge algorithm, we assign as cost the difference between the maximum value and the bid, so that the higher the bid the lower the cost, and positive.
After we run this, we should remove the offset we gave to work with positive edges, that is the houses sold (= flow) * maximum_cost - cost_calculated.