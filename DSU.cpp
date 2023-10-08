struct DSU
{
    vector<ll> f, siz;
    DSU() {}
    DSU(int n)
    {
        init(n);
    }
    void init(int n)
    {
        f.resize(n);
        iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }
    ll find(int x)
    {
        if (f[x]==x){
            return x;
        }
        //ll tt = f[x];
        f[x] = find(f[x]);
        // val[x]  +=val[t];//带权并查集
        return f[x];
    }
    bool same(int x, int y)
    {
        return find(x) == find(y);
    }
    bool merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return false;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x)
    {
        return siz[find(x)];
    }
};
