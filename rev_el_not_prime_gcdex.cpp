#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#define endl "\n" 
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
template<typename T>
using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

constexpr int N = 1e3 + 5;
constexpr int mod = 1e9 + 7;

// simple gcd: gcd(a, b) == gcd(a, b % a)
int gcd(int a, int b) {
  return b ? gcd(b, a % b) : a;
}

// a * x + b * y = gcd(a, b)
// rev el (x, m) == 1: x * x ^ -1 + m * b = 1  
int gcd(int a, int b, int& x, int& y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	int x1, y1;
	int d = gcd(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

int a, b, n, x;

void solve() {
  cin >> n >> x;
  cout << gcd(x, n, a, b) << endl << ((a % n) + n) % n;
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
