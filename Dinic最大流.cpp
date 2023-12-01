ll S, T; // 源点(起点) ,汇点(终点)
ll pre[N]; // 记录前驱点
ll mf[N];  // 记录单边最大流量
ll cur[N], d[N];
bool bfs()
{ // 寻找通往汇点（终点）的增广路
    memset(d, 0, sizeof(d));
    queue<ll> q;
    q.push(S);
    d[S] = 1;
    while (!q.empty())
    {
        ll tt = q.front();
        q.pop();
        for (int i = h[tt]; ~i; i = e[i].next)
        {
            ll v = e[i].to, w = e[i].w;
            if (d[v] == 0 && w)
            {
                d[v] = d[tt] + 1;
                q.push(v);
                if (v == T)
                    return 1;
            }
        }
    }
    return 0;
}
ll dfs(ll now, ll mf)
{
    if (now == T)
        return mf;
    ll sum = 0;
    for (int i = cur[now]; ~i; i = e[i].next)
    {
        ll v = e[i].to, w = e[i].w;
        cur[now] = i; // 当前弧优化
        if (d[v] == d[now] + 1 && w)
        {                                 // 相邻节点并且还有流量
            ll flow = dfs(v, min(mf, w)); // 求得从此路后可能的flow
            e[i].w -= flow;
            e[i ^ 1].w += flow; // 更新残留网
            sum += flow;        // 累加now节点此时可流出的流量
            mf -= flow;         // 相对的now节点剩下的流量减少
            if (mf == 0)
                break; // 余量优化，没东西流出就跳出循环
        }
    }
    if (sum == 0)
        d[now] = 0; // 残枝优化
    return sum;     // 返回总流量
}
ll Dinic()//如果是有备用流量的二分图多重匹配的话，需要从超级源点往一个超级源点2点add(S,S2,k),add(S2,S,0)，然后超级源点2也要对其他点有1的汇路与反边
{//作为多重关系匹配时，对于唯一类型可能需要对其进行拆点(P1231) add(i,i+n,1);add(i+1,i,0);
    ll maxflow = 0;
    while (bfs())
    {
        memcpy(cur, h, sizeof(h)); // cur弧初始化
        maxflow += dfs(S, INF);
    }
    return maxflow;
}