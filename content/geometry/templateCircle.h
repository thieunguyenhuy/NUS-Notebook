/**
 * Author: Le Pham Duy Khoa
 * Description: Common circle geometry functions.
 * Requires geo\_T=double.
 */
#include "TemplatePoint.h"
#include "TemplateLine.h"
vector<pt> circle_circle_inter(pt o1, double r1, pt o2, double r2){
  double d_sq = sq_len(o2 - o1);
  if(d_sq == 0) return {}; //assume different circles
  double mido1_mul_d = (d_sq + r1 * r1 - r2 * r2) / 2;
  double h_sq = r1 * r1 - mido1_mul_d * mido1_mul_d / d_sq;
  vector<pt> ans;
  if(h_sq >= 0){
    pt mid = o1 + (o2 - o1) * mido1_mul_d / d_sq; 
    pt h = perp(o2 - o1) * sqrt(h_sq / d_sq);
    ans = {mid - h, mid + h};
    if (h_sq == 0) ans.pop_back();
  }
  return ans;
}
vector<pt> circle_line_inter(pt o, double r, line l){
  double h_sq = r * r - line_dist(o, l) * line_dist(o, l);
  vector<pt> ans;
  if(h_sq >= 0){
    pt mid = line_proj(o, l), h = l.v * sqrt(h_sq) / len(l.v);
    ans = {mid - h, mid + h};
    if(h_sq == 0) ans.pop_back();
  }
  return ans;
}
//if r2 > 0, gets the outer tangents of circle (o1, r1) and (o2, r2).
//if r2 < 0, gets the inner tangent of circle (o1, r1) and (o2, -r2)
//set r2 = 0 to get tangents through a point.
vector<pair<pt, pt>> tangents(pt o1, double r1, pt o2, double r2) {
  double dr = r1 - r2, d_sq = sq_len(o2 - o1);
  double h_sq = d_sq - dr * dr;
  if(d_sq == 0 || h_sq < 0) return {}; //assume different circles
  vector<pair<pt, pt>> ans;
  for (double sign : {-1, 1}) {
    pt dir = ((o2 - o1) * dr + perp(o2 - o1) * sqrt(h_sq) * sign) / d_sq;
    ans.push_back({o1 + dir * r1, o2 + dir * r2});
  }
  if (h_sq == 0) ans.pop_back();
  return ans;
}
//finds the center of the circle going through points a, b, c.
pt circumCenter(pt a, pt b, pt c) {
  b = b-a, c = c-a; assert(cross(b,c) != 0); //assume points not collinear.
  return a + perp(b * sq_len(c) - c * sq_len(b)) / (cross(b, c) * 2);
}
