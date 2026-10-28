#include "../utilities/template.h"
#include "../../content/data-structures/FenwickTree2d.h"

int main(){vector<pii>ups{{0,INT_MAX},{1,-10},{3,7},{2,7}};FT2 ft(4,ups);ft.init();ft.update(0,INT_MAX,5);ft.update(1,-10,3);ft.update(3,7,4);assert(ft.query(3,INT_MAX)==12);assert(ft.query(3,7)==7);assert(ft.query(0,INT_MAX)==5);}
