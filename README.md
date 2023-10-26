# acm-algorithm

绝大部分代码模板已经封装完毕
只需在题目的基础上稍加修改
而图类模板没有添加前向星的代码
struct node
{
    ll to, next, w;
    node() {}
    node(ll w, ll to) : to(to), next(0), w(w) {}
    friend bool operator<(node a, node b)
    {
        return a.w > b.w;
    }
};
ll nxt, rnxt;
node e[maxn];
ll h[N];
void add(ll u,ll v,ll w){
    e[++nxt].next=h[u];
    e[nxt].w=w;
    e[nxt].to=v;
    h[u] = nxt;
}
void init(){
    nxt=rnxt=1;
    for (int i = 0; i <= n; i++)
    {
        h[i]= -1;
    }
}
