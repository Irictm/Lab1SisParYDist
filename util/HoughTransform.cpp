#include "HoughTransform.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <omp.h>


Ellipse** HoughTransform::findEllipses(Position** border, long border_count, long image_size, double min_biggest_axis, long qty_smallest_axis, double relative_min_votes, int main_threads, int secondary_threads){
    double smallest_axis_resolution = (double) (image_size) / qty_smallest_axis;
    long max_qty_ellipses = image_size * image_size;

    found_ellipses = (Ellipse**) calloc(max_qty_ellipses, sizeof(Ellipse*));
    found_ellipses_count = -1;

    #pragma omp parallel num_threads(main_threads)
    #pragma omp for
    for (long i = 0; i < border_count; i++) {
        int* votes = (int*) calloc(qty_smallest_axis, sizeof(int));
        for (long j = 0; j < border_count; j++) {
            // Resets the votes
            memset(votes, 0, qty_smallest_axis * sizeof(int));
            long new_ellipses = 0;

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

            #pragma omp parallel num_threads(secondary_threads)
            #pragma omp for 
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
                
                #pragma omp critical(vote)
                votes[(int) round(smallest_axis / smallest_axis_resolution)]++;
            }
            
            // Filters out all the invalid ellipses based on the votes of the smallest axis size
            for (int idx_vote = 1; idx_vote < qty_smallest_axis; idx_vote++){
                double discrete_smallest = idx_vote * smallest_axis_resolution;

                // The votes should be bigger than the required minimum of the countour of the circumference
                if (votes[idx_vote] <= Ellipse::calcCircumference(biggest_axis, discrete_smallest) * relative_min_votes)
                    continue;
                
                new_ellipses++;
                #pragma omp critical(register_ellipse)
                found_ellipses[++found_ellipses_count] = new Ellipse(center, biggest_axis, discrete_smallest, angle);
            }

            // If there is not a single found ellipse, then the center of the ellipse memory is freed
            if(new_ellipses == 0)
                delete center;
        }
        delete[] votes;
    }

    // Adds the last found ellipse to the count
    found_ellipses_count++;

    return found_ellipses;
}