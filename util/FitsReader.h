#ifndef __FitsReader_h__
#define __FitsReader_h__
#include "Position.h"
#include "fitsio.h"

class FitsReader
{
    public:
    FitsReader(char* file_path);

    Position** getBorder(){ return border; };
    int getBorderCount(){ return border_count; };
    long getImageMaxSize() { return size[0] > size[1] ? size[0] : size[1];}

    private:
    fitsfile *file_ptr;
    long size[2];
    Position** border;
    int border_count = 0;
};

#endif