#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <sys/wait.h>
 

int main(int argc, char *argv[]){
	//	VARIABLES
	int option;			// option para getopt
	int mandatory = 0;		// asegura que se entreguen ciertos argumentos de getopt

    // PARAMETROS DE ENTRADA
    char file_name_in[100];		// nombre de imagen de entrada
	int min_a;				// valor minimo para alfa
	float ratio;			// porcentaje aplicado a la circunferencia
	int betas;				// numero de betas
	int u;				// numero de hebras para el nivel1
	int d;				// numero de hebras para el nivel2
	
	// 	PROCESO RECUPERACION DE VARIABLES GETOPT
	while((option = getopt(argc, argv, "i:a:r:b:u:d:")) != -1){
		switch(option){
			case 'i':
				strcpy(file_name_in, optarg);
				mandatory += 1;
				break;
			case 'a':
				min_a = atoi(optarg);
				mandatory += 1;
				break;
			case 'r':
				ratio = atof(optarg);
				mandatory += 1;
				break;
			case 'b':
				betas = atoi(optarg);
				mandatory += 1;
				break;
			case 'u':
				u = atoi(optarg);
				mandatory += 1;
				break;
			case 'd':
				d = atoi(optarg);
				mandatory += 1;
				break;
		}
	}
	
	// si falta algun parametro obligatorio se finaliza ejecucion.
	if(mandatory < 5){
		printf("ERROR: falta parametro obligatorio - Se termina ejecucion.\n");
		return 1;
	}
	
	// 
	sprintf(min_a_str, "%d", min_a);
	sprintf(ratio_str, "%d", ratio);
	sprintf(betas_str, "%d", betas);
	sprintf(u_str, "%d", u);
	sprintf(d_str, "%d", d);
		
	char* arguments[] = {"./hough", file_name_in, min_a_str, ratio_str, betas_str, u_str, c_str, d_str, NULL};
	execv(arguments[0], arguments);	// ejecutar programa
}