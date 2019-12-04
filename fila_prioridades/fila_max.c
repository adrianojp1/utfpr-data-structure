#include <stdio.h>
#include <math.h>
/*
int pai(int i)
{
    return (i - 1) / 2;
}

void build_maxHeap(int V[], int size)
{
    int i;
    for (i = floor(size / 2 - 1); i > -1; i--)
    {
        max_heapify(V, size, i);
    }
}

void heap_sort(int V[], int size)
{
    build_maxHeap(V, size);
    int i;

    for (i = size - 1; i > 0; i--)
    {
        trocar(V, 0, i);
        size = i;
        max_heapify(V, size, 0);
    }
}
*/
void trocar(int V[], int a, int b)
{
    int aux = V[a];
    V[a] = V[b];
    V[b] = aux;
}

void imprimir(int V[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%d ", V[i]);
    }
    printf("\n");
}

int esquerda(int i)
{
    return i * 2 + 1;
}

int direita(int i)
{
    return i * 2 + 2;
}

void max_heapify(int V[], int size, int i)
{
    int d = direita(i);
    int e = esquerda(i);

    int maior = i;
    if (e < size && V[e] > V[i])
        maior = e;

    if (d < size && V[d] > V[maior])
        maior = d;

    if (maior != i)
    {
        trocar(V, maior, i);
        max_heapify(V, size, maior);
    }
}

void heap_decrease_key(int V[], int size, int i, int chave)
{
    if (chave > V[i])
    {
        printf("Erro: chave maior que atual");
        return;
    }

    V[i] = chave;
    max_heapify(V, size, i);
}

int main()
{

    int i;

    int size = 12;

    int V[100] = {15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1};
    //15,13,9,5,12,8,7,4,0,6,2,1

    printf("Vetor inicial : ");
    imprimir(V, size);

    heap_decrease_key(V, size, 0, 1);

    printf("Vetor final : ");
    imprimir(V, size);

    return 0;
}
