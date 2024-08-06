#include <algorithm>
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
    freopen("in.txt", "r", stdin);
    freopen("std.txt", "w", stdout);
    cin >> n >> m;
    string s, t;
    cin >> s >> t;
    ll ans = 0;
    string tmp;
    set<string> b;
    auto check = [&](string str) -> bool {
        ll st = 0;

        for (auto i : str) {
            if (st < m && i == t[st]) {
                st++;
            } else {
                break;
            }
        }
        bool ok = 1;
        ok &= (st == m);
        reverse(str.begin(), str.end());
        st = 0;
        for (auto i : str) {
            if (st < m && i == t[st]) {
                st++;
            } else {
                break;
            }
        }
        ok &= (st == m);
        return ok;
    };
    auto dfs = [&](auto self, ll num) -> void {
        if (tmp.length() >= m) {
            if (check(tmp)) {
                b.insert(tmp);
            }
        }
        if (num == n) {
            return;
        }
        tmp.push_back(s[num]);
        self(self, num + 1);
        tmp.pop_back();
        self(self, num + 1);
    };
    dfs(dfs, 0);
    for (auto i : b) {
        cout << i << '\n';
    }
    cout << b.size();
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
