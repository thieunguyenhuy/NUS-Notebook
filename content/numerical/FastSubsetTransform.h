/**
 * Author: Lucian Bicsi
 * Date: 2015-06-25
 * License: GNU Free Documentation License 1.2
 * Source: csacademy
 * Description: Transform to a basis with fast convolutions of the form
 * $\displaystyle c[z] = \sum\nolimits_{z = x \oplus y} a[x] \cdot b[y]$,
 * where $\oplus$ is one of AND, OR, XOR. Convolution inputs must have the same
 * power-of-two size. Intermediate sums and products must fit in int.
 * Time: O(N \log N)
 * Status: stress-tested
 */
#pragma once
void FST(vector<int> &a, bool inv) {
  assert(a.empty() || ((int)a.size() & ((int)a.size() - 1)) == 0);
  for (int n = (int)a.size(), step = 1; step < n; step *= 2) {
    for (int i = 0; i < n; i += 2 * step)
      for (int j = i; j < i + step; ++j) {
        int &u = a[j], &v = a[j + step]; tie(u, v) =
          inv ? pair<int, int>(v - u, u) : pair<int, int>(v, u + v); // AND
          // inv ? pair<int, int>(v, u - v) : pair<int, int>(u + v, u); // OR /// include-line
          // pair<int, int>(u + v, u - v); // XOR /// include-line
      }
  }
  // if (inv) for (int &x : a) x /= (int)a.size(); // XOR only /// include-line
}
vector<int> conv(vector<int> a, vector<int> b) {
  assert(a.size() == b.size());
  FST(a, 0); FST(b, 0);
  for (int i = 0; i < (int)a.size(); ++i) a[i] *= b[i];
  FST(a, 1); return a;
}
