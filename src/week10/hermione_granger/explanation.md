#### Topic
Linear Programming + Delaunay Triangulation

#### Explanation

Story summarised:
Harry and Hermione plan to distribute a limited amount of Felix Felicis among members of DA so they can interrogate Slytherin students. Each DA member can only reach the nearest Slytherin, and we want to see if it’s possible—within 24 hours and without exceeding the total Felix Felicis—to gather enough information about Malfoy, Crabbe, and Goyle.
In particular we have:
1. D DA members and S Slytherin students
2. Each DA is characterised by (x, y) and fi: ml of potion needed for each hour of luck.
3. Each Slytherin is characterised by (x, y) and (mi, ci, gi): how much information they provide for each hour of luck, respectively about M, C, and G.
4. We have a total amounts of info needed about (M, C, G) and F ml of potion that we can use.
5. Each DA can interrogate only their nearest Slytherin (which is guaranteed to be unique)
6. We can decide how many hours each "chosen" Slytherin is interrogated, while assuring:
   - total potion cannot exceed F
   - total hours of interrogation cannot exceed one day (24)
   - we collect at least M, C, G information about each respective individual
If there is a feasible solution we return L, else H.

Approach:
- We use DT to find the nearest students and LP to find whether we satisfy the constraints
- We have two data structures defining students: pts (containing the respective point and index) and students (contain structs with the amount of information per hour for each individual)
- We initialise another int vector for students to -1 having the best f, i.e. the lower ml of potion needed, for each
- So we iterate the DT members, find the closest student, and check if their rate is higher than the current (or null, -1) we substitute it
- We instantiate our LP program with upper bound 0 and lower bound 24, indicating that everything needs to happen within one day
- One variable per valid student, and in total 4 constraints: consumption (<= F), m (>= M), c (>= C), and g (>= G)
- We then need to just check the feasibility of our solution