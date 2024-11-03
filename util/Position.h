#ifndef __Position_h__
#define __Position_h__

class Position
{
    public:
    int x, y;

    Position(int x, int y);

    double distSqrd(Position* other);
};


#endif