#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "util/Position.h"
#include "util/Ellipse.h"
#include "util/FitsReader.h"
#include "util/HoughTransform.h"


int main(){
    // Read the image and obtain the border
    FitsReader reader = FitsReader("elipsesimple1.fits");
    int image_size = reader.getImageMaxSize();
    int border_count = reader.getBorderCount();
    Position** border = reader.getBorder();
    
    HoughTransform transform = HoughTransform();

    Ellipse** found_ellipses = transform.findEllipses(border, border_count, image_size, 10, 1000, 0.25);
    long found_ellipses_count = transform.getFoundEllipsesCount();

    for(int i=0; i<=found_ellipses_count; i++){
        printf("\t%i %i %.2f %.2f %.2f\n", 
            found_ellipses[i]->getPositionX(), found_ellipses[i]->getPositionY(),
            found_ellipses[i]->getBiggestAxis(), found_ellipses[i]->getSmallestAxis(),
            found_ellipses[i]->getAngle()
        );
    }
}