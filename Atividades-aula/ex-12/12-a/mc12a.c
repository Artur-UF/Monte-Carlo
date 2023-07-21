#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>

#define N 10000     // Número de Passos
#define AM 1000		// Amostras
#define STEP 10	// A cada quantos passos eu pego para calcular o MSD

int main(){
    double uniform(double min, double max);
    int seed = time(NULL);
    srand(seed);

    // Criação da pasta da simulação e comando de análise
    char pasta[30], saida1[50], saida2[50], info[50];
    sprintf(pasta, "AN-%d-AM-%d-STEP-%d", N, AM, STEP);
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
    FILE *msd = fopen(saida2, "w");
    FILE *informa = fopen(info, "w");

    char comando[50];
    sprintf(comando, "python3 tracka.py %s\n", pasta);
    printf("%s", comando);
    
    //___________________DINAMICA___________________________
    int rand, n;
    int x = 0, y = 0;
    
    double *amostras = calloc((N/STEP), sizeof(double)); // pode usar memset() aqui tmb
    
    
    clock_t tic = clock();
    for(int am = 1; am <= AM; ++am){
        for(n = 1; n <= N; ++n){
            if(am == 1) fprintf(track, "%d\t%d\n", x, y);        
            if(n%STEP == 0) amostras[(n/STEP)-1] += (double) x*x + y*y;
            // Dinâmica
            rand = uniform(0, 4);
            switch(rand){
                case 0:
                    x++;
                break;
                case 1:
                    y++;
                break;            
                case 2:
                    x--;
                break;
                case 3:
                    y--;
                break;
            }
        }
        x = 0;
        y = 0;
        seed += 3;
        srand(seed);
    }
    	
    clock_t toc = clock();
    double time = (double)(toc - tic)/CLOCKS_PER_SEC;
    
    // Escrevendo o arquivo do MSD
    for(int i = STEP; i <= N; i += STEP){
    	fprintf(msd, "%d\t%lf\n", i, amostras[(i/STEP)-1]/AM);
    }
    
    // Escreve arquivo de informações sobre a simulação
    fprintf(informa, "seed = %d\n", seed);
    fprintf(informa, "\n#define N %d     // Número de Passos\n#define AM %d		// Amostras\n#define STEP %d	// A cada quantos passos eu pego para calcular o MSD\n", N, AM, STEP);
    fprintf(informa, "tempo de execução = %.4lfs", time);
    
    fclose(track);
    fclose(msd);
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

