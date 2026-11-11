/**
 * Author: Per Austrin
 * Date: 2004-02-08
 * License: CC0
 * Description: Finds distinct real roots in $[xmin, xmax]$, in sorted order.
 * Uses derivative roots to split into monotone intervals. Repeated roots are
 * detected with a relative residual tolerance; ill-conditioned roots may be inaccurate.
 * Returns no roots for constant polynomials, including the zero polynomial.
 * Usage: polyRoots({{2, -3, 1}}, -1e9, 1e9) // Solves x^2-3x+2 = 0.
 * Time: O(n^3 I), where I = 80 bisection iterations
 */
#pragma once
#include "Polynomial.h"
vector<double> polyRoots(Poly p, double xmin, double xmax) {
  while (!p.a.empty() && p.a.back() == 0) p.a.pop_back();
  if (p.a.size() < 2 || xmin > xmax) return {};
  if (p.a.size() == 2) {
    double x = -p.a[0] / p.a[1];
    return xmin <= x && x <= xmax ? vector<double>{x} : vector<double>{};
  }
  Poly der = p;
  der.diff();
  vector<double> cuts = {xmin}, ret;
  for (double x : polyRoots(der, xmin, xmax))
    if (xmin < x && x < xmax) cuts.push_back(x);
  if (xmin < xmax) cuts.push_back(xmax);
  auto isRoot = [&](double x) {
    double scale = 0;
    for (int i = (int)p.a.size() - 1; i >= 0; --i)
      scale = scale * max(1.0, abs(x)) + abs(p.a[i]);
    return abs(p(x)) <= 1e-12 * scale;
  };
  for (int i = 0; i < (int)cuts.size(); ++i) {
    double l = cuts[i];
    if (isRoot(l)) ret.push_back(l);
    if (i + 1 == (int)cuts.size()) break;
    double h = cuts[i + 1];
    if (isRoot(l) || isRoot(h) || (p(l) > 0) == (p(h) > 0)) continue;
    bool sign = p(l) > 0;
    for (int it = 0; it < 80; ++it) {
      double m = l + (h - l) / 2;
      if (m == l || m == h) break;
      if ((p(m) > 0) == sign) l = m;
      else h = m;
    }
    ret.push_back(l + (h - l) / 2);
  }
  return ret;
}
