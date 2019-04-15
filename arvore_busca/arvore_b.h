#include <stdio.h>
#include <stdlib.h>

typedef struct _arvore{
    int _info;
    struct _arvore *_esq;
    struct _arvore *_dir;
} Arvore;

int verifica_arv_vazia (Arvore *a);

Arvore* cria_arv(int info, Arvore* esq, Arvore* dir);

Arvore* inserir (Arvore* a, int info);

int buscar (Arvore* a, int info);

Arvore* remover (Arvore* a, int info);

int min1 (Arvore *a);

int max1 (Arvore *a);

void imprime_decrescente (Arvore *a);

int maior_ramo (Arvore *a);

int ancestral (Arvore *a, int e1, int e2);
