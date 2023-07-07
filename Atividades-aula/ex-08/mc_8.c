#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/stat.h>

#define TA 1000000	// Tamanho da amostra
#define NAM 10.		// Número de amostras
#define LAMB "RAND"		// Determina se o lambda é aleatório ou não

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
    char pasta[25], dinamicaC[50], dinamicaS[50], tracker[50], info[50];
    sprintf(pasta, "TA-%d-NAM-%d-%s", TA, (int) NAM, LAMB);
//    sprintf(dinamicaC, "%s/dinamicaC.dat", pasta);
//    sprintf(dinamicaS, "%s/dinamicaS.dat", pasta);
    sprintf(dinamicaC, "%s/dinamicaC.bin", pasta);
    sprintf(dinamicaS, "%s/dinamicaS.bin", pasta);
    sprintf(tracker, "%s/tracker.dat", pasta);
    sprintf(info, "%s/info.txt", pasta);

    if(mkdir(pasta, 0777) == -1){
    	printf("Já existe, vou limpar\n");
    	remove(dinamicaS);
    	remove(dinamicaC);
    	remove(tracker);
    	remove(info);
    }
	FILE *simulaC = fopen(dinamicaC, "wb");
	FILE *simulaS = fopen(dinamicaS, "wb");
	FILE *rastreia = fopen(tracker, "w");
	FILE *informa = fopen(info, "w");

	char comando[150];
	sprintf(comando, "python3 plot.py %s\npython3 hist.py %s\npython3 walk.py %s\n", pasta, pasta, pasta);
	char transformadorS[150];
	sprintf(transformadorS, "python3 bintonpy.py %s %s/dinamicaS.npy", dinamicaS, pasta);
	char transformadorC[150];
	sprintf(transformadorC, "python3 bintonpy.py %s %s/dinamicaC.npy", dinamicaC, pasta);
    //____________________________ O IMPORTANTE ESTÁ AQUI _________________________________
    
    // Definições para a dinâmica
    double pi = acos(-1.);
    int n = 0;
    int N;
    double r1, r2;    
    double estim;
    double dx, xaux, x = .5;
    double dy, yaux, y = .5;
	double lambda = .3;
	int amostras;

	int RAND;
	if(LAMB == "FIXO") RAND = 0;
	else RAND = 1; 

	// Vetores que armazenam as amostras
    double *semREJ = (double*) malloc(TA*sizeof(double));
	double *comREJ = (double*) malloc(TA*sizeof(double));
	    
    // Vetores que armazenam as posições (pro histograma e pro "walk.png")
	vetor *trackCREJ = (vetor*) malloc(TA*sizeof(vetor));
	vetor *trackSREJ = (vetor*) malloc(TA*sizeof(vetor));
	
	clock_t tic = clock();
	// Sem Rejeição
    for(amostras = 0; amostras < NAM; amostras++){
        for(N = 1; N <= TA; ++N){
            if(RAND) r1 = uniform(.0, lambda);
            else r1 = lambda;
            r2 = uniform(0., 2*pi);
            dx = r1*cos(r2);
            dy = r1*sin(r2);
            xaux = x + dx;
            yaux = y + dy;
            if((xaux < 1.) && (xaux > 0.) && (yaux < 1.) && (yaux > 0.)){
            	x = xaux;
            	y = yaux;
            }
            if((x*x) + (y*y) < 1) n++;
            estim = ((double) n)/((double) N);           
            semREJ[N] = estim;
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
		fwrite(semREJ, sizeof(double), TA, simulaS);
		/*for(N = 1; N <= TA; ++N){
        	//fprintf(simulaS, "%d\t%lf\n", N, semREJ[N-1]);
    	}*/
    }
    
    // Com Rejeição
    x = .5;
    y = .5;
    n = 0;
    srand(seed2);
    for(amostras = 0; amostras < NAM; amostras++){
        for(N = 1; N <= TA; ++N){
            if(RAND) r1 = uniform(.0, lambda);
            else r1 = lambda;
            r2 = uniform(0., 2*pi);
            dx = r1*cos(r2);
            dy = r1*sin(r2);
			xaux = x + dx;
			yaux = y + dy;
            if((xaux < 1.) && (xaux > 0.) && (yaux < 1.) && (yaux > 0.)){
            	x = xaux;
            	y = yaux;
            	if((x*x) + (y*y) < 1) n++;
			    estim = ((double) n)/((double) N);           
				comREJ[N] = estim;
            	if(amostras == NAM-1){
					trackCREJ[N].x = x;
					trackCREJ[N].y = y;            	
				}
            }else N--;
        }
        n = 0;
		x = .5;
		y = .5;
        seed2 += 3;
        srand(seed2);
        fwrite(comREJ, sizeof(double), TA, simulaC);
        /*for(N = 1; N <= TA; ++N){
        	fprintf(simulaC, "%d\t%lf\n", N, comREJ[N-1]);
    	}*/
    }
    
    // Escreve os arquivos a serem analisados
/*    for(N = 1; N <= TA; ++N){
        fprintf(simula, "%d\t%lf\t%lf\n", N, comREJ[N-1]/NAM, semREJ[N-1]/NAM);
    }*/
    
    
    for(N = 1; N <= TA; ++N){
		fprintf(rastreia, "%d\t%lf\t%lf\t%lf\t%lf\n", N, trackCREJ[N-1].x, trackCREJ[N-1].y, trackSREJ[N-1].x, trackSREJ[N-1].y);
    }
    
    //__________________________________ O IMPORTANTE TERMINA AQUI ____________________________________
    	
    clock_t toc = clock();
	double time = (double)(toc - tic)/CLOCKS_PER_SEC;
	
	// Escreve arquivo de informações sobre a simulação
	fprintf(informa, "seed = %d\n", seed3);
	fprintf(informa, "\n#define TA %d		// Tamanho da amostra\n#define NAM %.1lf		// Número de amostras\n\n", TA, NAM);
	fprintf(informa, "tempo de execução = %.3lfs", time);
    
	// Roda o script de python
	fclose(simulaS);
	fclose(simulaC);
	fclose(rastreia);
	fclose(informa);
	printf("%s", comando);
	system(transformadorS);
	system(transformadorC);
	remove(dinamicaS);
	remove(dinamicaC);
	

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

