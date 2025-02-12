## Linear Programming in CGAL

### Main Points
Linear programming (LP) is a mathematical approach to optimise a linear objective function subject to linear constraints.  
CGAL supports LP with high precision and various input/output types, making it suitable for computational geometry problems.

1. LP Components:
   - Variables: Parameters whose values we can choose.
   - Objective Function: Criterion to minimise (cost) or maximise (profit). 
   (Note that we just consider minimisation since if we need to maximise we can just take the negation of the function and the constraints: minimising -f = maximising f)
   - Constraints: Linear (in)equalities limiting variable values.

2. CGAL LP Features:
   - Handles minimisation problems; convert maximisation to minimisation by negating the objective.
   - Supports three solution types:
     - Feasible: Satisfies all constraints.
     - Optimal: Feasible and minimises the objective function.
     - Infeasible: No feasible solution exists.
   - Input types: int, long, CGAL::Gmpz - arbitrary precision integer, CGAL::Gmpq - arbitrary precision rational(increasing precision and cost).
   - Complexity: given a minimization problem of a linear function in n variables subject to m linear (in)equalities constraints, the worst case is exponential in n and m, but for min{n, m} small (<= 200) the complexity is O(max{n, m}).

3. Common Applications:
   - Resource allocation.
   - Maximizing profits or minimizing costs.
   - Geometric optimizations like separation or coverage.

4. Use:
   - Type of problem: lp = Program(CGAL::SMALLER, true, 0, false, 0) (true with lower-bound 0 and false with no upper-bound)
   - For matrix A: lp.set_a(#var, #eq, coeff);
   - For vector b: lp.set_b(#eq, coeff);
   - For vector c: lp.set_c(#var, coeff);
   - For coeff of c: lp.set_c0(coeff);
   - Type of solution: s = CGAL::solve_linear_program(lp, ET()); s.is_unbounded(), s.is_infeasible(), s.objective_value()
   - When we try linear separation we are looking for a line ax + by + c = 0 (unknowns a, b, c) so that apx + by <= c for p in B
   - On top of the code snippet for linear separation we need to choose one of the three variables like var to normalise: lp.set_l(var, true, 1); lp.set_u(var, true, 1);
   - While we do this we disregard: horizontal lines (if a), vertical lines (if b), and lines through the origin (if c).
