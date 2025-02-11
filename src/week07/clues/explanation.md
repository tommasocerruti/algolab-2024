#### Explanation
Given a set of congruent disks, determine whether it is possible to assign one of two colors (frequencies) to each disk such that:
1. No two disks of the same color overlap.
2. A given pair of points (Holmes and Watson) are in the same connected network.

Approach:
1. Construct a Delaunay triangulation for the disk centers, and square the distance to work with squared distances and EPEC kernel.
2. Perform DFS to check if the graph is 2-colorable, where edges represent overlaps.
   - If a 2-colorable graph is possible, split the disks into two separate graphs for each color.
3. Verify that no edges within a single graph violate the overlap constraints.
4. Check if the nearest disks to Holmes and Watson belong to the same connected component.

The problem revolves around checking if a network without interferences exists, which means to check if the graph is 2-colorable.
If it exists, we need to check if communication is possible, which means if their closest disks belong to the same connected component or if they are close enough to communicate with each other.
Also, we cannot construct a graph and check if it's 2-colorable, since it would be O(n^2), but we construct the Delaunay triangulation since it guarantees to contain an Euclidian MST.
We perform DFS on all the vertices of the triangulation, while ignoring those that do not satify the requirement edge length <= r.
1. Enhancing the face with a pair<bool, int> indicating {colour, #component}
2. Initialising two triangulation for the respective colours
3. Iterating through the finite vertices, if #component = 0 it means unvisited
4. Doing DFS on the neighbour vertices using circulator and checking if the neighbour is not and infinite vertex and closed enough.
   To each vertex we want its CC = immediate predecessor and its colour != immediate predecessor:
    - If their information is the same, i.e. same #component and same colour, the network is not valid
    - If its unvisited (#component = 0), we push the current component with the opposite colour
    - Else we ignore it since its irrelevant
5. After each DFS we push the node in its respective triangulation
6. We further need to check if the triangulation violates the constraint by iterating through the edges and checking if the segments are greater than the required distance.
7. If both are valid, we have a valid network!
