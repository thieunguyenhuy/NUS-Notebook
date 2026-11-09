// FILE: Point.h
/**
 * Author: Le Pham Duy Khoa
 * Description: Point/Vector representation. 
 * geo\_T is the type of the point (double or int or ll).
 * Note that division doesn't work when geo\_T = ll (floor division);
 */
using geo_T = double;
struct pt{
  geo_T x, y;
  pt (geo_T x=0, geo_T y=0) : x(x), y(y) {}
  pt operator+(pt p){ return pt(x + p.x, y + p.y);}
  pt operator-(pt p){ return pt(x - p.x, y - p.y);}
  pt operator*(geo_T c){ return pt(x * c, y * c);}
  friend pt operator*(geo_T c, pt p){ return pt(p.x * c, p.y * c);}
  pt operator*(pt p){ 
    return pt(x * p.x - y * p.y, x * p.y + y * p.x);
  }
  pt operator/(geo_T c){ return pt(x / c, y / c);}
  bool operator==(pt p){ return x == p.x && y == p.y;}
};
int sign(geo_T x){ return (x < 0 ? -1 : (x == 0 ? 0 : 1));}
geo_T sq_len(pt p){ return p.x * p.x + p.y * p.y;}
double len(pt p){ return sqrtl(sq_len(p));}
geo_T dot(pt a, pt b){ return a.x * b.x + a.y * b.y;}
geo_T cross(pt a, pt b){ return a.x * b.y - a.y * b.x;}
//rotates a vector v by 90 degrees ccw.
pt perp(pt v){ return pt(-v.y, v.x);}
//applies the linear transformation (combination of translation, rotation, scaling)
//that moves line p-q to fp-fq on point r.
pt linearTransform(pt p, pt q, pt r, pt fp, pt fq) {
  pt pq = q - p, pr = r - p, fpq = fq - fp;
  return fp + (dot(pq, pr) * fpq + cross(pq, pr) * perp(fpq)) / sq_len(pq);
}

