int dfn[N],low[N];
int idx;
bool ins[N];
// vector<vector<ll>> scc;//强连通分量
// stack<int> stk;//强连通分量
// ll[N] scc 求解2-SAT时 记录当前点所在的强连通分量
void Tarjan(ll u){
    dfn[u] = low[u]=++idx;
    ins[u] =1;
    // stk.push(u);//强连通分量
    for (int i= h[u]; ~i; i=e[i].next)
    {
        ll v= e[i].to;
        if (!dfn[v]){
            Tarjan(v);
            low[u] = min(low[u],low[v]);
        }else if(ins[v]){
            low[u] = min(low[u],dfn[v]);//
        }
    }
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
    //注意：而用于求解2-SAT问题时若变量A与!A在同一个连通分量则为矛盾
    //         ++siz[ex[u]];//该强连通分量的大小
    //         if (u==tt) break;
    //     }
    // }
}
void solve(){
    for (int i = 0; i < m; i++)
    {
        cin >>x>>y;
        add(x,y,1);//缩点为有向图
        /*
            对于2-SAT存在变量A与变量B的某种约束
            需转化为
            cin >>x>>a>>y>>b;
            // [1, n] -> false, [n+1, 2n] -> true 
            // x_a, x_b 均不满足不能同时成立 //
            add(i+(a^1)*n, j+b*n,1);
            add(j+(b^1)*n, i+a*n,1);
        */
    }
    for (int i = 1; i <= n; i++)
    {
        if (!dfn[i]){
           Tarjan(i);
        }
    }
    /*  2-SAT求解
        bool ok =1;
        for (int i = 1; i <= n; i++)
        {
            if(scc[i]==scc[n+i]){
                ok =0;
            }
        }
        for (int i = 1; i <= n; i++)
        {
            if (scc[i]>scc[i+n])//强联通分量编号越小 -> 拓扑序越大 -> 越优
                printf("1");
            else printf("0");
            printf(" ");
        }
    */
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