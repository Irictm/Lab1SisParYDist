#include "Position.h"


Position::Position(int x, int y): x(x), y(y){}

double Position::distSqrd(Position* other){
    return 
        (this->x - other->x) * (this->x - other->x) + 
        (this->y - other->y) * (this->y - other->y);
}
