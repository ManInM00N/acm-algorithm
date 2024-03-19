template <class T = int >
class Trie01{
public:
    std::vector<std::vector<T>> nex;
    T idx;
    std::vector<T> cnt;
    Trie01(){};
    // 总体数量和字典种类
    Trie01(T siz, T varity = 2){
        idx =0 ;
        nex.resize(siz+1,vector<T>(varity));
        cnt.resize(siz*varity+1);
    }
    void insert(T num){
        int p = 0;
        for (int i = 30; i >=0; i--)
        {
            T type = (num>>i) & 1;
            if (!nex[p][type]){
                nex[p][type] = ++idx;
            }
            p = nex[p][type];
            cnt[p]++;
        }
    }
    bool find( T num ){
        T p = 0;
        T res= 0;
        for (int i = 30; i >=0; i--)
        {
            T type = (num>>i)&1;
            if (!cnt[nex[p][type]]){
                return false;
            }
            p = nex[p][type];
        }
        return true;
    }
    void del(T num){
        T p = 0;
        for (int i = 31 - 1; i >= 0; i--)
        {
            T type = (num>>i)&1;
            p = nex[p][type];
            cnt[p]--;
        }
    }
    T find_rank(T num){
        T p = 0;
        T sum = 0;
        for (int i = 31 - 1; i >= 0; i--)
        {
            T type = (num>>i)&1;
            if ( type==1&&nex[p][type^1] ){
                
                sum+= cnt[nex[p][type^1]];
            }
            if (!nex[p][type]){
                break;
            }
            p = nex[p][type];
        }
        return sum;
    }
    T find_by_rank(T num){
        T p = 0;
        T ans = 0;
        T sum = 0;
        for (int i = 31 - 1; i >= 0; i--)
        {
            T type = 1;
            if (cnt[nex[p][type^1]]+sum<num){
                sum+=cnt[nex[p][type^1]];
                p = nex[p][type];
                ans+= 1ll<<i;
            }else {
                p = nex[p][type^1];
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
        for (int i = 0; i < ss.length(); i++)
        {
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
        for (int i = 0; i < ss.length(); i++)
        {
            T type = ss[i]-'a';
            if (!nex[p][type]) return 0;
            p = nex[p][type];
        }
        return 1;
    }
}