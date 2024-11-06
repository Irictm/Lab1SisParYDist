#ifndef __HoughTransform_h__
#define __HoughTransform_h__
#include "Ellipse.h"
#include "Position.h"

class HoughTransform
{
    public:
    /// @brief Finds the ellipses from the border
    /// @param border 
    /// @param border_count 
    /// @param image_size 
    /// @return 
    Ellipse** findEllipses(Position** border, long border_count, long image_size, double min_biggest_axis, long qty_smallest_axis, double relative_min_votes, int main_threads, int secondary_threads);
    
    /// @brief Gets the ammount of ellipses found
    /// @return 
    long getFoundEllipsesCount(){ return found_ellipses_count; }

    /// @brief Gets the time that the serial part of the program elapsed.
    /// @return 
    double getSerialTime(){ return serial_time; }

    /// @brief Gets the time that the Hough transform part of the program elapsed.
    /// @return 
    double getHoughTime(){ return hough_time; }

    private:
    // Hough transform results
    Ellipse** found_ellipses;
    long found_ellipses_count = -1;

    // Time of execution results
    double serial_time;
    double hough_time;
};

#endif