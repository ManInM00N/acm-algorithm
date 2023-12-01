struct node
{
    ll to, next, w,flow;
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
void add(ll u,ll v,ll w,ll flow){
    e[++nxt].next=h[u];
    e[nxt].w=w;
    e[nxt].to=v;
    e[nxt].flow=flow;
    h[u] = nxt;
}
void init(){
    nxt=1;
    for (int i = 0; i <= n*2+m; i++)//网络流使用2*n+7
    {
        h[i] = -1;
    }
}
ll S, T; // 源点(起点) ,汇点(终点)
ll mf[N];  // 记录单边最大流量
ll cur[N]; //当前弧优化
int  d[N];
ll maxflow, mincost;
bool spfa(){
    memset(d,0x3f,sizeof(d));
    queue<ll> q;
    q.push(S);
    vis[S] = 1;
    d[S] = 0;
    while (!q.empty())
    {
        ll tt =q.front();
        q.pop();
        vis[tt] = 0;
        for(int i = h[tt];~i;i=e[i].next){
            ll v= e[i].to;
            ll w = e[i].w;
            ll flow = e[i].flow;
            if (flow&&d[v]>d[tt]+w){//有流量且是最短路;
                d[v] = d[tt]+w;
                if (!vis[v]){
                    vis[v] =1;
                    q.push(v);
                }
            }
        }
    }
    return d[T]!=INF;//检验是否有剩余流量
}
ll dfs(ll now, ll mf)
{
    if (now == T)
        return mf;
    ll sum = 0;
    vis[now] = 1;
    for (int i = cur[now]; ~i; i = e[i].next)
    {
        ll v = e[i].to, w = e[i].w;
        ll f = e[i].flow;
        cur[now] = i; // 当前弧优化
        if (!vis[v] && f && d[v] == d[now] + w) // 按层推流，费用流是按距离推流
        {                                       // 相邻节点并且还有流量
            ll flow = dfs(v, min(mf, f));       // 求得从此路后可能的flow
            if (flow == 0)
                continue;
            e[i].flow -= flow;
            e[i ^ 1].flow += flow; // 更新残留网
            sum += flow;           // 累加now节点此时可流出的流量
            mf -= flow;            // 相对的now节点剩下的流量减少
            mincost += flow * w;
            if (mf == 0)
                break; // 余量优化，没东西流出就跳出循环
        }
    }
    vis[now] = 0;
    return sum;     // 返回总流量
}
void MCMF()
{
    maxflow = 0;
    mincost = 0 ;
    memset(vis, 0, sizeof(vis));
    while (spfa())
    {
        memcpy(cur, h, sizeof(h)); // cur弧初始化
        maxflow+=dfs(S,INF); 
   }
}
void solve()
{
    string ss;
    cin >>n ;
    cin >>m;
    cin>>S>>T;
    init();
    for (int i = 0; i < m; i++)
    {
        cin >>x>>y>>z>>k;
        add(x,y,k,z);//建边原理：费用正向边为w，反向边为-w，容量与最大流一样正边为z，反边为0
        add(y,x,-k,0);
    }
    MCMF();
    cout << maxflow<< ' '<< mincost;
    cout << endl;
}