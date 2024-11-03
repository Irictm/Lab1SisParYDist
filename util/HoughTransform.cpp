#include "HoughTransform.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>


Ellipse** HoughTransform::findEllipses(Position** border, long border_count, long image_size, double min_biggest_axis, long qty_smallest_axis, double relative_min_votes){
    double smallest_axis_resolution = (double) (image_size) / qty_smallest_axis;
    int max_qty_ellipses = image_size;

    int* votes = (int*) calloc(qty_smallest_axis, sizeof(int));
    found_ellipses = (Ellipse**) calloc(max_qty_ellipses, sizeof(Ellipse*));
    int last_found_ellipse = -1;

    for (int i = 0; i < border_count; i++) {
        for (int j = 0; j < border_count; j++) {
            // Resets the votes
            memset(votes, 0, qty_smallest_axis * sizeof(int));

            // Selects two positions from which calculate the ellipse
            Position* first = border[i];
            Position* second = border[j];

            // Calculates the biggest axis and discards the ellipse if its not large enough
            double biggest_axis = Ellipse::calcBiggestAxis(first, second);
            if (biggest_axis < min_biggest_axis)
                continue;

            // Calculates the rest of the parameters of the ellipse
            Position* center = Ellipse::calcCenter(first, second);
            double angle = Ellipse::calcAngle(first, second);

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
                double smallest_axis = Ellipse::calcSmallestAxis(center, third, biggest_axis, angle);

                if (std::isnan(smallest_axis))
                    continue;

                votes[(int) round(smallest_axis / smallest_axis_resolution)]++;
            }
            
            // Filters out all the invalid ellipses based on the votes of the smallest axis size
            for (int idx_vote = 1; idx_vote < qty_smallest_axis; idx_vote++){
                double discrete_smallest = idx_vote * smallest_axis_resolution;

                // The votes should be bigger than the required minimum of the countour of the circumference
                if (votes[idx_vote] <= Ellipse::calcCircumference(biggest_axis, discrete_smallest) * relative_min_votes)
                    continue;
                
                found_ellipses[++last_found_ellipse] = new Ellipse(center, biggest_axis, discrete_smallest, angle);
            }

            // If there is not a single found ellipse, then the center of the ellipse memory is freed
            if(last_found_ellipse == -1)
                delete center;
        }
    }

    // Updates the found ellipse count
    found_ellipses_count = last_found_ellipse;

    return found_ellipses;
}