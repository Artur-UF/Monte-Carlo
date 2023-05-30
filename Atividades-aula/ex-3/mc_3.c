#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 100
#define TF 100000	// Tempo final
#define EE 1000		// Estado Estacionário

/*
Aqui eu olhei e assumi que 10000 seria um numero adequado para atingir o equilíbrio, talvez mais que o necessário, 
e coletei os dados dos próximos 90000 passos, também talvez mais que o necessário.
*/

int main(){
	double uniform(double min, double max);
    double funcao(int t, int na, int n);
    int seed = time(NULL);
    srand(seed);
    
    // Variaveis para simulação
	int urnaA = N;
	int rand;
	int t = 0;
	
    // Criação do arquivo
    char titulo1[20], titulo2[20];
    sprintf(titulo1, "%i-N%i.txt", seed, N);
	FILE *saida = fopen(titulo1, "w");
    
    // Variaveis para a probabilidade
    float probs[N] = {0.};
    float cont = 0.;	

	for(t; t < TF; t++){
		rand = (int) uniform(0, N-1);
		
		if(rand < urnaA){
			urnaA--;
		}else{
			urnaA++;
		}

        if(t > EE){
            probs[urnaA] += 1.;
            cont += 1.;
        }
	}

    for(int i = 0; i < N; i++){
   	    probs[i] /= cont;
    	fprintf(saida, "%i\t%lf\n", i+1, probs[i]);
    }
	
	fclose(saida);
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

