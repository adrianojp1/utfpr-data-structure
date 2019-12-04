#include <stdio.h>
#include <math.h>
#include <limits.h>

int pai(int i)
{
    return (i - 1) / 2;
}

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
    printf("\n\n");
}

int esquerda(int i)
{
    return i * 2 + 1;
}

int direita(int i)
{
    return i * 2 + 2;
}

/*===============================================================================================*/

void min_heapify(int V[], int size, int i)
{
    int d = direita(i);
    int e = esquerda(i);

    int menor = i;
    if (e < size && V[e] < V[i])
        menor = e;

    if (d < size && V[d] < V[menor])
        menor = d;

    if (menor != i)
    {
        trocar(V, menor, i);
        min_heapify(V, size, menor);
    }
}

void climb_inMinHeap(int V[], int i)
{
    while (i > 0 && V[pai(i)] > V[i])
    {
        trocar(V, i, pai(i));
        i = pai(i);
    }
}

void heap_decrease_key(int V[], int i, int chave)
{
    if (chave > V[i])
    {
        printf("Erro: chave maior que atual");
        return;
    }
    V[i] = chave;

    climb_inMinHeap(V, i);
}

int heap_extract_min(int V[], int *size)
{
    if (*size < 1)
    {
        printf("Erro: heap underflow");
        return INT_MIN;
    }
    int min = V[0];
    V[0] = V[*size - 1];
    *size -= 1;
    min_heapify(V, *size, 0);
    return min;
}

void build_minHeap(int V[], int size)
{
    int i;
    for (i = floor(size / 2 - 1); i > -1; i--)
    {
        min_heapify(V, size, i);
    }
}

void min_heap_insert(int V[], int *size, int chave)
{
    *size += 1;
    V[*size - 1] = INT_MAX;
    heap_decrease_key(V, *size - 1, chave);
}

int main()
{

    int i;

    int size = 10;

    int V[100] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    printf("Vetor inicial : ");
    imprimir(V, size);

    build_minHeap(V, size);
    printf("Vetor ordenado : ");
    imprimir(V, size);

    printf("Min extraido: %d\n", heap_extract_min(V, &size));
    printf("Vetor apos extracao : ");
    imprimir(V, size);

    heap_decrease_key(V, 8, 1);
    printf("Vetor apos diminuir 16 para 1 : ");
    imprimir(V, size);

    min_heap_insert(V, &size, 0);
    printf("Vetor apos insercao de 0 : ");
    imprimir(V, size);

    return 0;
}
