# acm-algorithm
<h1>使用须知</h1>
绝大部分代码模板已经封装完毕<br>
只需在题目的基础上稍加修改<br>
数组下标默认从 <strong>1</strong> 开始,所以会对初始数组开的大一点<br>
而图类模板没有添加以下前向星的代码,请在使用前复制或自行修改:<br>

```
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
    for (int i = 0; i <= n; i++)//使用网络流时修改为2*n+7
    {
        h[i]= -1;
    }
}
```
