#### Topic
Min Cost Max Flow

#### Explanation

Story summarised:
Note: This problem has a simple description but yet it is very hard conceptually to come up with an efficient solution, be ready to cry.
There are S car rental stations and N booking requests. Each station has li initially stored cars. The bookings are described by s (start station), t (target station), d (departure time), a (arrival time), and p (profit).
We want to select a set of booking requests that is feasible (there must be the cars needed) and optimal (maximal profit).

Approach:
General approach:
* space-time graph:
   - vertex = position in time (discretize time in minutes) and space
      - parking = edge moving forward in time but not in space (0 cost and maximal capacity)
      - rental = edge that jumps forward in time from one station to another (pi cost *** and 1 capacity)
   - single super source with an edge to the beginning of the timeline of each station i with 0 cost and li capacity
   - single super sink with an edge from the end of the timeline of each station i with 0 cost and maximal capacity
   - our flow formulation ensures max flow is always L = sum(li), since no bottlenecks other than the super source edges
* eliminating negative edges:
   - adding offset P (max price) for the parkings and (t2-t1)P - pi for the rental i going from t1 to t2 with profit pi
* compressing the graph:
   - we need to compress all the boring two-degree vertices, since too many!
      - insert all the times in a vector<set<int>> where all relevant times for each station are stored in order
      - put all enumerated times as key-value pairs into a map, where m[station][time] = index of the graph
Detailed approach:
- define structure Request with all the relevant values: si, ti, di, ai, pi
- read the initial cars per station and keep track of the total_cars
- define three maximums: max_capacity = total_cars, max_profit = 100, max_arrival = 100000
- define a vector of requests and a vector of sets to store the timestamps of each station
- read each request, store it appropriately (shifting stations index) and insert the timestamps in the respective station if different from the extrema (di for si and ai for ti)
- define the map (si, ti) -> j that from a station si at a time ti it will give us the index j corresponding to the node of the graph
- starting from index 0 populate the map from station 0 to s-1 by giving an index to to 0, all the timestamps in the set, and max_arrival
- this index is the total number of nodes, so define the graph, its edge_adder and the respective source and sink
- for each request add the corresponding edge from map_to_g[si][di] to map_to_g[ti][ai] with capacity 1 and cost max_p*(ai-do)-pi
- now add the other edges, so iterate all the stations and add: edge source to time 0, edge time max_arrival to sink, and all the others (which total cars as max capacity and variant cost multiplying the length and the maximum power)
- if timestamps is empty add an edge between these two nodes
- else instantiate two iterators t1 and t2 at the beginning of the set and the second shifted by one, we add the edge between 0 and t1 and then iterate both of them while adding edges in between with cost (*t2 - *t1)*max_p, and to conclude t1 to max_arrival.
- run non negative min cost max flow algorithm and remove the offset which is the total flow (total_cars) times the max_arrival and the max_power: cost - (total_cars * max_p * max_arrival)