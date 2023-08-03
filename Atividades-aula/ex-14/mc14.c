#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>

#define AM 10000         // Número de amostras


int main(){
    int **vizinhos(int l);
    int energia(int *sis, int **viz, int n, int j);
    double magnetizacao(int *sis, int n);
    double uniform(double min, double max);
    int seed0, seed = time(NULL);
    seed0 = seed;
    srand(seed);

    // Criação da pasta da simulação e comando de análise
    char pasta[30], saida1[50], saida2[50], saida3[50], saida4[50], info[50];
    sprintf(pasta, "AM-%d", AM);
    sprintf(saida1, "%s/ising5.dat", pasta);
    sprintf(saida2, "%s/ising10.dat", pasta);
    sprintf(saida3, "%s/ising50.dat", pasta);
    sprintf(saida4, "%s/ising100.dat", pasta);
    sprintf(info, "%s/info.txt", pasta);

    if(mkdir(pasta, 0777) == -1){
        printf("Já existe, vou limpar\n");
        remove(saida1);
        remove(saida2);
        remove(saida3);
        remove(saida4);
        remove(info);
    }
    FILE *rede5 = fopen(saida1, "w");
    FILE *rede10 = fopen(saida2, "w");
    FILE *rede50 = fopen(saida3, "w");
    FILE *rede100 = fopen(saida4, "w");
    FILE *informa = fopen(info, "w");

    FILE *arks[4] = {rede5, rede10, rede50, rede100};

    char comando[50];
    sprintf(comando, "python3 hist.py %s\n", pasta);
    printf("%s", comando);

    clock_t tic = clock();
    //__________________________________SIMULAÇÃO__________________________
    int L, N, l[4] = {5, 10, 50, 100};
    for(int li = 0; li < 4; ++li){
        L = l[li];
        N = L*L;
        int **viz = vizinhos(L);
        int *sis = (int*)calloc(N, sizeof(int));
        for(int a = 0; a < AM; ++a){
            //GERANDO A CONFIGURAÇÃO
            for(int i = 0; i < N; ++i) sis[i] = (uniform(0., 1.) < .5) ? -1 : 1;
            fprintf(arks[li], "%d\t%lf\n", energia(sis, viz, N, 1), magnetizacao(sis, N));
            seed += 3;
            srand(seed);
        }
    }

    //_________________________________FIM DA SIMULAÇÃO______________________ 
    clock_t toc = clock();
    double time = (double)(toc - tic)/CLOCKS_PER_SEC;

    // Escreve arquivo de informações sobre a simulação
    fprintf(informa, "seed = %d\n", seed0);
    fprintf(informa, "\n#define AM %d         // Número de amostras para cara p\n", AM);
    fprintf(informa, "tempo de execução = %.5lfs", time);
    
    fclose(rede5);
    fclose(rede10);
    fclose(rede50);
    fclose(rede100);
    fclose(informa);
    //system(comando); 
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

int **vizinhos(int l){
    int n = l*l;
    int **mtzviz = (int **)malloc(n*sizeof(int*));
    for(int ni = 0; ni < n; ++ni){
        mtzviz[ni] = (int *)malloc(4*sizeof(int));
    }
    /*
    mtzviz[0] - Direita
    mtzviz[1] - Cima
    mtzviz[2] - Esquerda
    mtzviz[3] - Baixo
    */

    for(int i = 0; i < n; ++i){  
        // ultima coluna, deslocamos  L-1
        if(i%l == l-1) mtzviz[i][0] = i + 1 - l;
        else mtzviz[i][0] = i + 1;
        // primeira coluna, somamos L-1
        if(i%l == 0) mtzviz[i][2] = i - 1 + l;
        else mtzviz[i][2] = i - 1;
        // primeira linha, somamos N-L
        if(i<l) mtzviz[i][1] = i - l + n;
        else mtzviz[i][1] = i - l;
        // ultima linha, modulo L
        if(i>=n-l) mtzviz[i][3] = (i % l);
        else mtzviz[i][3] = i + l;
    }
    
    return mtzviz;
}

int energia(int *sis, int **viz, int n, int j){
    int en = 0;
    for(int i = 0; i < n; ++i) en += sis[i]*(sis[viz[i][0]] + sis[viz[i][3]]);
    return -j*en;
}

double magnetizacao(int *sis, int n){
    double m = 0;
    for(int i = 0; i < n; ++i) m += sis[i];
    return m/n;
}

