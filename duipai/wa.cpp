#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e6 + 7;
const int N = 2e5 + 7;
const ll INF = 1e18;
ll n, m, k, x, y, z;
#define Pa pair<ll, ll>
#define YES cout << "YES\n"
#define NO cout << "NO\n"
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define FOR(n) for (int i = 0; i < (int)n; i++)
#define repi(i, a, b) for (int i = (int)a; i < (int)b; i++)
// cout << fixed << setprecision(10) << '\n';
ll mx[4] = {0, 0, 1, -1}, my[4] = {1, -1, 0, 0};

class manacher {
  public:
    vector<ll> d;
    int len;
    string pattern;
    manacher(){};
    manacher(string ss) {
        pattern = "$#";
        init(ss);
        len = pattern.length();
        d.resize(len + 1);
    }
    void init(string ss) {
        for (int i = 0; i < ss.length(); i++) {
            pattern.push_back(ss[i]);
            pattern.push_back('#');
        }
        pattern.push_back('&');
    }
    ll work() {
        d[1] = 1;
        ll ans = 1;
        for (ll i = 0, l = 0, r = 1; i < len; i++) {
            if (i <= r)
                d[i] = min(d[r - i + l], r - i + 1);
            else
                d[i] = 1;
            while (pattern[i - d[i]] == pattern[i + d[i]])
                d[i]++;
            ans = max(ans, d[i]);
            if (i + d[i] - 1 > r)
                l = i - d[i] + 1, r = i + d[i] - 1;
        }
        return ans - 1;
    }
    bool check(ll l, ll r) {
        ll l0 = 2 * l, r0 = 2 * r;
        ll mid = (l0 + r0) >> 1;
        if (d[mid] >= r - l + 1) {
            return 1;
        }
        return 0;
    }
};

