#### Topic
UnionFind with BS

#### Explanation

Story summarised:
There are n planets and "everyday we start from one planet of your choice" and travel to some planets in the nearby to conquer them based on the operation range r.
However also the enemies are conquering the planets "one per day", and we do not want to visit a planet that is either conquered already or will be conquered before we finish our plan.
In particular we know the plans of the enemies, i.e. the order of the planets (including them all), as well as their coordinates.
We want the maximum number of planets conquered, which means given planets p_0, ..., p_n-1, we want the maximum number of planets conquered among those already not visited, p_k, ..., p_n-1. 

Approach: 
- We read the number of planets, the range, and store the planets with their indices.
- We want to find k, that is them maximum number of planets conquered, which has a 1 to 1 correspondence with the number of days passed (since we conquer one planet per day).
- We look for the ideal k using binary search, starting with left = 2 and right = n/2, since right > n/2 will be irrelevant (since the enemies would have reached us) and we shift left to -1 (we are guaranteed to conquer at least one planet, our start).
- We therefore insert planets from mid onwards inside the triangulation, and initialise the union-find data structure.
- Note that we are not looking for the EMST, we just look for the component with the most planets, so we can skip the sorting edges and go directly into finding the components, calculating their distance, and if valid, link the components.
- While we link we update the component with the most planets, which if greater than mid will be shrieked to mid (mid+1 since then we will shift left with -1), else we shrink right to mid-1.