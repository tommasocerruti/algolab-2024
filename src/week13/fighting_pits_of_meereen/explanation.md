#### Topic
Dynamic Programming

#### Explanation

Story summarised:
We need to design a schedule that maximises the overall excitement.
- There are n (<= 10^4) fighters lined up in a queue each having one out of k (2 <= k <= 4) types
- There are 2 entrances (north/south) and each round the first in the queue gets assigned to one of them
- The audience can remember only the last m (2 <= m <= 3) fighters that entered through each entrance
- Excitement calculated as 1000 * #distinct types of fighters among the last min{m, q} of such entrance (where q are the last fighters entered)
- If the number of fighters sent to the entrances is unbalanced, the excitement decreases of 2^abs(p-q), where p and q are the counts of the north and south entrance respectively.
- We also need to guaranteed that there is no individual round with negative excitement

Approach: 

Note: really really bad dp, really disgusting.
Goal - assign to each fighter an entrance that maximises the excitement (contributed positively by the diversity and negatively by the imbalance, and must be different than zero)
Dp state: 1. Current fighter index
	  2. Last m fighters at each entrance
	  3. Difference in assignments
We need to encode the dp state into a form suitable for memoization:
1. Last m fighters: given m <= 3 and k <= 5 (including a k=0 for empty turn), since we care about the last two fighters of type f1 (most recent) and f2: 5*f1 + f2 -> max 25 (actually 24 but 0-indexed so 25)
2. Difference d: since the maximum excitement for the last 3 is 3000, we have a constraint abs(p - q) < 12, which considering both negative and positive makes 25 cells (11 + 1 + 11 + 2 for the impossible cases)
Hence we have a dp[a][b][c][d] of size n x 25 x 25 x 25, where a = current fighter index, b = encoding of the last two fights coming from north, c = encoding of the last two fights(types) from south, and d = difference in the number of entrances between gates
The dp is initialised to -1 indicating not calculated yet, and the bases cases are next = -1 -> 0 (no more fighters, since next indicates the index of the next fighter) and abs(p-q) >= 12 -> INT_MIN (not to be used since invalid)

Detailed approach:
- define a struct of fighters_queue with int f1, f2, f3 indicating the three most recent fighters (f1 being the most recent)
- define a function int num_distinct that uses casting to a set and finding its size key in, given a queue and a value m, the number of distinct fighters (different from zero)
- read the fighters types in backwards order to start from index 0 when going through the queue, and offset the type by +1 (to use 0 as "no fighter")
- initialise the dp to -1 and an empty queue to call a recursive solve function that takes: 
   VVVVI &dp, int next (n-1 at first), VI &fighters, fighters_queue_t &north (empty queue at first), fighters_queue_t &south (empty queue at first), int diff (0 at first)
- solve:
   - base cases for std::abs(diff) >= 12 [returning INT_MIN] and next == - 1 [returning 0]
   - encode the last two fighters of each queue
   - shift the difference to be positive (+12 offset) to have its index in the dp table
   - if dp[next][encode_north][encode_south][shifted_diff] != -1, dont recompute, just return the value
   - find the next fighter and put it in two new queues that are the two possibilities, either for north or south gate
   - we calculate the excitement of both of them, by multiplying the difference by 1000 and removing the pow(2, std::abs(diff +1 or -1 depending on if its for the north or south gate) --> be coherent with your choice!)
   - we consider the best excitement between them if non-negative (else the best = INT_MIN), we put it in the respective index of the table and return it
