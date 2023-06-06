#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 10000000  // Número de pontos
#define TC 1000		// "Tempo de correlação"

int main(){
    double uniform(double min, double max);
    int seed = time(NULL);
    srand(seed);
    
    // Criação do arquivo
    char titulo1[20], titulo2[20];
    sprintf(titulo1, "%i-N%i.txt", seed, N);
	FILE *saida = fopen(titulo1, "w");
    
    // Definições para a dinâmica
    float pi = acos(-1.);
    int Nac = 0;
    double rand1, rand2;
    int t;

    float razao;
    for(t = 0; t < N; ++t){
        rand1 = uniform(0., pi);
        rand2 = uniform(0., 1.);
        if(rand2 < sin(rand1)) Nac++;
        if(t%TC == 0){
            razao = (2.*t)/((float) Nac);
            fprintf(saida, "%d\t%f\n", t, razao);
        }
    }
    
	// Roda o script de python
	fclose(saida);
	char comando[50];
	sprintf(comando, "python3 analise5.py %s\n", titulo1);
	printf("%s\n", comando);
	system(comando);

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

