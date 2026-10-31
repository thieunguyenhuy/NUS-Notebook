/**
 * Author: Le Pham Duy Khoa
 * Description: Returns the convex hull given set of points v in ccw order.
 * Works when geo\_T = ll;
 * Time: O(n \log n)
*/
#include "templatePoint.h"
vector<pt> convex_hull(vector<pt> v){
  if(v.size() <= 1) return v;
  auto cmp = [&](pt &a, pt &b){ return tie(a.x, a.y) < tie(b.x, b.y);};
  sort(v.begin(), v.end(), cmp);
  vector<pt> st; st.reserve(v.size() + 5);
  int s = 0;
  for(int _ = 0; _ < 2; _++){
    for(pt p: v){
      while(st.size() >= s + 2){
        pt a = st[st.size() - 2];
        if(cross(st.back() - a, p - a) <= 0) st.pop_back();
        else break;
      }
      st.push_back(p);
    }
    reverse(v.begin(), v.end()); st.pop_back(); s = st.size();
  }
  if(st.size() == 2 && st[0] == st[1]) st.pop_back();
  return st;
}