#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>

#define NP 10.   // Número de p utilizados em cada simulação

int main(){
    int **vizinhos(int l);
    double uniform(double min, double max);
    int seed = time(NULL);
    srand(seed);

    // Criação da pasta da simulação e comando de análise
    char pasta[30], saida1[50], saida2[50], saida3[50], info[50];
    sprintf(pasta, "NP-%.0lf", NP);
    sprintf(saida1, "%s/50.dat", pasta);
    sprintf(saida2, "%s/100.dat", pasta);
    sprintf(saida3, "%s/150.dat", pasta);
    sprintf(info, "%s/info.txt", pasta);

    if(mkdir(pasta, 0777) == -1){
        printf("Já existe, vou limpar\n");
        remove(saida1);
        remove(saida2);
        remove(saida3);
        remove(info);
    }
    FILE *rede50 = fopen(saida1, "w");
    FILE *rede100 = fopen(saida2, "w");
    FILE *rede150 = fopen(saida3, "w");
    FILE *informa = fopen(info, "w");
    // Vetor com os files
    FILE *arks[3] = {rede50, rede100, rede150};

    char comando[50];
    sprintf(comando, "python3 plot.py %s\n", pasta);
    printf("%s", comando);

    clock_t tic = clock();
    
    int L, N;
    for(int j = 1; j <= 3; ++j){
        L = 50*j;
        printf("---L = %d---\n", L);
        N = L*L;
        //_____________________GERANDO MATRIZES________________________
        int *s = (int *)calloc(N, sizeof(int));
        int *f = (int *)calloc(N, sizeof(int));
        int **mtzviz = vizinhos(L);

        for(double p = .3; p < .9; p += (.6/NP)){
            printf("p = %.2lf\n", p);
            //_______________________CONDIÇÕES INICIAIS_______________________
            for(int i = 0; i < N; ++i){
                (uniform(0, i) < p) ? s[i] = 1 : true ;
            }
            
            for(int i = 0; i < L; ++i){
                (s[i] == 1) ? f[i] = 1 : true ;
            }

            //____________________________DINÂMICA_____________________________TEM ALGO ERRADO
            int t = 0;
            int ign = 0;
            
            do{
                ign = 0;
                for(int i = 0; i < N; ++i){
                    (i%100 == 0) ? printf("sitio(%d)\n", i) : true ;
                    if(f[i] == 1){
                        if(s[mtzviz[i][0]] == 1 && f[mtzviz[i][0]] == 0){
                            f[mtzviz[i][0]] = 1;
                            ign++;
                        }
                        if(s[mtzviz[i][1]] == 1 && f[mtzviz[i][1]] == 0){
                            f[mtzviz[i][1]] = 1;
                            ign++;
                        }
                        if(s[mtzviz[i][2]] == 1 && f[mtzviz[i][2]] == 0){
                            f[mtzviz[i][2]] = 1;
                            ign++;
                        }
                        if(s[mtzviz[i][3]] == 1 && f[mtzviz[i][3]] == 0){
                            f[mtzviz[i][3]] = 1;
                            ign++;
                        }
                    }
                }
                ++t;
            }while(ign != 0);
            printf("Terminou um\n");
            fprintf(arks[j-1], "%d\n", t);
        }
    }

    clock_t toc = clock();
    double time = (double)(toc - tic)/CLOCKS_PER_SEC;

    // Escreve arquivo de informações sobre a simulação
    fprintf(informa, "seed = %d\n", seed);
    fprintf(informa, "\n#define NP %.0lf   // Número de p utilizados em cada simulação\n", NP);
    fprintf(informa, "tempo de execução = %.5lfs", time);
    
    fclose(rede50);
    fclose(rede100);
    fclose(rede150);
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

