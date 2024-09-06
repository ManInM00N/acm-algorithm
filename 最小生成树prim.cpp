bool vis[N];
ll dis[N];
ll prim() { // res为-1时表示无生成树(图不连通)，反之返回生成树所需最小和
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    priority_queue<node> q;
    dis[1] = 0;
    q.push({0, 1});
    ll res = 0;
    ll cnt = 0;
    while (!q.empty()) {
        node tt = q.top();
        q.pop();
        if (vis[tt.to])
            continue;
        vis[tt.to] = 1;
        cnt++;
        res += tt.w;
        for (int i = h[tt.to]; ~i; i = e[i].next) {
            ll v = e[i].to, w = e[i].w;
            if (dis[v] > w) {
                dis[v] = w;
                q.push({dis[v], v});
            }
        }
    }
    if (cnt != n)
        res = -1;
    return res;
}
