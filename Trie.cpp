// clang-format off
template <class T = int> class Trie01 {
  public:
    struct node {
        vector<T> dir;
        // ll dir[2];
    };
    std::vector<node> nex;
    std::vector<T> cnt;
    T idx;
    T varity;
    // T static base;
    Trie01() { // base = 0;
    };
    // 总体字典种类
    Trie01(T varity) : varity(varity) {
        idx = 0;
        nex.clear();
        nex.push_back({vector<T>(varity)});
        // nex.resize(1);
        cnt.resize(1);
        // base = 0;
        // cnt[0] = INF;
    }
    void init() {
        idx = 0;
        nex.clear();
        nex.push_back({vector<T>(varity)});
        // nex.resize(1);
        cnt.resize(1);
    }
    void insert(T num, T u = 1) {
        int p = 0;
        for (int i = 30; i >= 0; i--) {
            T type = (num >> i) & 1;
            if (!nex[p].dir[type]) {
                nex[p].dir[type] = ++idx;
                nex.push_back({vector<T>(varity)});
                cnt.push_back(0);
            }
            p = nex[p].dir[type];
            cnt[p]++;
            // cnt[p] = max(cnt[p], u);//小于等于这部分的最大值
            // cnt[p]= min(cnt[p],u);
        }
    }
    bool find(T num) {
        T p = 0;
        for (int i = 30; i >= 0; i--) {
            T type = num >> i & 1;
            p = nex[p].dir[type];
            if (!p) {
                return 0;
            }
        }
        return p != 0;
    }
    // 查找比num^tt的数的个数
    // bool find(T num, ll rr) {
    //     T p = 0;
    //     ll res = 0;
    //     bool ok = 0;
    //     for (int i = 30; i >= 0; i--) {
    //         T type = (num >> i) & 1;
    //         T tt = (k >> i) & 1;
    //         if (tt == 0) {
    //             if (nex[p].dir[type ^ 1]) {
    //                 ok |= (rr <= cnt[nex[p].dir[type ^ 1]]);
    //             }
    //         }
    //         p = nex[p].dir[type ^ tt];
    //         if (!p) {
    //             return ok;
    //         }
    //     }
    //     return ok;
    // }
    T find(T num, ll rr) {

        T p = 0;
        ll res = 0;
        for (int i = 30; i >= 0; i--) {
            T type = (num >> i) & 1;
            T tt = (rr >> i) & 1;
            if (tt == 0) {
                if (nex[p].dir[type ^ 1]) {
                    res += cnt[nex[p].dir[type ^ 1]];
                }
                p = nex[p].dir[type];
            } else {
                p = nex[p].dir[type ^ 1];
            }
            if (!p) {
                return res;
            }
        }
        // res+= cnt[p]; // 考虑是否等于
        return res;
    }
    void del(T num) {
        T p = 0;
        for (int i = 30; i >= 0; i--) {
            T type = (num >> i) & 1;
            /*nex[p].cnt[type]--;*/
            p = nex[p].dir[type];
            assert("Not exist numer");
            cnt[p]--;
        }
    }
    T find_rank(T num) {
        T p = 0;
        T sum = 0;
        for (int i = 30; i >= 0; i--) {
            T type = (num >> i) & 1;
            if (type == 1 && nex[p].dir[type ^ 1]) {
                sum += cnt[nex[p].dir[type ^ 1]];
            }
            if (!nex[p].dir[type]) {
                break;
            }
            p = nex[p].dir[type];
        }
        return sum;
    }
    T find_by_rank(T num) {
        T p = 0;
        T ans = 0;
        T sum = 0;
        for (int i = 30; i >= 0; i--) {
            T type = 1;
            if (cnt[nex[p].dir[type ^ 1]] + sum < num) {
                sum += cnt[nex[p].dir[type ^ 1]];
                p = nex[p].dir[type];
                ans += 1ll << i;
            } else {
                p = nex[p].dir[type ^ 1];
            }
            if (!p) {
                break;
            }
        }
        return ans;
    }
    T pre(T num) { return find_by_rank(find_rank(num)); }
    T nxt(T num) { return find_by_rank(find_rank(num + 1) + 1); }
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
// clang-format on
