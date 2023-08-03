#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>

#define MCSSIZE 100     // Tamanho do passo de Monte Carlo
#define STEPS 10000      // Número de MCS

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
    sprintf(pasta, "MCSSIZE-%d-STEPS-%d", MCSSIZE, STEPS);
    sprintf(saida1, "%s/ising50.dat", pasta);
    sprintf(saida2, "%s/ising100.dat", pasta);
    sprintf(saida3, "%s/upising50.dat", pasta);
    sprintf(saida4, "%s/upising100.dat", pasta);
    sprintf(info, "%s/info.txt", pasta);

    if(mkdir(pasta, 0777) == -1){
        printf("Já existe, vou limpar\n");
        remove(saida1);
        remove(saida2);
        remove(saida3);
        remove(saida4);
        remove(info);
    }
    FILE *rede50 = fopen(saida1, "w");
    FILE *rede100 = fopen(saida2, "w");
    FILE *uprede50 = fopen(saida3, "w");
    FILE *uprede100 = fopen(saida4, "w");

    FILE *informa = fopen(info, "w");

    FILE *arks[4] = {rede50, rede100, uprede50, uprede100};

    char comando[50];
    sprintf(comando, "python3 plot.py %s\n", pasta);
    printf("%s", comando);

    clock_t tic = clock();
    //__________________________________SIMULAÇÃO__________________________

    int i, j, s, p, t, dE, L, N, l[4] = {50, 100, 50, 100}; // eu criei um vetor com os tamanhos de rede
    int J = 1;
    double E;
    double T = 1;
    double beta = 1./T;
    for(int li = 0; li < 4; ++li){ //Loop sobre sistemas
        L = l[li];
        N = L*L;
        int **viz = vizinhos(L);
        int *sis = (int*)calloc(N, sizeof(int));
        //____________________________________ aqui ficaria um Loop sobre amostras
        // GERANDO A CONFIGURAÇÃO
        // como os tamanhos se repetem primeiro eu faço as aleatórias e dps as interias com 1
        if(li < 2) for(i = 0; i < N; ++i) sis[i] = (uniform(0., 1.) < .5) ? -1 : 1;
        else for(i = 0; i < N; ++i) sis[i] = 1;
        E = (double)energia(sis, viz, N, 1)/N;
        t = 0;
        //---METROPOLIS---
        for(s = 0; s < STEPS; ++s){ //Loop sobre passos de Monte Carlo
            //MCS
            for(p = 0; p < MCSSIZE; ++p){
                j = (int) uniform(0., (double)N);
                dE = 2*J*sis[j]*(sis[viz[j][0]] + sis[viz[j][1]] + sis[viz[j][2]] + sis[viz[j][3]]);
                if(dE > 0){
                    if(uniform(0., 1.) < exp(-beta*dE)){
                        sis[j] *= -1;
                        E += dE;
                    }
                }
                else{
                    sis[j] *= -1;
                    E += dE;
                }
            }
            t++;
            //Fim do MCS

            fprintf(arks[li], "%d\t%lf\t%lf\n", t, E/N, magnetizacao(sis, N));
        } //Fim do loop sobre MCSs
        //________________ aqui acabaria um loop sobre amostras
    } //Fim do loop sobre sistemas

    //_________________________________FIM DA SIMULAÇÃO______________________ 
    clock_t toc = clock();
    double time = (double)(toc - tic)/CLOCKS_PER_SEC;

    // Escreve arquivo de informações sobre a simulação
    fprintf(informa, "seed = %d\n", seed0);
    fprintf(informa, "\n#define MCSSIZE %d     // Tamanho do passo de Monte Carlo\n#define STEPS %d      // Número de MCS\n", MCSSIZE, STEPS);
    fprintf(informa, "tempo de execução = %.5lfs", time);
    
    fclose(rede50);
    fclose(rede100);
    fclose(uprede50);
    fclose(uprede100);

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

