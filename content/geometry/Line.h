/**
 * Author: Le Pham Duy Khoa
 * Description: Line representation. line is represented by a vector v and a number c,
 * denoting all points p such that v \times p=c. Note that v is parallel to the line.
 * geo_T is the type of the number/vector (double or int or ll).
 */
#include "Point.h"
struct line{
  pt v; geo_T c;
  line() {}
  line(pt v, geo_T c): v(v), c(c) {} 
  //from equation ax+by=c
  line(geo_T a, geo_T b, geo_T c): v(b, -a), c(c) {}
  //assume a != b
  line(pt a, pt b): v(b - a), c(cross(v, a)) {}
  friend ostream& operator<<(ostream &os, line l){
    os << l.v << ' ' << l.c << endl; return os;
  }
  geo_T side(pt p){ return cross(v, p) - c;}
};