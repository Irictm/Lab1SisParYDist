#ifndef __FitsReader_h__
#define __FitsReader_h__
#include "Position.h"
#include "fitsio.h"

class FitsReader
{
    public:
    /// @brief Reads the fits file and analizes it
    /// @param file_path The path of the fits file
    FitsReader(char* file_path);

    /// @brief Gets the positions of border of the image
    /// @return 
    Position** getBorder(){ return border; };

    /// @brief Gets the ammount of borders found
    /// @return 
    int getBorderCount(){ return border_count; };

    /// @brief Gets the biggest image size comparing both axis
    /// @return 
    long getImageMaxSize() { return size[0] > size[1] ? size[0] : size[1];}
    
    /// @brief Prints to the stdout the found points in two columns X and Y
    void printBorder();

    private:
    fitsfile *file_ptr;
    long size[2];
    Position** border;
    int border_count = 0;
};

#endif