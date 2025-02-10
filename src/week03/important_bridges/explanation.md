#### Explanation
Identify critical edges (bridges) in an undirected graph. A bridge is an edge that, if removed, disconnects the graph.  
As explained in the biconnected component part, in order to find the bridges we compute the biconnected components, and check which of the components has only one edge, such edge is a bridge.

Approach:
- Read the graph, which is undirected and initiate the necessary data structures:
   - edge_component, map edge_desc -> component, which maps an edge to the biconnected component
   - component_map (like in the snippet, a vector), that will map the index of the node to the index of the component
   - an assoc property map of the edge_component (using boost::make_assoc_prioperty_map, to be found under property maps), to use as the second parameter to the biconnected components
- Now call the biconnected component, which will store inside the edge_component the result
- We now iterate through the pairs edge, bcc_index in order to increment the edge_count
- A bridge is a biconnected component that has only one edge, so we iterate again, and use the just populated edge_count to check if that bcc has only one edge, if yes we push it in order to a set of bridges (a set of pair<int, int> that we will output)

This exercise is easy but we have no code snippet about how to use biconnected component function, which makes it a bit boring to read and understand the documentation of BGL.