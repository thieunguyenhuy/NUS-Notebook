/**
 * Author: Simon Lindholm
 * Date: 2017-05-10
 * License: CC0
 * Source: Wikipedia
 * Description: Given $n$ points with distinct x-coordinates, computes a polynomial $p$ of degree at most $n-1$ that
 *  passes through them: $p(x) = a[0]*x^0 + ... + a[n-1]*x^{n-1}$.
 *  For numerical precision when $n>1$, pick $x[k] = c*\cos(k\pi/(n-1)), k=0 \dots n-1$.
 * Time: O(n^2)
 */
#pragma once
using vd = vector<double>;
vd interpolate(vd x, vd y, int n) {
  if (!n) return {};
  assert(n > 0 && n <= (int)x.size() && n <= (int)y.size());
  vd res(n), temp(n);
  for (int k = 0; k < n - 1; ++k)
    for (int i = k + 1; i < n; ++i)
      y[i] = (y[i] - y[k]) / (x[i] - x[k]);
  double last = 0; temp[0] = 1;
  for (int k = 0; k < n; ++k)
    for (int i = 0; i < n; ++i) {
      res[i] += y[k] * temp[i];
      swap(last, temp[i]);
      temp[i] -= last * x[k];
    }
  return res;
}
