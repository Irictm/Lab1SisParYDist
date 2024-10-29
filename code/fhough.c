#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int calc_o_x(int t_x, int u_x) {
	return (t_x + u_x)/2;
}

int calc_o_y(int t_y, int u_y) {
	return (t_y + u_y)/2;
}

double calc_alpha(int t_x, int t_y, int u_x, int u_y) {
	double numerator = (u_x - t_x)*(u_x - t_x) + (u_y - t_y)*(u_y - t_y);
	return sqrt(numerator)/2;
}

double calc_theta(int t_x, int t_y, int u_x, int u_y) {
	double res = (u_y - t_y)/(u_x - t_x);
	return atan(res);
}

double calc_delta(int o_x, int o_y, int k_x, int k_y) {
	double numerator = (k_y - o_y)*(k_y - o_y) + (k_x - o_x)*(k_x - o_x);
	return sqrt(numerator);
}

double calc_gamma(int o_x, int o_y, int k_x, int k_y, double theta) {
	return sin(theta) * (k_y - o_y) + cos(theta) * (k_x - o_x);
}

double calc_beta(int o_x, int o_y, int k_x, int k_y, double alpha, double theta) {
	double delta = calc_delta(o_x, o_y, k_x, k_y);
	double gamma = calc_gamma(o_x, o_y, k_x, k_y, theta);
	double val1 = alpha*alpha*delta*delta;
	double val2 = alpha*alpha*gamma*gamma;
	double val3 = alpha*alpha - gamma*gamma;
	return sqrt((val1 - val2)/val3);
}

double calc_dist_squared(o_x, o_y, k_x, k_y) {
	return (k_y - o_y)*(k_y - o_y) + (k_x - o_x)*(k_x - o_x);
}