#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/stat.h>

#define TA 100000		// Tamanho da amostra
#define NAM 50.		// Número de amostras

typedef struct {
	double x;
	double y;
}vetor;

int main(){
    double uniform(double min, double max);
    int seed1 = time(NULL);
    int seed2 = seed1;
    int seed3 = seed1;
    srand(seed1);
    
    // Criação da pasta da simulação e comando de análise
    char pasta[25], dinamica[50], tracker[50], info[50];
    sprintf(pasta, "TA-%d-NAM-%d", TA, (int) NAM);
    sprintf(dinamica, "%s/dinamica.dat", pasta);
    sprintf(tracker, "%s/tracker.dat", pasta);
    sprintf(info, "%s/info.txt", pasta);

    if(mkdir(pasta, 0777) == -1){
    	printf("Já existe, vou limpar\n");
    	remove(dinamica);
    	remove(tracker);
    	remove(info);
    }
	FILE *simula = fopen(dinamica, "w");
	FILE *rastreia = fopen(tracker, "w");
	FILE *informa = fopen(info, "w");

	char comando[100];
	sprintf(comando, "python3 analise8.py %s\n", pasta);

    //____________________________ O IMPORTANTE ESTÁ AQUI _________________________________
    
    // Definições para a dinâmica
    double pi = acos(-1.);
    int n = 0;
    int N;
    double r1, r2;    
    double razao;
    double dx, x = .5;
    double dy, y = .5;
	double lambda = .3;
	int amostras;

	// Vetores que armazenam as amostras
    double piREJ[TA] = {0.};
    double piSREJ[TA] = {0.};
    
    // Vetores que armazenam as posições (pro histograma e pro "walk.png")
    vetor trackREJ[TA];
    vetor trackSREJ[TA];
	
	clock_t tic = clock();
	// Sem Rejeição
    for(amostras = 0; amostras < NAM; amostras++){
        for(N = 1; N <= TA; ++N){
            r1 = uniform(0., lambda);
            r2 = uniform(0., 2*pi);
            dx = r1*cos(r2);
            dy = r1*sin(r2);
            x += dx;
            y += dy;
            if((x > 1.) || (x < 0.) || (y > 1.) || (y < 0.)){
            	x -= dx;
            	y -= dy;
            }
            if((x*x) + (y*y) < 1) n++;
            razao = ((double) n)/(N);           
            piSREJ[N] += razao;
            if(amostras == NAM-1){
		        trackSREJ[N].x = x;
		        trackSREJ[N].y = y;
        	}
        }
        n = 0;
        x = .5;
        y = .5;
        seed1 += 3;
        srand(seed1);
    }
    
    // Com Rejeição
    x = .5;
    y = .5;
    n = 0;
    srand(seed2);
    for(amostras = 0; amostras < NAM; amostras++){
        for(N = 1; N <= TA; ++N){
            r1 = uniform(0., lambda);
            r2 = uniform(0., 2*pi);
            dx = r1*cos(r2);
            dy = r1*sin(r2);
            x += dx;
            y += dy;
            if((x <= 1.) && (x >= 0.) && (y <= 1.) && (y >= 0.)){
            	if((x*x) + (y*y) < 1){
				 	n++;
				    razao = ((double) n)/(N);           
				    piREJ[N] += razao;
            	}
            	if(amostras == NAM-1){
					trackREJ[N].x = x;
					trackREJ[N].y = y;            	
				}
            }else{
            	x -= dx;
            	y -= dy;
            	N--;
            }
        }
        n = 0;
		x = .5;
		y = .5;
        seed2 += 3;
        srand(seed2);
    }
    
    // Escreve os arquivos a serem analisados
    for(N = 1; N <= TA; ++N){
        fprintf(simula, "%d\t%lf\t%lf\n", N, piREJ[N-1]/NAM, piSREJ[N-1]/NAM);
    }
    
    
    for(N = 1; N <= TA; ++N){
		fprintf(rastreia, "%d\t%lf\t%lf\t%lf\t%lf\n", N, trackREJ[N-1].x, trackREJ[N-1].y, trackSREJ[N-1].x, trackSREJ[N-1].y);
    }
    
    //__________________________________ O IMPORTANTE TERMINA AQUI ____________________________________
    
    clock_t toc = clock();
	double time = (double)(toc - tic)/CLOCKS_PER_SEC;
	
	// Escreve arquivo de informações sobre a simulação
	fprintf(informa, "seed = %d\n", seed3);
	fprintf(informa, "\n#define TA %d		// Tamanho da amostra\n#define NAM %.1lf		// Número de amostras\n\n", TA, NAM);
	fprintf(informa, "tempo de execução = %.3lfs", time);
    
	// Roda o script de python
	fclose(simula);
	fclose(rastreia);
	fclose(informa);
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

