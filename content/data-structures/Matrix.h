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

  void resize(int _n, int _m) {
    n = _n, m = _m;
    val.assign(n, vector<uint64_t>(m));
  }
  Matrix operator * (const Matrix &other) {
    Matrix ret(n, other.m);
    for (int i = 0; i < n; ++i)
      for (int k = 0; k < m; ++k) {
        for (int j = 0; j < other.m; ++j)
          ret[i][j] += val[i][k] * other[k][j];
        if (k % 8 == 0) {
          for (int j = 0; j < other.m; ++j)
            ret[i][j] = min(ret[i][j], ret[i][j] - modmod);
        }
      }
    for (auto &row : ret.val) for (auto &x : row) x %= MOD;
    return ret;
  }
};