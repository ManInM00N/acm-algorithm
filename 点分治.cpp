bool vis[N];
ll Siz[N],MaxSiz[N];//Siz[u]表示u的子树大小，及MaxSiz[u]子树里面的最大子树大小
ll S;//某个子树的大小，记得在求重心前求完
ll root;//重心
//求重心
void GetRt(ll u,ll f)
{
    Siz[u] = 1;
    MaxSiz[u] = 0;
    for (int i = h[u]; ~i; i=e[i].next)
    {
        ll v=e[i].to;
        if (v!=f&&!vis[v]){
            GetRt(v,u);
            Siz[u]+=Siz[v];
            MaxSiz[u] = max(MaxSiz[u],Siz[v]);
        }
    }
    MaxSiz[u] = max(MaxSiz[u],S-Siz[u]);
    if (MaxSiz[u]<MaxSiz[root]){
        root = u;
    }
}
vector<int> roads(4,0);//某个子树内的路径
//求出以某个节点为起点向下的路径
void GetDis(ll u,ll f){
    roads.push_back(dis[u]);
    for (int i = h[u]; ~i; i=e[i].next)
    {
        ll v=e[i].to;
        ll w = e[i].w;
        if (v!=f&&!vis[v]){
            dis[v] = (dis[u]+w);
            GetDis(v,u);
        }
    }
}
bool ans[N];
ll cnt=0;
//分治计数
void calc(ll u,ll f){
    dis[u] = 0;
    vector<int> hasyes;
    for (int i = h[u]; ~i; i=e[i].next)
    {
        ll v=e[i].to;
        ll w =e[i].w;
        //必须同时满足非父亲和未访问
        if (v!=f&&!vis[v]){
            roads.clear();
            dis[v] = w+dis[u];
            GetDis(v,u);
            /*
                通过此时得到的路径和之前累加的路径求解
                

                求解后将路径累加
                for(auto ro:roads){
                    hasyes.push_back(ro);
                }
            */
        }
    }
    /*
        清空状态
        for(auto i:hasyes){
            ans[i] = 0;
        }
    */
}
void dfs(ll u,ll f){
    vis[u] =1;
    calc(u,f);
    for (int i = h[u]; ~i; i=e[i].next)
    {
        ll v=e[i].to;
        if (v==f||vis[v]) continue;
        S = Siz[v];
        root = 0;
        MaxSiz[root] = n;
        GetRt(v, u);
        dfs(root, u);
    }
}
//需要先求出第一个重心
void solve(){
    S = n;
    cnt =0;
    MaxSiz[0] = n;
    GetRt(1,0);
    dfs(root,0);
}