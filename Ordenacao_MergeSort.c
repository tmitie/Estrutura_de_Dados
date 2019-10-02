#include<stdlib.h>
#include<stdio.h>


/* A fun��o recebe vetores crescentes v[p..q�1] e v[q. . r�1] * e rearranja v[q. . r�1] em ordem crescente. */
void Intercala (int p, int q, int r, int v[])
{
    int i, j, k, *w;

    w = malloc ((r-p) * sizeof (int));

    i = p;
    j = q;
    k = 0;

    while(i < q && j < r)
    {
        if (v[i] <= v[j])
            w[k++] = v[i++];

        else
            w[k++] = v[j++];
    }
    while (i < q)
        w[k++] = v[i++];

    while (j < r)
        w[k++] = v[j++];

    for (i = p; i < r; i++)
        v[i] = w[i-p];

    free (w);
}


/* Esta funcao rearranja o vetor v[p..r�1] em ordem * crescente. */
void Mergesort (int p, int r, int v[])
{
    if (p < r -1)
    {
        int q = (p + r)/2;
        Mergesort (p, q, v);
        Mergesort (q, r, v);
        Intercala (p, q, r, v);
    }
}


int main()
{
    int i;
    int v[10] = {-1, 15, -999, 10, 7, 6, 0, 0, 7, 100};

    Mergesort (0, 10, v);

    for(i = 0; i < 10; i++)
        printf(" %d ", v[i]);

    printf("\n\n\n");
    return 0;
}
