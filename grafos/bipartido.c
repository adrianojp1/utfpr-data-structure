#include <stdio.h>
#include <stdlib.h>

/*Estrutura para um nó em uma lista encadeada: */
typedef struct noA
{
    int id;           /*Identificador armazenado no nó. */
    struct noA *next; /* Próximo nó na lista encadeada. */
} NoA;

/*Estrutura de Grafo com lista de adjacências: */
typedef struct grafoA
{
    int E;     /* Quantidade de arestas. */
    int V;     /* Quantidade de vértices. */
    NoA **Adj; /* Lista de adjacências. */
} GrafoA;

/*Estrutura para um nó em uma matriz de adjacências: */
typedef struct noM
{
    int peso; /*Peso armazenado na aresta. */
} NoM;

/*Estrutura de Grafo com matriz de adjacências: */
typedef struct grafoM
{
    int E;     /* Quantidade de arestas. */
    int V;     /* Quantidade de vértices. */
    NoM **Mat; /* Matrix de adjacências. */
} GrafoM;

/*Função para criar um grafo com lista de adjacências.*/
GrafoA *criar_grafo_adj(int tamanho)
{
    int v;
    GrafoA *G = (GrafoA *)malloc(sizeof(GrafoA));
    G->E = 0;
    G->V = tamanho;
    G->Adj = (NoA **)malloc(tamanho * sizeof(NoA *));
    for (v = 0; v < G->V; v++)
    {
        G->Adj[v] = NULL;
    }
    return G;
}

/*Função para criar um grafo com matriz de adjacências.*/
GrafoM *criar_grafo_mat(int tamanho)
{
    int v;
    GrafoM *G = (GrafoM *)malloc(sizeof(GrafoM));
    G->E = 0;
    G->V = tamanho;
    G->Mat = (NoM **)malloc(tamanho * sizeof(NoM *));
    for (v = 0; v < G->V; v++)
    {
        G->Mat[v] = (NoM *)malloc(tamanho * sizeof(NoM));
    }
    return G;
}

/*Função para destruir um grafo construído com lista de adjacências.*/
void liberar_grafo_adj(GrafoA *G)
{
    int v;
    for (v = 0; v < G->V; v++)
    {
        if (G->Adj[v] != NULL)
        {
            free(G->Adj[v]);
        }
    }
    free(G->Adj);
    free(G);
}

/*Função para destruir um grafo construído com lista de adjacências.*/
void liberar_grafo_mat(GrafoM *G)
{
    int v;
    for (v = 0; v < G->V; v++)
    {
        if (G->Mat[v] != NULL)
        {
            free(G->Mat[v]);
        }
    }
    free(G->Mat);
    free(G);
}

void inicializar_grafo_mat(GrafoM *Gm)
{
    int i, j;
    for (i = 0; i < Gm->V; i++)
    {
        for (j = 0; j < Gm->V; j++)
        {
            Gm->Mat[i][j].peso = 0;
        }
    }
}

void adicionar_aresta_grafo_mat(int v1, int v2, GrafoM *Gm)
{
    Gm->Mat[v1][v2].peso = 1;
    Gm->Mat[v2][v1].peso = 1;
    Gm->E++;
}

void imprimir_grafo_mat(GrafoM *Gm)
{
    printf("Grafo (Matriz Adjacencia):\n");
    int i, j;

    printf("   ");
    for (i = 0; i < Gm->V; i++)
    {
        printf(" %d ", i);
    }
    printf("\n\n");

    for (i = 0; i < Gm->V; i++)
    {
        printf("%d  ", i);
        for (j = 0; j < Gm->V; j++)
        {
            printf(" %d ", Gm->Mat[i][j]);
        }
        printf("\n");
    }
}

void adicionar_aresta_unilateral_grafo_adj(int v1, int v2, GrafoA *Ga)
{
    NoA *pAux = Ga->Adj[v1], *ultimo = NULL;
    while (pAux != NULL)
    {
        ultimo = pAux;
        pAux = pAux->next;
    }

    NoA *novo = (NoA *)malloc(sizeof(NoA));
    novo->id = v2;
    novo->next = NULL;

    if (ultimo != NULL)
    {
        ultimo->next = novo;
    }
    else
    {
        Ga->Adj[v1] = novo;
    }
}

void adicionar_aresta_grafo_adj(int v1, int v2, GrafoA *Ga)
{
    adicionar_aresta_unilateral_grafo_adj(v1, v2, Ga);
    adicionar_aresta_unilateral_grafo_adj(v2, v1, Ga);
    Ga->E++;
}

