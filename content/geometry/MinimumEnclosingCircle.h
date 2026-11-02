/**
 * Author: Le Pham Duy Khoa
 * Description: Computes the minimum circle that encloses a set of points.
 * The code has lots of precision problems, so please use long double instead of double.
 * Time: expected O(n)
 * Status: Tested on library checker (with long double instead).
 */
#pragma once
const double EPS = 1e-10;
mt19937 rng(6736);
#include "TemplatePoint.h"
#include "TemplateCircle.h"
pair<pt, double> min_enclosing_circle(vector<pt> v){
  shuffle(v.begin(), v.end(), rng);
  pt o = v[0]; double r = 0;
  for(int i = 0; i < v.size(); i++){
    if(r * r - sq_len(v[i] - o) >= -EPS) continue;
    o = v[i], r = 0;
    for(int j = 0; j < i; j++){
      if(r * r - sq_len(v[j] - o) >= -EPS) continue;
      o = (v[i] + v[j]) / 2.0; r = len(v[i] - o);
      for(int k = 0; k < j; k++){
        if(r * r - sq_len(v[k] - o) >= -EPS) continue;
        o = circumCenter(v[i], v[j], v[k]); r = len(v[i] - o);
      }
    }
  }
  return {o, r};
}
