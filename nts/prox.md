## Proximity Structures in CGAL

### Main Points

Proximity structures are geometric data structures designed for efficient handling of spatial relationships among points. One of the most fundamental structures is the **Delaunay Triangulation**, which has various applications.

Key concepts:

1. Delaunay Triangulation:
   - Ensures that no point is inside the circumcircle of any triangle.
   - Maximizes the smallest angle across all possible triangulations.
   - Uniquely defined for points in general position (no three points collinear, no four points co-circular).

2. Properties of Delaunay Triangulation:
   - Contains the Euclidean Minimum Spanning Tree (EMST) and the nearest neighbour graph.
   - Dual of the Voronoi Diagram, making it suitable for nearest neighbour queries.

   Example for nearest neighbour query:

   cpp
   P point = P(x, y);
   auto closest = t.nearest_vertex(point);
   P closest_point = closest.point();
   

3. Applications:

   - Efficient solutions to problems like nearest neighbour search (Problem 1), disk motion planning (Problem 2), and disk growing/intersection (Problem 3).

4. CGAL Support:

   - Constructed in O(nlogn) in 2D.
   - Provides efficient iteration through vertices, edges, and faces.

   Examples:

   - Iterating through finite faces and enhancing faces:
     cpp
     size_t num_faces = 1;
     for (auto f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f) f->info() = num_faces++;
     
   - Iterating through every face:
     cpp
     for (auto f = t.all_faces_begin(); f != t.all_faces_end(); ++f) f->info() = num_faces++;
     
   - Finding if a face is infinite:
     cpp
     bool is_infinite = t.is_infinite(f);
     
   - Locating a point to its face:
     cpp
     auto face_of_p = t.locate(p);
     
   - Iterating through the neighbors of a face (since every face has three neighbors):
     cpp
     for (int i = 0; i < 3; i++) auto fn = f->neighbor(i);
     
   - Circulators (like iterators but for circular structures like the edges incident to a vertex):
     cpp
     auto ec = t.incident_edges(v);
     do {
       if (t.is_infinite(c)) continue; // the edge is infinite
     } while (++c != t.incident_edges(v));
     
   - Iterating through the vertices of the triangulation:
     cpp
     for (auto vertex = t.finite_vertices_begin(); vertex != t.finite_vertices_end(); ++vertex) {
       double x = vertex.point().x();
       double y = vertex.point().y();
     }
     

5. Union-find data structure: 

   - Usage: Often used for connectivity queries or building an Euclidian Minimum Spanning Tree (EMST) from edges extracted via a Delaunay Triangulation or other graph sources.
   - Key Idea:  
     The union-find (disjoint set) data structure maintains a collection of disjoint sets, allowing two primary operations:
       1. Find: Determine the representative (or “parent”) of the set containing a given element.  
       2. Union: Merge two sets if they are distinct, so that all elements of both sets share a single representative.
   - Boost Implementation:  
     In many CGAL-based solutions, the union-find structure is provided by
     cpp
     #include <boost/pending/disjoint_sets.hpp>
     
     // Example usage
     boost::disjoint_sets_with_storage<> uf(n);
     
     where n is the number of elements. Each element is initially in its own set, labeled by an integer from 0 to n - 1.
   - Typical EMST Workflow:
     1. Sort all edges by ascending weight (e.g., squared distance).
     2. Iterate over these edges in order:
        - Let the endpoints be (u, v).  
        - Find the current representatives:  
          cpp
          Index c1 = uf.find_set(u);
          Index c2 = uf.find_set(v);
          
        - If c1 != c2, union them (they are distinct sets):
          cpp
          uf.link(c1, c2);
          
        - Continue until all elements are connected or all edges are processed.
   - Example (pseudocode, more detailed in problem 5):
     cpp
     // Suppose we have edges in 'edges' sorted by weight
     for (auto &edge : edges) {
       Index i1 = std::get<0>(edge);
       Index i2 = std::get<1>(edge);
       double weight = std::get<2>(edge);

       Index c1 = uf.find_set(i1);
       Index c2 = uf.find_set(i2);
       if (c1 != c2) {
         // unify their sets
         uf.link(c1, c2);
         // edge is part of MST
       }
     }
     
   - Maintaining Additional Data:  
     Sometimes, we store extra info (e.g., number of “bones” or “weight sum”) in an array indexed by the union-find representative. After merging two representatives c1 and c2, we pick the new representative c3 = uf.find_set(c1) and transfer the data:
     cpp
     data[c3] = data[c1] + data[c2];
     data[c1] = 0;
     data[c2] = 0;
     
     so that queries on the representative c3 reflect the merged information (e.g., total bone count).

6. Main functions to know:
- v->point()
- f->vertex()
- t.finite_faces_begin() / t.finite_faces_end()
- t.finite_vertices_begin() / t.finite_vertices_end()
- t.finite_edges_begin() / t.finite_edges_end()
- t.incident_edges(v) / t.incident_vertices(v)
- face_base_with_info / f->info()
- t.is_infinite(f/v)
- t.nearest_vertex(p)
- t.segment(*e)
- t.locate(p)
- Delaunay::Vertex_handle
- all about union find that are in the code snippet
