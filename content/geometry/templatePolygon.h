/**
 * Author: Le Pham Duy Khoa
 * Description: Polygon algorithms.
 */
//Note: double is not needed before the final step. Works when geo\_T = ll;
//Points need to be given in ccw or cw, if cw then $ans = -2 \times area$.
double polygon_area(vector<pt> v){
  if(v.size() < 3) return 0;
  geo_T ans = 0;
  for(int i = 1; i + 1 < v.size(); i++) 
    ans += cross(v[i] - v[0], v[i + 1] - v[0]);
  return abs(ans) / 2.0;
}