/**
 * Author: Le Pham Duy Khoa
 * Description: Circle geometry algorithms.
 */
vector<pt> circleCircle(pt o1, double r1, pt o2, double r2){
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
vector<pt> circleLine(pt o, double r, line l){
  double h_sq = r * r - line_dist(o, l) * line_dist(o, l);
  vector<pt> ans;
  if(h_sq >= 0){
    pt mid = line_proj(o, l), h = l.v * sqrt(h_sq) / len(l.v);
    ans = {mid - h, mid + h};
    if(h_sq == 0) ans.pop_back();
  }
  return ans;
}
/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-10-31
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Finds the external tangents of two circles, or internal if r2 < 0 (radius |r2| in this case).
 * Can return 0, 1, or 2 tangents -- 0 if one circle contains the other (or overlaps it, in the internal case, or if the circles are the same);
 * 1 if the circles are tangent to each other (in which case .first = .second and the tangent line is perpendicular to the line between the centers).
 * .first and .second give the tangency points at circle 1 and 2 respectively.
 * To find the tangents of a circle with a point set r2 to 0.
 * Status: tested
 */
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
/**
 * Author: Le Pham Duy Khoa
 * Source: cp-geo
 * Description: Find the center of the circle that goes through 3 points A, B, C.
 * Status: tested
 */
pt circumCenter(pt a, pt b, pt c) {
  b = b-a, c = c-a; assert(cross(b,c) != 0); //assume points not collinear.
  return a + perp(b * sq_len(c) - c * sq_len(b)) / (cross(b, c) * 2);
}
