#### Explanation
Simulate the growth of bacteria in a rectangular dish. Each bacterium grows quadratically over time, and its growth stops when it touches another bacterium or the dish boundary.  
Determine the time when:
1. The first bacterium dies.
2. Less than half of the bacteria remain alive.
3. The last bacterium dies.

Key Observations:
1. Bacteria grow at a rate described by rho(t) = t^2 + 0.5, where t is the time elapsed.
2. Use a Delaunay triangulation to compute proximity relationships efficiently.
3. For each bacterium:
   - Calculate the minimum distance to the dish boundary.
   - Use incident edges to find the minimum distance to neighbouring bacteria.

More detailed procedure:
1. Read the boundaries of the dish and the coordinates of the bacteria, in order to construct the Delaunay triangulation based on the points.
2. Iterate through the finite vertices and compute the die_distance with the boundaries.
3. Use a circulator to circulate the edges at such vertex to calculate the die_distance_squared, i.e. the shortest segment square: t.segment(ec).squared_length()
4. Find the minimum squared time corresponding to the death of the bacterium: std::min(die_distance - 0.5, sqrt(die_distance_squared)/2 - 0.5)
5. Translate to time, so take the square root and the ceil. The three solutions at the respective indices: 0, n/2, n-1.