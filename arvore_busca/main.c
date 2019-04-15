#include "arvore_b.h"

int main () 
{
    Arvore *a = NULL;
    a = inserir (a, 50);
    a = inserir (a, 30);
    a = inserir (a, 90);
    a = inserir (a, 20);
    a = inserir (a, 40);
    a = inserir (a, 95);
    a = inserir (a, 10);
    a = inserir (a, 35);
    a = inserir (a, 45);

    printf("Max: %d\n", max1(a));
    printf("Min: %d\n", min1(a));
    
    imprime_decrescente(a);
    printf("\n");
    
    printf("Maior ramo: %d\n", maior_ramo(a));
    
    return 0;
}
