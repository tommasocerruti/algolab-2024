#### Explanation
- Given a board of size n, with holes (represented by 0, where we cannot place a knight), we need to find the maximum number of knights so that no knights threatens each other.
- This problem means to find the maximum independent set of knights so no two knights are attacking each other, very analogous to MaxIS.
- Find the MaxIS by per se is NP-complete, by we know is much faster by using the theorem of maximum matching when the graph is bipartite, but is it?
Well, we know the knight moves as an L and that no knight can attack another knight of the same colour, making the graph bipartite by splitting the knights by the colour of their square (white/black).
We therefore pick one direction of the edges (white -> black, in this case) and build the graph.
- We find MinVC with max flow and since they are complementary we take the difference between the total number of vertices and the flow.