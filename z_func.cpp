#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#define endl "\n" 
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using ordered_set = __gnu_pbds::tree<int, __gnu_pbds::null_type,less<int>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

constexpr int N = 2e3 + 5;

string s;

void z_func(string& str, vector<int>& z) {
  int n = str.size();
  z.assign(n, 0);
  for (int i = 1, l = 0, r = 0; i < n; i++) {
    z[i] = (i > r ? 0 : min(r - i, z[i - l]));
    while(i + z[i] < n && str[z[i]] == str[i + z[i]])
      z[i]++;
    if (r < i + z[i])
      r = i + z[i], l = i;
  }
}

void solve() {
  
}


int main() {
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