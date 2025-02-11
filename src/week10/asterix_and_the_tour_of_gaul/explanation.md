#### Topic
Max Flow Min Cost

#### Explanation

Story summarised:
There are n stops and m foods. From each stop we can carry just ci (<= 100) food to the next stop. The m foods are defined by a b c, which means we need to pick up the food at station a, bring it to station b, and this has a significance c (<= 2^7 = 128).
Our goal is to maximise the possible significance.

Approach:
Note: the solution itself is not complex, but quite hard to find.
We split the flow into two parallel levels: level 0 where the useful flow will go through symbolising the food/space in the bag, and level 1 where useless flow will go through in case we need to increase/decrease the useful one.
In level 0, we connect j to j+1 with capacity c[j] and cost 128 (maximum significance), while in level 1, we connect n+j to n+j+1 with capacity 100-c[j] (maximum capacity) and zero cost.
Moreover if c[j] > c[j-1] it means we just increased our capacity by c[j]-c[j-1], so we need to transfer this flow from n+j to j, and opposite in case c[j] < c[j-1]. 
This is why we ned to treat j = 0 differently outside the loop, since we do not have any previous flows...
Then we enter the food just as edges from a to b with capacity (b-a)*128 - c, which makes sense since the more cost we can minimise the better it is.
To finish the graph we just add the respectively connect the source to the start nodes 0 and n, and the nodes n-1 and 2*n-1 to the sink, all of these with the next/last capacity and zero cost.
We then calculate the cost, which however has a positive offset equal to the sum of the capacities in level0 (which we need to keep track all of this time).