template <class T> constexpr T power(T a, ll b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

constexpr ll mul(ll a, ll b, ll p) {
    ll res = a * b - ll(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}
template <class T = long long> struct MODINT {
    ll x;
    constexpr MODINT() : x{} {}
    constexpr MODINT(ll x) : x{norm(x % getMod())} {}

    static ll Mod;
    constexpr static ll getMod() {
        // if (P > 0) {
        //     return P;
        // } else {
        //     return Mod;
        // }
        return Mod;
    }
    constexpr static void setMod(T Mod_) { Mod = Mod_; }
    constexpr T norm(T x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    // constexpr T &operator() ()const{
    //     return val();
    // }
    constexpr T val() const { return x; }
    explicit constexpr operator T() const { return x; }
    constexpr MODINT operator-() const {
        MODINT res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MODINT inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MODINT &operator*=(MODINT rhs) & {
        x = mul(x, rhs.x, getMod());
        return *this;
    }
    constexpr MODINT &operator+=(MODINT rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MODINT &operator-=(MODINT rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MODINT &operator/=(MODINT rhs) & { return *this *= rhs.inv(); }
    friend constexpr MODINT operator*(MODINT lhs, MODINT rhs) {
        MODINT res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MODINT operator+(MODINT lhs, MODINT rhs) {
        MODINT res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MODINT operator-(MODINT lhs, MODINT rhs) {
        MODINT res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MODINT operator/(MODINT lhs, MODINT rhs) {
        MODINT res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MODINT &a) {
        ll v;
        is >> v;
        a = MODINT(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os,
                                              const MODINT &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MODINT lhs, MODINT rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MODINT lhs, MODINT rhs) {
        return lhs.val() != rhs.val();
    }
};
template <> ll MODINT<ll>::Mod = 1e9 + 7;
using Z = MODINT<ll>;

/*
    1e18+9
    998244353
    1e9 + 7
    1e9 + 9
*/
// class Combine
namespace combine {
using ll = long long;
ll p = Z::Mod;
const int MAXN = 2e6 + 5;
Z fact[MAXN];
Z inv[MAXN]; // 逆元
// Z B[MAXN]; // 伯努利数,求解自然数幂次数列求和 eg. S_{m}(n) = 1^m + 2^m + ...
// + n^m
inline Z C(ll m, ll n);
void Init() // 组合数初始化；
{
    inv[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        // inv[i] = (m- m/i) * inv[m%i] % m;
        inv[i] = (Z::Mod - Z::Mod / i) * inv[Z::Mod % i];
    } // 在模数为合数时线性求逆元
    fact[0] = 1;
    for (int i = 1; i < MAXN; ++i)
        fact[i] = fact[i - 1] * i;
    // B[0] = 1;
    // for(int i =1;i<MAXN;i++){
    //     Z ans  =0 ;
    //     if (i==MAXN-1){
    //         break;
    //     }
    //     for(int k = 0;k<i;i++){
    //         ans += C(i+1,k)*B[k];
    //     }
    //     ans = ans + (-inv[i+1]);
    //     B[i] = ans;
    // }
}
// 从 m 个数中选出 n 个数
inline Z C(ll m, ll n) { // 求组合
    return m < n ? 0ll : (fact[m] / fact[n] / fact[m - n]);
}
// 从 m 个数中选出 n 个数
inline Z Lucas(ll m, ll n) { // 卢卡斯定理
    return n == 0 ? 1ll : C(m % p, n % p) * Lucas(m / p, n / p);
}
// 从 m 个数中按顺序取 n 个数
inline Z P(ll m, ll n) //
{
    return fact[m] / fact[m - n];
}
// Catalan 卡特兰数列
inline Z H(ll n) { return C(n * 2, n) - C(n * 2, n - 1); }
// 第二类斯特林数 表示将 m 个两两不同的元素，划分为 n
// 个互不区分的非空子集的方案数
inline Z Second_Stirling(ll m, ll n) {
    Z ans = 0;
    ll base = (n % 2 == 1) ? -1 : 1;
    for (int i = 0; i <= n; i++) {
        ans += base * power(Z(i), m) / fact[i] / fact[n - i];
        base *= -1;
    }
    // for (int i = 0; i <=n; i++)
    // {
    //     ans+= base*C(n,i)*power(Z(i),m);
    //     base*=-1;
    //     /* code */
    // }
    // ans/=fact[n];
    return ans;
}
} // namespace combine
using namespace combine;
void solve() {
    string ss;
    freopen("in.txt", "r", stdin);
    freopen("wa.txt", "w", stdout);
    cin >> n >> m;
    string s, t;
    cin >> s >> t;
    Z ans = 0;
    ll cnt = 0;
    for (int i = m - 1; i >= 0; i--) {
        if (t[i] == t[m - 1]) {
            cnt++;
        } else {
            break;
        }
    }
    string t2 = t;
    manacher mana(t);
    mana.work();
    if (mana.check(1, m)) {
        set<ll> b;
        for (auto i : t) {
            b.insert(i);
        }
        if (b.size() == 1) {
        } else {
            ll st = 0;
            for (auto i : s) {
                if (st < m && i == t[st]) {
                    st++;
                }
            }
            if (st == m) {
                ans += 1;
            }
        }
    }
    FOR(cnt) { t2.pop_back(); }
    // reverse(t2.begin(), t2.end());
    // t2 = t + t2;
    s = "#" + s;
    if (1) {
        ll l = 0, r = n + 1;
        ll st = 0;
        ll len = t2.length();
        for (int i = 1; i <= n; i++) {
            if (st < len && s[i] == t2[st]) {
                st++;
                l = i;
            }
        }
        bool ok = 1;
        if (st == len) {
            l++;

        } else {
            ok = 0;
        }

        st = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (st < len && s[i] == t2[st]) {
                st++;
                r = i;
            }
        }
        if (st == len) {
            r--;
        } else {
            ok = 0;
        }
        if (ok) {
            ll cnt2 = 0;
            for (int i = l; i <= r; i++) {
                if (s[i] == t[m - 1]) {
                    cnt2++;
                }
            }
            ans += max(0ll, min(cnt2 - cnt + 1, cnt + 1));
        }
        // cerr << l << ' ' << r << '\n';
    }
    ll l = 1, r = n;
    ll st = 0;
    for (int i = 1; i <= n; i++) {
        if (st < m && s[i] == t[st]) {
            st++;
            l = i;
        }
    }
    if (st == m) {
        l++;
    } else {
        l = n + 1;
    }
    st = 0;
    for (int i = n; i >= 1; i--) {
        if (st < m && s[i] == t[st]) {
            st++;
            r = i;
        }
    }
    if (st == m) {
        r--;
    } else {
        r = 0;
    }
    if (l > r) {
        cout << ans << '\n';
        return;
    }
    vector<Z> dp(n + 1);
    dp[0] = 0;

    vector<int> last(26, -1);
    for (int i = l - 1; i <= r - 1; i++) {
        int ch = s[i + 1] - 'a';
        dp[i + 1] = (2 * dp[i] + 1);
        if (last[ch] >= 0) {
            dp[i + 1] -= (dp[last[ch]] + 1);
        }

        last[ch] = i;
        /*cerr << dp[i + 1] << " \n"[i == r];*/
    }

    cout << ans + dp[r];
    cout << endl;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    ll t = 1;
    /*cin >>t;*/
    while (t--)
        solve();
    return 0;
}
