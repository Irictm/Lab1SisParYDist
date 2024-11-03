#include "FitsReader.h"
#include <stdlib.h>


FitsReader::FitsReader(char* file_path){
    int status = 0;
    long file_pixel = 1;

    fits_open_file(&file_ptr, file_path, READONLY, &status);

    fits_get_img_size(file_ptr, 2, size, &status);

    double *image = (double *) malloc(size[0]*size[1]*sizeof(double));

    fits_read_img(file_ptr, TDOUBLE, file_pixel, size[0]*size[1], NULL, image, NULL, &status);
    
    for(int i=0; i<size[0]*size[1]; i++){
        if(image[i] > 128){
            border_count++;
        }
    }

    border = (Position**) malloc(border_count * sizeof(Position*));

    int border_indx = 0;
    for(int i=0; i<size[0]*size[1]; i++){
        if(image[i] > 128){
            border[border_indx++] = new Position(i % size[0], i / size[1]);
        }
    }
}


void FitsReader::printBorder(){
    for(int i=0; i<border_count; i++){
        printf("%d %d\n", border[i]->x, border[i]->y);
    }
}