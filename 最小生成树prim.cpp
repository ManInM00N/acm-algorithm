#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 7;
const int N = 1e4+7;
const int INF = 0x3f3f3f3f;
ll n;
struct node
{
    ll to, next, w;
    node() {}
    node(ll w, ll to) : to(to), next(0), w(w) {}
    friend bool operator<(node a, node b)
    {
        return a.w > b.w;
    }
};
ll nxt, rnxt;
node e[maxn * 2];
ll h[N];
bool vis[N];
ll dis[N];
void add(ll u,ll v,ll w){
    e[++nxt].next=h[u];
    e[nxt].w=w;
    e[nxt].to=v;
    h[u] = nxt;
}
void init(){
    nxt=1;
    memset(h,-1,sizeof(h));
}
ll prim(){//res为-1时表示无生成树(图不连通)，反之返回生成树所需最小和
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    priority_queue<node> q;
    dis[1] =0;
    q.push({0,1});
    ll res = 0;
    ll cnt=0;
    while (!q.empty())
    {
        node tt = q.top();
        q.pop();
        if (vis[tt.to]) continue;
        vis[tt.to] = 1;
        cnt++;
        res+=tt.w;
        for (int i = h[tt.to]; ~i; i=e[i].next)
        {
            ll v=  e[i].to,w=  e[i].w;
            if (dis[v]>w){
                dis[v] = w;
                q.push({dis[v],v});
            }
        }
        
    }
    if (cnt!=n) res=-1;
    return res;
}
