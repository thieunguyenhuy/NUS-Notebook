#include "../utilities/template.h"
#include "../../content/math/GaussElimination2.h"

int main(){using namespace Gauss;vector<T>a(1);a[0][0]=a[0][1]=1;init(1,1,a);assert(gauss()==1&&ans[0]);a[0].reset();init(1,1,a);assert(gauss()==0&&!ans[0]);}
