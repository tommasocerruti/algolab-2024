#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

struct mine{int d; std::vector<int> res;};
struct mineral{int c, s, p;};

long conv(const CGAL::Quotient<ET> &x){
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return long(a);
}

void find_downstream(int curr, int dang, std::vector<std::vector<int>>& graph, std::vector<std::vector<int>>& downstream, std::vector<mine>& mines){
  downstream[dang].push_back(curr);
  if (mines[curr].d != -1) dang = curr;
  for (int neigh : graph[curr]) find_downstream(neigh, dang, graph, downstream, mines);
}

void solve(){
  int n, m; std::cin >> n >> m;
  std::vector<mine> mines(n);
  std::vector<mineral> minerals(m);
  std::unordered_map<int, int> dang_index;
  int dang_counter = 2;
  for (int i = 0; i < n; i++){
    int d; std::vector<int> res(m);
    std::cin >> d;
    if (d != -1) dang_index[i] = dang_counter++;
    for (int j = 0; j < m; j++) std::cin >> res[j];
    mines[i].d = d;
    mines[i].res = res;
  }
  std::vector<std::vector<int>> graph(n);
  std::vector<std::vector<int>> downstream(n);
  for (int i = 0; i < n - 1; i++){
    int u, v; std::cin >> u >> v;
    graph[v].push_back(u);
  }
  for (int i = 0; i < m; i++){
    int c, s, r; std::cin >> c >> s >> r;
    minerals[i] = {c, s, r};
  }
  find_downstream(0, 0, graph, downstream, mines);
  Program lp(CGAL::SMALLER, true, 0, false, 0);
  int eq = 0;
  for (int i = 0; i < n; i++){
    bool entrance = (i == 0);
    bool dangerous = (mines[i].d != -1);
    if (entrance || dangerous){
      for (int j = 0; j < m; j++){
        int value = 0;
        for (int neigh : downstream[i]){
          if (mines[neigh].d == -1) value += mines[neigh].res[j];
          else lp.set_a(dang_index[neigh]*m + j, eq, -1);
        }
        if (entrance) lp.set_a(j, eq, 1);
        else lp.set_a(dang_index[i]*m + j, eq, 2);
        lp.set_b(eq++, value);
      }
      if (!entrance){
        for (int j = 0; j < m; j++) lp.set_a(dang_index[i]*m + j, eq, 2);
        lp.set_b(eq++, mines[i].d);
      }
    }
  }
  for (int j = 0; j < m; j++){
    lp.set_a(j, eq, -1);
    lp.set_a(j + m, eq, -1);
    lp.set_b(eq++, -minerals[j].c);
    lp.set_a(j + m, eq, 1);
    lp.set_b(eq++, minerals[j].s);
    lp.set_c(j + m, minerals[j].p);
  }
  Solution sol = CGAL::solve_linear_program(lp, ET());
  if (sol.is_infeasible()) std::cout << "Impossible!\n";
  else std::cout << conv(sol.objective_value()) << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) solve();
}