#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define ls p << 1
#define rs p << 1 | 1
class Segment
{
public:
    struct tree
    {
        int l, r;
        int sum, lazy;
    };
    int num;
    vector<tree> tr;
    vector<int> arr;
    Segment(){};
    template <class T>
        requires(
            is_integral_v<T>)
    Segment(T n) : num(n + 7)
    {
        tr.resize(4 * num);
        arr.resize(num, 1);
    };
    void pushup(ll p)
    {
        tr[p].sum = tr[ls].sum + tr[rs].sum;
    }
    void pushdown(ll p)
    {
        tr[ls].sum += tr[p].lazy * (tr[ls].r - tr[ls].l + 1);
        tr[rs].sum += tr[p].lazy * (tr[rs].r - tr[rs].l + 1);
        tr[ls].lazy += tr[p].lazy;
        tr[rs].lazy += tr[p].lazy;
        tr[p].lazy = 0;
    }
    template <class T, class V, class W>
        requires(
            is_integral_v<T> && is_integral_v<V> && is_integral_v<W>)
    void build(T p, V l, W r)
    {
        tr[p].l = l;
        tr[p].r = r;
        tr[p].sum = arr[l];
        tr[p].lazy = 0;
        if (l == r)
            return;
        long long mid = l + r >> 1;
        build(ls, l, mid);
        build(rs, mid + 1, r);
        pushup(p);
    }
    template <class T, class V>
        requires(
            is_integral_v<T> && is_integral_v<V>)
    void update(V p, T x, T y, V z)
    {
        if (tr[p].l >= x && tr[p].r <= y)
        {
            tr[p].sum += (tr[p].r - tr[p].l + 1) * z;
            tr[p].lazy += z;
            return;
        }
        long long mid = tr[p].l + tr[p].r >> 1;
        pushdown(p);
        if (mid >= x)
            update(ls, x, y, z);
        if (mid < y)
            update(rs, x, y, z);
        pushup(p);
    }

    template <class T, class V, class W>
        requires(
            is_integral_v<T> && is_integral_v<V> && is_integral_v<W>)
    T query(V p, T x, W y)
    {
        if (tr[p].l >= x && tr[p].r <= y)
        {
            return tr[p].sum;
        }
        long long mid = tr[p].l + tr[p].r >> 1;
        T sum = 0;
        pushdown(p);
        if (mid >= x)
            sum += query(ls, x, y);
        if (mid < y)
            sum += query(rs, x, y);
        return sum;
    }
};