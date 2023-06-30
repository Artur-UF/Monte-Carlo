#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>

#define N 100000

int main(){
	double uniform(double min, double max);
	int seed = time(NULL);
	
	// Criação da pasta da simulação e comando de análise
    char pasta[20], saida1[50], saida2[50];
    sprintf(pasta, "ex5-6-N-%d", N);
    sprintf(saida1, "%s/out1.dat", pasta);
    sprintf(saida2, "%s/out2.dat", pasta);

    if(mkdir(pasta, 0777) == -1){
    	printf("Já existe, vou limpar\n");
    	remove(saida1);
    	remove(saida1);
    }
	FILE *out1 = fopen(saida1, "w");
	FILE *out2 = fopen(saida2, "w");

    char comando[50];
    sprintf(comando, "python3 hist.py %s\n", pasta);
    printf("%s", comando);
	//___________________DINAMICA___________________________
	double r;

	for(int i = 0; i < N; ++i){
		r = uniform(0., 1.);
		fprintf(out1, "%lf\n", -log(1.-r));
		fprintf(out2, "%lf\n", pow(r, 1./(1-.4)));
	}

	
	fclose(out1);
	fclose(out2);
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

