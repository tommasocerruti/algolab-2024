#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

typedef std::pair<int, int> p;

void solve(){
  int n, m; std::cin >> n >> m;
  std::vector<int> strengths(n);
  std::vector<int> weights(m);
  for (int i = 0; i < n; i++) std::cin >> strengths[i];
  for (int i = 0; i < m; i++) std::cin >> weights[i];
  std::sort(strengths.begin(), strengths.end(), std::greater<int>());
  std::sort(weights.begin(), weights.end(), std::greater<int>());
  if (weights[0] > strengths[0]){
    std::cout << "impossible\n";
    return;
  }
  std::priority_queue<p, std::vector<p>, std::greater<p>> pq;
  for (int i = 0, curr = 0; i < m; i++){
    int next = curr;
    while (next < n && strengths[next] >= weights[i]) next++;
    for (int j = curr; j < next; j++) pq.push({0, j});
    curr = next;
    auto man = pq.top();
    pq.pop();
    pq.push({man.first + 1, man.second});
  }
  int t = 0;
  while (!pq.empty()){
    t = pq.top().first;
    pq.pop();
  }
  std::cout << 3*t - 1 << '\n';
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) solve();
}
