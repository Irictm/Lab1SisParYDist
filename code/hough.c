#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef
struct Pixel {
    int x;
    int y;
} Pixel;

typedef
struct Ellipse {
    int o_x;
    int o_y;
    double alpha;
    double theta;
    double beta;
} Ellipse;

int main(int argc, char *argv[]){
    Pixel border[1000];
    Ellipse newEP[1000];
    
    int N = 2000;
    int resolution;
    double min_alpha = 0.69420;
    
    int o_x = 0;
    int o_y = 0;
    double alpha = 0;
    double theta = 0;
    double beta = 0;

    int* votes = (int *)calloc(N, sizeof(int));

    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            memset(votes, 0, N * sizeof(int));

            // Obteniendo coordenadas pixels t y u
            int t_x = border[i].x;
            int t_y = border[i].y;
            int u_x = border[j].x;
            int u_y = border[j].y;

            // Obteniendo parametros iniciales

            alpha = calc_alfa(t_x, t_y, u_x, u_y);
            if (alpha < min_alpha) {
                continue;
            }
            o_x = calc_o_x(t_x, u_x);
            o_y = calc_o_y(t_y, u_y);
            theta = calc_theta(t_x, t_y, u_x, u_y);

            for (int k = 0; k < 1000; k++) {
                // Obteniendo coordenadas pixel k
                int k_x = border[k].x;
                int k_y = border[k].y;

                // 
                if (calc_dist_squared(o_x, o_y, k_x, k_y) > alpha*alpha) {
                    continue;
                }

                // Votando beta
                beta = calc_beta(o_x, o_y, k_x, k_y, alpha, theta);
                vote(votes, beta);

            }
        }
    }
}
