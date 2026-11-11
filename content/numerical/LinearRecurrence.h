/**
 * Author: Lucian Bicsi
 * Date: 2018-02-14
 * License: CC0
 * Source: Chinese material
 * Description: Generates the $k$'th term of an $n$-order
 * linear recurrence $S[i] = \sum_j S[i-j-1]tr[j]$,
 * given $S[0 \ldots \ge n-1]$ and $tr[0 \ldots n-1]$.
 * Faster than matrix multiplication.
 * Useful together with Berlekamp--Massey.
 * Set mod. Requires a nonempty recurrence, $k \ge 0$, and coefficients/terms in $[0, mod)$.
 * Usage: linearRec({0, 1}, {1, 1}, k) // k'th Fibonacci number
 * Time: O(n^2 \log k)
 * Status: bruteforce-tested mod 5 for n <= 5
 */
#pragma once
const ll mod = 5; /** exclude-line */
using Poly = vector<ll>;
ll linearRec(Poly S, Poly tr, ll k) {
  int n = (int)tr.size();
  assert(n > 0 && (int)S.size() >= n && k >= 0);
  if (k < n) return S[k];
  auto combine = [&](Poly a, Poly b) {
    Poly res(n * 2 + 1);
    for (int i = 0; i < n + 1; ++i)
      for (int j = 0; j < n + 1; ++j)
        res[i + j] = (res[i + j] + a[i] * b[j]) % mod;
    for (int i = 2 * n; i > n; --i)
      for (int j = 0; j < n; ++j)
        res[i - 1 - j] = (res[i - 1 - j] + res[i] * tr[j]) % mod;
    res.resize(n + 1);
    return res;
  };
  Poly pol(n + 1), e(pol);
  pol[0] = e[1] = 1;
  // Use an unsigned exponent so k = LLONG_MAX also permits k + 1.
  for (unsigned long long ebit = (unsigned long long)k + 1; ebit; ebit >>= 1) {
    if (ebit & 1) pol = combine(pol, e);
    e = combine(e, e);
  }
  ll res = 0;
  for (int i = 0; i < n; ++i) res = (res + pol[i + 1] * S[i]) % mod;
  return res;
}
