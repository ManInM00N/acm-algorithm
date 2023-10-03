ll tr[maxn*2];
ll query(ll x){
    ll res = 0;
    while (x)
    {
        res += tr[x];
        x -= x & (-x);
    }
    return res;
}
void add(ll x,ll z){
    while (x<=n)
    {
        tr[x] += z;
        x += x & (-x);
    }
}
