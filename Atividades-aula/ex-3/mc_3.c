#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 100		// Número total de bolas
#define TF 50000000	// Tempo final
#define EE 10000	// Estado Estacionário
#define TC 101		// Tempo de correlação

int main(){
	double uniform(double min, double max);
    double funcao(int t, int na, int n);
    int seed = time(NULL);
    srand(seed);
	
    // Criação do arquivo
    char titulo1[20], titulo2[20];
    sprintf(titulo1, "%i-N%i.txt", seed, N);
	FILE *saida = fopen(titulo1, "w");
    
    // Variaveis para simulação
	int urnaA = N;
	int rand;
	int t = 0;
    float probs[N] = {0.};
    int cont = 0;
	
	// Dinâmica até sair do transiente
	for(t; t < EE; t++){
		rand = (int) uniform(1, N);
		if(rand < urnaA) urnaA--;
        else urnaA++;
	}

	// Coletando do Estado estacionário
	for(t; t < TF; t++){
		// Faz a dinâmica
		rand = (int) uniform(0, N-2);
		if(rand < urnaA) urnaA--;
        else urnaA++;
	    
	    // Coleta os dados
	    if(t%TC == 0){
        	probs[urnaA] += 1.;
    		cont++;
    	}
	}
	
	printf("Amostras = %d\n", cont);
	
	// Escreve o arquivo de saída
    for(int i = 0; i < N; i++){
   	    probs[i] /= (float) cont;
    	fprintf(saida, "%i\t%lf\n", i+1, probs[i]);
    }
	
	// Roda o script de python
	fclose(saida);
	char comando[50];
	sprintf(comando, "python3 analise3.py %s\n", titulo1);
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

