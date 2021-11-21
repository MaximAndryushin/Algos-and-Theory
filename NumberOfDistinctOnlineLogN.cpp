#include <bits/stdc++.h>

#define endl "\n" 
using namespace std;

constexpr int N = 1e5 + 5;

// Store in persistent SegTree alive elements closest from left to Current Right, which is version

// Atcoder submission
// https://atcoder.jp/contests/abc174/submissions/27437009

struct Node {
    int sum = 0;
    Node* l = nullptr;
    Node* r = nullptr;
};

Node arr[N * 200];
size_t id = 0;
using pN = Node*;

pN getL(pN v) {
    return v == nullptr ? nullptr : v -> l;
}

pN getR(pN v) {
    return v == nullptr ? nullptr : v -> r;
}

int getS(pN v) {
    return v == nullptr ? 0 : v -> sum;
}

pN newN(int val = 0, pN l = nullptr, pN r = nullptr) {
    return &(arr[id++] = Node{val, l, r});
}

struct SegTree {
    void upd(int pos, int val, pN& v, int l, int r) {
        if (l + 1 == r) {
            v = newN(val);
            return;
        }
        int mid = (l + r) >> 1;
        auto left = getL(v);
        auto right = getR(v);
        if (pos < mid) 
            upd(pos, val, left, l, mid);
        else    
            upd(pos, val, right, mid, r);
        v = newN(getS(left) + getS(right), left, right);
    }

    int get(int l, int r, pN v, int cl, int cr) {
        if (l >= r || getS(v) == 0) 
            return 0;
        if (l == cl && r == cr) 
            return getS(v);
        int mid = (cl + cr) >> 1;
        auto left = getL(v);
        auto right = getR(v);
        return (
            get(l, min(mid, r), left, cl, mid)
            +
            get(max(l, mid), r, right, mid, cr)
        );
    }

    pN root = nullptr;
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

    SegTree tr;
    vector<pN> ver(n);

    for (int i = 0; i < n; i++) {
        if (val[i] != -1) {
            tr.upd(val[i], 0, tr.root, 0, n);
        }
        tr.upd(i, 1, tr.root, 0, n);
        ver[i] = tr.root;
    }

    while(q--) {
        cin >> l >> r;
        l--;
        cout << tr.get(l, r, ver[r - 1], 0, n) << endl;
    }
} 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
        Solve();
    return 0;
}
