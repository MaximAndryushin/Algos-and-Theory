

struct DSegTree {
    struct SegTree {
        struct Node {
            ll push = 0;
            ll val = 0;
        };

        SegTree(int n) : t(n << 2) {};

        void push(int i, int l, int m, int r) {
            if (t[i].push == 0)
                return;
            t[(i << 1) + 1].val += t[i].push * (m - l);
            t[(i << 1) + 2].val += t[i].push * (r - m);

            t[(i << 1) + 1].push += t[i].push;
            t[(i << 1) + 2].push += t[i].push;
            
            t[i].push = 0;
        }

        Node combine(const Node& l, const Node& r) {
            return {
                .push = 0,
                .val = l.val + r.val
            };
        }

        void upd(int l, int r, ll v, int i, int cl, int cr) {
            if (l >= r)
                return;
            if (l == cl && r == cr) {
                t[i].val += v * (r - l);
                t[i].push += v;
                return;
            }
            int mid = (cl + cr) >> 1;
            push(i, cl, mid, cr);

            upd(l, min(mid, r), v, (i << 1) + 1, cl, mid);
            upd(max(l, mid), r, v, (i << 1) + 2, mid, cr);

            t[i] = combine(t[(i << 1) + 1], t[(i << 1) + 2]);
        }

        Node get(int l, int r, int i, int cl, int cr) {
            if (l >= r) 
                return {};
            if (l == cl && r == cr)
                return t[i];

            int mid = (cl + cr) >> 1;
            push(i, cl, mid, cr);

            return combine(
                get(l, min(mid, r), (i << 1) + 1, cl, mid),
                get(max(l, mid), r, (i << 1) + 2, mid, cr)
            );
        }
    private:
        vector<Node> t;
    };

    struct Node {
        SegTree val;
        SegTree add;
    };

    DSegTree(int n, int m) : n_(n), m_(m), t(n << 2, {{m}, {m}}) {};

    void upd(int lx, int rx, int ly, int ry, ll v) {
        upd(lx, rx, ly, ry, v, 0, 0, n_);
    }

    ll get(int lx, int rx, int ly, int ry) {
        return get(lx, rx, ly, ry, 0, 0, n_);
    }

private:
    ll upd(int lx, int rx, int ly, int ry, ll v, int i, int cl, int cr) {
        if (lx >= rx)
            return 0;
        if (lx == cl && rx == cr) {
            t[i].add.upd(ly, ry, v, 0, 0, m_);

            return v * (cr - cl);
        }

        int mid = (cl + cr) >> 1;

        auto res = (
            upd(lx, min(mid, rx), ly, ry, v, (i << 1) + 1, cl, mid)
            +
            upd(max(lx, mid), rx, ly, ry, v, (i << 1) + 2, mid, cr)
        );

        t[i].val.upd(ly, ry, res, 0, 0, m_);

        return res;
    }

    ll get(int lx, int rx, int ly, int ry, int i, int cl, int cr) {
        if (lx >= rx)
            return 0;
        if (lx == cl && rx == cr) {
            return (
                t[i].val.get(ly, ry, 0, 0, m_).val 
                + 
                (cr - cl) * t[i].add.get(ly, ry, 0, 0, m_).val
            );
        }

        int mid = (cl + cr) >> 1;

        ll dop = t[i].add.get(ly, ry, 0, 0, m_).val * (rx - lx);

        ll ret = (
            get(lx, min(mid, rx), ly, ry, (i << 1) + 1, cl, mid)
            +
            get(max(lx, mid), rx, ly, ry, (i << 1) + 2, mid, cr)
        );

        return dop + ret;
    }

private:
    int n_, m_;
    vector<Node> t;
};