// FILE: Point.h
/**
 * Author: Le Pham Duy Khoa
 * Description: Point representation. 
 * geo\_T is the type of the point (double or int or ll).
 * Note that division doesn't work when geo\_T = ll;
 */
using geo_T = double;
struct pt{
  geo_T x, y;
  pt (geo_T x=0, geo_T y=0) : x(x), y(y) {}
  
  pt operator +(pt p){ return pt(x + p.x, y + p.y);}
  pt operator -(pt p){ return pt(x - p.x, y - p.y);}
  pt operator -(){ return pt(-x, -y);}
  pt operator *(geo_T c){ return pt(x * c, y * c);}
  pt operator *(pt p){ 
    return pt(x * p.x - y * p.y, x * p.y + y * p.x);
  }
  pt operator /(double c){ return pt(x / c, y / c);}
  bool operator ==(pt p){ return x == p.x && y == p.y;}
  bool operator !=(pt p){ return x != p.x || y != p.y;}

  friend ostream& operator<<(ostream &os, pt p){
    os << p.x << ' ' << p.y; return os;
  }
};
int sign(geo_T x){ return (x < 0 ? -1 : (x == 0 ? 0 : 1));}
geo_T sq_len(pt p){ return p.x * p.x + p.y * p.y;}
double len(pt p){ return sqrtl(sq_len(p));}
geo_T dot(pt a, pt b){ return a.x * b.x + a.y * b.y;}
geo_T cross(pt a, pt b){ return a.x * b.y - a.y * b.x;}
pt perp(pt p){ return pt(-p.y, p.x);}
//EOF Point.h
//-1 if APB > 90, 0 if APB = 90, 1 if APB < 90
int check_ang(pt p, pt a, pt b) { return sign(dot(a - p, b - p));}
