#### Topic
Delaunay triangulation

#### Explanation

Story summarised:
A subset T c= F of trees is admissible for a distance d if there exists a spot such that every tree in T has distance exactly d to p, and every other tree in F has distance at least d.
We need to output four values: a2, a3, as, amax.
- ak, the number of pairwise distinct admissible sets of size k for dk where k = {2, 3} and dk is the smallest distance d so that the number of admissible sets of size k for d is strictly greater than zero.
- as, the number of pairwise distinct admissible sets of size two for the given distance sqrt(s)
- amax, the maximum number of pairwise distinct admissible sets of size two for d, over all distances d

Approach: 
Remember a Delaunay Triangulation for a set of points is a triangulation such that no point lies inside the circumcircle of any triangle, which ensures the circumcenter is equidistant to all three vertices without having closer trees (given the assumptions).
We also introduce the concept of an Event, that is a pair of radius_squared and type (0 or 1 indicating the minimum and maximum radius squared valid for that face) which will be useful for amax.
A fundamental function to define is one taking a Face_handle and returning the squared radius of the circumcircle of the face (using its three vertices).
Defining these two things we can get into the coding approach (after reading the points and storing them into the triangulation with their index).
a_2 and a_s:
- iterate the edges and finding the v_left and v_right, find the midpoint
- find the nearest vertex to the midpoints, as well as the two faces adjacent to the edge (e->first and t.mirror_edge(*e).first) and their face_radius
- the max_radius_squared is simply the maximum between these two
- the min_radius_squared is the minimum between these two only if the nearest vertex is different than these, else it is the segment of squared length divided by 4
- we emplace the two events (min with 0 and max with 1) into the vector of events
- if s is in between (boundaries included) min_radius_squared and max_radius_squared, we increment a_s
- if we find a new min_radius_squared_2 we set a_2 to 1, but if we find the same value we increment a_2
a_3:
- in this case we just consider the encirclements, so we iterate through the faces, find the radius_squared and if we find a new min_radius_squared_3 we set a_3 to 1, but if we find the same value we increment a_3
a_max:
- we just sort the events and increment a counter for each type 0, while decrement for type 1, meanwhile checking if we find a max(a_max, curr)
Note: since we are constructing the encirclements we need exact constructions!