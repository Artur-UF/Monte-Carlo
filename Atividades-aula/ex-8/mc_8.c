#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TA 100000		// Tamanho da amostra
#define NAM 100.		// Número de amostras

int main(){
    double uniform(double min, double max);
    int seed1 = time(NULL);
    int seed2 = seed1;
    srand(seed1);
    
    // Criação do arquivo
    char titulo1[20], titulo2[20];
    sprintf(titulo1, "%i-NAM%i.txt", seed1, (int) NAM);
	FILE *saida = fopen(titulo1, "w");
	char comando[50];
	sprintf(comando, "python3 analise8.py %s\n", titulo1);

    
    // Definições para a dinâmica
    double pi = acos(-1.);
    int n = 0;
    int N;
    double r1, r2;    
    double piREJ[TA] = {0.};
    double piSREJ[TA] = {0.};
    double razao;
    double dx, x = uniform(0., 1.);
    double dy, y = uniform(0., 1.);
	double lambda = .3;

    for(int amostrasS = 0; amostrasS < NAM; amostrasS++){
        for(N = 1; N <= TA; ++N){
            r1 = uniform(0., lambda);
            r2 = uniform(0., 2*pi);
            dx = r1*cos(r2);
            dy = r1*sin(r2);
            x += dx;
            y += dy;
            if(x > 1. || x < 0. || y > 1. || y < 0.){
            	x -= dx;
            	y -= dy;
            }
            if((x*x) + (y*y) < 1) n++;
            razao = ((double) n)/(N);           
            piSREJ[N] += razao;
        }
        n = 0;
        seed1 += 3;
        srand(seed1);
    }
    
    x = uniform(0., 1.);
    y = uniform(0., 1.);
    n = 0;
    srand(seed2);
    for(int amostrasR = 0; amostrasR < NAM; amostrasR++){
        for(N = 1; N <= TA; ++N){
            r1 = uniform(0., lambda);
            r2 = uniform(0., 2*pi);
            dx = r1*cos(r2);
            dy = r1*sin(r2);
            x += dx;
            y += dy;
            if(x <= 1. || x >= 0. || y <= 1. || y >= 0.){
            	if((x*x) + (y*y) < 1) n++;
            }else{
            	x -= dx;
            	y -= dy;
            	N--;
            }
            razao = ((double) n)/(N);           
            piREJ[N] += razao;
        }
        n = 0;
        seed2 += 3;
        srand(seed2);
    }
    
    
    
    for(N = 1; N <= TA; ++N){
        fprintf(saida, "%d\t%lf\t%lf\n", N, piREJ[N-1]/NAM, piSREJ[N-1]/NAM);
    }
    
	// Roda o script de python
	fclose(saida);
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

