

int dfn[N],low[N];
int idx;
stack<ll> stk;


//------------------割点/点双连通分量-------------------//

ll num = 0 ;
ll cut_point[N];//割点
ll Root;//假设根
vector<ll> dcc[N];//点双连通分量

void Tarjan(ll u){//割点
    dfn[u] = low[u]=++idx;
    stk.push(u);
    if (u == Root && h[u] == -1) { //孤立点
		dcc[++num].push_back(u);
		return;
	}
    ll son = 0;
    for (int i= h[u]; ~i; i=e[i].next)
    {
        ll v= e[i].to;
        if (!dfn[v]){
            Tarjan(v);
            low[u] = min(low[u],low[v]);
            if (low[v]>=dfn[u]){
                son++;
                if (u!=Root||son>1){//v节点能会跳至u及其以后的节点，并且u节点为所假设的根节点R的子节点则u为割点
                    cut_point[u] = 1;
                }
                num++;
                while (!stk.empty())
                {
                    ll now = stk.top();
                    stk.pop();
                    dcc[num].push_back(now);
                    if (now==v) break;//弹栈时不能弹出割点，因为割点属于多个点双,即点双的大小大于等于2
                }
                dcc[num].push_back(u);
            }
        }else{
            low[u] = min(low[u],dfn[v]);//
        }
    }
}



//---------------------割边/边双连通分量---------------------//

ll cut_edge[maxn*2];//割边
vector<ll> bcc[N];//边双连通分量
ll from[N];//点所在边双连通分量
ll num;
void Tarjan(ll u,ll f){
    dfn[u] = low[u]=++idx;
    stk.push(u);
    for (int i = h[u];~i; i=e[i].next)
    {
        ll v= e[i].to;
        if (!dfn[v]){
            Tarjan(v,i);
            low[u] = min(low[u],low[v]);
            if (low[v]>dfn[u]){//
                cut_edge[i] = cut_edge[i^1] = 1;
            }
        }else if(i!=(f^1)){
            low[u] = min(low[u],dfn[v]);//
        }   
    }
    if (dfn[u]==low[u]){
        num++;
        while (!stk.empty())
        {
            ll now= stk.top();
            stk.pop();
            bcc[num].push_back(now);
            from[now] = num;
            if (now==u) break;
        }
    }
}
void solve(){
    for (int i = 0; i < m; i++)
    {
        cin >>x>>y;
        add(x,y,1);
        add(y,x,1);//割点/边时为无向图
    }
    for (int i = 1; i <= n; i++)
    {
        
        if (!dfn[i]){
        //    R=i;//割点需要考虑从各个点为根时是否可以为割点
           Tarjan(i);//割点/点双
           Tarjan(i,0);//割边/边双
        }
    }
}