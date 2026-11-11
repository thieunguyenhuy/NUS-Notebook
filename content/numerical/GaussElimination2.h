/**
 * Author: Thieu Nguyen Huy
 * Description: Gaussian elimination over GF(2). Destroys a.
 * gauss() returns the rank, or -1 if inconsistent. ans is one solution.
 * Requires $m < M$ to leave room for the right-hand-side bit.
 * Usage: init(n, m, a), then gauss(). If consistent, get_basis() returns a
 * nullspace basis; all solutions are ans XOR any subset of the basis vectors.
 * Time: O(nm + \min(n,m) n \lceil M/64 \rceil) for gauss(), using fixed-size bitsets
 * Status: Tested on judge.yosupo.jp
 */
#pragma once
namespace Gauss {
  // n equations, m variables; column m is the right-hand side.
  const int M = 4096 + 5;
  using T = bitset<M>;
  int n, m;
  int where[M];
  vector<T> a;
  T ans;
  void init(int _n, int _m, const vector<T> &_a) {
    assert(_n == (int)_a.size() && 0 <= _m && _m < M);
    n = _n, m = _m, a = _a;
  }
  int gauss() {
    ans.reset();
    for (int i = 0; i < m; ++i) where[i] = -1;
    int row = 0;
    for (int col = 0; col < m && row < n; ++col) {
      for (int i = row; i < n; ++i) if (a[i][col]) {
        swap(a[i], a[row]);
        break;
      }
      if (!a[row][col]) continue;
      where[col] = row;
      for (int i = 0; i < n; ++i)
        if (i != row && a[i][col]) a[i] ^= a[row];
      ++row;
    }
    for (int i = 0; i < m; ++i) if (where[i] != -1) {
      ans[i] = a[where[i]][m];
    }
    for (int i = row; i < n; ++i) if (a[i][m]) return -1;
    return row;
  }
  vector<T> get_basis() { // Requires a successful call to gauss().
    vector<T> basis;
    for (int i = 0; i < m; ++i) if (where[i] == -1) {
      T x; x[i] = 1;
      // x(j) + a[where[j]][i] * x[i] = 0
      for (int j = 0; j < m; ++j)
        if (where[j] != -1) x[j] = a[where[j]][i];
      basis.emplace_back(x);
    }
    return basis;
  }
}
