#### Explanation
We are given the 1D coordinates of the bars and need to find the optimal location that maximizes the number of bars within a ±100 range.  
If multiple optimal locations exist, we need to choose those that minimize the distance to the furthest bar.  
We return:
1. The maximum value of bars covered.
2. The minimum distance to the furthest bar.
3. All coordinates satisfying these conditions.

We can sort the array to move left to right contiguously. Using a sliding window, we maintain a range where the bar at the right (pars[r]) is not further than 200 from the left (pars[l]). Update the maximum size and the minimum distance as better values are found. Consider that the difference between the two endpoints might be odd, which means that for a single position there are two best coordinates.

Take care about the difference between the two extrema. If the sum is odd it means we have two solutions.