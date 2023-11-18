#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define ls p << 1
#define rs p << 1 | 1
/* 扫描线
struct line
{
    ll x1,x2,y,tag;
    bool operator<(const line& a)const{
        return y<a.y;
    }
};
line a[N*2];
ll X[N*2];
void init(){
    for (int i = 1; i <= n; i++)
    {
        ll x1,x2,y1,y2;
        cin >>x1>>y1>>x2>>y2;
        a[i] = {x1,x2,y1,1};
        a[i+n] = {x1,x2,y2,-1};
        X[i] = x1;
        X[i+n] = x2; 
    }
    n*=2;
    sort(a+1,a+n+1);
    sort(X+1,X+1+n);
    ll m = unique(X+1,X+1+n) - X-1;
    Segment seg(m+1);
    seg.build(1,1,m);//离散化预处理
}
*/

class Segment
{
public:
    struct tree
    {
        int l, r;
        int sum, lazy;
        //扫描线的sum区间的真实长度，lazy表示被覆盖的次数
    };
    int num;
    vector<tree> tr;
    vector<int> arr;
    Segment(){};
    template <class T>
    Segment(T n) : num(n + 7)
    {
        tr.resize(4 * num);//扫描线需要开8倍空间，因为叶节点是按线段计算
        arr.resize(num, 1);
    };
    void pushup(ll p)
    {
        tr[p].sum = tr[ls].sum + tr[rs].sum;
    }
    // void pushup(ll p)//扫描线
    // {
    //     if (tr[p].lazy){
    //         tr[p].sum = X[tr[p].r+1]-X[tr[p].l];//是覆盖线段
    //     }else {
    //         tr[p].sum = tr[ls].sum+tr[rs].sum;//不是覆盖线段用容斥取距离，对于周长计算需要再加变量计算经过竖边
    //     }
    // }
    void pushdown(ll p)//扫描线基本不需要pushdown
    {
        tr[ls].sum += tr[p].lazy * (tr[ls].r - tr[ls].l + 1);
        tr[rs].sum += tr[p].lazy * (tr[rs].r - tr[rs].l + 1);
        tr[ls].lazy += tr[p].lazy;
        tr[rs].lazy += tr[p].lazy;
        tr[p].lazy = 0;
    }
    template <class T, class V, class W>
    void build(V l, W r,T p=1ll )
    {
        tr[p].l = l;
        tr[p].r = r;
        tr[p].sum = arr[l];
        tr[p].lazy = 0;
        if (l == r)
            return;
        long long mid = l + r >> 1;
        build(ls, l, mid);
        build(rs, mid + 1, r);
        pushup(p);
    }
    template <class T, class V>
    void update(T x, T y, V z,V p = 1ll )
    {
        if (tr[p].l >= x && tr[p].r <= y)
        {
            tr[p].sum += (tr[p].r - tr[p].l + 1) * z;//扫描线不需要这行
            tr[p].lazy += z;
            return;
        }
        long long mid = tr[p].l + tr[p].r >> 1;
        pushdown(p);
        if (mid >= x)
            update(ls, x, y, z);
        if (mid < y)
            update(rs, x, y, z);
        pushup(p);
    }

    template <class T, class V, class W>
    T query( T x, W y,V p=1ll)
    {
        if (tr[p].l >= x && tr[p].r <= y)
        {
            return tr[p].sum;
        }
        long long mid = tr[p].l + tr[p].r >> 1;
        T sum = 0;
        pushdown(p);
        if (mid >= x)
            sum += query(ls, x, y);
        if (mid < y)
            sum += query(rs, x, y);
        return sum;
    }
};

// void solve()//扫描线向上推移遍历
// {
//     ll ans =0 ;
//     for (int i = 1; i < n; i++)
//     {
//         ll l = lower_bound(X+1,X+1+m,a[i].x1) -X;
//         ll r = lower_bound(X+1,X+1+m,a[i].x2) - X;
//         seg.update(1ll,l,r-1,a[i].tag);//更新的区间右点是开的
//         ans+=seg.tr[1].sum*(a[i+1].y-a[i].y);//矩形覆盖面积，tr[1].sum表示当前扫描到的长度
//     }
//     cout <<ans;
//     cout << endl;
// }