void imprimir_grafo_adj(GrafoA *Ga)
{
    printf("Grafo (Lista Adjacencia):\n");
    int i;
    NoA *pAux;
    for (i = 0; i < Ga->V; i++)
    {
        printf("%d -> ", i);
        pAux = Ga->Adj[i];
        while (pAux != NULL)
        {
            printf("%d ", pAux->id);
            pAux = pAux->next;
        }
        printf("\n");
    }
}

#define BRANCO 0
#define CINZA 1
#define PRETO 2
#define VERMELHO 3
#define AZUL 4

#define NIL -1

/*Estrutura para atributos de uma busca em profundidade de uma lista de adjacências */
typedef struct depth_first_search
{
    int cor;
    int pai;
    int f;
    int d;
} DFS;

void DFS_Visit(GrafoA *G, int u, DFS *V, int *tempo, int u_cor)
{
    V[u].cor = CINZA;
    V[u].d = ++(*tempo);
    NoA *pAux;
    for (pAux = G->Adj[u]; pAux != NULL; pAux = pAux->next)
    {
        if (V[pAux->id].cor == u_cor)
        {
            printf("O grafo nao e bipartido\n");
            return;
        }
        else if (V[pAux->id].cor == BRANCO)
        {
            V[pAux->id].pai = u;
            DFS_Visit(G, u, V, tempo, u_cor == AZUL ? VERMELHO : AZUL);
        }
    }
    V[u].f = ++(*tempo);
}

void imprime_caminho(int u, DFS *V)
{
    printf("%d ", u);
    if (V[u].pai != NIL)
        imprime_caminho(V[u].pai, V);
}

void Caminho_DFS(int u, DFS *V) //vi = vértice inicial
{
    printf("Caminho: ");
    imprime_caminho(u, V);
    printf("\n");
}

/*Função para busca em profundidade de uma lista de adjacências */
void Busca_Profundidade(GrafoA *G)
{
    int u;
    DFS *V = (DFS *)malloc(G->V * sizeof(DFS));
    for (u = 0; u < G->V; u++)
    {
        V[u].cor = BRANCO;
        V[u].pai = NIL;
    }

    int tempo = 0;

    for (u = 0; u < G->V; u++)
    {
        if (V[u].cor == BRANCO)
        {
            DFS_Visit(G, u, V, &tempo, VERMELHO);
        }
    }
    printf("O grafo é bipartido\n");

    printf("\n");
    /*
    Caminho_DFS(3, V);
    Caminho_DFS(8, V);
    Caminho_DFS(11, V);*/
}

int main()
{
    int Va = 7; //Número de vértices

    GrafoA *Ga = criar_grafo_adj(Va);

    adicionar_aresta_grafo_adj(1, 0, Ga);
    adicionar_aresta_grafo_adj(1, 2, Ga);
    adicionar_aresta_grafo_adj(1, 4, Ga);
    adicionar_aresta_grafo_adj(0, 5, Ga);
    adicionar_aresta_grafo_adj(5, 4, Ga);
    adicionar_aresta_grafo_adj(3, 6, Ga);

    Busca_Profundidade(Ga);

    //imprimir_grafo_adj(Ga);

    liberar_grafo_adj(Ga);

    return 0;
}

/*
int main()
{

    int Vm = 6; /Número de vértices
    GrafoM *Gm = criar_grafo_mat(Vm);
    inicializar_grafo_mat(Gm);
    adicionar_aresta_grafo_mat(0, 1, Gm);
    adicionar_aresta_grafo_mat(0, 2, Gm);
    adicionar_aresta_grafo_mat(0, 5, Gm);
    adicionar_aresta_grafo_mat(1, 2, Gm);
    adicionar_aresta_grafo_mat(1, 3, Gm);
    adicionar_aresta_grafo_mat(2, 3, Gm);
    adicionar_aresta_grafo_mat(2, 4, Gm);
    adicionar_aresta_grafo_mat(3, 4, Gm);
    adicionar_aresta_grafo_mat(4, 5, Gm);
    imprimir_grafo_mat(Gm);

    printf("\n");

    int Va = 6; //Número de vértices

    GrafoA *Ga = criar_grafo_adj(Va);
    adicionar_aresta_grafo_adj(0, 1, Ga);
    adicionar_aresta_grafo_adj(0, 2, Ga);
    adicionar_aresta_grafo_adj(0, 5, Ga);
    adicionar_aresta_grafo_adj(1, 2, Ga);
    adicionar_aresta_grafo_adj(1, 3, Ga);
    adicionar_aresta_grafo_adj(2, 3, Ga);
    adicionar_aresta_grafo_adj(2, 4, Ga);
    adicionar_aresta_grafo_adj(3, 4, Ga);
    adicionar_aresta_grafo_adj(4, 5, Ga);
    imprimir_grafo_adj(Ga);

    liberar_grafo_adj(Ga);
    liberar_grafo_mat(Gm);

    return 0;
}
*/