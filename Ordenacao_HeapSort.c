 #include<stdio.h>
 #include<stdlib.h>

/* Esta função recebe um max-heap v[1..m] e transforma * v[1..m+1] em max-heap. */
/*void InsereEmHeap (int m, int v[]) não tá inserindo na 1 posicao v[0]
{
    int f = m + 1;

    while(f > 1 && v[f/2] < v[f])
    {
        int t = v[f/ 2];
        v[f/2] = v[f] ;
        v[f] = t;
        f = f/2;
    }
}
 /* Rearranja um quase max-heap v[1..m] de modo a * transformá-lo em um max-heap. */
/* void SacodeHeap (int m, int v[])
 {
     int t, f = 2;

     while(f <= m)
    {
        if (f < m && v[f] < v[f+1])
        ++f;

        if (v[f/2] >= v[f])
        break;

        t = v[f/2];
        v[f/2] = v[f];
        v[f] = t;
        f *= 2;
    }
}

/* Rearranja o vetor v[1..n] de modo que ele fique * crescente. */
/*void Heapsort (int n, int v[])
{
    int m;

    for (m = 1; m < n; m++)
        InsereEmHeap (m, v);

    for (m = n; m > 1; m--)
    {
        int t = v[1];
        v[1] = v[m];
        v[m] = t;
        SacodeHeap (m-1, v);
    }
}*/
void heapsort(int a[], int n)
{

   int i = n / 2, pai, filho, t;

    for (;;)
    {
        if (i > 0)
        {
            i--;
            t = a[i];
        }
        else
        {
            n--;
            if (n == 0)
                return;
                t = a[n];
                a[n] = a[0];
        }

        pai = i;

        //Primeiro será feita a comparação com o filho da esquerda.
        filho = i * 2 + 1;

        while (filho < n)
        {
         //Se o filho da esquerda for menor do que o filho da direita,então será feita a troca do filho que será comparado.
          if ((filho + 1 < n)  &&  (a[filho + 1] > a[filho]))
              filho++;

          if (a[filho] > t)
          {
             a[pai] = a[filho];
             pai = filho;
             filho = pai * 2 + 1;
          }
          else
             break;
        }
      a[pai] = t;
   }
}

int main()
{
    int i;
    int v[5] = {0, 50, -35, 985, -35};

    heapsort(v,5);

    for(i = 0; i < 5; i++)
        printf("\n%d\n",v[i]);


    return 0;
}
