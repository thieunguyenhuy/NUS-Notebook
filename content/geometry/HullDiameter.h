/**
 * Author: Le Pham Duy Khoa
 * Date: 2019-05-05
 * Source: https://codeforces.com/blog/entry/133763
 * Description: Returns the two points with max distance on a polygon.
 * If polygon is convex then no need to include ConvexHull.h.
 * Time: O(n)
 */
#include "templatePoint.h"
#include "ConvexHull.h"
pair<pt, pt> hull_diameter(vector<pt> v, bool convex=true){
  if(!convex) v = convex_hull(v);
  int n = v.size(), ptr = 0; pair<pt, pt> ans = {v[0], v[0]};
  if(n == 1) return {v[0], v[0]};
  else if(n == 2) return {v[0], v[1]};
  auto upd = [&](pt &x, pt &y){ 
    if(sq_len(x - y) > sq_len(ans.fi - ans.se)) ans = {x, y};
  };
  for(int i = 0; i < n; i++){
    pt dir = v[(i + 1) % n] - v[i];
    for(;;ptr = (ptr + 1) % n){
      int p1 = sign(cross(dir, v[ptr] - v[(ptr + n - 1) % n]));
      int p2 = sign(cross(dir, v[(ptr + 1) % n] - v[ptr]));
      if(ptr != i && ptr != (i + 1) % n && p1 != p2) break;
    }
    upd(v[i], v[ptr]), upd(v[(i + 1) % n], v[ptr]);
    if(cross(dir, v[(ptr + 1) % n]) == 0){
      upd(v[i], v[(ptr + 1) % n]), upd(v[(i + 1) % n], v[(ptr + 1) % n]);
    }
  }
  return ans;
}
