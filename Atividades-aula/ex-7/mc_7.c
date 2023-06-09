#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 1000000  // Número de pontos
#define TC 100		// "Tempo de correlação"

int main(){
    double uniform(double min, double max);
    int seed = time(NULL);
    srand(seed);
    
    // Criação do arquivo
    char titulo1[20], titulo2[20];
    sprintf(titulo1, "%i-N%i.txt", seed, N);
	FILE *saida = fopen(titulo1, "w");
    
    // Definições para a dinâmica
    int Nac = 0;			// Número de acertos
    double rand1, rand2;
    int t;
    float razao;

    for(t = 0; t < N; ++t){
        rand1 = uniform(0., 1.);
        rand2 = uniform(0., 1.);
        if(rand2 < pow(sin(1./rand1), 2)) Nac++;
        if(t%TC == 0){
            razao = ((float) Nac)/(t);
            fprintf(saida, "%d\t%f\n", t, razao);
        }
    }
    
	// Roda o script de python
	fclose(saida);
	char comando[50];
	sprintf(comando, "python3 analise7.py %s\n", titulo1);
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

