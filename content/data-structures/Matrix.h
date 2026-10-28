/**
 * Author: Thieu Nguyen Huy
 * Description: Matrix multiplication modulo MOD. Stored entries must be in [0, MOD).
 * Usage: Set MOD; 8 * MOD * MOD must fit in signed 64-bit.
 * Status: Randomized multiplication and exponentiation regression test
 */

struct Matrix {
    static const ll MOD = 1000000007; // Set to the required modulus.
    static const uint64_t modmod = 8ULL * MOD * MOD; // must be < 2^63

    vector<vector<uint64_t>> val;
    int n, m;

    Matrix(int _n = 0, int _m = 0) {
        resize(_n, _m);
    }

    Matrix(vector<vector<ll>> ve) {
        init(ve);
    }

    void resize(int _n, int _m) {
        n = _n, m = _m;
        val.assign(n, vector<uint64_t>(m));
    }

    void init(vector<vector<ll>> ve) {
        n = ve.size(), m = n ? ve[0].size() : 0;
        val.assign(n, vector<uint64_t>(m, 0));
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
            val[i][j] = (ve[i][j] % MOD + MOD) % MOD;
        }
    }

    friend istream& operator >> (istream &is, Matrix &T) {
        for (auto &x : T.val) {
            for (auto &y : x) {
                ll v; if (!(is >> v)) return is;
                y = (v % MOD + MOD) % MOD;
            }
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

    vector<uint64_t>& operator [] (int i) { return val[i]; }
    const vector<uint64_t>& operator [] (int i) const { return val[i]; }

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
        for (auto &row : ret.val) for (auto &x : row) x %= MOD;
        return ret;
    }

    Matrix binpow(ll n) {
        assert(this->n == m && n >= 0);
        Matrix A = *this, ret(A.n, A.n);
        for (int i = 0; i < A.n; ++i) ret[i][i] = 1;
        while (n > 0) {
            if (n & 1) ret = ret * A;
            A = A * A, n >>= 1;
        }
        return ret;
    }
};