#### Explanation
There are n friends, each with strength s corresponding to the maximum weight they can carry.  
There are m boxes, each weighing w. Each friend can carry only one box at a time, and friends cannot cooperate to carry a single box.  

The times to bring the boxes and to return are fixed: 2 minutes to carry and 1 minute to return.  
We need to find the minimum time to bring all the boxes (if possible).  

Hence the procedure is:
1. sort both the strenghts and weights in descending order and check if it is possible
2. define min-heap of pairs {#moves, index_of_person}
3. iterate through the weights, while keeping an index to the weakest person able
4. add the new people using the reference (hence {0, index})
5. pick the top and push it incrementing the moves by one
6. once finished the weights iteration, count all the moves and format it