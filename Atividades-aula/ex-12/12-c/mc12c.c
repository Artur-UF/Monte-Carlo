#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>

#define P 1000          // Número de Passos
#define L 50            // Aresta do Sistema
#define N (L*L)         // Número de Sítios
#define AM 100          // Amostras

int main(){
    void colisao(int loc);
    double uniform(double min, double max);
    int seed = time(NULL);
    srand(seed);

    // Criação da pasta da simulação e comando de análise
    char pasta[30], saida1[50], saida2[50], info[50];
    sprintf(pasta, "P-%d-L-%d-N-%d-AM-%d", P, L, N, AM);
    sprintf(saida1, "%s/track.dat", pasta);
    sprintf(saida2, "%s/msd.dat", pasta);
    sprintf(info, "%s/info.txt", pasta);

    if(mkdir(pasta, 0777) == -1){
        printf("Já existe, vou limpar\n");
        remove(saida1);
        remove(saida2);
        remove(info);
    }
    FILE *track = fopen(saida1, "w");
    FILE *informa = fopen(info, "w");
    FILE *msd = fopen(saida2, "w");

    char comando[50];
    sprintf(comando, "python3 trackc.py %s\n", pasta);
    printf("%s", comando);
    //_____________________GERANDO MATRIZES________________________
    int *v = (int *)calloc(N, sizeof(int));
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
    int nv, rand;
    v[loc] = 1;
    int x = 0;
    int y = 0;

    fprintf(track, "%d\n", loc);
    fprintf(msd, "%d\n", x*x + y*y);

    for(int a = 0; a < AM; ++a){    
        for(int p = 0; p < P; ++p){
            auxloc = loc;
            rand = (int)uniform(0, 4);
            
            nv = v[mtzviz[loc][0]] + v[mtzviz[loc][1]] + v[mtzviz[loc][2]] + v[mtzviz[loc][3]];
            if(nv < 4 && v[mtzviz[loc][rand]] == 0){
                switch(rand){
                    case 0:
                        loc = mtzviz[loc][0];
                        x++;          
                    break;
                    case 1:
                        loc = mtzviz[loc][1];
                        y++;
                    break;
                    case 2:
                        loc = mtzviz[loc][2];
                        x--;
                    break;
                    case 3:
                        loc = mtzviz[loc][3];
                        y--;
                    break;
                }
                v[loc] = 1;
                if(fabs((auxloc%L) - (loc%L)) > 1 || fabs((auxloc/L) - (loc/L)) > 1) fprintf(track, "-1\t-1\n");
                fprintf(track, "%d\n", loc);
                fprintf(msd, "%d\n", x*x + y*y);  
            }else if(nv == 4){
                //printf("Tamanho = %d\n", p);
                break;
            }else{
                fprintf(track, "%d\n", loc);
                fprintf(msd, "%d\n", x*x + y*y);
            }
        }
        memset(v, 0, N*sizeof(int));
        x = 0;
        y = 0;
        loc = (int)N/2 + L/2;
        v[loc] = 1;
        fprintf(track, "-2\n%d\n", loc);
        fprintf(msd, "-2\n%d\n", x*x + y*y);
        seed += 3;
        srand(seed);
    }

    clock_t toc = clock();
    double time = (double)(toc - tic)/CLOCKS_PER_SEC;

    // Escreve arquivo de informações sobre a simulação
    fprintf(informa, "seed = %d\n", seed);
    fprintf(informa, "\n#define P %d         // Número de Passos\n#define L %d            // Aresta do Sistema\n#define N %d         // Número de Sítios\n#define AM %d          // Amostras\n", P, L, N, AM);
    fprintf(informa, "tempo de execução = %.4lfs", time);
    
    fclose(track);
    fclose(informa);
    fclose(msd);
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

