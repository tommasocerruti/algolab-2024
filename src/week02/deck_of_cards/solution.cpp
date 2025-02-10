#include <iostream>
#include <vector>
#include <cmath>

void test(){
  int n, k;
  std::cin >> n >> k;
  std::vector<int> vec(n);
  for (int i = 0; i < n; i++) std::cin >> vec[i];
  int l = 0, r = 0;
  double sum = vec[0];
  int best_diff = abs(vec[0] - k), best_i = 0, best_j = 0;
  while(r < n){
    if (best_diff == 0) break;
    if (sum < k){
      r++;
      if (r < n) sum += vec[r];
    }
    else{
      sum -= vec[l];
      l++;
      if (l > r){
        r++;
        if (r < n) sum += vec[r];
      }
    }
    if (abs(sum - k) < best_diff){
      best_diff = abs(sum - k);
      best_i = l;
      best_j = r;
    }
  }
  std::cout << best_i << ' ' << best_j << '\n';
}

int main(){
  int t; std::cin >> t;
  while(t--) test();
}