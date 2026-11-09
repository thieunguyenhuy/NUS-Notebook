#include "TemplatePoint.h"
#include "TemplateSegment.h"
/**
 * Author: Le Pham Duy Khoa
 * Description: Common polygon functions. 
 * Works when geo\_T=ll except for polygon\_center.
 */
double signed_polygon_area(vector<pt> &v){
  if(v.size() < 3) return 0;
  geo_T ans = 0;
  for(int i = 1; i + 1 < v.size(); i++) 
    ans += cross(v[i] - v[0], v[i + 1] - v[0]);
  return ans / 2.0;
}
double polygon_area(vector<pt> &v){ 
  return abs(signed_polygon_area(v));
}
//check whether polygon is in ccw order
bool check_ccw(vector<pt> &v){return signed_polygon_area(v) >= 0;}
//check whether a is in polygon. turns strict=true to reject if a is in boundary.
bool in_polygon(vector<pt> &p, pt a, bool strict=false){
  int cnt = 0, n = p.size();
  for(int i = 0; i < n; i++){
    pt q = p[(i + 1) % n];
    if (on_seg(a, make_pair(p[i], q))) return !strict;
    if(((a.y < p[i].y) - (a.y < q.y)) * cross(p[i] - a, q - a) > 0) cnt ^= 1;
  }
  return cnt;
}
//returns the center of mass of a polygon
pt polygon_center(vector<pt>& v) {
  pt res(0, 0); geo_T A = 0;
  for (int i = 0, j = (int)v.size() - 1; i < (int)v.size(); j = i++) {
    geo_T cr = cross(v[j], v[i]);
    res = res + (v[i] + v[j]) * cr; A += cr;
  }
  return res / A / 3;
}

