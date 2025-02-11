#### Explanation
There are n bombs (n guaranteed to be odd since n = 2^i - 1, where i = {1, ..., 16}) stacked up in such a way that B_j stands on both B_(2j+1) and B_(2j+2).
Each bomb has a timer ti so that bomb i needs to be deactivated before time i. Another constraint is that we cannot deactivate the bomb on top of others, before deactivating the below ones.
We can assume there is no time in between the deactivation of different bombs. Is it possible to find a permutation of bombs satisfying these constraints?
A greedy quick approach to solve it is to set the timer of the below bombs minimum to itself and the one above minus one. We then sort all the timers and if time constraint is satisfied, we can solve it. In particular:
i < balls[i] (since the index i indicates the time of the deactivation and the balls[i] the timer of the bomb, which needs to be strictly greater than i).