#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


#define AM 5000         // Número de amostras
#define DLI 20           // # de divisões iniciais
#define DLF 100         // # de divisões finais
#define DDL 5          // passo de DL


int main(){
    double uniform(double min, double max);

    char nome[50];
    sprintf(nome, "rwC_AM_%d_DLI_%d_DLF_%d_DDL_%d.dat", AM, DLI, DLF, DDL);

    FILE *ark = fopen(nome, "w");


    // SIMULAÇÃO
    int ndls = (DLF-DLI)/DDL;
    int *dls = (int*) malloc((ndls+1)*sizeof(int));
    dls[0] = DLI;
    for(int i = 1; i <= ndls; ++i){
        dls[i] = dls[i-1] + DDL; 
    }
    double x = 1./3.;
    double l, tm = 0.;
    int t = 0;

    clock_t tic = clock();
    for(int i = 0; i <= ndls; ++i){
        l = 1./dls[i];
        for(int a = 0; a < AM; ++a){
            while(x < 1){
                x = (uniform(0., 1.) > .5) ? x+l : x-l;
                x = (x < 0) ? x+(2*l) : x; 
                t++;
            }
            tm += t;
            t = 0;
            x = 1./3.;
        }
        tm /= AM;
        fprintf(ark, "%lf %d %lf\n", l, dls[i], tm);
    }
    clock_t toc = clock();
    double time = (double)(toc - tic)/CLOCKS_PER_SEC;

    printf("Tempo de execução: %.3lfs\n", time);

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
