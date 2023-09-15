/*

Esse código performa uma simulação do Modelo de Ising-2D de acordo com os parâmetros dados ao rodar
o código compilado nessa seguinte ordem

./a.out pasta seed L STEPS RND IMG CI TI TF dT TRANS CR

As medidas que podem ser feitas nessa versão são:
- Densidade de Energia
- Magnetização
- Correlação Temporal
- Correlação Espacial

ELE NÃO CRIA A PASTA, ELE SÓ RECEBE O NOME DELA E BOTA OS ARQUIVOS LÁ
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>

#define PASTA "resultados"         // Define o nome da pasta na qual serão guardados os arquivos de saída 
#define SEED 1694805433          // Define a Seed
#define L 25             // Aresta da Rede
#define STEPS 5000         // Número de MCS no equilíbrio
#define RND 0           // 0: inicialização da rede toda com spin 1 || 1: inicialização aleatória da rede
#define IMG 0           // Para gravar snapshots
#define CI 0            // Para gravar a condição inicial
#define TI 1.0            // Temperatura inicial
#define TF 3.0            // Temperatua final
#define dT 0.05            // Delta T
#define TRANS 1000         // Número de MCS para jogar fora (transiente)
#define CR 0            // Gravar a Correlação espacial

int main(int argc, char *argv[]){
 
    int **vizinhos(int l);
    int energia(int *sis, int **viz, int n, int j);
    double magnetizacao(int *sis, int n);
    double uniform(double min, double max);
    double corrtemp(int *s0, int *st, double m0, double mt, int n);
    void corresp(double *cr, int *s, int **viz, int n, int l, double m);
    int seed = SEED;
    srand(seed);

    // Criação da pasta da simulação e comando de análise
    char saida1[100], saida2[100], saida3[100], saida4[100];
    sprintf(saida1, "%s/medidas-L-%d-TI-%.2lf-TF-%.2lf-dT-%.2lf-STEPS-%d-RND-%d-TRANS-%d.dat", PASTA, L, TI, TF, dT, STEPS, RND, TRANS);
    sprintf(saida2,      "%s/im-L-%d-TI-%.2lf-TF-%.2lf-dT-%.2lf-STEPS-%d-RND-%d-TRANS-%d.dat", PASTA, L, TI, TF, dT, STEPS, RND, TRANS);
    sprintf(saida3,      "%s/ci-L-%d-TI-%.2lf-TF-%.2lf-dT-%.2lf-STEPS-%d-RND-%d-TRANS-%d.dat", PASTA, L, TI, TF, dT, STEPS, RND, TRANS);
    sprintf(saida4,      "%s/CR-L-%d-TI-%.2lf-TF-%.2lf-dT-%.2lf-STEPS-%d-RND-%d-TRANS-%d.dat", PASTA, L, TI, TF, dT, STEPS, RND, TRANS);

    FILE *medidas = fopen(saida1, "a");
    FILE *img = fopen(saida2, "w");
    FILE *ci = fopen(saida3, "w");
    FILE *cr = fopen(saida4, "a"); // FAZ ALGO PRA MANTER O CR

    //__________________________________SIMULAÇÃO______________________________________________________________

    int i, j, s, t, dE, N, ncr = 0; 
    int J = 1;
    double E, m0 = 0, mt = 0;
    N = L*L;
    int stepcr = (CR <= 0) ? STEPS : STEPS/CR;      //Espaçamento entre medidas de C(r) 

    // Definição de temperatura(s)
    int nT;
    if(TI == TF) nT = 1;
    else nT = (int)((TF-TI)/dT);
    double T[nT];
    T[0] = TI;
    if(nT > 1) for(int t = 1; t <= nT; ++t) T[t] = T[t-1] + dT;

    double beta = 1./T[0];

    // Criando matriz e vetores necessários
    int **viz = vizinhos(L);
    int *sis = (int*)calloc(N, sizeof(int));
    int *s0 = (int*)calloc(N, sizeof(int));
    double *crr = (double*)calloc(L/2, sizeof(double));

    // Aplicando a Condição inicial
    if(RND) for(i = 0; i < N; ++i) sis[i] = (uniform(0., 1.) < .5) ? -1 : 1;
    else for(i = 0; i < N; ++i) sis[i] = 1;
    
    if(CI) for(i = 0; i < N; ++i) fprintf(ci, "%d\n", sis[i]);

    // Loop para passar pelo transiente
    E = (double) energia(sis, viz, N, 1);
    for(s = 0; s < TRANS; ++s){ //Loop sobre passos de Monte Carlo
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
        // se quiser gravar o transiente vc faria aqui
    }
    // Fim do loop transiente
    // Definindo s(t=0) e m(t=0)
    if(s == TRANS){
        for(i = 0; i < N; ++i) s0[i] = sis[i];
        m0 = magnetizacao(sis, N);
    }
    // Loop sobre o estado estacionário
    t = 0;
    for(int temp = 0; temp <= nT; ++temp){      // Loop de temperaturas
        for(s = 0; s < STEPS; ++s){             // Roda STEPS de MCS
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
    
            // Imagens para fazer o gif
            if(IMG){
                for(i = 0; i < N; ++i) fprintf(img, "%d\n", sis[i]);
                fprintf(img, "-2\n");
            }
            // Medidas
            mt = magnetizacao(sis, N);
            fprintf(medidas, "%d\t%lf\t%lf\t%lf\n", t, E/N, mt, corrtemp(s0, sis, m0, mt, N));
            if((CR > 0) && (ncr < CR) && (s%stepcr == 0)){
                corresp(crr, sis, viz, N, L, mt);
                for(int l  = 0; l < L/2; ++l) fprintf(cr, "%d\t%lf\n", l+1, crr[l]);
                fprintf(cr, "-1\t-1\n"); // tu podia usar a seed como separador pra garantir
                memset(crr, 0, (L/2)*sizeof(double));
                ncr++;
            }
        }
        beta = 1./T[temp];
        // Loop para passar pelo transiente
        E = (double) energia(sis, viz, N, 1);
        for(s = 0; s < TRANS; ++s){ //Loop sobre passos de Monte Carlo
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
            // se quiser gravar o transiente vc faria aqui
        }
        // Fim do loop transiente
        // Definindo s(t=0) e m(t=0)
        if(s == TRANS){
            for(i = 0; i < N; ++i) s0[i] = sis[i];
            m0 = magnetizacao(sis, N);
        }
    }
    //_________________________________FIM DA SIMULAÇÃO_____________________________________________ 
    fprintf(medidas, "-1\t-1\t-1\t-1\n"); 

    fclose(medidas);
    fclose(img);
    fclose(ci);
    fclose(cr);
    if(!IMG) remove(saida2);
    if(!CI) remove(saida3);
    if(CR == 0) remove(saida4);
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
    /*
    Função que calcula a energia do sistema
    */
    int en = 0;
    for(int i = 0; i < n; ++i) en += sis[i]*(sis[viz[i][0]] + sis[viz[i][3]]);
    return -j*en;
}

double magnetizacao(int *sis, int n){
    /*
    Função que calcula a magnetização so sistema
    */
    double m = 0;
    for(int i = 0; i < n; ++i) m += sis[i];
    return m/n;
}

double corrtemp(int *s0, int *st, double m0, double mt, int n){
    /*
    Função que mede a correlação temporal no tempo  t do sistema
    */
    double C = 0;
    for(int i = 0; i < n; ++i){
        C += s0[i]*st[i];
    }
    C /= n;
    C -= m0*mt;
    return C;
}

void corresp(double *crr, int *s, int **viz, int n, int l, double m){
    /*
    Função que mede a correlação espacial do sistema
    */
    double c = 0;
    int vv, vh;
    for(int i = 0; i < n; ++i){
        vv = viz[i][3];
        vh = viz[i][0];
        for(int li = 0; li < l/2; ++li){
            c = s[i]*(s[vh] + s[vv]);
            vv = viz[vv][3];
            vh = viz[vh][0];
            crr[li] += c; 
        }
    }
    for(int li = 0; li < l/2; ++li){
        crr[li] /= 2*n;
        //crr[l] -= m*m;
    }
}

