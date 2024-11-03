#include "Ellipse.h"
#include <math.h>


Ellipse::Ellipse(Position* center, double biggest_axis, double smallest_axis, double angle):
    center(center), 
    biggest_axis(biggest_axis), smallest_axis(smallest_axis),
    angle(angle){}

double Ellipse::calcBiggestAxis(Position* first, Position* second){
    return sqrt(first->distSqrd(second));
}

Position* Ellipse::calcCenter(Position* first, Position* second){
    return new Position((first->x + second->x)/2, (first->y + second->y)/2);
}

double Ellipse::calcAngle(Position* first, Position* second){
    return atan2(second->y - first->y, second->x - first->x);
}


double calc_gamma(int o_x, int o_y, int k_x, int k_y, double theta) {
	return sin(theta) * (k_y - o_y) + cos(theta) * (k_x - o_x);
}

double Ellipse::calcSmallestAxis(Position* center, Position* point, double biggest_axis, double angle){
	double biggest_axis_sqrd = biggest_axis * biggest_axis;
    double delta_sqrd = center->distSqrd(point);
	double gamma_sqrd = 
        sin(angle) * (point->y - center->y) + 
        cos(angle) * (point->x - center->x);
    gamma_sqrd *= gamma_sqrd;

	return sqrt((biggest_axis_sqrd * delta_sqrd - biggest_axis_sqrd * gamma_sqrd)/(biggest_axis_sqrd - gamma_sqrd));
}