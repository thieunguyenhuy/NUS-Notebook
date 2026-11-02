#pragma once
#include "TemplatePoint.h"
#include "TemplateSegment.h"
/**
 * Author: Le Pham Duy Khoa
 * Description: Polygon. Works when geo\_T=ll except for polygonCenter.
 */
//Note: double is not needed before the final step.
//Points need to be given in ccw or cw, if cw then $ans = -2 \times area$.
double polygon_area(vector<pt> v){
  if(v.size() < 3) return 0;
  geo_T ans = 0;
  for(int i = 1; i + 1 < v.size(); i++) 
    ans += cross(v[i] - v[0], v[i + 1] - v[0]);
  return abs(ans) / 2.0;
}
/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Returns true if p lies within the polygon. If strict is true,
 * it returns false for points on the boundary. The algorithm uses
 * products in intermediate steps so watch out for overflow.
 * Time: O(n)
 * Usage:
 * vector<P> v = {P{4,4}, P{1,2}, P{2,1}};
 * bool in = inPolygon(v, P{3, 3}, false);
 * Status: stress-tested and tested on kattis:pointinpolygon
 */
bool inPolygon(vector<pt> &p, pt a, bool strict=false){
  int cnt = 0, n = p.size();
  for(int i = 0; i < n; i++){
    pt q = p[(i + 1) % n];
    if (on_seg(a, make_pair(p[i], q))) return !strict;
    if(((a.y < p[i].y) - (a.y < q.y)) * cross(p[i] - a, q - a) > 0) cnt ^= 1;
  }
  return cnt;
}

/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-08
 * License: CC0
 * Source:
 * Description: Returns the center of mass for a polygon.
 * Time: O(n)
 * Status: Tested
 */
#pragma once
pt polygonCenter(vector<pt>& v) {
  pt res(0, 0); geo_T A = 0;
  for (int i = 0, j = (int)v.size() - 1; i < (int)v.size(); j = i++) {
    geo_T cr = cross(v[j], v[i]);
    res = res + (v[i] + v[j]) * cr; A += cr;
  }
  return res / A / 3;
}

