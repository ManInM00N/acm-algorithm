const int MAXN = 1e6  + 10;// 字典树最长大小 Sum(dict)
int tr[MAXN][26];// 字典树储存容器
int fail[MAXN];// 匹配失败时的指针
int cnt[MAXN];.// 记录单词结束
int idx;// 字典树末尾添加节点

// 构建字典树同时初始化, 如果只有一组数据可不加
void init(int i){
    memset(tr[i], 0, 26 << 2);
    fail[i] = cnt[i] = 0;
}

// 构建字典树
void insert(const string &s){
    int u = 0;
    for(auto i : s){
        if(!tr[u][i - 'a']){
            tr[u][i - 'a'] = ++idx;
            init(idx);
        }
        u = tr[u][i - 'a'];
    }
    cnt[u] ++;
}
// 构造fail指针
void build(){
    queue<int> q;
    // 遍历第一层
    for(int i=0;i<26;i++)
        if(tr[0][i])
            q.push(tr[0][i]);
    // 
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i=0;i<26;i++){
            //如果字典树上拥有指向下一个字母的指针
            if(tr[u][i]){
                // 将下个字母匹配失败时的fail指针指向此时失败后匹配的位置
                fail[tr[u][i]] = tr[fail[u]][i];
                
                q.push(tr[u][i]);
            }else{
                tr[u][i] = tr[fail[u]][i];
            }
        }
    }
}
// 查询s串中存在多少字典树中的单词
int query(const string &s){
    int u = 0, ans = 0;
    for(auto i : s){
        u = tr[u][i - 'a'];
        for(int j = u; j && cnt[j]!=-1; j=fail[j]){
            ans += cnt[j];
            cnt[j] = -1;
        }
    }
    return ans;
}
