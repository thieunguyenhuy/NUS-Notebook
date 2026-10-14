/**
 * Author: Thieu Nguyen Huy
 * Description: Matrix multiplication
 * Status: ~370ms on yosupo
 */

struct Matrix {
    static const ull modmod = 8LL * MOD * MOD; // should be < 2^63

    vector<vector<ull>> val;
    int n, m;

    Matrix(int _n = 0, int _m = 0) {
        resize(_n, _m);
    }

    Matrix(vector<vector<ll>> ve) {
        init(ve);
    }

    void resize(int _n, int _m) {
        n = _n, m = _m;
        val.assign(n, vector<ull>(m));
    }

    void init(vector<vector<ll>> ve) {
        n = ve.size(), m = ve[0].size();
        val.assign(n, vector<ull>(m, 0));
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
            val[i][j] = ve[i][j];
        }
    }

    friend istream& operator >> (istream &is, Matrix &T) {
        for (auto &x : T.val) {
            for (auto &y : x) is >> y;
        }
        return is;
    }

    friend ostream& operator << (ostream &os, Matrix T) {
        for (auto &x : T.val) {
            for (auto &y : x) os << (int)(y % MOD) << ' ';
            os << '\n';
        }
        return os << '\n';
    }

    vector<ull>& operator [] (int i) { return val[i]; }
    const vector<ull>& operator [] (int i) const { return val[i]; }

    Matrix operator * (const Matrix &other) {
        assert(m == other.n);
        Matrix ret(n, other.m);
        for (int i = 0; i < n; ++i) {
            for (int k = 0; k < m; ++k) {
               for (int j = 0; j < other.m; ++j) {
                    ret[i][j] += val[i][k] * other[k][j];
                }
                if (k % 8 == 0) {
                    for (int j = 0; j < other.m; ++j) {
                        ret[i][j] = min(ret[i][j], ret[i][j] - modmod);
                    }
                }
            }
        }
        return ret;
    }

    Matrix binpow(ll n) {
        Matrix A = *this, ret(A.n, A.n);
        for (int i = 0; i < A.n; ++i) ret[i][i] = 1;
        while (n > 0) {
            if (n & 1) ret = ret * A;
            A = A * A, n >>= 1;
        }
        return ret;
    }
};