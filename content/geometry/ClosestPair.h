/**
 * Author: Le Pham Duy Khoa
 * Source: https://codeforces.com/blog/entry/58747
 * Description: Finds the closest pair of points. In order to do so, 
 * sort points by x, sweep line. Denote current min as d.
 * Check all the points in rectangle (x - d, y - d); (x, y + d), there are at most 8 points.
 * Time: O(n \log n)
 */
