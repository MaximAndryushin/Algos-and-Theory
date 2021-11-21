#include <bits/stdc++.h>
 
#define endl "\n" 
using namespace std;

// Store sorted vectors in SegTree Node 
// and just binary search for each Node
 
struct SegTree {
    SegTree(const vector<int>& v) : t(v.size() << 2) {
        build(0, 0, v.size(), v);
    }
 
    void build(int i, int l, int r, const vector<int>& v) {
        if (l >= r)
            return;
        if (l + 1 == r) {
            t[i] = {v[l]};
            return;
        }
        int mid = (l + r) >> 1;
        build((i << 1) + 1, l, mid, v);
        build((i << 1) + 2, mid, r, v);
        merge(
            t[(i << 1) + 1].begin(), t[(i << 1) + 1].end(),
            t[(i << 1) + 2].begin(), t[(i << 1) + 2].end(),
            back_inserter(t[i]));
    }
 
    int get(int l, int r, int v, int i, int cl, int cr) {
        if (l >= r)
            return 0;
        if (l == cl && r == cr) {
            auto it = lower_bound(t[i].begin(), t[i].end(), v);
            return distance(t[i].begin(), it);
        }
        int mid = (cl + cr) >> 1;
        return (
            get(l, min(mid, r), v, (i << 1) + 1, cl, mid)
            +
            get(max(l, mid), r, v, (i << 1) + 2, mid, cr)
        );
    }
 
private: 
    vector<vector<int>> t;
};
 
void Solve() {
    int n, q, l, r;
    cin >> n >> q;
    vector<int> val(n);
    map<int, int> mp;
 
    for (int i = 0, v; i < n; ++i) {
        cin >> v;
        if (mp.count(v)) {
            val[i] = mp[v];
        } else {
            val[i] = -1;
        }
        mp[v] = i;
    }
    
    SegTree tr(val);
 
    while(q--) {
        cin >> l >> r;
        l--;
        cout << tr.get(l, r, l, 0, 0, n) << endl;
    }
} 
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
        Solve();
    return 0;
}
