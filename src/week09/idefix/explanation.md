#### Explanation
Key idea: 1:1 correspondence between points being connected (connected components in EMST) <==> we can move between the disks of the points (for a radius >= 2 * minimal distance betw. them, making s = 4r^2 very convenient, since comparing 2r all squared) 
Can copy code from the EMST template, and adapt:
- two UF structures, one for given initial radius with s, one for radius needed to get k
- for first problem (max bones): For each component of tree, store the number of bones reachable (i.e. 4 *distance to closest point <= s)
This can be done via a simple array, as UF comp. have index <= n
Upon merging, add together the numbers. At the end (when all edges <= s considered) look for max
- for second problem (min. radius b to get k): Have additional edges from each bone to closest point with edge weight 4 * dist.                                 Sort as usual, then do same procedure as above (i.e. UF) until one comp has >= k bones
Then the latest edge considered has minimal radius needed
Comments in the code:
1) Read n, m, s, k: #tree, #bones, s = 4*r^2 where r is the radius of a tree, k = min number of bones in the same region
2) Read oak-tree positions, build Delaunay
3) For each bone, find nearest oak tree, decide if it is in its shadow
   - find nearest oak-tree vertex in Delaunay
   - if bone is within radius r => 4 * dist <= s => bone belongs to that oak
4) Build edges between oak trees (from the Delaunay triangulation)
5) Sort edges by their length
6) UNION-FIND #1: largest number of bones for radius r
  - unify oak trees that are within distance sqrt(s) => edge^2 <= s
  - merge the two components into the new representative (if condition is satisfied)
  - no need to continue if edges exceed s
  - a = maximum bones in any connected component
7) UNION-FIND #2: find minimal radius => edges + oak-to-bone
  - add to the edges also those from oak to bone
  - sort again
  - we have n + m total "vertices" => 0..n-1 for oaks, n..n+m-1 for bones; where each bone-vertex has 1 bone
  - unify in ascending order => as soon as a component has >= k bones, store cost
  - b_squared = 4b^2 = q = minimum squared radius for a shadow region to contain at least k bones