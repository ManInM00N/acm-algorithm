template<class T  = long long>
struct BIT
{
    vector<T> tr;
    T n;
    BIT(){}
    BIT(T n): n(n){
        tr.resize(n*2+7);
    }
    ll query(int x){
        ll res = 0;
        while (x)
        {
            res += tr[x];
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
