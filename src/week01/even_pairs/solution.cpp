#include <iostream>
#include <vector>

void solve(){
  int n;
  std::cin >> n;
  int ec = 1;
  int oc = 0;
  int sum = 0;
  for (int i = 0; i < n; i++){
    int num; std::cin >> num;
    sum += num;
    if (sum % 2 == 0) ec++;
    else oc++;
  }
  int couples = (oc*(oc-1))/2 + (ec*(ec-1))/2;
  std::cout << couples << std::endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) solve();
}