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
template<class T = long long>
struct MODINT {
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
    constexpr static void setMod(T Mod_) {
        Mod = Mod_;
    }
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
    constexpr T val() const {
        return x;
    }
    explicit constexpr operator T() const {
        return x;
    }
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
    constexpr MODINT &operator/=(MODINT rhs) & {
        return *this *= rhs.inv();
    }
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
    friend constexpr std::ostream &operator<<(std::ostream &os, const MODINT &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MODINT lhs, MODINT rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MODINT lhs, MODINT rhs) {
        return lhs.val() != rhs.val();
    }
};
template<>
ll MODINT<ll>::Mod = 998244353;
using Z = MODINT<ll>;

/*
    1e18+9
    998244353
    1e9 + 7
    1e9 + 9
*/
// class Combine
namespace combine
{
    ll p = Z::Mod;
    Z fact[2000005];
    void Init() // 组合数初始化；
    {
        // inv[1] = 1;
        // for (int i = 2; i <= n; i++)
        // {
        //     inv[i] = (m- m/i) * inv[m%i] % m;
        // }//在模数为合数时线性求逆元
        fact[0] = 1;
        for (int i = 1; i <= 2000004; ++i)
            fact[i] = fact[i - 1] * i;
    }
    //从n个数中选出m个数
    inline Z C(ll m, ll n)
    { // 求组合
        return m < n ? 0ll : (fact[m] / fact[n] / fact[m - n]);
    }
    //从n个数中选出m个数
    inline Z Lucas(ll m, ll n)
    { // 卢卡斯定理
        return n == 0 ? 1ll : C(m % p, n % p) * Lucas(m / p, n / p);
    }
    //从m个数中按顺序取n个数
    inline Z P(ll m, ll n)//
    {
        return fact[m] / fact[m - n];
    }
}
using namespace combine;

