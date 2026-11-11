/**
 * Author: Thieu Nguyen Huy
 * Description: Multiplies integer polynomials with a long-double FFT, then reduces modulo MOD.
 * Usage: Set MOD. Unreduced coefficients must fit in ll, and FFT error must be below 0.5.
 * Precision depends on coefficient magnitudes, input lengths, and long-double precision.
 * For large modular coefficients, use NTT/CRT or coefficient splitting.
 * Time: O(N \log N), where N is the sum of the input sizes
 * Status: Well-tested
 */
#pragma once
namespace FFT {
  using ld = long double;
  const int MOD = 1000000007; // Set to the required modulus.
  const ld pi = acosl(-1.0L);
  struct cmplx {
    ld a, b;
    cmplx(ld a1 = 0, ld b1 = 0) : a(a1), b(b1) {}
  };
  inline cmplx sum(const cmplx &c1, const cmplx &c2) {
    return {c1.a + c2.a, c1.b + c2.b};
  }
  inline cmplx sub(const cmplx &c1, const cmplx &c2) {
    return {c1.a - c2.a, c1.b - c2.b};
  }
  inline cmplx mult(const cmplx &c1, const cmplx &c2) {
    return {c1.a * c2.a - c1.b * c2.b, c1.a * c2.b + c1.b * c2.a};
  }
  void fft(vector<cmplx> &a, int n) {
    assert(n > 0 && n <= (int)a.size() && (n & (n - 1)) == 0);
    for (int i = 1, j = 0; i < n; ++i) {
      int bit = n >> 1;
      for (; j >= bit; bit >>= 1) j -= bit;
      j += bit;
      if (i < j) swap(a[i], a[j]);
    }
    for (int k = 1; k < n; k *= 2) {
      ld phi = pi / k;
      cmplx wt(cos(phi), sin(phi));
      for (int i = 0; i < n; i += 2 * k) {
        cmplx w(1, 0);
        for (int j = 0; j < k; ++j) {
          cmplx u = a[i + j], v = mult(a[i + j + k], w);
          a[i + j] = sum(u, v);
          a[i + j + k] = sub(u, v);
          w = mult(w, wt);
        }
      }
    }
  }
  vector<int> multiply(const vector<int> &s, const vector<int> &t) {
    if (s.empty() || t.empty()) return {};
    int need = (int)s.size() + (int)t.size() - 1, sz = 1;
    while (sz < need) sz <<= 1;
    vector<cmplx> a(sz), b(sz);
    for (int i = 0; i < sz; ++i) {
      if (i < (int)s.size()) a[i] = cmplx(s[i], 0);
      if (i < (int)t.size()) b[i] = cmplx(t[i], 0);
    }
    fft(a, sz);
    fft(b, sz);
    for (int i = 0; i < sz; ++i) {
      a[i] = mult(a[i], b[i]);
    }
    fft(a, sz);
    reverse(a.begin() + 1, a.end());
    vector<int> ans(need);
    for (int i = 0; i < need; ++i) ans[i] = (llround(a[i].a / sz) % MOD + MOD) % MOD;
    return ans;
  }
}
vector<int> operator*(const vector<int> &s, const vector<int> &t) {
  return FFT::multiply(s, t);
}
