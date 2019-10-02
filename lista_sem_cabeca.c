#include<stdio.h>
#include<stdlib.h>
#define MAX 100
#include<string.h>


struct conteu
{
    float Salario, Altura;
    char Nome[MAX];
};
typedef struct conteu Pessoa;


struct cel
{
    Pessoa  *Conteudo;
    struct cel *seg;
};
typedef struct cel Celula;

typedef Celula * Lista;


void Imprimir(Celula *p)
{
    Celula * i;
    for ( i = p->seg; i != NULL; i = i -> seg)
        printf("   %s %f\n\n\n", i->Conteudo->Nome, i->Conteudo->Altura);
}


void Inserir( Lista * el, Pessoa *X, Celula *p)
{
    Celula *nova;
    nova = (Celula*)malloc(sizeof(Celula));
    nova -> Conteudo = X;

    if( *el == NULL )
    {
        *el = nova;
        nova -> seg = NULL;

    }
    else
    {
        nova->seg = p->seg;
        p->seg = nova;
    }
}


void Remove(Celula *p)
{
    Celula *lixo;
    lixo = p ->seg;
    p -> seg = lixo -> seg;
    free (lixo);
}


void Imprime(Celula *p)
{
    Celula * i;
    for ( i = p->seg; i != NULL; i = i -> seg)
        printf("   %s \n\n %f\n %f\n \n", i->Conteudo->Nome, i->Conteudo->Altura, i->Conteudo->Salario);
}


int main()
{
    Lista  lst = NULL;
    Pessoa p1, p2, p3;

    strcpy(p1.Nome, "Joao");
    p1.Altura = 1.69;
    p1.Salario = 1000;

    Inserir(&lst, &p1, NULL);

    strcpy(p2.Nome, "Joana");
    p2.Altura = 1.58;
    p2.Salario = 5000;

    Inserir( &lst, &p2, lst);


    strcpy(p3.Nome, "Jose");
    p3.Altura = 1.936;
    p3.Salario = 4000;
    Inserir(&lst, &p3, lst);

    Imprimir(lst);

    return 0;
}
