/*
  Matheus de Oliveira Barcelos         - 14104028
  Thaynara Tessaline Mitie Sei Soares  - 13204556
  Filipe Rafael Lopes da Silva         - 14205352
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Process_ {
    int id; /* 1 <= id <= 5000 */
    int time; /* 1 <= time <= 100 */
    int priority; /* 1 <= priority <= 1000 */
};
typedef struct Process_ Process;

int Insere(Process v[], Process x, int f) {
    int n = f;
    Process aux;
    v[f] = x;
    while (f > 1 && v[f/2].priority <= v[f].priority){
        aux = v[f];
        v[f] = v[f/2];
        v[f/2] = aux;
        f = f/2;
    }
    return n + 1;
}


int Delete(Process *Heap, int pos, int t) {
    /* segue o caminho do maior sempre "subindo" */
    while (pos < t) {
        int IMai;
        if (pos * 2 < t) {
            if (pos * 2 + 1 < t) {
                if (Heap[pos * 2 + 1].priority > Heap[pos * 2].priority) {
                    IMai = pos * 2 + 1;
                } else {
                    /* se for a última linha, inverte a posiçao t - 2 pela t - 1 e sobe a t - 1 */
                    if (pos * 2 == t - 2) {
                        Process aux;
                        aux = Heap[pos * 2];
                        Heap[pos * 2] = Heap[pos * 2 + 1];
                        Heap[pos * 2 + 1] = aux;
                        IMai = pos * 2 + 1;
                    } else
                        IMai = pos * 2;
                }
            } else {
                IMai = pos * 2;
            }
            Heap[pos] = Heap[IMai];
        } else {
            /* Caso nao haja mais "filho" e ainda haja termos mais a "frente" no vetor */
            if (Insere(Heap, Heap[t - 1], pos)); /* Ele nao vai ter que ir descendo na árvore, a última posiçao do vetor,*/
            return t - 1;       /*só deverá subi-la a partir da posiçao em que se está quando chega aqui a execuçao */
        }
        pos = IMai;
    }
    return t - 1;
}

int main() {
    int t = 1;
    Process Heap[5000], P, Exec;
    int NL, i;
    printf("Digite quantos processos seram feitos:\n");
    scanf("%d", &NL);
    printf("Digite os processos, onde o primeiro numero eh a quantidade de processos para entrar na fila,\n");
    printf("seguidos do nome do processo, prioridade e tempo de execucao(EX: 3 id1 id2 id3 1 2 3 1 2 3)\n");
    while (NL > 0) {
        /* recebendo os novos processos */
        int NP;
        char idAux[7];
        int *id, *time, *priority;
        scanf("%d", &NP);
        id = malloc(NP * sizeof(int));
        priority = malloc(NP * sizeof(int));
        time = malloc(NP * sizeof(int));
        for (i = 0; i < NP; i++) {
            scanf("%s", idAux);
            id[i] = atoi(idAux + 2);
        }
        for (i = 0; i < NP; i++) {
            scanf("%d", &priority[i]);
        }
        for (i = 0; i < NP; i++) {
            scanf("%d", &time[i]);
        }
        for (i = 0; i < NP; i++) {
            P.id = id[i];
            P.time = time[i];
            P.priority = priority[i];
            t = Insere(Heap, P, t);
        }
        /* excluindo o processo da fila */
        if (t > 1) {
            Exec = Heap[1];
            t = Delete(Heap, 1, t);

            /* Atualizando o valor de tempo do processo em execuçao */
            Exec.time -= 50;
            printf("id%d\n", Exec.id);
            if (Exec.time > 0) {
                t = Insere(Heap, Exec, t);
            }

        }
        NL--;
    }
    for (i = 1; i < t; i++)
        printf("id%d %d %d\n", Heap[i].id, Heap[i].time, Heap[i].priority);
    return 0;
}
