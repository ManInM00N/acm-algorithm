#include <bits/stdc++.h>
using namespace std;
namespace geometry
{

    template <typename T>
    concept onlyint = is_integral_v<T>;
    class Martix
    {
    public:
        vector<vector<long long>> martix;
        int row, col;
        static const long long MOD = 1e9 + 7;
        bool valid;
        Martix() : row(0), col(0), valid(1){};
        template <onlyint T>
        Martix(T row, T col) : row(row), col(col), valid(1) // 初始化零矩阵
        {
            martix.resize(row + 1, vector<ll>(col + 1, 0));
        }
        template <onlyint T, onlyint V>
        Martix(T row, T col, V p) : row(row), col(col), valid(1) // 初始化成p*E(单位矩阵);
        {
            martix.resize(row + 1, vector<ll>(col + 1, 0));
            for (int i = 1; i <= min(row, col); i++)
                martix[i][i] = p;
        }
        Martix operator*(const Martix &x)
        {
            Martix res((*this).row, x.col);
            for (int i = 1; i <= (*this).row; i++)
            {
                for (int j = 1; j <= x.col; j++)
                {
                    for (int k = 1; k <= (*this).col; k++)
                    {
                        // res.martix[i][j] = ((res.martix[i][j] + quick_mul((*this).martix[i][k], x.martix[k][j], MOD)) % MOD + MOD) % MOD;
                        res.martix[i][j] += (x.martix[k][j] * (*this).martix[i][k]) % MOD;
                        res.martix[i][j] %= MOD;
                        // if (res.martix[i][j]<0)
                        //     res.martix[i][j] += MOD;
                    }
                }
            }
            return res;
        }
        template <onlyint T>
        Martix operator*(T x)
        {
            Martix res = (*this);
            for (int i = 1; i <= row; i++)
            {
                for (int j = 1; j <= col; j++)
                {
                    res.martix[i][j] = ((res.martix[i][j] * x) % MOD + MOD) % MOD;
                }
            }
            return res;
        }
        Martix Gauss(){//高斯消元求方程组[col==row+1],变相为求此矩阵是否可为i单位矩阵e变换而成
            Martix self = (*this);
            for (int i = 1; i <= row; i++)
            {
                if (self.martix[i][i] == 0)
                {
                    for (int j = i + 1; j <= row; j++)
                    {
                        if (self.martix[j][i])
                        {
                            self.row_swap(i, j);
                            break;
                        }
                    }
                }
                if (!self.martix[i][i])
                {
                    return Martix(); // 如果消着消着某一列没有数了，说明无解
                }
                // self.mul(i, 1.0/self.martix[i][i]); // 把self[i][i]变成1
                // 需注意修改为double类型进行计算
                for (int j = i + 1; j <= row; j++)
                {
                    self.md(i, j, -self.martix[j][i]);
                }
                for (int j = 1; j <= row; j++)
                {
                    if (j==i) continue;
                    self.md(i, j, -self.martix[j][i]);
                }
            }
            return self;
        }
        Martix operator~() // 求逆矩阵
        {
            Martix res((*this).row, (*this).col, 1);
            Martix self = (*this);
            for (int i = 1; i <= row; i++)
            {
                if (self.martix[i][i] == 0)
                {
                    for (int j = i + 1; j <= row; j++)
                    {
                        if (self.martix[j][i])
                        {
                            self.row_swap(i, j);
                            res.row_swap(i, j);
                            break;
                        }
                    }
                }
                if (!self.martix[i][i])
                {
                    return Martix(); // 如果消着消着某一列没有数了，说明无解
                }
                res.mul(i, inv(self.martix[i][i]));
                self.mul(i, inv(self.martix[i][i])); // 把self[i][i]变成1
                for (int j = i + 1; j <= row; j++)
                {
                    res.md(i, j, -self.martix[j][i]);
                    self.md(i, j, -self.martix[j][i]);
                }
            }
            for (int i = row - 1; i >= 1; i--) // 消成对角矩阵
            {
                for (int j = i + 1; j <= col; j++)
                {
                    res.md(j, i, -self.martix[i][j]);
                    self.md(j, i, -self.martix[i][j]);
                }
            }
            return res;
        }
        //乘法运算时需考虑是否会溢出，视情况使用龟速乘
        template <onlyint T, onlyint V>
        void mul(T row, V k)//将row行乘上k倍
        {
            for (int i = 1; i <= col; i++)
            {
                martix[row][i] = (martix[row][i] * k % MOD + MOD) % MOD;
            }
        }
        template <onlyint T, onlyint W, onlyint V>
        void md(T from, W to, V k)//对to行加上k倍的from行
        {
            for (int i = 1; i <= col; i++)
            {
                martix[to][i] = ((martix[to][i] + martix[from][i] * k) % MOD + MOD) % MOD;
            }
        }
        Martix operator+(const Martix &x)
        {
            Martix res((*this).row, (*this).col);
            for (int i = 1; i <= (*this).row; i++)
            {
                for (int j = 1; j <= (*this).col; j++)
                {
                    res.martix[i][j] = (*this).martix[i][j] + x.martix[i][j];
                    res.martix[i][j] %= MOD;
                }
            }
            return res;
        }
        Martix operator-(const Martix &x)
        {
            Martix res((*this).row, (*this).col);
            for (int i = 1; i <= (*this).row; i++)
            {
                for (int j = 1; j <= (*this).col; j++)
                {
                    res.martix[i][j] = (*this).martix[i][j] - x.martix[i][j];
                    res.martix[i][j] %= MOD;
                }
            }
            return res;
        }
        void row_swap(int x, int y)
        {
            swap((*this).martix[x], (*this).martix[y]);
        }
        static const long long inv(long long a)
        {
            long long res = 1;
            a %= MOD;
            long long k = MOD - 2;
            while (k)
            {
                if (k & 1)
                    res = res * a % MOD;
                a = a * a % MOD;
                k >>= 1;
            }
            return res % MOD;//求逆元
        }
        template <onlyint T>
        Martix qpow(T k)
        {
            Martix res((*this).row, (*this).col, 1), a = (*this);
            while (k)
            {
                if (k & 1)
                    res = res * a;
                a = a * a;
                k >>= 1;
            }
            return res;//矩阵快速幂，内置
        }
        template <onlyint T>
        Martix qpow(Martix b, T k)
        {
            Martix res = (*this);
            while (k)
            {
                if (k & 1)
                    res = res * b;
                b = b * b;
                k >>= 1;
            }
            return res;//矩阵快速幂，外置
        }
        void print()
        {
            for (int i = 1; i <= row; i++)
                for (int j = 1; j <= col; j++)
                    cout << martix[i][j] << " \n"[j == col];
        }
    };
    istream &operator>>(istream &in, Martix &x)
    {
        // 初始化矩阵大小
        for (int i = 1; i <= x.row; i++)
            for (int j = 1; j <= x.col; j++)
                in >> x.martix[i][j];
        return in;
    }
    ostream &operator<<(ostream &out, const Martix &x)
    {
        for (int i = 1; i <= x.row; i++)
        {
            for (int j = 1; j <= x.col; j++)
                out << x.martix[i][j] << ' ';
            out << '\n';
        }
        return out;
    }
}
using namespace geometry;