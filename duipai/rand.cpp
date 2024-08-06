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
void solve() {
    string ss;
    freopen("in.txt", "w", stdout);
    n = rand() % 15 + 3;

    m = rand() % 4 + 2;
    string s, t;
    FOR(n) { s.push_back('a' + (rand() % 3)); }
    FOR(m) { t.push_back('a' + (rand() % 2)); }
    cout << n << ' ' << m << '\n';
    cout << s << '\n';
    cout << t;
    cout << endl;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    ll t = 1;
    srand(time(nullptr));
    /*cin >>t;*/
    while (t--)
        solve();
    return 0;
}
