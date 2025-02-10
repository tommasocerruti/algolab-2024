#include <iostream>
#include <algorithm>
#include <queue>
#include <climits>

struct boat_t{int len, pole, first_begin, first_end;};

auto comp_boats = [](boat_t b1, boat_t b2){return b1.first_end > b2.first_end;};

void solve(){
  int n; std::cin >> n;
  std::priority_queue<boat_t, std::vector<boat_t>, decltype(comp_boats)> boats(comp_boats);
  for (int i = 0; i < n; i++){
    int len, pole; std::cin >> len >> pole;
    boats.push({len, pole, pole - len, pole});
  }
  int count = 0;
  int prev = INT_MIN;
  while (!boats.empty()){
    auto boat = boats.top();
    boats.pop();
    if (prev <= boat.first_begin){
      count++;
      prev = boat.first_end;
    }
    else if (prev <= boat.pole){
      boat.first_begin = prev;
      boat.first_end = prev + boat.len;
      boats.push(boat);
    }
  }
  std::cout << count << std::endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int t; std::cin >> t;
  while(t--) solve();
}