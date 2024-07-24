// clang-format off
struct DSU
{
#define ll long long
    std::vector<ll> f, siz;
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
#undef ll
};
struct DSU_RollBack
{
    #define ll long long
    std::vector<ll> f, siz;
    std::stack<ll> stk;
    ll limit;
    DSU_RollBack() {}
    DSU_RollBack(int n)
    {
        init(n);
    }
    void init(int n)
    {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }
    ll find(int x)
    {
        while (f[x] != x) x = f[x];
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
        if (siz[x] < siz[y])
            std::swap(x,y);
        siz[x] += siz[y];
        f[y] = x;
        limit++;
        stk.push(y);
        return true;
    }
    ll size(int x)
    {
        return siz[find(x)];
    }
    ll roll_back(ll req = 1e9){
        while (!stk.empty()&&req>0)
        {
            ll x = stk.top();
            stk.pop();
            limit--;
            req--;
            siz[f[x]]-=siz[x];
            f[x] = x;
        }
        return limit;
    }
    #undef ll
};
// clang-format on
