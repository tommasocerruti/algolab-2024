#### Explanation
Find the smallest integral radius of a circle that covers all given citizens (described by points).  
The radius must be rounded up to the nearest integer.  

Key Takeaways:
1. Use the Sqrt kernel to handle square roots in calculations (since we are asked for the radius, not the squared one).
2. Use CGAL's Min_circle and Min_circle_traits_2 structures to compute the smallest enclosing circle.
3. Implement a custom ceil_to_double function to round up the radius to the next integer.
