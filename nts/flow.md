## Flow Algorithms

### Main Points

Key concepts:
1. Maximum Flow:
   - Directed edges now have a capacity, which means that, given a capacity c, no more than c can flow through that edge.
   - We have a source that has only outgoing flow, where everything starts, and a sink, where everything ends, and we want to maximise the flow going from the source to the sink (for the other nodes, flow is conserved).
   - Algorithm: Push-Relabel or Edmonds-Karp, O(n^3).

2. BGL implementation:
   - Code snippet provide us with a graph and graph adder definition, that we can simply use as adder.add_edge(from, to, capacity). 
   - We then provide a source and sink, and then just run long flow = boost::push_relabel_max_flow(G, v_source, v_sink), which runs in O(n^3).

3. Extensions:
   - Multiple Sources: Combine sources into a super-source with infinite outflow, so that the bottleneck will be in the outward capacity of each single source. (Problem 1)
   - Undirected Graphs: Represent as directed edges in both directions. (Problem 2)
   - Vertex Capacities: Double the graph, one with only inward edges and the other with only outward edges, we then connect node a of graph 1 to node a of graph 2 with capacity equivalent to the node capacity. (Problem 2)
   - Minimum Edge Flow: Subtract the flow from f by connecting it to the sink, and adding the flow to t by connecting it to the source. (Problem 3)