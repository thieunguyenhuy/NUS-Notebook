/**
 * Author: Thieu Nguyen Huy
 * Description: Ordered set.
 * Usage: 0-indexed. 
 * find_by_order(x) returns x-th element (ascending order)
 * order_of_key(x) returns no. of elements <x.
 * Time: O(\log N) for each operation
 * Status: Tested on one problem.
 */
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T>
using orderset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
