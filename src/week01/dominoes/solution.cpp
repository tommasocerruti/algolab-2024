#include <iostream>
#include <vector>
#include <algorithm>

void solve(){
  int n;
  std::cin >> n;
  std::vector<int> heights(n);
  for (int i = 0; i < n; i++){
    int h; std::cin >> h;
    heights[i] = h;
  }
  int reach = heights[0];
  int fallen = 1;
  for (int i = 1; (i < n) && (i < reach); i++){
    reach = std::max(reach, i + heights[i]);
    fallen++;
  }
  std::cout << fallen << std::endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) solve();
}