//FILE: Line.h
/**
 * Author: Le Pham Duy Khoa
 * Description: Line representation. line is represented by a vector $v$ and a number $c$,
 * denoting all points $p$ such that $v \times p=c$. Note that $v$ is parallel to the line.
 * Works for geo\_T = ll;
 */
//assume v is nonzero.
struct line{
  pt v; geo_T c;
  line() {}
  line(pt v, geo_T c): v(v), c(c) {} 
  //from equation ax+by=c
  line(geo_T a, geo_T b, geo_T c): v(b, -a), c(c) {}
  line(pt a, pt b): v(b - a), c(cross(v, a)) {}
  friend ostream& operator<<(ostream &os, line l){
    os << l.v << ' ' << l.c; return os;
  }
  geo_T side(pt p){ return cross(v, p) - c;}
};
//EOF File Line.h
//works for geo_T = ll except for last two.
double line_dist(pt p, line l) {return abs(l.side(p)) / len(l.v);}
bool same_side(pt a, pt b, line l){ 
  return sign(l.side(a)) == sign(l.side(b));
} 
bool inside_line(pt p, line l){ return l.side(p) == 0;}
line perp_line(pt p, line l) { return line(p, p + perp(l.v));}

//set refl=true to get line reflection instead
pt line_proj(pt p, line l, bool refl=false){
  return p - perp(l.v) * l.side(p) * (1 + refl) / sq_len(l.v);
}
pt line_intersect(line l1, line l2){
  assert(cross(l1.v, l2.v) != 0); //assume non-parallel lines
  return (l2.v * l1.c - l1.v * l2.c) / cross(l1.v, l2.v);
}