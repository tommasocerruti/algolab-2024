#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>

void solve() {
    int n; 
    std::cin >> n;
    std::vector<int> pars(n, 0);
    for (int i = 0; i < n; i++) std::cin >> pars[i];
    std::sort(pars.begin(), pars.end());
  
    int l = 0, r = 0, max_v = 0, min_d = INT_MAX;
    std::vector<int> res;
    bool valid = true;
    do {
        while (r < n && pars[r] <= pars[l] + 200) r++;
        if (r == n) valid = false;
        r--;
        if ((r - l + 1) > max_v) {
            max_v = r - l + 1;
            min_d = ceil((double(pars[r]) - pars[l]) / 2);
            int sum = pars[r] + pars[l];
            res.erase(res.begin(), res.end());
            if (sum % 2 != 0) res.push_back(floor(double(sum) / 2));
            res.push_back(ceil(double(sum) / 2));
        } else if ((r - l + 1) == max_v) {
            int curr_min_d = ceil((double(pars[r]) - pars[l]) / 2);
            if (curr_min_d <= min_d) {
                if (curr_min_d < min_d) {
                    min_d = curr_min_d;
                    res.erase(res.begin(), res.end());
                }
                int sum = pars[r] + pars[l];
                if (sum % 2 != 0) res.push_back(floor(double(sum) / 2));
                res.push_back(ceil(double(sum) / 2));
            }
        }
        l++;
    } while (valid);
    std::cout << max_v << ' ' << min_d << '\n';
    for (int pos : res) std::cout << pos << ' ';
    std::cout << std::endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) solve();
}