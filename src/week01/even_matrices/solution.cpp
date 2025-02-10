#include <iostream>
#include <vector>

void solve(){
  int N; std::cin >> N;
  std::vector<std::vector<int>> arr(N + 1, std::vector<int>(N + 1, 0));
  for(int i = 1; i <= N; i++) {
    for(int j = 1; j <= N; j++){
      int num; std::cin >> num;
      arr[i][j] = arr[i-1][j] + arr[i][j-1] - arr[i-1][j-1] + num;
    }
  }

  long res = 0;
  auto sum = [](std::vector<std::vector<int>>& arr, int x1, int x2, int y1, int y2) {
    return arr[x2][y2] - arr[x1 - 1][y2] - arr[x2][y1 - 1] + arr[x1 - 1][y1 - 1];
  };
  
  const int j1 = 1;
  for(int i1 = 1; i1 <= N; i1++) {
    for(int i2 = i1; i2 <= N; i2++) {
      int odd = 0, even = 0;
      for(int j2 = 1; j2 <= N; j2++) {
        if (sum(arr, i1, i2, j1, j2) % 2 != 0) odd++;
        else even++;
      }
      res += (even*(even - 1))/2 + even + (odd*(odd - 1))/2;
    }
  }

  std::cout << res << std::endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) solve();
}
