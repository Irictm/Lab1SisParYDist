#ifndef __Ellipse_h__
#define __Ellipse_h__
#include "Position.h"

class Ellipse
{
    public:
    Position* center;
    double biggest_axis, smallest_axis;
    double angle;

    Ellipse(Position* center, double biggest_axis, double smallest_axis, double angle);

    static double calcBiggestAxis(Position* first, Position* second);
    static Position* calcCenter(Position* first, Position* second);
    static double calcAngle(Position* first, Position* second);
    static double calcSmallestAxis(Position* center, Position* point, double biggest_axis, double angle);


    int getPositionX(){ return center->x; };
    int getPositionY(){ return center->y; };
    double getBiggestAxis(){  return biggest_axis; };
    double getSmallestAxis(){ return smallest_axis; };
    double getAngle(){ return angle; };
};

#endif