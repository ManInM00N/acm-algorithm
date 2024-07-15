// clang-format off
template<class T>
constexpr T power(T a, ll b) {
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
    constexpr MODINT& operator*=(MODINT rhs) & {
        x = mul(x, rhs.x, getMod());
        return *this;
    }
    constexpr MODINT& operator+=(MODINT rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MODINT& operator-=(MODINT rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MODINT& operator/=(MODINT rhs) & { return *this *= rhs.inv(); }
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
    friend constexpr std::istream& operator>>(std::istream& is, MODINT& a) {
        ll v;
        is >> v;
        a = MODINT(v);
        return is;
    }
    friend constexpr std::ostream& operator<<(std::ostream& os,
                                              const MODINT& a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MODINT lhs, MODINT rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MODINT lhs, MODINT rhs) {
        return lhs.val() != rhs.val();
    }
};
template <> ll MODINT<ll>::Mod = 998244353;
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
// clang-format on
