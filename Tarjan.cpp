int dfn[N],low[N];
int idx;
bool ins[N];
// vector<vector<ll>> scc;//强连通分量
// stack<int> stk;//强连通分量
// set<ll> ans;//割点
// ll R;//割点
void dfs(ll u){
    dfn[u] = low[u]=++idx;
    ins[u] =1;
    // stk.push(u);//强连通分量
    // ll son = 0;//割点
    for (int i= h[u]; ~i; i=e[i].next)
    {
        ll v= e[i].to;
        if (!dfn[v]){
            dfs(v);
            low[u] = min(low[u],low[v]);
            //------------割点----------//
            // if (low[v]>=dfn[u]&&u!=R){//v节点能会跳至u及其以后的节点，并且u节点为所假设的根节点R的子节点则u为割点
            //     son++;
            //     ans.insert(u);
            // }
        }else if(ins[v]){
            low[u] = min(low[u],dfn[v]);//
        }
    }
    //------------割点----------//
    // if (son>=2&&u==R){
    //     ans.insert(u);
    // }

    // ----------强连通分量-----------//
    // if (dfn[u]==low[u]){
    //     vector<ll> res;
    //     while (!stk.empty())
    //     {
    //         ll tt = stk.top();
    //         res.push_back(tt);
    //         ins[tt] = 0;
    //         stk.pop();
    //         if (u==tt) break;
    //     }
    //     sort(res.begin(),res.end());
    //     scc.push_back(res);
    // }//强连通分量

    //----------缩点-----------------//
    // if (dfn[u]==low[u]){
    //     ex[u] = ++exnum;
    //     while (!stk.empty())
    //     {
    //         ll tt = stk.top();
    //         stk.pop();
    //         ans[exnum]+=val[tt];
    //         ins[tt] = 0;
    //         ex[tt]=exnum;//将该强连通分量的点存入一个新的点
    //         ++siz[ex[u]];//该强连通分量的大小
    //         if (u==tt) break;
    //     }
    // }
}
void solve(){
    for (int i = 0; i < m; i++)
    {
        cin >>x>>y;
        add(x,y,1);//缩点多为有向图
        // add(y,x,1);//割点时多为无向图
    }
    for (int i = 1; i <= n; i++)
    {
        
        if (!dfn[i]){
        //    R=i;//割点需要考虑从各个点为根时是否可以为割点
           dfs(i);
         }
    }
    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = h[i]; ~j; j=e[j].next)
    //     {
    //         ll v = e[j].to;
    //         if (ex[i]!=ex[v]){
    //             add2(ex[i],ex[v],1);
    //             ru[ex[v]]++;
    //         }
    //     }
    // }//缩点后需考虑是否以存入新图的方式求解
}