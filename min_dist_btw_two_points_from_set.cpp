#include "bits/stdc++.h"

using namespace std;

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// template <typename T>
// using ordered_set = tree<
// T,
// null_type,
// less<T>,
// rb_tree_tag,
// tree_order_statistics_node_update>;

#define endl "\n" 
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

constexpr char delimeter = '\n';
constexpr int N = 1e7 + 5;
constexpr int mod = 1e9 + 7;
constexpr int LOG = 18;
constexpr int M = 1e9 + 1;
constexpr ll MAXLL = 1e18 + 1;
constexpr ld EPS = 1e-9;

bool NEAR(ld a, ld b, ld eps = EPS) {
    return b - eps < a && a < b + eps; 
}

template <typename ...Ts>
void dout(Ts&&... args) {
    ((cout << args << delimeter), ...) << endl;
}

template <typename ...Ts>
void vout(Ts&&... args) {
    dout(forward<Ts>(args)...);
    exit(0);
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());


ll get_dist(const pii& a, const pii& b) {
    return ll(a.first - b.first) * ll(a.first - b.first) + ll(a.second - b.second) * ll(a.second - b.second);
}

const auto cmp_y = [](const auto& a, const auto& b) {
    return a.second < b.second;
};

ll get(int l, int r, vector<pii>& a, vector<pii>& buff) {
    if (r - l < 4) {
        ll ans = numeric_limits<ll>::max(); 
        for (int i = l; i < r; ++i)
			for (int j = i + 1; j < r; ++j) {
                ans = min(ans, get_dist(a[i], a[j]));
            }
		sort(a.begin() + l, a.begin() + r, cmp_y);
		return ans;
    }
    int mid = (l + r) >> 1;
    int mx = a[mid].first;
    ll ans = min(get(l, mid, a, buff), get(mid, r, a, buff));
    merge(a.begin() + l, a.begin() + mid, a.begin() + mid, a.begin() + r, buff.begin(), cmp_y);
    copy(buff.begin(), buff.begin() + r - l, a.begin() + l);

    int tsz = 0;
	for (int i = l; i < r; ++i) {
        if (ll(a[i].first - mx) * ll(a[i].first - mx) < ans) {
			for (int j = tsz - 1; j >= 0 && ll(a[i].second - buff[j].second) * ll(a[i].second - buff[j].second) < ans; --j)
				ans = min(ans, get_dist(a[i], buff[j]));
			buff[tsz++] = a[i];
		}
    }
    return ans;
}

void Solve() {
    int n;
    cin >> n;
    vector<pii> a(n);
    int sum = 0;
    int i = 0;
    for (auto& [x, y]: a) {
        cin >> x;
        x += sum;
        sum = x; 
        y = i;
        ++i;
    }

    sort(a.begin(), a.end());

    vector<pii> buff(n);

    cout << get(0, n, a, buff);
}

int main() {
    // freopen("ans.txt", "r", stdin);
    // freopen("fb/second/answer.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int tests = 1;
    int test_num = 0;
    // cin >> tests;
    while(tests--) {
        //auto start = chrono::high_resolution_clock::now();
        // cout << "Case #" << ++test_num << ": ";
        Solve();
        cout << endl;
        // auto end = chrono::high_resolution_clock::now();
        // cout << endl << (chrono::duration_cast<chrono::duration<double>>(end - start)).count();
    }
    return 0;
}
