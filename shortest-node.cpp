
bool vis[N];
ll dis[N];
void dij(ll st)
{
    memset(dis, 0x3f, sizeof(dis));
    dis[st] = 0;
    priority_queue<node> q;
    q.push({0, st});
    while (!q.empty())
    {
        node tt = q.top();
        q.pop();
        if (vis[tt.to])
            continue;
        vis[tt.to] = 1;
        for (int i = h[tt.to]; ~i; i = e[i].next)
        {
            ll v = e[i].to, w = e[i].w;
            if (dis[v] > tt.w + w)
            {
                dis[v] = tt.w + w;
                q.push({dis[v], v});
            }
        }
    }
}
ll cnt[N];
bool spfa(ll fi)
{
    //求解差分约束时 有条件 x-y<=z;
    //需要add(y,x,z);
    //且要对0作根节点来遍历图 add(0,i,0);  spfa(0);
    queue<ll> q;
    q.push(fi);
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[fi] = 0;
    vis[fi] = 1;
    cnt[fi] = 1;
    while (!q.empty())
    {
        ll tt = q.front();
        q.pop();
        vis[tt] = 0;
        for (int i = h[tt]; ~i; i = e[i].next)
        {
            ll v = e[i].to;
            ll w = e[i].w;
            if (dis[v] > dis[tt] + w)
            {
                dis[v] = dis[tt] + w;
                if (!vis[v])
                {
                    cnt[v]++;
                    if (cnt[v]>n){
                        return 0;
                    }
                    q.push(v);
                    vis[v] = 1;
                }
            }
        }
    }
    // 非负环dis数组则为fi到[1,n]最短路.
    return 1;
}