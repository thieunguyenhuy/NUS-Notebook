/**
 * Author: Stanford
 * Source: Stanford Notebook
 * License: MIT
 * Description: Solves a general linear maximization problem: maximize $c^T x$ subject to $Ax \le b$, $x \ge 0$.
 * Returns -inf if there is no solution, inf if there are arbitrarily good solutions, or the maximum value of $c^T x$ otherwise.
 * The output vector is set to an optimal $x$ (or a feasible solution in the unbounded case).
 * Numerical stability is not guaranteed. For better performance, define variables such that $x = 0$ is viable.
 * Usage:
 * vvd A = {{1,-1}, {-1,1}, {-1,-2}};
 * vd b = {1,1,-4}, c = {-1,-1}, x;
 * T val = LPSolver(A, b, c).solve(x);
 * Time: O((n + 1)(m + 1) \cdot \#pivots); exponentially many pivots are possible
 * Status: seems to work?
 */
#pragma once
using T = double; // Can also use long double; retune eps if needed.
using vd = vector<T>;
using vvd = vector<vd>;
const T eps = 1e-8, inf = numeric_limits<T>::infinity();
struct LPSolver {
  int m, n;
  vector<int> N, B;
  vvd D;
  LPSolver(const vvd &A, const vd &b, const vd &c) :
    m((int)b.size()), n((int)c.size()), N(n + 1), B(m), D(m + 2, vd(n + 2)) {
    for (int i = 0; i < m; ++i)
      for (int j = 0; j < n; ++j) D[i][j] = A[i][j];
    for (int i = 0; i < m; ++i) { B[i] = n + i; D[i][n] = -1; D[i][n + 1] = b[i]; }
    for (int j = 0; j < n; ++j) { N[j] = j; D[m][j] = -c[j]; }
    N[n] = -1; D[m + 1][n] = 1;
  }
  void pivot(int r, int s) {
    T *a = D[r].data(), inv = 1 / a[s];
    for (int i = 0; i < m + 2; ++i) if (i != r && abs(D[i][s]) > eps) {
      T *b = D[i].data(), inv2 = b[s] * inv;
      for (int j = 0; j < n + 2; ++j) b[j] -= a[j] * inv2;
      b[s] = a[s] * inv2;
    }
    for (int j = 0; j < n + 2; ++j) if (j != s) D[r][j] *= inv;
    for (int i = 0; i < m + 2; ++i) if (i != r) D[i][s] *= -inv;
    D[r][s] = inv;
    swap(B[r], N[s]);
  }
  bool simplex(int phase) {
    int x = m + phase - 1;
    for (;;) {
      int s = -1;
      for (int j = 0; j <= n; ++j) if (N[j] != -phase)
        if (s == -1 || tie(D[x][j], N[j]) < tie(D[x][s], N[s])) s = j;
      if (s == -1 || D[x][s] >= -eps) return true;
      int r = -1;
      for (int i = 0; i < m; ++i) {
        if (D[i][s] <= eps) continue;
        if (r == -1 || make_pair(D[i][n + 1] / D[i][s], B[i])
               < make_pair(D[r][n + 1] / D[r][s], B[r])) r = i;
      }
      if (r == -1) return false;
      pivot(r, s);
    }
  }
  T solve(vd &x) {
    int r = 0;
    for (int i = 1; i < m; ++i) if (D[i][n + 1] < D[r][n + 1]) r = i;
    if (m && D[r][n + 1] < -eps) {
      pivot(r, n);
      if (!simplex(2) || D[m + 1][n + 1] < -eps) return -inf;
      for (int i = 0; i < m; ++i) if (B[i] == -1) {
        int s = -1;
        for (int j = 0; j <= n; ++j) if (N[j] != -1 && abs(D[i][j]) > eps)
          if (s == -1 || tie(D[i][j], N[j]) < tie(D[i][s], N[s])) s = j;
        if (s != -1) pivot(i, s);
      }
    }
    bool ok = simplex(1); x = vd(n);
    for (int i = 0; i < m; ++i) if (0 <= B[i] && B[i] < n) x[B[i]] = D[i][n + 1];
    return ok ? D[m][n + 1] : inf;
  }
};
