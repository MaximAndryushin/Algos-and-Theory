#include <bits/stdc++.h>

#define endl "\n" 
using namespace std;

using pii = pair<int, int>;

constexpr int N = 2e5 + 5;

vector<int> gr[N];

int n, m, f;

namespace lca {
  vector<int> ord;
  int height[N];
  int tin[N], tout[N], t = 0;

  void dfs_order(int v) {
    tin[v] = ord.size();
    ord.push_back(v);
    for (int u: gr[v]) {
      height[u] = height[v] + 1;
      dfs_order(u);
      ord.push_back(v);
    }
    tout[v] = ord.size() - 1;
  }

  int min_h(int a, int b) {
    return height[a] < height[b] ? a : b;
  }

  struct sparse_table {
    sparse_table(const vector<int>& v) {
      int sz = v.size();
      if (lg.size() < sz + 1) {
        int cur = max((int)lg.size(), 2);
        lg.resize(sz + 1);
        for (int i = cur; i <= sz; i++)
          lg[i] = lg[i >> 1] + 1;
      }
      t.assign(lg[sz] + 1, vector<int>(sz));
      for (int i = 0; i < sz; i++) 
        t[0][i] = v[i];
      for (int i = 1; i <= lg[sz]; i++) 
        for (int j = 0; j + (1 << (i - 1)) < sz; j++)
          t[i][j] = min_h(t[i - 1][j], t[i - 1][j + (1 << (i - 1))]);
    }

    int get(int l, int r) {
      int sz = lg[(r - l + 1)];
      return min_h(t[sz][l], t[sz][r - (1 << sz) + 1]);
    }

    private:
    inline static vector<int> lg = vector<int>();

    vector<vector<int>> t;
  };

  void build() {
    dfs_order(1);
    sparse_table t(ord);
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
