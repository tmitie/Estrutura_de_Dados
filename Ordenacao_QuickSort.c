 #include<stdio.h>
 #include<stdlib.h>


 /* Recebe um vetor v[p..r] com p <= r. Rearranja os * elementos do vetor e devolve j em p..r tal que * v[p..j-1] <=[j] < v[j+1..r].*/
 int Separa (int p, int r, int v[])
 {
     int c, j, k, t;
     c = v[r];
     j = p;
     for (k = p; k < r; k++)

        if (v[k] <= c)
        {
            t = v[j];
            v[j] = v[k];
            v[k] = t;
            j++;
        }

     v[r] = v[j];
     v[j] = c;
     return j;
}
/* Esta função rearranja o vetor v[p..r], com p <= r+1, * de modo que ele fique em ordem crescente. */
void Quicksort (int p, int r, int v[])
{
    int j;
    if (p < r)
    {
        j = Separa (p, r, v);
        Quicksort (p, j - 1, v);
        Quicksort (j + 1, r, v);
    }
}

int main()
{
    int i;
    int v[5] = {0, 50, -35, 985, -35};

    Quicksort(0,5,v);

    for(i = 0; i < 5; i++)
        printf("\n%d\n",v[i]);
    return 0;
}
