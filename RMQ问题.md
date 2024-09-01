## 对于连续区间的第K最大值

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

