#### Explanation
The goal is to determine the maximum radius (r) of a ball that can fit inside a polyhedron defined by n linear equations in d-dimensional space.
The polyhedron is represented by inequalities of the form: a_i * x <= b_i
where:
- a_i is the normal vector to the i-th plane.
- b_i is the offset for the i-th plane.

Approach:
1. Identify the LP problem
- Typically we have unknowns being the LP var (in this case the ball) and knowns to be the constraints (in this case the cave).
- We want to model the ball in function of its centre c and its radius r, so for a ball B: B(r, c)
2. Remarks
- We are guaranteed that the input type is int (since the norm is still an int)
- Every constraint is already in the form of an inequality 
- We don't want any constraints on the centre -> (false, 0, false, 0) construction
- We want to maximise r (indexed d) -> we put it negated (and also we put a lower bound since a negative radius is insignificant)
3. Derivation of the equations:
- The closest point to the border will be p = c + r * a/||a||2
- We are given equations of the type a^t*p <= b -> a^t(c + r * a/||a||2) <= b -> 1->d[sum(aici)] + r*norm(a) <= b, which means we have d+1 variables (d for the centre and one for r)