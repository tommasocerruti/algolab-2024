#### Topic
Linear Programming + Recursive DFS

#### Explanation

Story summarised:
This problem man... It involves determining whether dwarfs can gather enough minerals from a tree-like network of mines to meet specific requirements while minimizing costs. Dangerous mines halve the minerals passing through them and collapse if total inflow exceeds a danger threshold, while additional minerals can be purchased from a shop with limited supply and costs. The task is to model and solve these constraints using a linear program to minimize the purchase cost or declare the problem "Impossible" if requirements cannot be met.

Approach: 
- Define mine: danger threshold (=-1 if not dangerous) and resources (vector with quantities of resources, if dangerous they are all zero)
- Define mineral: by its required amount, its maximum shop supply and respective cost per supply
- Define find_downstream, that explores the subtrees of the dangerous: pushing the current mine to the subtree of dangerous, if the current is dangerous switch the current and iterate the children recursively
- Read the mines, and use a dangerous_index map to map indices to dang_indices, which start from 2 to reserve 0-m-1 for the minerals we extract and m-2m-1 for the minerals bought at the shop (remember to allocate the space for the minerals)
- Construct the adjacency for downstream (to construct it read the edges in reverse since we want them to go down), and populate it using the function starting from 0,0
- Read the minerals
- Set lp program with lower bound 0 and insert the constraints with the helper of a counter_index that increments at each constraint inserted
- There are three types of constraints:
1. Flow constraints
   - In general the outgoing flow from mine i of mineral j is labeled as dangerous[i]*m + j
   - We iterate though the mines and continue if the current is either the entrance or its dangerous (let's say we work on mine i) (and we keep track of which one between these two it is)
      - We iterate through the minerals (let's say we work on mineral j)
         - We iterate through the downstream of mine i and we either
            - Accumulate the amount of mineral j (if the current mine is not dangerous nor entrance)
            - We remove the outgoing flow if instead it is (hence multiplied by -1 in the equation)
         - We then add the ingoing flow of mine i either multiplied by 1 (if entrance) or by 2 (else, since its halved)
      2. Danger threshold constraints
      - If different than the entrance, we set the ingoing flow (still multiplied by 2) less than the danger threshold
3. Shop constraints
   - For each mineral we want to set
       - purchased (m + j) <= supply
       - purchased + found (j) >= required
   - And we want to minimise (m + j)*price
- If the solution is feasible, we do floor to long, else it is impossible to satisfy
Note: variables 0 to m-1 are the minerals collected out of the entry, m to 2*m-1 are the minerals bought at the shop, the rest is dangerous_index[i]*m + j indicating the mineral j outflowing of mine i 