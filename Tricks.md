### 序列转换

对于将一个数组 $a$ 转化为一个 **非严格递增or递减** 的数组 $b$ 代价为 $\sum_{i=1}^{n} \left| {a[i]-b[i]} \right|$ 
如果仅求解最小的费用,可以直接采用 **反悔贪心** 的形式求解
当题意为**严格递增or递减**时,可以预先将 $a[i] - i$ 转换成**非严格**的形式

```cpp
priority_queue<ll> q1;
priority_queue<ll, vector<ll>, greater<ll>> q2;
ll ans = 0;
ll ans2 = 0;
for(int i = 1;i<=n;i++) {
    cin >> x;
    /*x -= i;*/ //当条件为严格递增or递减
    q1.push(x);
    if (x < q1.top()) {
        ans += q1.top() - x;
        q1.pop();
        q1.push(x);
    }
    q2.push(x);
    if (x > q2.top()) {
        ans2 += x - q2.top();
        q2.pop();
        q2.push(x);
    }
}
```

而如果需要转换后的数组 $b$ ,那么就需要用**整体二分**的形式求解

```cpp
vector<ll> a(n + 1), b(n + 1);
auto calc = [&](auto self, ll ld, ll rd, ll ql, ll qr) -> void {
    // 下标区间
    if (ld > rd)
        return;
    // 值域区间
    if (ql >= qr)
        return;
    ll mid = ql + qr >> 1;
    ll sum = 0;
    // 把所有值都归到右区间mid+1
    for (int i = ld; i <= rd; i++) {
        sum += abs(a[i] - (mid + 1));
    }
    ll id = ld - 1;
    ll mn = sum;
    // 枚举归到左区间mid的值的最优边界
    for (int i = ld; i <= rd; i++) {
        sum -= abs(a[i] - (mid + 1));
        sum += abs(a[i] - mid);
        if (sum < mn) {
            mn = sum;
            id = i;
        }
    }
    for (int i = ld; i <= id; i++) {
        b[i] = mid;
    }
    for (int i = id + 1; i <= rd; i++) {
        b[i] = mid + 1;
    }
    self(self, ld, id, ql, mid);
    self(self, id + 1, rd, mid + 1, qr);
};
for(int i = 1;i< n + 1;i++) {
    cin >> a[i];
    a[i] -= i;
}
ll ans = 0;
calc(calc, 1, n, -INF, INF);
for(int i = 1;i< n + 1;i++) { ans += abs(a[i] - b[i]); }
cout << ans << '\n';
for(int i = 1;i< n + 1;i++) { cout << b[i] + i << ' '; }
cout << endl;
```

