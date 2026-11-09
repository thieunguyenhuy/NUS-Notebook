/**
 * Author: Le Pham Duy Khoa
 * Description: Line representation and common line functions. line is represented by a vector $v$ and a number $c$,
 * denoting all points $p$ such that $v \times p=c$. Note that $v$ is parallel to the line.
 * Works for geo\_T = ll except for line\_proj and line\_intersect
 */
#include "TemplatePoint.h"
//assume v is nonzero.
struct line{
  pt v; geo_T c;
  line(pt a, pt b): v(b - a), c(cross(v, a)) {}
  geo_T side(pt p){ return cross(v, p) - c;}
};
//get the shortest distance from p to a point in line l.
double line_dist(pt p, line l) {return abs(l.side(p)) / len(l.v);}
//get the perpendicular line of l through point p
line perp_line(pt p, line l) { return line(p, p + perp(l.v));}
//get line projection, set refl=true to get line reflection instead
pt line_proj(pt p, line l, bool refl=false){
  return p - perp(l.v) * l.side(p) * (1 + refl) / sq_len(l.v);
}
pt line_intersect(line l1, line l2){
  assert(cross(l1.v, l2.v) != 0); //assume non-parallel lines
  return (l2.v * l1.c - l1.v * l2.c) / cross(l1.v, l2.v);
}
