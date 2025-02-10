#### Explanation
Given n students, each with c characteristics, determine if it is possible to match pairs of students such that:
1. Each pair shares more than f characteristics.
2. If the matching size is less than n/2, the current value of f is "not optimal."

Approach:
1. Represent each student’s characteristics as an unordered set.
2. Iterate through all pairs of students to count shared characteristics.
3. Build a graph where an edge exists if two students share more than f characteristics.
4. Compute the maximum matching using Edmonds' algorithm and check if f is optimal (i.e. if > f is not a perfect matching).