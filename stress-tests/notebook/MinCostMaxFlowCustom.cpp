#include "../utilities/template.h"
#include "../../content/graph/MinCostMaxFlow.h"

int main(){MCMF f(4);f.add(1,2,2,3);f.add(1,3,1,1);f.add(3,2,1,-2);f.add(2,4,3,1);f.add(3,4,1,10);assert(f.minCost(1,4)==make_pair(3LL,8LL));}
