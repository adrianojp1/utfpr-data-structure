#include "arvore.h"

int main()
{
    Arvore *a = constroi_arv ('a',
    constroi_arv('b',
    cria_arv_vazia(),
    cria_arv_vazia())
    ,
    constroi_arv('c',
    cria_arv_vazia(),
    cria_arv_vazia()
    ));

    imprime_pre_ordem(a);
    printf("\n");

    imprime_in_ordem(a);
    printf("\n");

    imprime_pos_ordem(a);
    printf("\n");

    imprime_arv_marcadores(a);
    printf("\n");

    printf("%d", pertence_arv(a, 'd'));
    printf("\n");

    printf("%d", conta_nos(a));
    printf("\n");

    printf("%d", calcula_altura_arvore(a));
    printf("\n");

    printf("%d", conta_nos_folha(a));
    printf("\n");

    getchar();
    
    return 0;
}
