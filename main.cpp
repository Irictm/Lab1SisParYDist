#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "util/Position.h"
#include "util/Ellipse.h"
#include "util/FitsReader.h"


int main(){
    // Read the image and obtain the border
    FitsReader reader = FitsReader("elipsesimple1.fits");
    int image_size = reader.getImageMaxSize();
    int border_count = reader.getBorderCount();
    Position** border = reader.getBorder();
    
    int smallest_axis_resolution = 2;
    int qty_smallest_axis = image_size / smallest_axis_resolution;
    double min_biggest_axis = 5; // alpha
    int max_qty_ellipses = image_size;

    double biggest_axis = 0;
    double angle = 0;
    double smallest_axis = 0;
    int relative_min_votes = 100;

    int* votes = (int*) calloc(qty_smallest_axis, sizeof(int));
    Ellipse** found_ellipses = (Ellipse**) calloc(max_qty_ellipses, sizeof(Ellipse*));
    int last_found_ellipse = -1;

    for (int i = 0; i < border_count; i++) {
        for (int j = 0; j < border_count; j++) {
            // Resets the votes
            memset(votes, 0, qty_smallest_axis * sizeof(int));

            // Selects two positions from which calculate the ellipse
            Position* first = border[i];
            Position* second = border[j];

            // Calculates the biggest axis and discards the ellipse if its not large enough
            biggest_axis = Ellipse::calcBiggestAxis(first, second);
            if (biggest_axis < min_biggest_axis)
                continue;

            // Calculates the rest of the parameters of the ellipse
            Position* center = Ellipse::calcCenter(first, second);
            angle = Ellipse::calcAngle(first, second);

            // Votes for the smallest axis based on a third position
            for (int k = 0; k < border_count; k++) {
                // Only process those positions different from the current two
                if (k == i || k == j)
                    continue;

                Position* third = border[k];
                
                // If the position is farther than the biggest possible, then skip the point
                if (center->distSqrd(third) > biggest_axis * biggest_axis)
                    continue;

                // Vote for the calculated smallest axis
                smallest_axis = Ellipse::calcSmallestAxis(center, third, biggest_axis, angle);

                if(std::isnan(smallest_axis))
                    continue;

                votes[(int) round(smallest_axis / smallest_axis_resolution)]++;
            }
            
            // Filters out all the invalid ellipses based on the votes of the smallest axis size
            for (int idx_vote = 0; idx_vote < qty_smallest_axis; idx_vote++){
                if (votes[idx_vote] <= relative_min_votes)
                    continue;
                
                found_ellipses[++last_found_ellipse] = new Ellipse(center, biggest_axis, smallest_axis, angle);
            }

            // If there is not a single found ellipse, then the center of the ellipse memory is freed
            if(last_found_ellipse == -1)
                delete center;
        }
    }

    for(int i=0; i<=last_found_ellipse; i++){
        printf("\t%i %i %.2f %.2f %.2f\n", 
            found_ellipses[i]->getPositionX(), found_ellipses[i]->getPositionY(),
            found_ellipses[i]->getBiggestAxis(), found_ellipses[i]->getSmallestAxis(),
            found_ellipses[i]->getAngle()
        );
    }
}