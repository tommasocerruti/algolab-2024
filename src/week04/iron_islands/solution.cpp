#include <bits/stdc++.h>

struct path{int ind, len; long sum;};
auto sort_paths = [](path p1, path p2){
  if (p1.sum == p2.sum) return p1.len < p2.len;
  return p1.sum < p2.sum;
};

void solve(){
  int n, k, w; std::cin >> n >> k >> w;
  std::vector<int> caps(n);
  for (int i = 0; i < n; i++) std::cin >> caps[i];
  std::vector<path> paths;
  int best = 0;
  for (int i = 0; i < w; i++){
    int l; std::cin >> l;
    std::vector<int> wat(l);
    long par_sum = 0;
    for (int j = 0; j < l; j++){
      int r; std::cin >> r;
      wat[j] = caps[r];
      par_sum += caps[r];
      paths.push_back({i, j + 1, par_sum});
    }
    int left = 0;
    long sum = 0;
    for (int right = left; right < l; right++){
      sum += wat[right];
      while (sum > k) sum -= wat[left++];
      if (sum == k) best = std::max(best, right - left + 1);
    }
  }
  std::sort(paths.begin(), paths.end(), sort_paths);
  int left = 0, right = paths.size() - 1;
  while (left < right){
    long sum = paths[left].sum + paths[right].sum - caps[0];
    if (sum == k && paths[left].ind != paths[right].ind) best = std::max(best, paths[left].len + paths[right].len - 1);
    if (sum <= k) left++;
    else right--;
  }
  std::cout << best << std::endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) solve();
}