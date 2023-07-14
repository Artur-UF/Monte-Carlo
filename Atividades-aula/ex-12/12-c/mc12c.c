#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>

#define P 5000         // Número de Passos
#define L 50             // Aresta do Sistema
#define N (L*L)         // Número de Sítios

int main(){
    void colisao(int loc);
    double uniform(double min, double max);
    int seed = time(NULL);
    srand(seed);

    // Criação da pasta da simulação e comando de análise
    char pasta[30], saida1[50], info[50];
    sprintf(pasta, "P-%d-L-%d-N-%d", P, L, N);
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
    sprintf(comando, "python3 trackc.py %s\n", pasta);
    printf("%s", comando);
    //_____________________GERANDO MATRIZES________________________
    int *sistema = (int *)calloc(N, sizeof(int));
    int **mtzviz = (int **)malloc(N*sizeof(int*));
    for(int n = 0; n < N; ++n){
        mtzviz[n] = (int *)malloc(4*sizeof(int));
    }
    /*
    mtzviz[0] - Direita
    mtzviz[1] - Cima
    mtzviz[2] - Esquerda
    mtzviz[3] - Baixo
    */

    for(int i = 0; i < N; ++i){  
        // ultima coluna, deslocamos  L-1
        if(i%L == L-1) mtzviz[i][0] = i + 1 - L;
        else mtzviz[i][0] = i + 1;
        // primeira coluna, somamos L-1
        if(i%L == 0) mtzviz[i][2] = i - 1 + L;
        else mtzviz[i][2] = i - 1;
        // primeira linha, somamos N-L
        if(i<L) mtzviz[i][1] = i - L + N;
        else mtzviz[i][1] = i - L;
        // ultima linha, modulo L
        if(i>=N-L) mtzviz[i][3] = (i % L);
        else mtzviz[i][3] = i + L;
    }
     

    //__________________________DINÂMICA__________________________
    clock_t tic = clock();
    
    int auxloc, loc = (int)N/2 + L/2;
    int x, y, rand, auxrand = -1;
    sistema[loc] = 1;

    fprintf(track, "%d\t%d\n", loc, sistema[loc]);
    
    for(int p = 0; p < P; ++p){
        auxloc = loc;
        rand = (int)uniform(0, 4);
        while(rand == auxrand){
            rand = (int)uniform(0, 4);
        }
        auxrand = rand;

        switch(rand){
           case 0:
               loc = mtzviz[loc][0];
           break;
           case 1:
               loc = mtzviz[loc][1];
           break;
           case 2:
               loc = mtzviz[loc][2];
           break;
           case 3:
               loc = mtzviz[loc][3];
           break;
        }
        if(sistema[loc] == 0) sistema[loc] = 1;
        else{
            printf("Tamanho = %d\n", p);
            if(fabs((auxloc%L) - (loc%L)) > 1 || fabs((auxloc/L) - (loc/L)) > 1) fprintf(track, "-1\n");
            fprintf(track, "%d\t%d\n", loc, sistema[loc]);
            break;
        }
        if(fabs((auxloc%L) - (loc%L)) > 1 || fabs((auxloc/L) - (loc/L)) > 1) fprintf(track, "-1\n");
        fprintf(track, "%d\t%d\n", loc, sistema[loc]);
    }

    clock_t toc = clock();
    double time = (double)(toc - tic)/CLOCKS_PER_SEC;

    // Escreve arquivo de informações sobre a simulação
    fprintf(informa, "seed = %d\n", seed);
    fprintf(informa, "\n#define P %d         // Número de Passos\n#define L %d            // Aresta do Sistema\n#define N %d         // Número de Sítios\n", P, L, N);
    fprintf(informa, "tempo de execução = %.4lfs", time);
    
    fclose(track);
    fclose(informa);
 
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

/*void colisao(int loc){
    if(loc == 1) return break;
}*/

