#### Explanation
Given a set of triangular map pieces, find the smallest number of contiguous pieces required to completely cover a given hiking path of m - 1 legs (i.e. defined by m points). 

Short Approach:
1. Use CGAL::orientation() to determine whether a point lies inside a triangle formed by three vertices.
2. Represent the path as a set of segments.
3. For each triangle, determine which path segments it covers. Store the coverage as a list.
4. Use a sliding window approach to find the minimum subset of triangles that fully covers the path.

Detailed approach:
1. Read the m points that define the m-1 legs
2. Read the n triangles that are defined by six points (three lines) and find the three intersections corresponding to the three vertices and convert them to points
3. For each triangle i you need to check for every point j if j is contained within i, which is found using CGAL::orientation with the points in order: (v1, v2), (v2, v3), (v3, v1), and checking if all of this have the same sign.
4. After checking for every point if its contained, we need to add to the triangle_cover_legs all the legs contained by triangle i
5. Then we use a sliding window to find the minimum contiguous sequence of triangles covering all the hiking path, we move the right pointer right if not enough, and when enough we shrink the left to the right as well