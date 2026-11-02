/**
 * Author: Le Pham Duy Khoa
 * Source: https://codeforces.com/blog/entry/48868
 * Description: Returns all segments of the intersection 
 * between a simple polygon and a line.
 * The points must be given in ccw order.
 * Time: O(n \log n)
 */
#pragma once
#include "TemplatePoint.h"
#include "TemplateLine.h"
vector<pair<pt, pt>> line_poly_inter(vector<pt> &v, line l){
  vector<pt> inter; vector<pair<pt, pt>> ans; int n = v.size();
  int prev = sign(l.side(v[n - 1])), curr = sign(l.side(v[0]));
  if(v.size() <= 2 && !l.side(v[0]) && !l.side(v[1])) ans.push_back({v[0], v[1]});
  for(int i = 0; i < n; i++){
    int nxt = sign(l.side(v[(i + 1) % n]));
    if(curr){
      if(nxt == -curr) 
        inter.push_back(line_intersect(l, line(v[i], v[(i + 1) % n])));
    }
    else if(prev && nxt){
      inter.push_back(v[i]);
      if(prev == nxt) inter.push_back(v[i]);
    }
    else if(!prev && nxt){
      if(sign(dot(l.v, v[i] - v[(i + n - 1) % n])) == nxt) inter.push_back(v[i]);    
    }
    else if(prev && !nxt){
      if(sign(dot(l.v, v[(i + 1) % n] - v[i])) == prev) inter.push_back(v[i]);
    }
    prev = curr, curr = nxt;
  }
  auto cmp = [&](pt &a, pt &b){ return dot(l.v, a) < dot(l.v, b);};
  sort(inter.begin(), inter.end(), cmp);
  for(int i = 0; i < inter.size(); i += 2) ans.push_back({inter[i], inter[i + 1]});
  return ans;
}