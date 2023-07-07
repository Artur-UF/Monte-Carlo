#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>

#define N 100000			// número de passos
#define ZETA -.7
#define GAMMA -.8

int main(){
	double uniform(double min, double max);
	double func(double gamma, double x);
	int seed = time(NULL);
	srand(seed);
	
	// Criação da pasta da simulação e comando de análise
    char pasta[30], saida1[50], info[50];
    sprintf(pasta, "ex7_N_%d_G_%.1f_Z_%.1f", N, GAMMA, ZETA);
    sprintf(saida1, "%s/out1.dat", pasta);
    sprintf(info, "%s/info.txt", pasta);

    if(mkdir(pasta, 0777) == -1){
    	printf("Já existe, vou limpar\n");
    	remove(saida1);
    	remove(info);
    }
	FILE *intg1 = fopen(saida1, "w");
	FILE *informa = fopen(info, "w");

    char comando[50];
    sprintf(comando, "python3 plot.py %s\n", pasta);
    printf("%s", comando);
	//___________________DINAMICA___________________________
	double rand;
	double I = 0.;
	
	clock_t tic = clock();
	// I(-0.8)
	for(int n = 1; n <= N; ++n){
		rand = pow(uniform(0, 1), 1./(1+ZETA));
		I += pow(rand, GAMMA-ZETA)/(1.+ZETA);
		fprintf(intg1, "%lf\n", I/((double)n));
	}
	
	clock_t toc = clock();
	double time = (double)(toc - tic)/CLOCKS_PER_SEC;
	
	// Escreve arquivo de informações sobre a simulação
	fprintf(informa, "seed = %d\n", seed);
	fprintf(informa, "\n#define N %d	// número de passos\n#define ZETA %.1f\n#define GAMMA %.1f\n", N, ZETA, GAMMA);
	fprintf(informa, "tempo de execução = %.3lfs", time);
	
	fclose(intg1);
	fclose(informa);
	return 0;
}

double uniform(double min, double max) {
	/*
	Função que gera um número aleatório em uma distribuição uniforme
	Para int: [min, max)
	*/
	double random  = ((double) rand()) / RAND_MAX;
	double range = (max - min) * random;
	double n = range + min;	
	
	return n;
}

