#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


#define AM 1000         // Número de amostras
#define NL 20           // # de divisões do espaço


int main(){
    double uniform(double min, double max);

    char nome[50];
    sprintf(nome, "rwC-AM-%d-NL-%d.dat", AM, NL);

    FILE *ark = fopen(nome, "w");


    // SIMULAÇÃO
    double x = 1./3.;
    double l = (1.-x)/NL;
    int t = 0;

    clock_t tic = clock();
    for(int a = 0; a < AM; ++a){
        while(x < 1){
            x = (uniform(0., 1.) > .5) ? x+l : x-l;
            x = (x < 0) ? x+l : x; 
            t++;
            //printf("x = %.3lf | t = %d\n", x, t);
        }
        //printf("TPP = %d\n", t);
        fprintf(ark, "%d\n", t);
        printf("AM = %d | t = %d\r", a, t);
        t = 0;
        x = 1./3.;
    }
    clock_t toc = clock();
    double time = (double)(toc - tic)/CLOCKS_PER_SEC;

    printf("\nTempo de execução: %.3lfs\n", time);

    fclose(ark);
    return 0;
}


double uniform(double min, double max){
    /*
    Função que gera um número aleatório em uma distribuição uniforme
    Para int: [min, max)
    */
    double random  = ((double) rand()) / RAND_MAX;
    double range = (max - min) * random;
    double n = range + min;	
    
    return n;
}
