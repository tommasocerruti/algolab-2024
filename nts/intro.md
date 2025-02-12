## Introduction

### Main Points
- Always put std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); as the first line of the main.
- Lambda functions:
  ```cpp
  auto funct = [](// arguments){// function;};
  ```
- Priority queue:
   - By default, we have a max heap, which means maximum values at the top:
    ```cpp
    std::priority_queue<int> max_heap;
    ```
   - Min heap requires specifying type, container, and ordering:
    ```cpp
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
    ```
   - Custom comparison for a min-heap:
    ```cpp
    auto compare = [](std::pair<int, int> p1, std::pair<int, int> p2) {
        return p1.first > p2.first; 
    };
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(compare)> pq(compare);
    ```
   - push_back: inserts a new element already constructed, emplace_back: pushes a new element while constructing it in-place
    Note: This comparator sorts an array in descending order, and it makes a min-heap since the minimum values are on the top (min -> > / max -> <).
- Basic algorithms that are needed:
   - Sliding Window
   - Binary Search
   - BFS/DFS
- We can approximate the number of operations per second as 10^7, and we need to consider this value to guide the complexity of our algorithm.
- Debugging will be very very useful... You can do
   - simple std::cout, to verify values
   - use the macro \_\_LINE\_\_ like std::cout << \_\_LINE\_\_, to verify where segfault could happen, by printing the values at lines
   - use assertions to help check assumption like assert(b!=0 && "Denominator must not be zero"), in case it is zero it will abort with an error and print the message