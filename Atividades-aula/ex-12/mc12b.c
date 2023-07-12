#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>

#define P 10000         // Número de Passos
#define L 4             // Aresta do Sistema
#define N (L*L)         // Número de Sítios

int main(){
    double uniform(double min, double max);
    int seed = time(NULL);
    srand(seed);
/*
    // Criação da pasta da simulação e comando de análise
    char pasta[30], saida1[50], info[50];
    sprintf(pasta, "B-P-%d-L-%d-N-%d", P, L, N);
    sprintf(saida1, "%s/track.dat", pasta);
    sprintf(info, "%s/info.txt", pasta);

    if(mkdir(pasta, 0777) == -1){
        printf("Já existe, vou limpar\n");
        remove(saida1);
        remove(info);
    }
    FILE *track = fopen(saida1, "w");
    FILE *informa = fopen(info, "w");

    char comando[50];
    sprintf(comando, "python3 trackb.py %s\n", pasta);
    printf("%s", comando);*/
    //_____________________GERANDO MATRIZES________________________
    printf("Oi 1\n");
    int *sistema = (int *)calloc(N, sizeof(int));
    int **mtzviz = (int **)malloc(N*sizeof(int));
    for(int n = 0; n < N; ++n){
        mtzviz[n] = (int *)malloc(4*sizeof(int));
    }
    /*
    mtzviz[0] - Direita
    mtzviz[1] - Cima
    mtzviz[2] - Esquerda
    mtzviz[3] - Baixo
    */
    printf("Oi 2\n");

    clock_t tic = clock();
    for(int i = 0; i < N; ++i){  
        printf(">>>>>>>>>>>>>>>>>>>>>i=%d\n", i);
        printf("Dentro 1\n");
        
        // ultima coluna, deslocamos  L-1
        if(i%L == L-1) mtzviz[i][0] = i + 1 - L;
        else mtzviz[i][0] = i + 1;
        printf("Dentro 2\n");
        
        // primeira coluna, somamos L-1
        if(i%L == 0) mtzviz[i][2] = i - 1 + L;
        else mtzviz[i][2] = i - 1;
        
        // primeira linha, somamos N-L
        if(i<L) mtzviz[i][1] = i - L + N;
        else mtzviz[i][1] = i - L;
        
        // ultima linha, modulo L
        if(i>=N-L) mtzviz[i][3] = (i % L);
        else mtzviz[i][3] = i + L;
        printf("%d | %d | %d | %d | %d\n", i, mtzviz[i][0], mtzviz[i][1], mtzviz[i][2], mtzviz[i][3]);
    }
    printf("Oi 3\n");

    for(int i = 0; i < N; ++i){
        printf("%d\t%d\t%d\t%d\t%d", mtzviz[i][0], mtzviz[i][1], mtzviz[i][2], mtzviz[i][3], mtzviz[i][4]);
    }
    printf("Oi 4\n");

    clock_t toc = clock();
    double time = (double)(toc - tic)/CLOCKS_PER_SEC;
       
    /*// Escreve arquivo de informações sobre a simulação
    fprintf(informa, "seed = %d\n", seed);
    fprintf(informa, "\n#define P 10000         // Número de Passos\n#define L 50            // Aresta do Sistema\n");
    fprintf(informa, "tempo de execução = %.4lfs", time);
    
    fclose(track);
    fclose(informa);*/
 
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

