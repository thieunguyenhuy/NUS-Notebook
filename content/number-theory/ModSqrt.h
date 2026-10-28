/**
 * Author: Simon Lindholm
 * Date: 2016-08-31
 * License: CC0
 * Source: http://eli.thegreenplace.net/2009/03/07/computing-modular-square-roots-in-python/
 * Description: Tonelli-Shanks algorithm for modular square roots. Finds $x$ s.t. $x^2 = a \pmod p$ ($-x$ gives the other solution).
 * Time: O(\log^2 p) worst case, O(\log p) for most $p$
 * Status: Tested for all a,p <= 10000
 */
#pragma once

namespace mod_sqrt_detail {
ll power(ll a, ll e, ll p) {
  ll res = 1;
  for (; e; e >>= 1, a = a * a % p)
    if (e & 1) res = res * a % p;
  return res;
}
}

ll sqrt(ll a, ll p) {
  a %= p; if (a < 0) a += p;
  if (p == 2) return a;
  if (a == 0) return 0;
  assert(mod_sqrt_detail::power(a, (p-1)/2, p) == 1); // else no solution
  if (p % 4 == 3) return mod_sqrt_detail::power(a, (p+1)/4, p);
  // a^(n+3)/8 or 2^(n+3)/8 * 2^(n-1)/4 works if p % 8 == 5
  ll s = p - 1, n = 2;
  int r = 0, m;
  while (s % 2 == 0)
    ++r, s /= 2;
  /// find a non-square mod p
  while (mod_sqrt_detail::power(n, (p - 1) / 2, p) != p - 1) ++n;
  ll x = mod_sqrt_detail::power(a, (s + 1) / 2, p);
  ll b = mod_sqrt_detail::power(a, s, p), g = mod_sqrt_detail::power(n, s, p);
  for (;; r = m) {
    ll t = b;
    for (m = 0; m < r && t != 1; ++m)
      t = t * t % p;
    if (m == 0) return x;
    ll gs = mod_sqrt_detail::power(g, 1LL << (r - m - 1), p);
    g = gs * gs % p;
    x = x * gs % p;
    b = b * g % p;
  }
}
