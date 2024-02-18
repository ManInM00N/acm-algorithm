ll fa[N][21];
ll idx = 0;
ll dfn[N];
ll dep[N];
void dfs(ll u,ll f){
    fa[u][0] =f;
    dfn[u] = ++idx;
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

void build_virtual_tree( vector<ll> a){
    //对dfn序排序 保证lca建树的有效性
    sort(a.begin(),a.end(),[&](ll i,ll j){
        return dfn[i]<dfn[j];
    });
    vector<ll> newP;
    rep(i,a.size()-1){
        newP.push_back(a[i]);
        newP.push_back(lca(a[i+1],a[i]));
    }
    newP.push_back(a.back());
    // imp.push_back(1);   //在部分虚树中若要求根为1需添加
    sort(newP.begin(),newP.end(),[&](ll i,ll j){
        return dfn[i]<dfn[j];
    });
    //重新排序并去重
    ll len = unique(newP.begin(),newP.end())-newP.begin();
    //切忌忘记清除原图
    rep(i,len){
        h[newP[i]]  = -1;
    }
    nxt= 1;
    rep(i,len-1){
        ll f=  lca(newP[i],newP[i+1]);
        add(f,newP[i+1],1);
    }
    //建完树后  newP[0:len]为树上节点  a为关键节点
}