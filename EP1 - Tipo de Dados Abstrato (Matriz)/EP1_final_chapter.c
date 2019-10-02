#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

/*
Universidade Federal de Santa Catarina
Engenharia de Computacao
Exercício Programa 1 de Estrutura de Dados
Matheus de Oliveira Barcelos - 14104028
Thaynara Tessaline Mitie Sei Soares - 13204556
Filipe Lopes - 14205352
*/


struct celula{
    int valor, posm, posn, indicev;
    struct celula *seg;
};
typedef struct celula Celula;

struct matriz_{
    int orderm, ordern, tamanho;
    Celula *V;
};

typedef struct matriz_ Matriz;

/*Declaração de Funções*/
Matriz LeM(FILE *arq);
void inserir(Celula *v, int x, int i, int j);
void inicializa(Celula *V, int m);
Matriz PotenciaMs(Matriz A, double p);
void imprimir (Celula *lst);
void EscreveM (Matriz A);
Matriz SubtraiMs(Matriz A, Matriz B);
void TelaInicial();
Matriz SomaMs(Matriz A, Matriz B);
Matriz MultiplicaMs(Matriz A, Matriz B);
void DesalocaM(Matriz A);
void AtribuiM(Matriz D, Matriz O);


int main(){

    /*PARA UTILIZAR AS FUNÇÕES DO TIPO MATRIZ É NESCESSARIO ATRIBUIR ELAS A MM, AS DO*/
    /*TIPO VOID BASTA CHAMAR NORMALMENTE*/

    Matriz A, W, O, MM;


    FILE *arq;

    arq = fopen("matriz1.txt", "r");
    A = LeM(arq);
    arq = fopen("matriz2.txt", "r");
    W = LeM(arq);
    arq = fopen("matriz3.txt", "r");
    O = LeM(arq);
    EscreveM(A);
    EscreveM(W);
    MM = SubtraiMs(A, W);
    EscreveM(MM);


return 0;
}

void DesalocaM(Matriz A){
    int i, j;

    for(i=0; i< A.orderm; i++ )
    {
        for(j=0; j< A.ordern; j++)
        {
            Celula *lixo;
            lixo = A.V[j].seg;
            A.V[j].seg = lixo->seg;
            free(lixo);
        }
    }
}


void AtribuiM(Matriz D, Matriz O)
{
    int m, n, i;
    Celula *auxA, *auxB;
    m = O.orderm;
    n = O.ordern;

    for ( i = 0; i < m; i++)
    {
        for(auxA= D.V[i].seg; auxA != NULL; auxA = auxA->seg)
        {
            for(auxB= O.V[i].seg; auxB != NULL; auxB = auxB->seg)
            {
                if(O.V[i].valor != 0)
                    auxA->valor = auxB->valor ;
                else
                    auxA->seg = NULL;
            }
        }
    }
}


void inserir(Celula * v, int x, int i, int j)
{
    Celula *nova, *aux;
    nova = (Celula *)malloc(sizeof(Celula));
    for(aux = v; aux->seg != NULL; aux = aux->seg);
    nova->valor = x;
    nova->posm = i;
    nova->posn = j;
    nova->seg = aux->seg;
    aux->seg = nova;

}
Matriz LeM(FILE *arq)
{
    int i, j, m, n, x;

    Matriz M;
    fscanf(arq,"%d %d", &m, &n); /*LE A ORDEM */
    M.orderm = m;
    M.ordern = n;
    M.V = (Celula*) malloc(sizeof(Celula)*m);
    inicializa(M.V, m);

    for (i=0; i<m ; i++){ /*LE OS ELEMENTOS DA MATRIZ*/
        for(j=0; j<n; j++){
             fscanf(arq, "%d ", &x);
             if(x != 0)
                inserir(&(M.V[i]) , x, i, j);
        }
    }
fclose(arq);

return M;
}

void inicializa(Celula *V, int m){ /*INICIALIZANDO UMA CELULA COM CABEÇA*/
    int i;
    for(i = 0; i< m; i++){
        V[i].seg = NULL;
    }
}

void imprimir (Celula *V) /*FUNÇÃO AUXILIAR PARA AJUDAR COM O ESCREVE*/
{
    Celula *p;
    int j = 0;
    for(p = V->seg; p != NULL; )
    {
        if(p->posn > j)
            printf("");
        else
        {
            printf("V[%d][%d] = %d ", p->posm, p->posn, p->valor);
        }
        j++;

        if (j > p->posn)
            p = p->seg;
    }

}

void EscreveM (Matriz A)
{
    int i;

    printf("\n\nLinhas: %d Colunas: %d\n", A.orderm, A.ordern);
    for (i=0; i < A.orderm ; i++)
    {
        printf("\n");
        imprimir(&A.V[i]);
    }
}


Matriz PotenciaMs(Matriz A, double p)
{
   int i, x, m, n;
   Celula *aux;

   m = A.orderm;
   n = A.ordern;

   for ( i = 0; i < m; i++)
   {
            for(aux = A.V[i].seg; aux != NULL; aux = aux->seg)
            {
                    x = pow((double)aux->valor, p);
                    aux->valor = x;
            }
   }
return A;
}

