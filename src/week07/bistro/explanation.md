#### Explanation
For a given set of m restaurants, find the squared distance to the nearest restaurant among n.  
Since we only need squared distances, we can use Epic.

Key operations:
1. Build a Delaunay triangulation for the restaurant locations.
2. For each location, find the nearest vertex in the triangulation using t.nearest_vertex(point).
3. Calculate the squared distance between the location and the nearest vertex.