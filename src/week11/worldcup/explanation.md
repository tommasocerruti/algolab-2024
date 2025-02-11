#### Topic
Linear Programming + Circle geometry

#### Explanation
Story summarised:
- You, as such a chad businessman, are managing Beer delivery from warehouses to stadiums during the World Cup, aiming to maximize profits while meeting specific demands and constraints.  
- Each warehouse has limited Beer supply with a defined alcohol content, and each stadium has an exact Beer demand and an upper limit on pure alcohol consumption.  
- Revenue from Beer transportation is adjusted based on terrain costs, calculated from crossing contour lines, which reduce the profit for each route.  
- The solution involves setting up and solving a linear program to ensure all constraints are met and the total profit is maximized, or determining that it's infeasible to fulfill the requirements.

Approach:
- We define the structs we need: Warehouse, Stadium and Contour. As well as a floor_to_long function to round down the revenue.
- We split the overall program in three functions:
1. solve: just reading all the values and calling the next to functions (update_costs, then compute_profit)
2. compute_profit: computes the profit given the warehouses, stadiums and profits
- define a lambda function that given warehouse w and stadium s returns the respective LP variable that is the quantity (litres) of beer from warehouse w consumed at stadium s: Xws
- we then insert all the constraints using a counter to help us:
   - supply constraints: for each warehouse w -> Xw1 + ... + Xwm <= supply(w)
   - demand constraints: for each stadium s -> X1s + ... + Xns = demand(s) (for the equality we need both <= and >= constraints for each stadium)
   - alcohol constraints: for each stadium s -> X1s*a1 + ... + Xns*an <= 100*upper_limit(s) (note that we multiply by 100 to avoid all the divisions)
   - profit objective function: for each warehouse w for each stadium s -> -Xws*revenue(w,s) (note that to maximise the revenue, we need to minimise the revenue loss)
- (if feasible) we return the objective_value divided by 100 (*see update_costs last point), rounded down and negated
3. update_costs: to update the costs due to the contours
- we create all the circles (using emplacements defined by the centre and squared radius, so we have to square it)
- vector of unordered sets w_c, where w_c[j] = set of all counter lines indices that contains warehouse i (circles[j].has_on_bounded_side(warehouse))
- same as to s_c, but for stadiums
- for each warehouse, stadium t is initially set to the sum of the two set sizes and we subtract 2 every time we find one in common (since if both inside they do not count)
- we update r[i][j] = 100*r[i][j] - t, to avoid many divisions (since each encirclement accounts for 0.01), which is considered in the other function