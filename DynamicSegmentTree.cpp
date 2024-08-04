// clang-format off
class info {
  public:
    int l = 0, r = 0;
    ll  sum = 0, lazy = 0;
    info operator+(const info& b) const {
        info a = *this, c;
        c.sum = a.sum + b.sum;
        return c;
    }
};
class DynamicSegmentTree {
  public:
#define ls tr[p].l
#define rs tr[p].r
    vector<info> tr;
    vector<int> rt;
    stack<int> cyc;
    int num;
    int dir;
    DynamicSegmentTree(int _) : num(_) {
        dir = 0;
        tr.resize((num + 1) * 16);
        rt.resize(num + 1, 0);
    }
    inline int AddNode(int p) {
        if (!cyc.empty()){
            p = cyc.top();
            cyc.pop();
            return p;
        }
        ++dir;
        if (!p) {
            tr[dir] = info();
        } else {
            tr[dir] = tr[p];
        }
        return dir;
    }
    inline int AddNode(info _) {
        if (!cyc.empty()){
            int p = cyc.top();
            cyc.pop();
            return p;
        }
        ++dir;
        tr[dir] = _;
        return dir;
    }
    void pushup(int p) { tr[p].sum = tr[ls].sum + tr[rs].sum; }
    void pushdown(int p,ll ld,ll rd) {
        ll mid = ld + rd >> 1;
        // if (!ls)
        //     ls = AddNode({0, 0, 0,});
        // if (!rs)
        //     rs = AddNode({0, 0, 0,});
        if (tr[p].lazy != 0) {
            tr[ls].sum = tr[p].lazy * (mid-ld+1);
            tr[rs].sum = tr[p].lazy * (rd-mid);
            tr[ls].lazy = tr[p].lazy;
            tr[rs].lazy = tr[p].lazy;
        }
        tr[p].lazy = 0;
    }
    int Modify(int p, ll ld, ll rd, ll ql, ll qr, ll z) {
        if (!p) {
            p = AddNode(p);
        }
        if (ql <= ld && rd <= qr) {
            tr[p].sum+=z; 
            tr[p].lazy += z;
            return p;
        }
        pushdown(p,ld,rd);
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
    int Merge(int a, int b, int ld, int rd) {
        if (!a || !b)
            return a + b;
        if (ld == rd) {
            tr[a].sum += tr[b].sum;
            tr[b] = info();
            cyc.push(b);
            return a;
        }

        ll mid = ld + rd >> 1;
        pushdown(a,ld,rd);
        pushdown(b,ld,rd);
        /*
            计算两段区间相互作用可以造成的贡献
            例如计算逆序对数量  
            交换区间: tr[tr[a].l].sum * tr[tr[b].r].sum 
            不交换: tr[tr[a].r].sum + tr[tr[b].l].sum
        */
        tr[a].l = Merge(tr[a].l, tr[b].l, ld, mid);
        tr[a].r = Merge(tr[a].r, tr[b].r, mid + 1, rd);
        pushup(a);
        tr[b] = info();
        cyc.push(b);
        return a;
    }
    // 注意:此处函数为可持久化处理,即保存子树信息,mle的可能非常大!!!
    int merge(int a, int b, int ld, int rd) {
        if (!a || !b)
            return a + b;
        int p = AddNode(0);
        if (ld == rd) {
            tr[p].sum = min(tr[a].sum, tr[b].sum);
            return p;
        }
        ll mid = ld + rd >> 1;
        tr[p].l = merge(tr[a].l, tr[b].l, ld, mid);
        tr[p].r = merge(tr[a].r, tr[b].r, mid + 1, rd);
        pushup(p);
        return p;
    }
    info Query(int p, ll ld, ll rd, ll ql, ll qr) {
        if (ql <= ld && rd <= qr) {
            return tr[p];
        }
        pushdown(p,ld,rd);
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
