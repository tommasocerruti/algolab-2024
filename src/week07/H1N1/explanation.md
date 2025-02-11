#### Explanation
Given a set of n infected people, determine which of other m individuals can escape without getting infected (defined by x, y, d: squared distance to be mantained).

Approach:
1. Create a Delaunay triangulation of the infected people's locations: t.insert(pts.begin(), pts.end())
2. Enhance the triangulation finite faces with an index for traversal starting from 1 (keeping 0 for infinite): f->info() = num_faces++
3. Iterate the finite faces and iterate their respective three neighbour faces: auto f2 = f->neighbour(i)
4. Get the traversal index of the face (if infinite it's zero, symbolising the escape): int v = t.is_infinite(f2) ? 0 : f2->info()
5. Get the respective two points in common between the two faces:
- auto p1 = f->vertex((i + 1) % 3)->point();
- auto p2 = f->vertex((i + 2) % 3)->point();
6. We calculate the squared distance between the two points and we store for every face, the respective neighbour face with the distance, and we do it also for the infinite face when we found them.
7. Perform a BFS on the triangulation:
   - Start from the infinite face with infinite as infection distance.
   - Traverse adjacent faces while maintaining the minimum infection distance in a bottleneck vector.
8. For each person, check:
   - The squared distance to the nearest infected person.
   - If this sufficient, we locate the point to the respective face their location is in a face with sufficient distance (4d since squared).