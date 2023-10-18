struct BIT
{
    vector<int> tr;
    const int p = 998244353;
    BIT(){}
    template<class T>BIT(T n){
        tr.resize(n*2+7);
    }
    ll query(int x){
        ll res = 0;
        while (x)
        {
            res += tr[x];
            res%=p;
            x -= x & (-x);
        }
        return res;
    }
    void add(int x,ll z){
        while (x<=n)
        {
            tr[x] += z;
            x += x & (-x);
        }
    }
};