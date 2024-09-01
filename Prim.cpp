auto prim = [&](ll st) -> ll {
    dis[st] = 0;
    priority_queue<node> q;
    q.push({0, st});
    ll res = 0;
    while (!q.empty()) {
        node tt = q.top();
        q.pop();
        if (in[tt.to])
            continue;
        in[tt.to] = 1;
        res++;
        sum += tt.w;
        for (int i = h[tt.to]; ~i; i = e[i].next) {
            ll v = e[i].to;
            ll w = e[i].w;
            if (!is[v])
                continue;

            if (dis[v] > w) {
                dis[v] = w;
                q.push({dis[v], v});
            }
        }
    }
    if (res != num) {
        sum = -1; // sum为外部变量,表示最小花费
    }
    return res;
};
