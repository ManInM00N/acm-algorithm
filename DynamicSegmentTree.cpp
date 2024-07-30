// clang-format off
class info {
  public:
    int l = 0, r = 0;
    ll val = 0, sum = 0, lazy = 0;
    ll ld = 0, rd = 0;
    info operator+(const info& b) const {
        info a = *this, c;
        c.ld = a.ld;
        c.rd = b.rd;
        c.sum = a.sum + b.sum;
        c.val = a.val + b.val;
        return c;
    }
};
class DynamicSegmentTree {
  public:
#define ls tr[p].l
#define rs tr[p].r
    vector<info> tr;
    vector<int> rt;
    int num;
    int dir;
    DynamicSegmentTree(int _) : num(_) {
        dir = 0;
        tr.resize((num + 1) << 6);
        rt.resize(num + 1, 0);
    }
    inline int AddNode(int p) {
        ++dir;
        if (!p) {
            tr[dir] = info();
        } else {
            tr[dir] = tr[p];
        }
        return dir;
    }
    inline int AddNode(info _) {
        ++dir;
        tr[dir] = _;
        return dir;
    }
    void pushup(int p) { tr[p].sum = tr[ls].sum + tr[rs].sum; }
    void pushdown(int p) {
        if (tr[p].ld == tr[p].rd) {
            return;
        }
        ll mid = tr[p].ld + tr[p].rd >> 1;
        if (!ls)
            ls = AddNode({0, 0, 0, 0, 0, tr[p].ld, mid});
        if (!rs)
            rs = AddNode({0, 0, 0, 0, 0, mid + 1, tr[p].rd});
        if (tr[p].lazy != -1) {
            tr[ls].sum = tr[p].lazy * (tr[ls].rd - tr[ls].ld + 1);
            tr[rs].sum = tr[p].lazy * (tr[rs].rd - tr[rs].ld + 1);
            tr[ls].lazy = tr[p].lazy;
            tr[rs].lazy = tr[p].lazy;
        }
        tr[p].lazy = -1;
    }
    int Modify(int p, ll ld, ll rd, ll ql, ll qr, ll z) {
        if (!p) {
            p = AddNode(p);
            tr[p].ld = ld;
            tr[p].rd = rd;
            tr[p].sum = rd - ld + 1;
            tr[p].lazy = -1;
        }
        if (ql <= ld && rd <= qr) {
            tr[p].sum = z * (rd - ld + 1);
            tr[p].lazy = z;
            return p;
        }
        pushdown(p);
        ll mid = ld + rd >> 1;
        if (ql <= mid) {
            tr[p].l = Modify(tr[p].l, ld, mid, ql, qr, z);
        }
        if (qr > mid) {
            tr[p].r = Modify(tr[p].r, mid + 1, rd, ql, qr, z);
        }
        pushup(p);
        return p;
    }
    int Merge(int a, int b, int l, int r) {
        if (!a)
            return b;
        if (!b)
            return a;
        if (l == r) {
            return a;
        }
        ll mid = l + r >> 1;
        tr[a].l = Merge(tr[a].l, tr[b].l, l, mid);
        tr[a].r = Merge(tr[a].r, tr[b].r, mid + 1, r);
        return a;
    }
    info Query(int p, ll ld, ll rd, ll ql, ll qr) {
        if (ql <= ld && rd <= qr) {
            return tr[p];
        }
        pushdown(p);
        info res;
        ll mid = ld + rd >> 1;
        if (ql <= mid) {
            res = Query(ls, ld, mid, ql, qr);
            if (qr > mid) {
                res = res + Query(rs, mid + 1, rd, ql, qr);
            }
        } else {
            res = Query(rs, mid + 1, rd, ql, qr);
        }
        return res;
    }
#undef ls
#undef rs
};
/*
    为了方便与主席树同步
    使用seg.rt[0] = seg.Modify(seg.rt[0],1,n,x,y,z);
 */
// clang-format on
