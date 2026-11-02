/**
 * Author: Le Pham Duy Khoa
 * Source: https://github.com/ngthanhtrung23/ACM_Notebook_new
 * Description: Determine whether a point t lies inside a convex 
 * polygon with no collinear points. The polygon can be in ccw or cw order. 
 * If strict is true, points on the boundary aren't included.
 * If v.size() >= 3, then no need to include TemplateSegment.h
 * Status: Tested on Atcoder
 * Time: $O(\log N)$
 */
#pragma once
#include "TemplatePoint.h"
#include "TemplateSegment.h"
bool in_convex_poly(vector<pt> &v, pt p, bool strict=false){
  int low = 1, high = v.size() - 1, r = !strict, n = v.size();
  if(n <= 2) return r && on_seg(p, {v[0], v[1 % n]});
  if(cross(v[1] - v[0], v[n - 1] - v[0]) < 0) swap(low, high); 
  if(sign(cross(p - v[0], v[high] - v[0])) <= -r) return false;
  if(sign(cross(p - v[0], v[low] - v[0])) >= r) return false;
  while(abs(high - low) > 1){
    int mid = ((low + high) >> 1);
    if(sign(cross(v[mid] - v[0], p - v[0])) == 1) low = mid;
    else high = mid;
  }
  return (cross(v[high] - v[low], p - v[low]) > -r);
}
