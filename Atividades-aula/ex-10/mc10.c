#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>

#define N 100000	// número de passos

int main(){
	double uniform(double min, double max);
	double func(double gamma, double x);
	int seed = time(NULL);
	
	// Criação da pasta da simulação e comando de análise
    char pasta[20], saida1[50], saida2[50], info[50];
    sprintf(pasta, "N-%d", N);
    sprintf(saida1, "%s/out1.dat", pasta);
    sprintf(saida2, "%s/out2.dat", pasta);
    sprintf(info, "%s/info.txt", pasta);

    if(mkdir(pasta, 0777) == -1){
    	printf("Já existe, vou limpar\n");
    	remove(saida1);
    	remove(saida1);
    	remove(info);
    }
	FILE *intg1 = fopen(saida1, "w");
	FILE *intg2 = fopen(saida2, "w");
	FILE *informa = fopen(info, "w");

    char comando[50];
    sprintf(comando, "python3 plot.py %s\n", pasta);
    printf("%s", comando);
	//___________________DINAMICA___________________________
	double rand;
	double I = 0.;
	
	clock_t tic = clock();
	// I(0.8)
	for(int n = 1; n <= N; ++n){
		rand = uniform(0, 1);
		I += func(.8, rand);
		fprintf(intg1, "%lf\n", I/((double)n));
	}
	
	// I(-0.8)
	I = 0.;
	for(int n = 1; n <= N; ++n){
		rand = uniform(0, 1);
		I += func(-.8, rand);
		fprintf(intg2, "%lf\n", I/((double)n));
	}
	
	clock_t toc = clock();
	double time = (double)(toc - tic)/CLOCKS_PER_SEC;
	
	// Escreve arquivo de informações sobre a simulação
	fprintf(informa, "seed = %d\n", seed);
	fprintf(informa, "\n#define N %d	// número de passos\n", N);
	fprintf(informa, "tempo de execução = %.3lfs", time);
	
	fclose(intg1);
	fclose(intg2);
	fclose(informa);
	return 0;
}

double func(double gamma, double x){
	return pow(x, gamma);
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

