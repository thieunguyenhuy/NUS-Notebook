/**
 * Author: chilli
 * Date: 2019-04-16
 * License: CC0
 * Source: based on KACTL's FFT
 * Description: ntt(a) computes $\hat f(k) = \sum_x a[x] g^{xk}$ for all $k$, where $g=\text{root}^{(mod-1)/N}$.
 * Nonempty inputs must have power-of-two size dividing mod-1.
 * Useful for convolution modulo specific nice primes of the form $2^a b+1$,
 * where the convolution result has size at most $2^a$.
 * For arbitrary moduli, use several NTT primes with CRT or coefficient splitting.
   \texttt{conv(a, b) = c}, where $c[x] = \sum a[i]b[x-i]$.
   For manual convolution: NTT the inputs, multiply
   pointwise, divide by n, reverse(start+1, end), NTT back.
 * Inputs must be in [0, mod).
 * Time: O(N \log N)
 * Status: stress-tested
 */
#pragma once
const ll mod = (119 << 23) + 1, root = 62; // = 998244353
ll nttPow(ll a, ll e) {
  ll res = 1;
  for (; e; e >>= 1, a = a * a % mod)
    if (e & 1) res = res * a % mod;
  return res;
}
// Other primes below 2^30: (5 << 25) + 1, (7 << 26) + 1,
// (479 << 21) + 1, (483 << 21) + 1. Check a primitive root before changing mod.
using vl = vector<ll>;
void ntt(vl &a) {
  int n = (int)a.size();
  if (n <= 1) return;
  assert((n & (n - 1)) == 0 && (mod - 1) % n == 0);
  int L = 31 - __builtin_clz(n);
  static vl rt(2, 1);
  for (static int k = 2, s = 2; k < n; k *= 2, ++s) {
    rt.resize(n);
    ll z[] = {1, nttPow(root, mod >> s)};
    for (int i = k; i < 2 * k; ++i) rt[i] = rt[i / 2] * z[i & 1] % mod;
  }
  vector<int> rev(n);
  for (int i = 0; i < n; ++i) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  for (int i = 0; i < n; ++i) if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int k = 1; k < n; k *= 2)
    for (int i = 0; i < n; i += 2 * k)
      for (int j = 0; j < k; ++j) {
        ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
        a[i + j + k] = ai - z + (z > ai ? mod : 0);
        ai += (ai + z >= mod ? z - mod : z);
      }
}
vl conv(const vl &a, const vl &b) {
  if (a.empty() || b.empty()) return {};
  int s = (int)a.size() + (int)b.size() - 1, n = 1;
  while (n < s) n *= 2;
  int inv = nttPow(n, mod - 2);
  vl L(a), R(b), out(n);
  L.resize(n), R.resize(n);
  ntt(L), ntt(R);
  for (int i = 0; i < n; ++i)
    out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * inv % mod;
  ntt(out);
  return {out.begin(), out.begin() + s};
}
