#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "util/Position.h"
#include "util/Ellipse.h"
#include "util/FitsReader.h"
#include "util/HoughTransform.h"

/// @brief Execution modes
enum{
    NORMAL = 1, VIEW_BORDER = 2
};

int main(int argc, char *argv[]){
    // Input parameters definition
    char* file_path = nullptr;
	double min_biggest_axis = -1;
	float relative_min_votes = -1;
	long qty_smallest_axis = -1;
	int main_threads = 1;
	int secondary_threads = 1;
    int mode = NORMAL;
	
	char option;
	while((option = getopt(argc, argv, "i:a:r:b:u:d:e:")) != -1){
		switch(option){
			case 'i':
                file_path = optarg;
				break;
			case 'a':
				min_biggest_axis = atof(optarg);
				break;
			case 'r':
				relative_min_votes = atof(optarg);
				break;
			case 'b':
				qty_smallest_axis = atoi(optarg);
				break;
			case 'u':
				main_threads = atoi(optarg);
				break;
			case 'd':
				secondary_threads = atoi(optarg);
				break;
            case 'e':
                switch(atoi(optarg)){
                    case 1:
                        mode = NORMAL;
                        break;
                    case 2:
                        mode = VIEW_BORDER;
                        break;
                }
                break;
		}
	}

    // Validates the input parameters
    if(file_path == nullptr){
        printf("Please add the file path parameter '-i'\n");
        return -1;
    }

    if(mode == NORMAL){
        if(min_biggest_axis == -1){
            printf("Please add the minimum minor axis parameter '-a'\n");
            return -1;
        }
        if(relative_min_votes == -1){
            printf("Please add the minimum relative votes parameter '-r'\n");
            return -1;
        }
        if(qty_smallest_axis == -1){
            printf("Please add the ammount of smallest axis parameter '-b'\n");
            return -1;
        }
    }

    // Read the image and obtain the border
    FitsReader reader = FitsReader(file_path);
    
    if(mode == VIEW_BORDER){
        reader.printBorder();
        return 0;
    }
    
    int image_size = reader.getImageMaxSize();
    int border_count = reader.getBorderCount();
    Position** border = reader.getBorder();
    
    // Search for the ellipses
    HoughTransform transform = HoughTransform();
    Ellipse** found_ellipses = transform.findEllipses(
        border, border_count, 
        image_size, 
        min_biggest_axis, qty_smallest_axis, 
        relative_min_votes,
        main_threads, secondary_threads
    );
    long found_ellipses_count = transform.getFoundEllipsesCount();

    // Print the found ellipses
    for(int i=0; i<found_ellipses_count; i++){
        printf("\t%i %i %.2f %.2f %.2f\n", 
            found_ellipses[i]->getPositionX(), found_ellipses[i]->getPositionY(),
            found_ellipses[i]->getBiggestAxis(), found_ellipses[i]->getSmallestAxis(),
            found_ellipses[i]->getAngle()
        );
    }
}