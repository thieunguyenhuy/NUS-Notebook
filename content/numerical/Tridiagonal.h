/**
 * Author: Ulf Lundstrom, Simon Lindholm
 * Date: 2009-08-15
 * License: CC0
 * Source: https://en.wikipedia.org/wiki/Tridiagonal_matrix_algorithm
 * Description: Solves a nonsingular tridiagonal system Ax = b.
 * diag has size n; super and sub have size n-1, with
 * A[i][i] = diag[i], A[i][i + 1] = super[i], A[i + 1][i] = sub[i].
 * For $a_i = b_i a_{i - 1} + c_i a_{i + 1} + d_i$ with known boundary values,
 * use diagonal 1, subdiagonal $-b_i$, superdiagonal $-c_i$, and RHS $d_i$;
 * move the known boundary contributions to the RHS.
 * Numerically stable for strictly diagonally dominant matrices or symmetric
 * positive definite matrices. In those cases, pivot tracking can be omitted.
 * Fails for singular systems; divisions by zero are not checked.
 * Time: O(N)
 * Status: Brute-force tested mod 5 and 7 and stress-tested for real matrices obeying the criteria above.
 */
#pragma once
using T = double;
vector<T> tridiagonal(vector<T> diag, const vector<T> &super,
    const vector<T> &sub, vector<T> b) {
  int n = (int)b.size(); vector<int> tr(n);
  for (int i = 0; i < n - 1; ++i) {
    if (abs(diag[i]) < 1e-9 * abs(super[i])) { // diag[i] == 0
      b[i + 1] -= b[i] * diag[i + 1] / super[i];
      if (i + 2 < n) b[i + 2] -= b[i] * sub[i + 1] / super[i];
      diag[i + 1] = sub[i]; tr[++i] = 1;
    } else {
      diag[i + 1] -= super[i] * sub[i] / diag[i];
      b[i + 1] -= b[i] * sub[i] / diag[i];
    }
  }
  for (int i = n - 1; i >= 0; --i) {
    if (tr[i]) {
      swap(b[i], b[i - 1]);
      diag[i - 1] = diag[i];
      b[i] /= super[i - 1];
    } else {
      b[i] /= diag[i];
      if (i) b[i - 1] -= b[i] * super[i - 1];
    }
  }
  return b;
}
