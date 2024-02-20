// d = gcd(a,b)
template <typename T = long long> long long extgcd(T a, T b, T &x, T &y) {
    if(!b) {
        x = 1, y = 0;
        return a;
    }
    long long res = extgcd(b, a % b, y, x);
    y -= a / b * x;
    return res;
}
// ax + by = d 不存在 x,y的解时 false
template <typename T = long long> bool extgcd(T a, T b, T &x, T &y, T d) {
    if(!b and d % a) return false;
    if(!b) {
        x = d / a, y = 0;
        return true;
    }
    if(extgcd(b, a % b, y, x, d)) {
        y -= a / b * x;
        return true;
    }
    return false;
}

