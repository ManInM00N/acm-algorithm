template <class T = int >
class Trie01{
public:
    struct node{
        T dir[2];
        ll cnt[2];
    };
    std::vector<node> nex;
    T idx;
    T varity = 2;
    Trie01(){};
    // 总体数量和字典种类
    Trie01(T siz, T varity = 2):varity(varity){
        idx =0 ;
        nex.resize(1);
        // cnt.resize(1);
        // cnt[0] = INF;
    }
    void init(){
        idx = 0;
        nex.clear();
        nex.resize(1);
    }
    void insert(T num){
        int p = 0;
        for (int i = 29; i >=0; i--)
        {
            T type = (num>>i) & 1;
            if (!nex[p].dir[type]){
                nex[p].dir[type] = ++idx;
                nex.push_back({{0,0},{0,0}});
            }
            nex[p].cnt[type]++;
            p = nex[p].dir[type];
            // cnt[p]= min(cnt[p],rr);
        }
    }
    bool find( T num, ll rr ){
        T p = 0;
        ll res= 0;
        bool ok =0;
        for (int i = 29; i >=0; i--){
            T type = (num>>i)&1;
            T tt = (k>>i)&1;
            if (tt==0){
                if (nex[p].dir[type^1]){
                    ok |= (rr<=nex[p].cnt[type ^ 1]);
                }
            }
            p = nex[p].dir[type^tt];
            if (!p){
                return ok;
            }
            // p = nex[p][type];
        }
        return ok;
    }
    void del(T num){
        T p = 0;
        for (int i = 30; i >= 0; i--){
            T type = (num>>i)&1;
            nex[p].cnt[type]--;
            p = nex[p].dir[type];
        }
    }
    T find_rank(T num){
        T p = 0;
        T sum = 0;
        for (int i = 30; i >= 0; i--){
            T type = (num>>i)&1;
            if ( type==1&&nex[p].dir[type^1] ){   
                sum+= nex[p].cnt[type^1];
            }
            if (!nex[p].dir[type]){
                break;
            }
            p = nex[p].dir[type];
        }
        return sum;
    }
    T find_by_rank(T num){
        T p = 0;
        T ans = 0;
        T sum = 0;
        for (int i = 30; i >= 0; i--){
            T type = 1;
            if (nex[p].cnt[type^1]+sum<num){
                sum+=nex[p].cnt[type^1];
                p = nex[p].dir[type];
                ans+= 1ll<<i;
            }else {
                p = nex[p].dir[type^1];
            }
            if (!p){
                break;
            }
        }
        return ans;
    }
    T pre(T num){
        return find_by_rank(find_rank(num));
    }
    T nxt(T num){
        return find_by_rank(find_rank(num+1)+1);
    }
};
template <class T = int >
class Trie{
public:
    std::vector<std::vector<T>> nex;
    T idx;
    std::vector<T> cnt;
    Trie(){};
    // 总体数量和字典种类
    Trie(T siz, T varity = 26){
        idx =0 ;
        nex.resize(siz+1,vector<T>(varity));
        cnt.resize(siz*varity+1);
    }
    void insert(std:: string ss){
        int p = 0;
        for (int i = 0; i < ss.length(); i++){
            T type = ss[i]-'a';
            if (!nex[p][type]){
                nex[p][type] = ++idx;
            }
            p = nex[p][type];
            cnt[p]++;
        }
    }
    bool find(std:: string ss){
        T p = 0;
        for (int i = 0; i < ss.length(); i++){
            T type = ss[i]-'a';
            if (!nex[p][type]) return 0;
            p = nex[p][type];
        }
        return 1;
    }
};
