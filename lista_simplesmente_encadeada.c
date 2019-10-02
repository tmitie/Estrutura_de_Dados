#include<stdio.h>
#include<stdlib.h>
#define MAX 100
#include<string.h>
#include<conio.h>

/* LISTA SIMPLESMENTE ENCADEADA */

struct cont
{
    float Salario, Altura;
    char Nome[MAX];
};
typedef struct cont Pessoa;

struct cel
{
    Pessoa  *Conteudo;
    struct cel *seg;
};
typedef struct cel Celula;



void Imprime(Celula *p)
{
    Celula * i;
    for ( i = p->seg; i != NULL; i = i -> seg)
        printf(" Nome: %s \n Altura: %f m \n Salario: R$ %f \n \n\n", i->Conteudo->Nome, i->Conteudo->Altura,i->Conteudo->Salario);
}


/* Criando um lista vazia sem cabeça
Celula *lst;
lst = NULL;

Criando uma lista vazia com cabeça 1 forma

Celula c *lst;
c.seg = NULL;
lst = &c;

 Criando uma lista vazia com cabeça 2 forma

Celula *lst;
lst = malloc(sizeof(Celula));
lst -> seg =  NULL; */


void Insere(Celula *p, Pessoa *y) /*Inserindo uma celula entre uma existente e outra, se for vazia, supor q seja com cabeça*/
{

    Celula * nova;
    nova = malloc(sizeof(Celula));
    nova -> seg = p -> seg;
    nova -> Conteudo = y;
    p -> seg = nova;
}


void Remove(Celula *p)
{
    Celula *lixo;
    lixo = p ->seg;
    p -> seg = lixo -> seg;
    free (lixo);
}


int main()
{

    Pessoa p1, p2, p3;

    Celula *lst;
    lst = malloc(sizeof(Celula));
    lst -> seg =  NULL;

    strcpy(p1.Nome, "Joao");
    p1.Altura = 1.69;
    p1.Salario = 1000;
    Insere(lst, &p1);

    strcpy(p2.Nome, "Jose");
    p2.Altura = 1.70;
    p2.Salario = 2000;
    Insere(lst, &p2);

    strcpy(p3.Nome, "Joana");
    p3.Altura = 1.80;
    p3.Salario = 3000;
    Insere(lst, &p3);

    Imprime(lst);

    Remove(lst->seg);

    Imprime(lst);

    return 0;
}
