/**
 * Author: Le Pham Duy Khoa
 * Source: https://cp-algorithms.com/geometry/manhattan-distance.html
 * Description: Given N points, returns up to 4*N edges, which are guaranteed
 * to contain a minimum spanning tree for the graph with edge weights w(p, q) =
 * |p.x - q.x| + |p.y - q.y|. Edges are returned in pair of indices.
 * Time: $O(N \log N)$
 * Status: Tested on Library Checker
 */
#pragma once
#include "TemplatePoint.h"
vector<pair<int, int>> manhattan_mst(vector<pt> v){
  vector<pair<int, int>> ans; vector<int> order(v.size()); 
  iota(order.begin(), order.end(), 0);
  for(int rot = 0; rot < 4; rot++){
    set<pair<int, int>> se;
    auto cmp = [&](int i, int j){ return v[i].x + v[i].y < v[j].x + v[j].y;};
    sort(order.begin(), order.end(), cmp);
    for(int idx: order){
      auto it = se.upper_bound({v[idx].y, 1e9 + 7});
      while(it != se.begin()){
        auto last = prev(it); int idx2 = last->se;
        if(v[idx2].x - v[idx2].y > v[idx].x - v[idx].y) break;
        ans.push_back({idx, idx2}); se.erase(last);
      }
      se.insert({v[idx].y, idx});
    }
    if(rot & 1) for(int i = 0; i < v.size(); i++) v[i].x = -v[i].x;
    else for(int i = 0; i < v.size(); i++) swap(v[i].x, v[i].y);
  }
  return ans;
}
