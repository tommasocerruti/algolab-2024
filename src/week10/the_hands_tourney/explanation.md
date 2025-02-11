#### Topic
UnionFind

#### Explanation

Story summarised:
- We have n tents (each identified by their coordinates) that all need to be assigned to different families.
- However families dislike each other and they need to be at a minimum distance, and families need to have at least k tents for them (k = {1,2,3,4})
- Given the n tents and parameter k, an assignment is (f, s)-reasonable iff:
   * all the n tents are assigned
   * each family f has at least k tents
   * tents of different families must be at least at a distance s between each other
- You have to answer two questions:
   * for a given f0, what is the largest s so that (f0, s) is reasonable?
   * for a given s0, what is the largest f so that (f, s0) is reasonable?

Approach:
It is clear that we need to construct UF to find the components, then we can approach the two different tasks.
In general we need two additional vectors: s_comp, where s_comp[j] = size of the jth component (all initialised to 1), and n_comp_k where n_comp_k[k] = number of components of size k (initialised to 0, but n_comp_k[1] = n).
Given a needed k we can define a function that find the number of components of our wanted size "max_num_families(k, n_comp_k)" (remember to pass the vector by reference):
- k = 1 -> just those of size 1 are relevant -> n_comp_k[1]
- k = 2 -> the size 2 and half of those of size 1 -> n_comp_k[2] + n_comp_k[1]/2
- k = 3 -> the size 3, plus making 3 with 2+1 (c12 = min(n_comp_k[1], n_comp_k[2])), plus one third of size 1 that remain and half of size 2 (a13 = (n_comp_k[1] - c12)/ 3 + (n_comp_k[2] - c12)/2) -> n_comp_k[3] + c12 + a13
- k = 4 -> the size 4, plus making 4 with 3+1 (c13 = min(n_comp_k[1], n_comp_k[3])), then we calculate the additional 2 (a2 = (n_comp_k[1] - c13)/2 + (n_comp_k[3] - c13)) and add the couple of size 2 (c22 = (n_comp_k[2] + a2) / 2) -> n_comp_k[4] + c13 + c22
We do the usual merging of the components until the total number of components is zero:
Take the individual sizes of the components, merge the components, set the size of the new component, decrement the count of sizes of the two merged components individually and increment the count of the size of the merged component.
While you do this increment/decrement, use the min between the size and k, since higher than k we should consider them as k as well!
Task 1: we initialise f to -1, and as soon as we find an edge >= s0, we calculate f using the function defined above (since we want the maximum number of families, and if we further increase s it will just decrease).
Task 2: we initialise s to 0, and every time we merge two components, before merging, we check if we satisfy the f0 condition (using the function) and if yes update s (initially it will be always valid and after one point it will stop).
Note: as the size of s (the edges) increases, and the number of f suitable decreases, the moment where f != -1 and max_num_families(k, n_comp_k) < f0, we have already found the best values of the two and we can return.
