#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#define endl "\n" 
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
template<typename T>
using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

constexpr int N = 2e5 + 5;

namespace tree_of_biconnected_comp {  
  int tin[N], tup[N], t = 0;
  int par[N], col[N], c = 0;
  vector<vector<int>> gr, ng;
  stack<int> st;

  void paint(int v) {
    ++c;
    int last = -1;
    while(!st.empty() && last != v) {
      col[st.top()] = c;
      last = st.top();
      st.pop();
    }
  }
  
  void dfs(int v, int p = 0) {
    tin[v] = tup[v] = ++t;
    st.push(v);
    for (int u: gr[v]) {
      if (u == p)
        continue;
      if (tin[u])
        tup[v] = min(tup[v], tin[u]);
      else {
        dfs(u, v);
        tup[v] = min(tup[v], tup[u]);
        if (tup[u] > tin[v]) {
          paint(u);
          par[u] = v;
        }
      }
    }
  }

  void build(int start, const vector<vector<int>>& g) {
    gr = g;
    dfs(start);
    if (!st.empty())
      paint(start);
    ng.resize(c + 1);
    for (int i = 1; i < gr.size(); i++) {
      if (par[i])
        ng[col[par[i]]].push_back(col[i]);
    }
  }
}


void solve() {
 
}


int main() {
  // freopen("casting.in", "r", stdin);
  // freopen("casting.out", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  // int tests;
  // cin >> tests;
  // while(tests--)
  //  auto start = chrono::high_resolution_clock::now();
    solve();
  //  auto end = chrono::high_resolution_clock::now();
  //  cout << endl << (chrono::duration_cast<chrono::duration<double>>(end - start)).count();
  return 0;
}
