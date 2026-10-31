/**
 * Author: chilli, Takanori MAEHARA
 * Date: 2019-10-31
 * License: CC0
 * Source: https://github.com/spaghetti-source/algorithm/blob/master/geometry/_geom.cc#L744
 * Description: Returns the area of the intersection of a circle with a
 * ccw polygon.
 * Time: O(n)
 * Status: Tested on one problem, stress-tested.
 */
#include "templatePoint.h"
double circlePoly(pt c, double r, vector<pt> ps) {
  auto arg = [](pt p, pt q) { return atan2(cross(p, q), dot(p, q)); };
  auto tri = [&](pt p, pt q) {
    auto r2 = r * r / 2;
    pt d = q - p;
    auto d2 = sq_len(d), a = dot(d, p) / d2, b = (sq_len(p) - r * r) / d2;
    auto det = a * a - b;
    if (det <= 0) return arg(p, q) * r2;
    auto s = max(0., -a-sqrt(det)), t = min(1., -a+sqrt(det));
    if (t < 0 || 1 <= s) return arg(p, q) * r2;
    pt u = p + d * s, v = p + d * t;
    return arg(p, u) * r2 + cross(u, v) / 2 + arg(v, q) * r2;
  };
  auto sum = 0.0;
  for (int i = 0; i < ps.size(); ++i)
    sum += tri(ps[i] - c, ps[(i + 1) % ps.size()] - c);
  return sum;
}
