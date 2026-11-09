/**
 * Author: Simon Lindholm
 * Date: 2015-01-31
 * License: CC0
 * Source: me
 * Description: A class for ordering angles (represented by a point and
 * a number of rotations around the origin). Useful for rotational sweeping.
 * Note that points are ordered in counterclockwise order.
 * Works with geo\_T = ll;
 */
#include "TemplatePoint.h"
//assumes x^2 + y^2 > 0
struct angle{
  pt p; int t;
  angle(pt p, int t=0): p(p), t(t) {}
  angle(geo_T x, geo_T y, int t=0): p(x, y), t(t) {}
  int half(){ return p.y < 0 || (p.y == 0 && p.x < 0);}
  angle turn_90(){ return angle(perp(p), t + (half() && p.x >= 0));}
  angle turn_180(){ return angle(-p.x, -p.y, t + half()); }
  angle turn_360(){ return angle(p, t + 1);}
};
bool operator<(angle a, angle b){
  return make_tuple(a.t, a.half(), 0) < 
    make_tuple(b.t, b.half(), cross(a.p, b.p));
}
