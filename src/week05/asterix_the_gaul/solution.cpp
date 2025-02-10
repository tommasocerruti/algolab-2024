#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

struct move {long d, t;};

auto comp_move = [](move m1, move m2){
  return m1.t > m2.t;
};

bool subset_sum(int beg, int end, std::vector<move> &moves, std::vector<move> &result, long D, long T){
  for (int i = 0; i < (1 << (end - beg)); i++){
    long sum_d = 0, sum_t = 0;
    for (int j = 0; j < (end - beg); j++){
      if (i & (1 << j)){
        sum_d += moves[j + beg].d;
        sum_t += moves[j + beg].t;
      }
    }
    if (sum_t < T){
      if (sum_d >= D) return true;
      result.push_back({sum_d, sum_t});
    }
  }
  return false;
}

bool split_and_list(int n, std::vector<move> &moves, long D, long T){
  std::vector<move> res_one;
  std::vector<move> res_two;
  if (subset_sum(0, n/2, moves, res_one, D, T)) return true;
  if (subset_sum(n/2, n, moves, res_two, D, T)) return true; //+1?
  std::sort(res_two.begin(), res_two.end(), comp_move);
  for (int i = int(res_two.size()) - 2; i >= 0; i--) res_two[i].d = std::max(res_two[i + 1].d, res_two[i].d); //other dir
  for (move m : res_one){
    move key = {D - m.d, T - m.t};
    auto upper = std::upper_bound(res_two.begin(), res_two.end(), key, comp_move); 
    if (upper != res_two.end() && (upper->d + m.d) >= D) return true; //end D condition
  }
  return false;
}

void solve(){
  int n, m;
  long D, T;
  std::cin >> n >> m >> D >> T;
  std::vector<move> moves(n);
  std::vector<long> sips(m);
  for (int i = 0; i < n; i++){
    long d, t;
    std::cin >> d >> t;
    moves[i] = {d, t};
  }
  for (int i = 0; i < m; i++) std::cin >> sips[i];

  if (split_and_list(n, moves, D, T)){
    std::cout << 0 << '\n';
    return;
  }
  int left = 0, right = m - 1;
  while(left <= right){
    int mid = left + (right - left)/2;
    for (int i = 0; i < n; i++) moves[i].d += sips[mid];
    if (split_and_list(n, moves, D, T)) right = mid - 1;
    else left = mid + 1;
    for (int i = 0; i < n; i++) moves[i].d -= sips[mid];
  }
  if (left == m) std::cout << "Panoramix captured\n";
  else std::cout << left + 1 << '\n';
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) solve();
}