#### Explanation
We have to design a two canals systems to satisfy some requirements in 2 dimensions (meaning ignoring depth/overlapping):
- Two massive canals, one for fresh water and the other for sewage, that meet and cross at a right angle
- Each canal is connected though pipes with each house, and the water pipes are vertical while sewage pipes are horizontal (this enforces the canals to be non-vertical for water and non-horizontal for sewage)
- Sewer canal separates noble houses on its left and common houses on its right (accepting houses being precisely on it), if not possible YUCK
- The total sum of the lengths of all sewage pipes cannot exceed the budget threshold s, if not possible BANKRUPT
- If all the constraints are satisfied, minimise the length of the longest water pipe rounded to the next integer

Approach:
- Building the sewage canal, that has a line: ax + by + c = 0
   - read the nobles and put them on the left (axi + byi + c <= 0), store them and store the cumulative x and y
   - read the commons and put them on the right (axi + byi + c >= 0), store them and store the cumulative x and y
   - since we are guaranteed that the sewage canal is non horizontal, normalise a
   - solve the problem, and if infeasible Y (we cannot separate the noble houses from the common ones, yuck!)
- Check if the budget constraint is satisfied (if s != -1, meaning infinite)
   - we add another equation that verifies this, since the common are on >= 0 and nobles on <= takes the negation of this two
   - in particular we have (sum_x_common - sum_x_noble) + b(sum_y_common - sum_y_noble) + c(m - n) <= s
   - solve the problem, and if infeasible B (we cannot use only s length in total for the pipes, bankrupt!)
- Build the water canal, that has a line: a2x + b2y + c2 = 0
   - while we do this we need to always keep the same solver so take particular care to the indices
   - we impose the perpendicularity property of the two canals by enforcing a2 = -b: a2 + b >=0 and a2 + b <= 0
   - since we are guaranteed that the water canal is non vertical, we normalise b
   - we introduce another variable r, that is the maximum distance from any canal
   - so for every noble/common position at (x_i and y_i) we want to impose that they stay within this range
   - in particular we have a2xi + b2yi + c2 >= -r and a2xi + b2yi + c2 <= r
   - we can therefore restructure the two above: a2xi + c2 - r <= -yi and -a2xi - c2 - r <= yi
   - our objective function to minimise is just this distance r
   - solve the problem, which cannot be infeasible, and the result rounded to the next integer is the length of the longest water pipe minimised