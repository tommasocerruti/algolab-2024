#### Topic
Min Cost Max Flow

#### Explanation

Story summarised:
- Teams are divided into two groups —East and West, with e and w teams respectively— and matches are played between teams from these groups.
- Matches are categorised into non-difficult (the first m) and difficult (the last d), and each match is associated with a respective risk r.
- The goal is to ensure that:
	1. Fairness: Each team participates in at least a minimum number (l) of type m matches.
	2. Efficiency: The total risk of the schedule (sum of all r of matches) is minimised.
	3. Feasibility: A fixed number of matches p are scheduled.
- The problem is to determine if a fair schedule is feasible, and then to find the most efficient one.

Approach:
The main challenge is to represent the graph correctly, then we just need to run min cost max flow algorithm from source to target and we find the result.
Graph representation:
- Since matches happen between team E and team W we have a bipartite graph, and we choose the edges to be E -> W
- We represent teams with nodes and matches with edges so an effective way to distinguish non-difficult matches from difficult ones is to duplicate the graph:
	0->e-1 E teams taking non-d matches, e->e+w-1 W teams taking non-d matches, e+w->2e+w-1 E teams taking d-matches, 2e+w->2e+2w-1 W teams taking d-matches
- To impose fairness (the minimum number of matches for each team), which effectively is the minimum number of flow through a vertex, we use two additional constrained sources and targets:
	source_l with capacity l connected to each team E involved in non-d matches and target_l with capacity l connected from each team W involved in non-d matches
	source_rest with max capacity connected to each team E involved in both d and non-d matches and target_rest with max capacity to each team W involved in both d and non-d matches
	source connected to source_l with e*l and to source_rest with p-e*l, target_l and target_rest connected to with w*l and p-w*l respectively
	(before assigning these capacities we need to check if p-max(e,w)*l < 0, since this would make it impossible from the start)
- We add the matches, that are the edges, based on the difficulty on one or the other part of the graph, with the first cost introduced that is the risk, which is our goal to be minimised
- We then run the algorithm and if the flow != p then there is no feasible plan that is fair, else we have it, and the cost corresponds to the minimum possible cost
