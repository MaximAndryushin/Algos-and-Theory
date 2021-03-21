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
constexpr pii NEUT = pii(-1, 0); 
constexpr int mod = 1e9 + 7; 

template<typename T, T (*F)(const T&, const T&)>
struct sparse_table {
  sparse_table() = default;

  sparse_table(const vector<T>& v) {
    int sz = v.size();
    if (lg.size() < sz + 1) {
      int cur = max((int)lg.size(), 2);
      lg.resize(sz + 1);
      for (int i = cur; i <= sz; i++)
        lg[i] = lg[i >> 1] + 1;
    }
    t.assign(lg[sz] + 1, vector<T>(sz));
    for (int i = 0; i < sz; i++) 
      t[0][i] = v[i];
    for (int i = 1; i <= lg[sz]; i++) 
      for (int j = 0; j + (1 << (i - 1)) < sz; j++)
        t[i][j] = F(t[i - 1][j], t[i - 1][j + (1 << (i - 1))]);
  }

  T get(int l, int r) {
    int sz = lg[(r - l + 1)];
    return F(t[sz][l], t[sz][r - (1 << sz) + 1]);
  }

  private:
  inline static vector<int> lg = vector<int>();

  vector<vector<T>> t;
};

int myop(const int& a, const int& b) {
  
}

/* 
разбиваем отрезки на непересекающиеся, каждый отрезок делится пополам (левая часть считает суффикс, правая - префикс)
таким образом для ответа на запрос (l, r) необходимо найти отрезок, левый ребенок, которого содержит l, а правый r,
и спросить значения на суффиксе/префиксе соответсвтенно 
запрос на полуинтервале [l, r)
*/
template<typename T, T (*F)(const T&, const T&), const T& neutral>
struct disjoint_sparse_table {
  disjoint_sparse_table() = default;

  disjoint_sparse_table(const vector<T>& v) {
    int sz = v.size();
    int h = highest_bit(sz + 1);
    t.assign(h + 1, vector<T>(sz + 1, neutral));
    for (int i = 0, len; i <= h; i++) {
      len = (1 << i);
      for (int j = len; j < sz + len; j += (len << 1)) {
        for (int r = j + 1; r < min(sz + 1, j + len); r++)
          t[i][r] = F(v[r - 1], t[i][r - 1]);
        for (int l = min(j - 1, sz - 1); l >= j - len; l--)
          t[i][l] = F(t[i][l + 1], v[l]);
      }
    }
  }

  T get(int l, int r) {
    int sz = highest_bit(l ^ r);
    return F(t[sz][r], t[sz][l]);
  }

  private:

  int highest_bit(int number) {
    return 31 - __builtin_clz(number);
  }

  vector<vector<T>> t;
};

pii func(const pii& l, const pii& r) {
  if (l.first > r.first) 
    return l;
  if (r.first > l.first)
    return r;
  return {l.first, l.second + r.second};
}

ll n, q, x, y, z, t, last = 0, l, r, ans = 1;
vector<pii> vec;

void solve() {
 
  cin >> n;
  vec.resize(n);
  for (auto& [v, c]: vec) {
    cin >> v;
    c = 1;
  }
  disjoint_sparse_table<pii, func, NEUT> tab(vec);
  cin >> q >> x >> y >> z >> t;
  while(q--) {
    l = (last * x + y) % n + 1;
    r = (last * z + t) % n + 1;
    if (l > r)
      swap(l, r);
    auto [min, cnt] = tab.get(l - 1, r);
    ans = (ans * cnt) % mod;
    last = cnt;
  }
  cout << ans;
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
