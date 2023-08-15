#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>

#define P 1000        // Número de Passos
#define L 50            // Aresta do Sistema
#define N (L*L)         // Número de Sítios
#define AM 1000        // Amostras

int main(){
    void colisao(int loc);
    double uniform(double min, double max);
    int seed = time(NULL);
    srand(seed);

    // Criação da pasta da simulação e comando de análise
    char pasta[30], saida1[50], saida2[50], saida3[50], info[50];
    sprintf(pasta, "P-%d-L-%d-N-%d-AM-%d", P, L, N, AM);
    sprintf(saida1, "%s/track1.dat", pasta);
    sprintf(saida1, "%s/track2.dat", pasta);
    sprintf(saida2, "%s/msd.dat", pasta);
    sprintf(info, "%s/info.txt", pasta);

    if(mkdir(pasta, 0777) == -1){
        printf("Já existe, vou limpar\n");
        remove(saida1);
        remove(saida2);
        remove(saida3);
        remove(info);
    }
    FILE *track1 = fopen(saida1, "w");
    FILE *track2 = fopen(saida3, "w");
    FILE *informa = fopen(info, "w");
    FILE *msd = fopen(saida2, "w");

    FILE *track[2] = {track1, track2};

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
    
    int auxloc[2], loc[2];
    loc[0] = (int)N/2 + L/2;
    loc[1] = loc[0] + 1;
    int nv, rand;
    v[loc[0]] = 1;
    v[loc[1]] = 1;
    int x = 0;
    int y = 0;
    printf("Oooi\n"); 
    int saida[2] = {0, 0};

    fprintf(track[0], "%d\n", loc[0]);
    fprintf(track[1], "%d\n", loc[1]);
    fprintf(msd, "%d\n", x*x + y*y);
    printf("Ooooiiii\n");
    for(int a = 0; a < AM; ++a){    
        for(int p = 0; p < P; ++p){
            for(int c = 0; c <= 1; ++c){
                //printf("Oi %d\n", p);
                if(saida[c] == 0){
                    auxloc[c] = loc[c];
                    rand = (int)uniform(0, 4);
                    nv = v[mtzviz[loc[c]][0]] + v[mtzviz[loc[c]][1]] + v[mtzviz[loc[c]][2]] + v[mtzviz[loc[c]][3]];
                    if(nv < 4 && v[mtzviz[loc[c]][rand]] == 0){
                        switch(rand){
                            case 0:
                                loc[c] = mtzviz[loc[c]][0];
                                x++;          
                            break;
                            case 1:
                                loc[c] = mtzviz[loc[c]][1];
                                y++;
                            break;
                            case 2:
                                loc[c] = mtzviz[loc[c]][2];
                                x--;
                            break;
                            case 3:
                                loc[c] = mtzviz[loc[c]][3];
                                y--;
                            break;
                        }
                        v[loc[c]] = 1;
                        if(fabs((auxloc[c]%L) - (loc[c]%L)) > 1 || fabs((auxloc[c]/L) - (loc[c]/L)) > 1) fprintf(track[c], "-1\n");
                        fprintf(track[c], "%d\n", loc[c]);
                        fprintf(msd, "%d\n", x*x + y*y);  
                    }else if(nv == 4){
                        saida[c]++;
                        break;
                    }else{
                        fprintf(track[c], "%d\n", loc[c]);
                        fprintf(msd, "%d\n", x*x + y*y);
                    }
                    //printf("Oi2\n");
                }
            }
            if(saida[0] + saida[1] == 2) break;
        }
        memset(v, 0, N*sizeof(int));
        x = 0;
        y = 0;
        loc[0] = (int)N/2 + L/2;
        loc[1] = loc[0] + 1;
        v[loc[0]] = 1;
        v[loc[1]] = 1;
        fprintf(track[0], "-2\n%d\n", loc[0]);
        fprintf(track[1], "-2\n%d\n", loc[1]);
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
    
    fclose(track1);
    fclose(track2);
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

