/**
 * Author: Le Pham Duy Khoa
 * Description: Segment algorithms.
 */
//works for geo_T = ll;
bool on_seg(pt p, pair<pt, pt> s){
  return cross(p - s.fi, s.se - s.fi) == 0 && dot(p - s.fi, p - s.se) <= 0;
}
//works for geo_T = ll;
double seg_dist(pt p, pair<pt, pt> s) {
  pt v = s.se - s.fi;
  auto cmpProj = [&](pt &a, pt &b){ return dot(v, a) <= dot(v, b);};
  if(s.fi != s.se && cmpProj(s.fi, p) && cmpProj(p, s.se))
    return line_dist(p, line(s.fi, s.se));
  return min(len(p - s.fi), len(p - s.se));
}
vector<pt> seg_intersect(pair<pt, pt> s1, pair<pt, pt> s2){
  pt a = s1.fi, b = s1.se, c = s2.fi, d = s2.se;
  line l1 = line(a, b), l2 = line(c, d);
  if(!same_side(a, b, l2) && !same_side(c, d, l1))
    return {line_intersect(l1, l2)};
  vector<pt> v;
  for(pt p: {a, b}) if(on_seg(p, s2)) v.push_back(p);
  for(pt p: {c, d}) if(on_seg(p, s1)) v.push_back(p);
  auto cmp = [&](pt &a, pt &b){ return tie(a.x, a.y) < tie(b.x, b.y);};
  sort(v.begin(), v.end(), cmp); v.erase(unique(v.begin(), v.end()), v.end());
  return v;
}