Matriz SubtraiMs(Matriz A, Matriz B)
{
        int i, m, n;

        Matriz Sub;
        Celula *auxA, *auxB;

        m = A.orderm;
        n = A.ordern;
        Sub.orderm = m;
        Sub.ordern = n;
        Sub.V = (Celula *) malloc(sizeof(Celula) * m);
        inicializa(Sub.V, m);

        for ( i = 0; i < m; i++)
        {
            for(auxA = A.V[i].seg; auxA != NULL; ) /* PARA A SUBTRAÇÃO DE MATRIZES, HAVERÁ PROBLEMAS SE O ÚLTIMO ELEMENTO DA COLUNA DA MATRIZ FOR ZERO, */
            {                                      /* POIS, POR NÃO ARMAZENAR OS ZEROS, O CAMPO SEG APONTARÁ PARA NULL, FAZENDO COM QUE VÁ PARA A PROXIMA LINHA*/
                for(auxB = B.V[i].seg; auxB != NULL; )
                {
                    if (auxA->posn == auxB->posn)
                    {
                        inserir(&Sub.V[i],(auxA->valor - auxB->valor), i, auxA->posn);
                        auxA = auxA->seg;
                        auxB = auxB->seg;
                    }
                    else if (auxA->posn < auxB->posn) /*SE A FOR MENOR QUE B, SIGNIFICA QUE O A PULOU DE POSIÇÃO, POR NÃO CONTER ELEMENTOS, OU ZEROS*/
                    {
                        inserir(&Sub.V[i],(auxA->valor + 0), i, auxA->posn);
                        auxA = auxA->seg;
                    }
                    else if (auxA->posn > auxB->posn) /*SE B FOR MENOR QUE A, SIGNIFICA QUE O B PULOU DE POSIÇÃO, POR NÃO CONTER ELEMENTOS, OU ZEROS*/
                    {
                        inserir(&Sub.V[i],(0 - auxB->valor), i, auxA->posn);
                        auxB = auxB->seg;
                    }
                }
            }
        }
return Sub;
}

Matriz SomaMs(Matriz A, Matriz B)
{
    int i, m, n;

    Matriz Soma;
    Celula *auxA, *auxB;

    if((A.orderm == B.orderm) && (A.ordern == B.ordern))
    {
        m = A.orderm;
        n = A.ordern;
        Soma.orderm = m;
        Soma.ordern = n;
        Soma.V = (Celula *) malloc(sizeof(Celula) * m);
        inicializa(Soma.V, m);

        for ( i = 0; i < m; i++)
        {

            for(auxA = A.V[i].seg; auxA != NULL; )/* PARA A SOMA DE MATRIZES, HAVERÁ PROBLEMAS SE O ÚLTIMO ELEMENTO DA COLUNA DA MATRIZ FOR ZERO, */
            {                                       /* POIS, POR NÃO ARMAZENAR OS ZEROS, O CAMPO SEG APONTARÁ PARA NULL, FAZENDO COM QUE VÁ PARA A PROXIMA LINHA*/
                for(auxB = B.V[i].seg; auxB != NULL; )
                {

                    if (auxA->posn == auxB->posn)
                    {
                        inserir(&Soma.V[i],(auxA->valor + auxB->valor), i, auxA->posn);
                        auxA = auxA->seg;
                        auxB = auxB->seg;
                    }
                    else if (auxA->posn < auxB->posn)/*SE A FOR MENOR QUE B, SIGNIFICA QUE O A PULOU DE POSIÇÃO, POR NÃO CONTER ELEMENTOS, OU ZEROS*/
                    {
                        inserir(&Soma.V[i],(auxA->valor + 0), i, auxA->posn);
                        auxA = auxA->seg;
                    }
                    else if (auxA->posn > auxB->posn) /*SE B FOR MENOR QUE A, SIGNIFICA QUE O B PULOU DE POSIÇÃO, POR NÃO CONTER ELEMENTOS, OU ZEROS*/
                    {
                        inserir(&Soma.V[i],(0 + auxB->valor), i, auxA->posn);
                        auxB = auxB->seg;
                    }
                }

            }
        }
    }
    else
    {
        system("color A5");
        printf("\n Nao eh Possivel somar as Matrizes! ");
    }
return Soma;
}


Matriz MultiplicaMs(Matriz A, Matriz B)
{
    int i, j, m, n, soma = 0;

    Matriz Mult;
    Celula *auxA, *auxB;

    m = A.orderm;
    n = A.ordern;
    Mult.orderm = A.orderm;
    Mult.ordern = B.ordern;
    Mult.V =(Celula*)malloc(sizeof(Celula)*m);

    inicializa(Mult.V, m);

    if((A.ordern == B.orderm))/*CONDIÇÃO PARA A MULTIPLICAÇAO*/ /* (A.orderm == B.ordern)) SIGNIFICA A ORDEM DA MATRIZ */
    {
        for ( i = 0; i < A.orderm; i++)
        {
            for(j = 0; j < B.ordern; j++)
            {
                for(auxA = A.V[i].seg; auxA != NULL; auxA = auxA->seg)
                {
                    for(auxB = B.V[j].seg; auxB != NULL; auxB = auxB->seg)
                    {
                        if((auxA->posm == auxB->posn) && (auxA->posn == auxB->posm)) /*VERIFICA A POSICAO DE LINHA E COLUNA DOS ELEMENTOS PARA REALIZAR A MULTIPLICAÇÃO*/
                        {
                               soma = soma + (auxA->valor * auxB->valor);
                               inserir(&Mult.V[i], soma, i, j);
                               soma = 0;
                        }
                    }
                }
            }
        }
    }
    else
    {
        system("color A5");
        printf("\n Nao eh Possivel Multiplicar! ");
    }
return Mult;
}
