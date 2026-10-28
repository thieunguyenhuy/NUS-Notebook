#include "../utilities/template.h"
#include "../../content/geometry/Geometry.h"

int main(){assert(polygon_area({})==0);assert(polygon_area({Point(1,2)})==0);assert(dist(Point(3,4),Point(0,0),Point(0,0))==5);}
