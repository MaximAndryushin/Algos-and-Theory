#include <vector>
#include <utility>


using namespace std;
using pii = pair<int, int>;

struct SegTree {
    struct Node {
        int val = std::numeric_limits<int>::max() / 2;
    };
 
    SegTree(int n): t(n << 2) {}
 
    Node combine(const Node& l, const Node& r) {
        return { .val = min(l.val, r.val) };
    }
 
    void upd(int pos, int val, int i, int l, int r) {
        if (l + 1 == r) {
            t[i].val = val;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos < mid) {
            upd(pos, val, (i << 1) + 1, l, mid);
        } else {
            upd(pos, val, (i << 1) + 2, mid, r);
        }
        t[i] = combine(t[(i << 1) + 1], t[(i << 1) + 2]);
    }
 
    Node get(int l, int r, int i, int cl, int cr) {
        if (l >= r) {
            return {};
        }
        if (l == cl && r == cr) {
            return t[i];
        }
        int mid = (cl + cr) >> 1;
        return combine(
            get(l, min(mid, r), (i << 1) + 1, cl, mid),
            get(max(l, mid), r, (i << 1) + 2, mid, cr)
        );
    }
 
private:
    vector<Node> t;
};


struct HLD {
    HLD(const vector<vector<int>>& g, int start = 0) : n(g.size()), gr(g), tr(g.size()) {
        tin = vector<int>(n, -1);
        tout = vector<int>(n, -1);
        head = vector<int>(n, -1);
        heavy = vector<int>(n, -1);
        par = vector<int>(n, -1);
        depth = vector<int>(n, -1);
 
        depth[start] = 0;
        [[maybe_unused]] auto _ = dfs(start);
        decompose(start, start);
    }
 
    pii get_path(int u, int v) {
        int res = numeric_limits<int>::max() / 2;
        while(1) {
            int hu = head[u];
            int hv = head[v];
 
            if (depth[hu] < depth[hv]) {
                swap(u, v);
                swap(hu, hv);
            }
            
            if (hu == hv) {
                if (depth[u] < depth[v]) {
                    swap(u, v);
                }
                res = min(tr.get(tin[v], tin[u] + 1, 0, 0, n).val, res);
                return {res, v};
            }
 
            res = min(tr.get(tin[hu], tin[u] + 1, 0, 0, n).val, res);
            u = par[head[u]];
        }
        assert(false);
    }
 
    void set(int v, int val) {
        tr.upd(tin[v], val, 0, 0, n);
    }
 
    int parent(int v) {
        return par[v];
    }
 
private:
    int dfs(int v) {
        int sz = 1;
        int max_child = 0;
        for (int u: gr[v]) {
            if (u == par[v]) {
                continue;
            }
            par[u] = v;
            depth[u] = depth[v] + 1;
            int child_sz = dfs(u);
            sz += child_sz;
            if (child_sz > max_child) {
                max_child = child_sz;
                heavy[v] = u;
            }
        }
        return sz;
    }
 
    void decompose(int v, int h) {
        head[v] = h;
        tin[v] = t++;
        if (heavy[v] != -1) {
            decompose(heavy[v], h);
        }
        for (int u: gr[v]) {
            if (u == heavy[v] || u == par[v]) {
                continue;
            }
            decompose(u, u);
        }
        tout[v] = t;
    }
 
private:
    int t = 0;
    int n;
    const vector<vector<int>>& gr;
    vector<int> tin, tout;
    vector<int> head;
    vector<int> par;
    vector<int> heavy;
    vector<int> depth;
 
    SegTree tr;
};