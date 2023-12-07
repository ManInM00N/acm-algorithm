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
    void build(T p=1ll,V l, W r )
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
    void update(V p = 1ll,T x, T y, V z )
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
    T query( V p=1ll, W y,T x)
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
//--------------------树链剖分-------------------//
// ll val[N],dep[N],siz[N],out[N],son[N];
// ll fa[N],dfn[N],idx=0,top[N];
// Segment seg;
// void dfs(ll u, ll f){
//     dep[u] = dep[f] +1;    
//     siz[u] = 1;
//     ll Maxson = -1;
//     fa[u] = f;
//     for (int i = h[u]; ~i; i=e[i].next)
//     {
//         ll v= e[i].to;
//         if (v!=f){
//             dfs(v,u);
//             siz[u]+=siz[v];
//             if (siz[v]>Maxson){
//                 Maxson = siz[v];
//                 son[u] = v;
//             }
//         }
//     }
// }
// void dfs2(ll u,ll topf){//树剖的topf为此重链的顶部
//     dfn[u] = ++idx;//dfn序构造线段树
//     seg.arr[idx] = val[u];
//     top[u] = topf;//此点所在重链的顶部
//     if (!son[u]) return;
//     dfs2(son[u],topf);//优先重儿子
//     for (int i = h[u]; ~i; i=e[i].next)
//     {
//         ll v=e[i].to;
//         if (!dfn[v]){
//             dfs2(v,v);
//         }   
//     }
// }
// void Treeupdate(ll u,ll z){
//     seg.update(1ll,dfn[u],dfn[u]+siz[u]-1,z);
// }
// ll Treequery(ll u){
//     return seg.query(1ll,dfn[u],dfn[u]+siz[u]-1)%mod;
// }
// void Roadupdate(ll u,ll v,ll z){
//     while (top[v]!=top[u])//通过重链来向上跳,类似于倍增
//     {
//         if (dep[top[u]]>dep[top[v]]){//注意是重链深度大的跳,否则会出现重链节点多次取值
//             swap(u,v);
//         }
//         seg.update(1ll,dfn[top[v]],dfn[v],z);
//         v = fa[top[v]];
//     }
//     if (dep[u]>dep[v]) swap(u,v);
//     seg.update(1ll,dfn[u],dfn[v],z);
// }

// ll Roadquery(ll u, ll v){
//     ll sum = 0;
//     while (top[v]!=top[u])
//     {
//         if (dep[top[u]]>dep[top[v]]){
//             swap(u,v);
//         }
//         sum+=seg.query(1ll,dfn[top[v]],dfn[v]);
//         sum%=mod;
//         v = fa[top[v]];
//         /* code */
//     }
//     if (dep[u]>dep[v]) swap(u,v);
//     sum +=seg.query(1ll,dfn[u],dfn[v]);
//     sum%=mod;
//     return sum;
// }
//--------------------树链剖分-------------------//
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
