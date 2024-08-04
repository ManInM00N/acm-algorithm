class info {
  public:
    int l = 0, r = 0;
    int val = INF;
    info operator+(const info& b) const {
        info a = *this, c;
        c.val = min(a.val, b.val);
        return c;
    }
};
template <class T = long long> class Persistant_Segment_Tree {
  public:
    constexpr static int maxn = 1e5 + 7;
    // 与常规线段树不同  主席树结构体的l,r是对树的索引而不是区间的索引！！
    // 而函数中的参数ld,rd则是对应的区间
    vector<info> tr;
    vector<int> arr, rt; // root[i]为第 i 个版本的根节点编号
    int dir, num;        // dir为节点数  siz为主席树范围
    Persistant_Segment_Tree(int n = maxn) : num(n + 7) {
        dir = 0;
        arr.resize(num, INF);
        rt.resize(num);
        tr.resize(num << 5);
    }
    int Build(int l, int r, int p = 0) {
        p = ++dir;
        if (l == r) {
            tr[p].val = arr[l];
            return p;
        }
        T mid = l + r >> 1;
        tr[p].l = Build(l, mid, tr[p].l);
        tr[p].r = Build(mid + 1, r, tr[p].r);
        pushup(p);
        return p;
    }
    inline int copy(int p) {
        ++dir;
        tr[dir] = tr[p];
        // tr[dir].val ++ ;  //区间第k值的前缀和累加  若为单点历史修改则不需要
        return dir;
    }
    constexpr inline int GetHead(int p) { return rt[p]; }
    void pushup(int p) { tr[p].val = min(tr[tr[p].l].val, tr[tr[p].r].val); }
    int Modify(int p, ll ld, ll rd, ll pos) // 区间第k值的更新  去掉val即可
    {
        p = copy(p);
        if (ld == rd) {
            return p;
        }
        T mid = ld + rd >> 1;
        if (pos <= mid) {
            tr[p].l = Modify(tr[p].l, ld, mid, pos);
        } else {
            tr[p].r = Modify(tr[p].r, mid + 1, rd, pos);
        }
        // pushup(p);
        return p;
    }
    int Modify(int p, int ld, int rd, int pos, int val) // 历史版本单点修改
    {
        p = copy(p);
        if (ld == rd) {
            tr[p].val = min(tr[p].val, val); // 版本修改
            return p;
        }
        T mid = ld + rd >> 1;
        if (pos <= mid) {
            tr[p].l = Modify(tr[p].l, ld, mid, pos, val);
        } else {
            tr[p].r = Modify(tr[p].r, mid + 1, rd, pos, val);
        }
        // pushup(p);
        return p;
    }
    T Query(T ld, T rd, T pos, T p) {
        if (ld == rd) {
            return tr[p].val;
        }
        T mid = ld + rd >> 1;
        if (pos <= mid) {
            return Query(tr[p].l, ld, mid, pos);
        } else {
            return Query(tr[p].r, mid + 1, rd, pos);
        }
    }
    T Query_Kth(T ld, T rd, T ql, T qr, T k) {
        if (ld == rd) {
            return ld;
        }
        T mid = ld + rd >> 1;
        T lsum = tr[tr[qr].l].val - tr[tr[ql].l].val;
        if (lsum >= k) {
            return Query_Kth(ld, mid, tr[ql].l, tr[qr].l, k);
        } else {
            return Query_Kth(mid + 1, rd, tr[ql].r, tr[qr].r, k - lsum);
        }
    }
    info Query(int p, ll ld, ll rd, int ql, int qr) {
        if (ql <= ld && rd <= qr) {
            return tr[p];
        }
        info res;
        ll mid = ld + rd >> 1;
        if (ql <= mid) {
            res = Query(tr[p].l, ld, mid, ql, qr);
            if (qr > mid) {
                res = res + Query(tr[p].r, mid + 1, rd, ql, qr);
            }

        } else {
            res = Query(tr[p].r, mid + 1, rd, ql, qr);
        }
        return res;
    }
};
// 最初的版本p默认为0  -> seg.root[0] = seg.build(l,r)
// 更新的版本 ： root[i] = modify(1,n,pos,val, root[x])
// 选取rt [查询] 的时候,切记不要使用未被使用的节点
