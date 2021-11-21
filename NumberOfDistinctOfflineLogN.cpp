#include <bits/stdc++.h>

#define endl "\n" 
using namespace std;

// Sort Queries (l, r) by ascending r
// Keep alive elements closest to current r

// Atcoder Submission
// https://atcoder.jp/contests/abc174/submissions/27397019

struct SegTree {
    SegTree(int n) : t(n << 2) {}

    void upd(int pos, int val, int i, int l, int r) {
        if (l + 1 == r) {
            t[i] = val;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos < mid)
            upd(pos, val, (i << 1) + 1, l, mid);
        else 
            upd(pos, val, (i << 1) + 2, mid, r);
        t[i] = (t[(i << 1) + 1] + t[(i << 1) + 2]);
    }

    int get(int l, int r, int i, int cl, int cr) {
        if (l >= r)
            return 0;
        if (l == cl && r == cr)
           return t[i];
        int mid = (cl + cr) >> 1;
        return (
            get(l, min(mid, r), (i << 1) + 1, cl, mid)
            +
            get(max(l, mid), r, (i << 1) + 2, mid, cr)
        );
    }

private: 
    vector<int> t;
};

void Solve() {
    int n, q;
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
    
    vector<tuple<int, int, int>> queries(q);
    int id = 0;
    for (auto& [l, r, i]: queries) {
        cin >> l >> r;
        --l;
        i = id++;
    }

    sort(queries.begin(), queries.end(), [](const auto& a, const auto& b) {
        return get<1>(a) < get<1>(b);
    });

    SegTree tr(n);
    vector<int> ans(q);
    int cur = 0;
    for (auto [l, r, i]: queries) {
        while(cur < r) {
            if (val[cur] != -1)
                tr.upd(val[cur], 0, 0, 0, n);
            tr.upd(cur, 1, 0, 0, n);
            ++cur; 
        }
        ans[i] = tr.get(l, r, 0, 0, n);
    }

    for (int v: ans) {
        cout << v << endl;
    }
} 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
        Solve();
    return 0;
}
