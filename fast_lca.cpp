#include <bits/stdc++.h>

#define endl "\n" 
using namespace std;

using ll = long long;
constexpr int N = 2e5 + 5;
constexpr int BLOCK = 10;

int n, m, f;

// FARACH-COLTON BENDER ALGORITHM

struct fast_lca {
  fast_lca(const vector<vector<int>>& gr) :
  gr(gr), height(gr.size(), 0), 
  tin(gr.size(), 0), tout(gr.size(), 0), B(log2(gr.size() * 2) / 2 + 1) { // SIZE OF BLOCK MAY BE NEEDED TO CHANGED
    dfs_order(0);

    id.resize(ord.size(), 0);
    type_of_seg.resize(ord.size(), 0);

    min_h = [&](int a, int b) {
      return height[ord[a]] < height[ord[b]] ? a : b;
    };

    vector<int> in_table;
    int max_mask = 0;
    for (int i = 0, j = B, cur = 0, mi; i < ord.size(); i = j, j = min((int)ord.size(), j + B), cur++) {
      mi = i;
     for (int k = i; k < j; k++) {
        id[k] = cur;
        mi = min_h(k, mi);
      }
      in_table.push_back(mi);
    }

    tab = sparse_table(in_table, min_h);

    for (int i = 0, cur = 0, j = 0; i < ord.size() || j < B; ++i, ++j) {
      if (j == B)
        j = 0,  ++cur;
      if (j > 0 && (i >= ord.size() || min_h(i - 1, i) == i - 1))
        type_of_seg[cur] += 1 << (j - 1);
      max_mask = max(type_of_seg[cur], max_mask);
    }

    ans.resize(max_mask + 1);
    for (int i = 0; i < (ord.size() + B - 1) / B; i++) {
      int mask = type_of_seg[i];
      if (!ans[mask].empty())
        continue;
      ans[mask].assign(B, vector<int>(B));

      for (int j = 0; j < B; j++) {
        ans[mask][j][j] = j;
        for (int k = j + 1; k < B; k++) {
          ans[mask][j][k] = ans[mask][j][k - 1];
          if (i * B + k < ord.size())
            ans[mask][j][k] = min_h(ans[mask][j][k] + i * B, k + i * B) - i * B;
        }
      }
    }
  };

  int get(int u, int v) {
    int l = min(tin[u], tin[v]);
    int r = max(tout[u], tout[v]);
    if (id[l] == id[r])
      return ord[get_in_block(id[l], l % B, r % B)];
    int cl = id[l] + 1;
    int cr = id[r] - 1;
    int res = l;
    if (cl <= cr)
      res = tab.get(cl, cr);
    res = min_h(get_in_block(id[l], l % B, B - 1), res);
    res = min_h(get_in_block(id[r], 0, r % B), res);
    return ord[res];
  }

  private:

  int get_in_block(int ib, int l, int r) {
    return ib * B + ans[type_of_seg[ib]][l][r];
  }

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

  struct sparse_table {
    sparse_table() = default;
    sparse_table(const vector<int>& v, const function<int(int,int)>& min_h) : min_h(min_h) {
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
    function<int(int,int)> min_h;
    vector<vector<int>> t;
  } tab;

  vector<vector<int>> gr;
  vector<int> ord;
  vector<int> height;
  vector<int> id;
  vector<int> type_of_seg;
  vector<vector<vector<int>>> ans;
  vector<int> tin, tout;
  function<int(int,int)> min_h;
  const int B;
  int t = 0;
};

void solve() {
  
}


int main() {
  // freopen("lca_rmq.in", "r", stdin);
  // freopen("lca_rmq.out", "w", stdout);
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
