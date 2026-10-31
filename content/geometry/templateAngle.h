//FILE: Angle.h
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
//EOF File: Angle.h
//Find smallest angle between a.p and b.p
pair<angle, angle> segment_angle(pt p, pt q){
  angle a = angle(p), b = angle(q);
  if(b < a) swap(a, b);
  if(b < a.turn_180()) return {a, b};
  else return {b, a.turn_360()};
}
//add angle a and vector v. Ensures that the new angle 
//is in [a - 180, a + 180]
angle add_angle(angle a, pt v) {
  angle r(a.p + v, a.t);
  if (a.turn_180() < r) r.t--;
  return r.turn_180() < a ? r.turn_360() : r;
}
angle angle_diff(angle a, angle b){ // angle a - angle b
  int tu = a.t - b.t; b.t = a.t;
  return angle(dot(b.p, a.p), cross(b.p, a.p), tu - (a < b));
}
