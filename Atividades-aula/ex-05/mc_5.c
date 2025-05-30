#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TA 10000		// Tamanho da amostra
#define NAM 1000.		// Número de amostras

int main(){
    double uniform(double min, double max);
    int seed = time(NULL);
    srand(seed);
    
    // Criação do arquivo
    char titulo1[20], titulo2[20];
    sprintf(titulo1, "%i-NAM%i.txt", seed, (int) NAM);
    FILE *saida = fopen(titulo1, "w");
    
    // Definições para a dinâmica
    float pi = acos(-1.);
    int Nac = 0;
    double rand1, rand2;
    int t;
    double piarr[TA] = {0.};
    double simsolta[TA] = {0.};
    float razao;

    for(int amostra; amostra <= NAM; amostra++){
        for(t = 0; t < TA; ++t){
            rand1 = uniform(0., pi);
            rand2 = uniform(0., 1.);
            if(rand2 < sin(rand1)) Nac++;
            razao = (2.*t)/((float) Nac);            
            if(amostra == NAM) simsolta[t] += razao;
            else piarr[t] += razao;
        }
        Nac = 0;
        seed += 3;
        srand(seed);
    }
    
    for(int i = 1; i <= TA; ++i){
        fprintf(saida, "%d\t%lf\t%lf\n", i, piarr[i-1]/NAM, simsolta[i-1]);
    }
    
	// Roda o script de python
	fclose(saida);
	char comando[50];
	sprintf(comando, "python3 analise5.py %s\n", titulo1);
	printf("%s", comando);
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

