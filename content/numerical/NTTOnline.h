/**
 * Author: YouKnowWho
 * Description: Online convolution modulo 998244353. Call extend(i, a[i], b[i])
 * for consecutive indices starting at 0; it returns the i-th convolution coefficient.
 * Inputs must be in $[0, mod)$. N bounds each padded transform length.
 * Time: $O(n \log^2 n)$ total for n calls to extend
 * Status: Probably Tested
 */
#pragma once
const int N = 1 << 18;
const int mod = 998244353;
const int root = 3;
int lim, rev[N], w[N], wn[N], inv_lim;
void reduce(int &x) { x = (x + mod) % mod; }
int POW(int x, int y, int ans = 1) {
  for (; y; y >>= 1, x = (long long) x * x % mod) if (y & 1) ans = (long long) ans * x % mod;
  return ans;
}
void precompute(int len) {
  assert(1 <= len && len <= N);
  lim = wn[0] = 1; int s = -1;
  while (lim < len) lim <<= 1, ++s;
  rev[0] = 0;
  for (int i = 1; i < lim; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << s);
  const int g = POW(root, (mod - 1) / lim);
  inv_lim = POW(lim, mod - 2);
  for (int i = 1; i < lim; ++i) wn[i] = (long long) wn[i - 1] * g % mod;
}
void ntt(vector<int> &a, int typ) {
  for (int i = 0; i < lim; ++i) if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int i = 1; i < lim; i <<= 1) {
    for (int j = 0, t = lim / i / 2; j < i; ++j) w[j] = wn[j * t];
    for (int j = 0; j < lim; j += i << 1) {
      for (int k = 0; k < i; ++k) {
        const int x = a[k + j], y = (long long) a[k + j + i] * w[k] % mod;
        reduce(a[k + j] += y - mod), reduce(a[k + j + i] = x - y);
      }
    }
  }
  if (!typ) {
    reverse(a.begin() + 1, a.begin() + lim);
    for (int i = 0; i < lim; ++i) a[i] = (long long) a[i] * inv_lim % mod;
  }
}
vector<int> multiply(const vector<int> &f, const vector<int> &g) {
  if (f.empty() || g.empty()) return {};
  int n = (int)f.size() + (int)g.size() - 1;
  precompute(n);
  vector<int> a = f, b = g;
  a.resize(lim); b.resize(lim);
  ntt(a, 1), ntt(b, 1);
  for (int i = 0; i < lim; ++i) a[i] = (long long) a[i] * b[i] % mod;
  ntt(a, 0);
  a.resize(n);
  return a;
}
// 1s for n = 2e5
struct OnlineConvolution {
  vector<int> a, b, c;
  int k;
  OnlineConvolution(int n): a(n), b(n), c(n), k(0) {}
  // Supply a[i] = x and b[i] = y; return c[i] of c = a * b.
  int extend(int i, int x, int y) {
    assert(i == k && k < (int)a.size());
    a[k] = x;
    b[k] = y;
    int s = k + 2;
    for (int w = 1; s % w == 0 && w < s; w <<= 1) {
      for (int ri = 0; ri < 2; ++ri) {
        if (ri == 0 || w * 2 != s) {
          vector<int> f(w), g(w);
          for (int i = 0; i < w; ++i) f[i] = a[w - 1 + i], g[i] = b[k - w + 1 + i];
          f = multiply(f, g);
          for (int i = 0, j = k; i < (int)f.size() && j < (int)c.size(); ++i, ++j) {
            c[j] += f[i];
            if (c[j] >= mod) c[j] -= mod;
          }
        }
        swap(a, b);
      }
    }
    return c[k++];
  }
};
