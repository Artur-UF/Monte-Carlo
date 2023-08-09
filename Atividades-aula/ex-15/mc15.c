#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
/*
#define L 50            // Aresta da rede
#define STEPS 1000     // Número de MCS
#define RND 0           // Condição inicial dos spins
#define IMG 1           // Gravar estados
#define CI 0            // Gravar condição inicial
*/
int main(int argc, char *argv[]){
    char pasta[30];
    sprintf(pasta, "%s", argv[1]);
    char *ptr;
    int seed = strtol(argv[2], &ptr, 10);
    int L = strtol(argv[3], &ptr, 10);
    int STEPS = strtol(argv[4], &ptr, 10);
    int RND = strtol(argv[5], &ptr, 10);
    int IMG = strtol(argv[6], &ptr, 10);
    int CI = strtol(argv[7], &ptr, 10);
    int T = strtol(argv[8], &ptr, 10);
    
    int **vizinhos(int l);
    int energia(int *sis, int **viz, int n, int j);
    double magnetizacao(int *sis, int n);
    double uniform(double min, double max);
    srand(seed);

    // Criação da pasta da simulação e comando de análise
    char saida1[100], saida2[100], saida3[100];
    sprintf(saida1, "%s/ising-L-%d-T-%d-STEPS-%d-rnd-%d.dat", pasta, L, T, STEPS, RND);
    sprintf(saida2, "%s/im-L-%d-T-%d-STEPS-%d-rnd-%d.dat", pasta, L, T, STEPS, RND);
    sprintf(saida3, "%s/ci-L-%d-T-%d-STEPS-%d-rnd-%d.dat", pasta, L, T, STEPS, RND);

    FILE *rede = fopen(saida1, "w");
    FILE *img = fopen(saida2, "w");
    FILE *ci = fopen(saida3, "w");

    //__________________________________SIMULAÇÃO__________________________

    int i, j, s, t, dE, N; 
    int J = 1;
    double E;
    double beta = 1./T;
    N = L*L;

    // Criando o sistema e matriz de vizinhos
    int **viz = vizinhos(L);
    int *sis = (int*)calloc(N, sizeof(int));

    //____________________________________ aqui ficaria um Loop sobre amostras
    // GERANDO A CONFIGURAÇÃO
    if(RND) for(i = 0; i < N; ++i) sis[i] = (uniform(0., 1.) < .5) ? -1 : 1;
    else for(i = 0; i < N; ++i) sis[i] = 1;
    
    if(CI) for(i = 0; i < N; ++i) fprintf(ci, "%d\n", sis[i]);
    
    E = (double) energia(sis, viz, N, 1);
    t = 0;
    //---METROPOLIS---
    for(s = 0; s < STEPS; ++s){ //Loop sobre passos de Monte Carlo
        //MCS
        for(j = 0; j < N; ++j){
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
        if(IMG){
            for(i = 0; i < N; ++i) fprintf(img, "%d\n", sis[i]);
            fprintf(img, "-2\n");
        }
        fprintf(rede, "%d\t%lf\t%lf\n", t, E/N, magnetizacao(sis, N));
    } //Fim do loop sobre MCSs
    //________________ aqui acabaria um loop sobre amostras

    //_________________________________FIM DA SIMULAÇÃO______________________ 
    
    fclose(rede);
    fclose(img);
    fclose(ci);
    if(!IMG) remove(saida2);
    if(!CI) remove(saida3);
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

