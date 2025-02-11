#### Topic
Linear Programming

#### Explanation

Story summarised:
- Bro wants to hang n new posters on a wall where each poster must be centered at one of n free nails, without overlapping either the m already-hung posters or other new posters.  
- Each poster has a base size of h x w, but Bro can enlarge them individually by a scaling factor a >= 1, ensuring no rotation or misalignment.  
- The task is to maximize the total perimeter of the n new posters, where the perimeter of a scaled poster is 2a(h + w).  
- This requires calculating the optimal scaling for each poster while ensuring no overlaps, based on distances between nails and existing posters.

Approach:
- Classical LP problem, but consider that the input types are rationals so we need to use typedef CGAL::Gmpq IT; but we do not need any geometry so no kernel (the points is just a struct)
- We read the new and old posters in their respective array
- We set up the LP program that has as lower bound 1 since the LP variables are the scaling factors that cannot be less than one since we can only enlarge the posters
- We have two types of constraints: new poster vs new poster and new poster vs old poster
1. New vs New
   - We iterate for every poster, for every other poster, we add the constraint:
      - x1 + a1*w/2 <= x2 - a2*w/2 or x2 + a2w/2 <= x1 - a1*w/2 --> a1 + a2 <= 2*abs(x1 - x2)/w
      - ... a1 + a2 <= 2*abs(y1 - y2)/h
      - since we want the tightest bound, to ensure 2d separation the greater of these two satisfies the problem (we just want separation on one axis), hence we pick the max between these two constraints, and put it in the IT as denominator, numerator.
2. New vs Old
   - We iterate for every poster, for every old poster, we add the constraint:
      - x + a*w/2 <= x0 - w/2 or x0 + w/2 <= x1 -a*w/2 --> a <= (2*abs(x - x0)+w)/w
      - ... a <= (2*abs(y - y0)+h)/h
      - as above we take the maximum between those two but we need to keep track of the minimum among these maximum
   - Once we finish, we set as upper bound of the new poster, the minimum bound of the old one
- The objective function is the perimeter of each poster, i.e. 2*ai(h+w), which, since we need to maximise, we will negate, and round it to the next integer (since negated we will take the floor) taking CGAL::Quotient<IT>.
