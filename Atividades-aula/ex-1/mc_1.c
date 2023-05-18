#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 100
#define TF 1000

int main(){
	double uniform(double min, double max);
    double funcao(int t, int na, int n);
    int seed = time(NULL);
    srand(seed);
    
	int urnaA = N;
	int rand;
	int t = 0;
	
    char titulo1[20], titulo2[20];
    sprintf(titulo1, "%i-N%i.txt", seed, N);
    sprintf(titulo2, "exato-N%i.txt", N);
	FILE *saida = fopen(titulo1, "w");
	FILE *exato = fopen(titulo2, "w");
	
	for(t; t < TF; t++){
		rand = (int) uniform(0, N-1);
		
		if(rand < urnaA){
			urnaA--;
		}else{
			urnaA++;
		}
		
		fprintf(saida, "%i\n", urnaA);
        fprintf(exato, "%f\n", funcao(t, urnaA, N));
		
	}
	
	fclose(saida);
    fclose(exato);
	return 0;
}

double uniform(double min, double max) {
	/*
	Função que gera um número aleatório em uma distribuição uniforme
	*/
	double random  = ((double) rand()) / RAND_MAX;
	double range = (max - min) * random;
	double n = range + min;	
	
	return n;
}

double funcao(int t, int na, int n){
    return ((n/2.) + (n/2.)*pow(1-(2./n), t));
}

