### 树剖$O(1)$求lca

```cpp
int que[N << 1], lg[N << 1], f[N << 1][21],dep[N],siz[N],dfn2[N];
void dfs(ll u, ll f) {
    dep[u] = dep[f] + 1;
    siz[u] = 1;
    dfn2[u] = ++idx;
    que[idx] = u;
    ll Maxson = -1;
    fa[u] = f;
    for (int i = h[u]; ~i; i = e[i].next) {
        ll v = e[i].to;
        if (v != f) {
            dfs(v, u);
            siz[u] += siz[v];
            que[++idx] = u;
            if (siz[v] > Maxson) {
                Maxson = siz[v];
                son[u] = v;
            }
        }
    }
}
void buildst() {
    repi(i, 1, idx + 1) f[i][0] = que[i];
    repi(j, 1, 21) {
        for (int i = 1; i + (1 << j) <= idx; ++i) {
            int f1 = f[i][j - 1], f2 = f[i + (1 << j - 1)][j - 1];
            f[i][j] = dep[f1] < dep[f2] ? f1 : f2;
        }
    }
    lg[0] = -1;
    repi(i, 1, idx + 1) lg[i] = lg[i >> 1] + 1;
}
inline int getlca(int u, int v) {
    if (dfn2[u] > dfn2[v])
        swap(u, v);
    u = dfn2[u], v = dfn2[v];
    int kk = lg[v - u + 1], f1 = f[u][kk], f2 = f[v - (1 << kk) + 1][kk];
    return dep[f1] < dep[f2] ? f1 : f2;
}
```



#### 对于连续区间的第K最大值

可以使用主席树求解,如果是求解最大$k$个值可以考虑用$ST$表和优先队列处理,参考[超级钢琴](https://www.luogu.com.cn/problem/P2048) 

```cpp
// ST表处理最大区间
namespace RMQ {
ll sum[N];
ll st[N][20];
void init() {
    for (int i = 1; i <= n; i++)
        st[i][0] = i;
    for (int k = 1; k < 20; k++) {
        for (int i = 1; i <= n; i++) {
            if (i + (1ll << (k - 1)) <= n) {
                ll x = st[i][k - 1];
                ll y = st[i + (1ll << (k - 1))][k - 1];
                if (sum[x] > sum[y]) {
                    st[i][k] = x;
                } else {
                    st[i][k] = y;
                }
            }
        }
    }
}
ll query(ll l, ll r) {
    ll len = log2(r - l + 1);
    if (sum[st[l][len]] > sum[st[r - (1ll << len) + 1][len]]) {
        return st[l][len];
    } else {
        return st[r - (1ll << len) + 1][len];
    }
}
} // namespace RMQ

```

#### 带修区间查询第k

```cpp
// 用树状数组的形式修改和查询主席树,此时主席树rt[x] 表示第 x 个位置有那些值能影响到
auto update = [&](ll pr, ll pos, ll v) {
    ll x = lower_bound(rr.begin() + 1, rr.begin()+1+len, pos) - rr.begin();
    for (; pr <= n; pr += lb(pr)) {
        rt[pr] = seg.Modify(rt[pr], 1, len, x, v);
    }
};
auto quer = [&](ll l, ll r, ll k) {
    vector<ll> ql, qr;
    for (int x = l - 1; x > 0; x -= lb(x)) {
        ql.push_back(rt[x]);
    }
    for (int x = r; x > 0; x -= lb(x)) {
        qr.push_back(rt[x]);
    }
    ll v = seg.Query_Kth_Extent(ql, qr, 1, len, k);
    cout << rr[v]-1 << '\n';
};
```

