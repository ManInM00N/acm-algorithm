ll fa[N][21];
ll dep[N];
void dfs(ll u,ll f){
    fa[u][0] =f;
    dep[u] = dep[f] +1;
    for (int i = 1; i < 21; i++)
    {
        fa[u][i] = fa[fa[u][i-1]][i-1];
    }
    for (int i = h[u]; ~i;i=e[i].next)
    {
        ll v= e[i].to;
        if (v==f) continue;
        dfs(v,u);
    }
    
}
ll lca(ll x,ll y){
    if (dep[y]>dep[x]){
        swap(x,y);
    }
    for (int i = 20; i >=0; i--)
    {
        if (dep[fa[x][i]]>=dep[y]){
            x=fa[x][i];
        }
    }
    if (x==y){
        return y;
    }
    for (int i = 20; i >=0; i--)
    {
        if (fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}