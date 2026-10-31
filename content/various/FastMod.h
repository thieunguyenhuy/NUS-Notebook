/**
 * Author: KACTL
 * Source: https://en.wikipedia.org/wiki/Barrett_reduction
 * Description: Compute $a \% b$ about 5 times faster than usual, where $b$ is constant but not known at compile time.
 * Returns a value congruent to $a \pmod b$ in the range $[0, 2b)$.
 * Status: proven correct, stress-tested
 */
struct FastMod {
  uint64_t b, m;
  FastMod(uint64_t b) : b(b), m(-1ULL / b) {}
  uint64_t reduce(uint64_t a) { // a % b + (0 or b)
    return a - (uint64_t)((__uint128_t(m) * a) >> 64) * b;
  }
};
