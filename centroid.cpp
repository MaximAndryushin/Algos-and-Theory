#include "bits/stdc++.h"

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
#include <concepts>
// #include <ranges>

using namespace std;
// using namespace __gnu_pbds;
// template <typename T>
// using ordered_set = tree<
// T,
// null_type,
// less<T>,
// rb_tree_tag,
// tree_order_statistics_node_update>;

#define endl '\n' 
using ll = long long;
using ld = long double;
// template <typename T = int>
using pii = pair<int, int>;
template<typename T, typename _Compare  = less<T>>
using CompQueue = priority_queue<T, vector<T>, _Compare>;
 
constexpr char delimeter = '\n';
constexpr int N = 2e5 + 5;
constexpr int mod = 998244353;
constexpr int LOG = 18;
constexpr int M = 1e9 + 1;
constexpr ll MAXLL = 1e18 + 1;
constexpr ld EPS = 1e-10;
constexpr int P = 33;
 
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
 
auto rng = std::mt19937(std::random_device()());
 
namespace shit {
namespace detail {
    struct Mint {
        unsigned long long val;
    };
  
    constexpr Mint operator +(Mint a, Mint b) noexcept {
        return Mint{(a.val + b.val) % mod};
    }
 
    constexpr Mint operator *(Mint a, Mint b) noexcept {
        return Mint{(a.val * b.val) % mod};
    }
}
template <typename ...Ts>
constexpr int sum(Ts&&... args) {
    return (detail::Mint{static_cast<unsigned long long>(args)} + ...).val;
}
 
template <typename ...Ts>
constexpr int mul(Ts&&... args) {
    return (detail::Mint{static_cast<unsigned long long>(args)} * ...).val;
}
}

struct Centroid {
    Centroid(const vector<vector<int>>& g, const vector<int>& vals) : gr(g), n(g.size()), vals(vals) {
        used.assign(n, 0);
        sz.assign(n, 0);
        par.resize(n);
        build(0, -1, 0);
    }

    ll get() const {
        return ans;
    }

private:
    int sizes(int v, int p = -1) {
        sz[v] = 1;
        for (int u: gr[v]) {
            if (u == p || used[u]) {
                continue;
            }
            sz[v] += sizes(u, v);
        }
        return sz[v];
    }

    int find_centroid(int v, int p, int s) {
        for (int u: gr[v]) {
            if (u != p && !used[u] && sz[u] * 2 > s) {
                return find_centroid(u, v, s);
            }
        }
        return v;
    }

    void dfs1(int v, int p, int cur, int c) {
        int x = vals[v] ^ cur;
        for (int i = 0; i < SZ; ++i) {
            int add = 0;
            if ((x ^ vals[c]) & (1 << i)) {
                add = cntz[i];
            } else {
                add = cnto[i];
            }
            ans += (ll)add * (1 << i);
        }
        for (int u: gr[v]) {
            if (u != p && !used[u]) {
                dfs1(u, v, x, c);
            }
        }
    }

    void dfs2(int v, int p, int cur, int c) {
        int x = vals[v] ^ cur;
        for (int i = 0; i < SZ; ++i) {
            if (x & (1 << i)) {
                ++cnto[i];
            } else {
                ++cntz[i];
            }
        }
        for (int u: gr[v]) {
            if (u != p && !used[u]) {
                dfs2(u, v, x, c);
            }
        }
    }

    void build(int v, int p, int level) {
        sizes(v);
        int c = find_centroid(v, -1, sz[v]);
        for (int& v: cnto) {
            v = 0;
        }
        for (int& v: cntz) {
            v = 0;
        }
        for (int u: gr[c]) {
            if (!used[u]) {
                dfs1(u, c, 0, c);
                dfs2(u, c, 0, c);
            }
        }
        for (int i = 0; i < SZ; ++i) {
            int add = 0;
            if (vals[c] & (1 << i)) {
                add = cntz[i];
            } else {
                add = cnto[i];
            }
            ans += (ll)add * (1 << i);
        }
        used[c] = 1;
        // if (p != -1) {
        //     par[c].resize(level);
        //     par[c][0] = p;
        //     for (int i = 0; i < par[p].size(); ++i) {
        //         par[c][i + 1] = par[p][i];
        //     }
        // }
        for (int u: gr[c]) {
            if (!used[u]) {
                build(u, c, level + 1);
            }
        }
    }

private:
    ll ans = 0;
    static constexpr int SZ = 20;
    const vector<vector<int>>& gr;
    const vector<int>& vals;
    int n;
    vector<int> used;
    vector<int> sz;
    vector<int> best;
    vector<vector<int>> par;
    array<int, SZ> cntz;
    array<int, SZ> cnto;
};

void Solve() {
    int n;
    cin >> n;
    vector<vector<int>> gr(n);
    vector<int> a(n);
    for (int& v: a) {
        cin >> v;
    }
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        gr[a].push_back(b);
        gr[b].push_back(a);
    }
    Centroid c(gr, a);
    cout << c.get() + std::accumulate(a.begin(), a.end(), 0LL);
}
 
int main() {
    // string name = "back_in_black_chapter_1_input.txt";
    // freopen("test.txt", "r", stdin);
    // freopen(("facebook1/output/" + name).c_str(), "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int tests = 1;
    int test_num = 0;
    // cin >> tests;
    while(tests--) {    
        // auto start = chrono::high_resolution_clock::now();
        // cout << "Case #" << ++test_num << ": ";
        
        Solve();
        cout << endl;
    
        // auto end = chrono::high_resolution_clock::now();
        // cout << endl << (chrono::duration_cast<chrono::duration<double>>(end - start)).count() << endl;
    }
    return 0;
}