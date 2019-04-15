#include "arvore.h"

Arvore* cria_arv_vazia()
{
    return NULL;
}

int verifica_arv_vazia (Arvore *a)
{
    return (a == NULL);
}

void destroi_arv(Arvore* arv)
{
    if(!verifica_arv_vazia(arv))
    {
        destroi_arv(arv->dir);
        destroi_arv(arv->esq);
        free(arv);
    }
}

Arvore* constroi_arv(char elem, Arvore* esq, Arvore* dir)
{
    Arvore *no = (Arvore*)malloc(sizeof(Arvore));
    no->dir = dir;
    no->esq = esq;
    no->info = elem;
    return no;
}

void imprime_pre_ordem(Arvore* a)
{
    if(!verifica_arv_vazia(a))
    {
        printf("%c ", a->info);
        imprime_pre_ordem(a->esq);
        imprime_pre_ordem(a->dir);
    }
}

void imprime_in_ordem(Arvore* a)
{
    if(!verifica_arv_vazia(a))
    {
        imprime_in_ordem(a->esq);
        printf("%c ", a->info);
        imprime_in_ordem(a->dir);
    }
}

void imprime_pos_ordem(Arvore* a)
{
    if(!verifica_arv_vazia(a))
    {
        imprime_pos_ordem(a->esq);
        imprime_pos_ordem(a->dir);
        printf("%c ", a->info);
    }
}

void imprime_arv_marcadores(Arvore* a)
{
    printf("<");
    if(!verifica_arv_vazia(a))
    {
        printf("%c", a->info);
        imprime_arv_marcadores(a->esq);
        imprime_arv_marcadores(a->dir);
    }
    printf(">");
}

int pertence_arv (Arvore *a, char c)
{
    return (!verifica_arv_vazia(a) ?
            (a->info == c ? 
                1 : (pertence_arv(a->dir, c) || pertence_arv(a->esq, c)) 
            ) : (0) );
}

int conta_nos (Arvore *a)
{
    return (!verifica_arv_vazia(a) ? conta_nos(a->dir) + conta_nos(a->esq) + 1 : 0);
}

int max(int a, int b)
{
    return (a > b ? a : b);
}

int calcula_altura_arvore (Arvore *a)
{
    return (!verifica_arv_vazia(a) ? ( max(calcula_altura_arvore(a->dir), calcula_altura_arvore(a->esq)) + 1) : (-1) );
}

int conta_nos_folha (Arvore *a)
{
    return (!verifica_arv_vazia(a) ?
            (verifica_arv_vazia(a->dir) && verifica_arv_vazia(a->esq) ?
                1 : (conta_nos_folha(a->dir) + conta_nos_folha(a->esq))
            ) : (0) );
}
