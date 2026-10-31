/**
 * Author: KickingKun
 * Description: Li Chao Tree, can query min and add line.
 * Time: Both operations are O(\log N)
 * Status: Tested by KickingKun
*/
struct LiChaoTree {
  //range for x is in [-lim, lim].
  static const ll lim = 1e9, INF = 1e18;
  struct Line {
    ll a, b;
    ll operator() (ll x) {
      return a * x + b;
    }
  };
  struct node {
    Line line;
    node *l, *r;
    node() {
      line = {0, INF};
      l = r = NULL;
    }
  };
  node *root = new node();
  ll query(node *i, ll l, ll r, ll x) {
    if (i == NULL || x < l || x > r) return INF;
    ll m = (l + r) >> 1;
    ll ans = i->line(x);
    ans = min(ans, query(i->l, l, m, x));
    ans = min(ans, query(i->r, m + 1, r, x));
    return ans;
  }
  ll query(ll x) { 
    return query(root, -lim, lim, x); 
  }
  void add(Line li, node *&cur, ll l, ll r) { 
    if (cur == nullptr){ 
      cur = new node(); cur->line = li;
      return;
    }
    ll mid = (l + r) >> 1;
    if (li(mid) < cur->line(mid)) swap(li, cur->line);
    if (li(l) < cur->line(l)) add(li, cur->l, l, mid);
    if (li(r) < cur->line(r)) add(li, cur->r, mid + 1, r);
  }
  void add(ll m, ll b) { 
    add({m, b}, root, -lim, lim); 
  }
} cht;
