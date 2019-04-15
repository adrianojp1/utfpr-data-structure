#include "arvore_b.h"

int verifica_arv_vazia (Arvore *a)
{
    return (a == NULL);
}

Arvore* cria_arv(int info, Arvore* esq, Arvore* dir)
{
  Arvore* no = (Arvore*)malloc(sizeof(Arvore));
  no->_esq = esq;
  no->_dir = dir;
  no->_info = info;
  return no;
}

Arvore* inserir (Arvore* a, int info)
{
  if(verifica_arv_vazia(a))
    a = cria_arv(info, NULL, NULL);
  else if (a->_info > info)
    a->_esq = inserir(a->_esq, info);
  else
    a->_dir = inserir(a->_dir, info);
  return a;
}

int buscar (Arvore* a, int info)
{
  if(verifica_arv_vazia(a))
    return 0;
  else if(a->_info < info)
    return (buscar(a->_dir, info));
  else if(a->_info > info)
    return (buscar(a->_esq, info));
  else
    return 1;
}

Arvore* remover (Arvore* a, int info)
{
  if(verifica_arv_vazia(a))
    return NULL;
  else
  {
    if (a->_info > info)
      a->_esq = remover (a->_esq, info);
    else if (a->_info < info)
      a->_dir = remover (a->_dir, info);
    else //Achou 
      {
        if(verifica_arv_vazia(a->_dir) && verifica_arv_vazia (a->_esq)) //sem filhos
        {
          free(a);
          a = NULL;
        }
        else if(verifica_arv_vazia(a->_dir)) //só tem esquerda
        {
          Arvore* aux = a;
          a = a->_esq;
          free(aux);
        }
        else if(verifica_arv_vazia(a->_esq)) //só tem direita
        {
          Arvore* aux = a;
          a = a->_dir;
          free(aux);
        }
        else //2 filhos
        {
          Arvore* aux = a->_esq;
          while (!verifica_arv_vazia(aux->_dir))
            aux = aux->_dir;
          a->_info = aux->_info;
          aux->_info = info;
          a->_esq = remover(a, info);
        }
      }
    return a;
  }
}

int min1 (Arvore *a)
{
  if(verifica_arv_vazia(a))
    return 0;
  while(!verifica_arv_vazia(a->_esq))
    a = a->_esq;
  return a->_info;
}

int max1 (Arvore *a)
{
  if(verifica_arv_vazia(a))
    return 0;
  while(!verifica_arv_vazia(a->_dir))
    a = a->_dir;
  return a->_info;
}

void imprime_decrescente (Arvore *a)
{
    if(!verifica_arv_vazia(a))
    {
        imprime_decrescente(a->_dir);
        printf("%d, ", a->_info);
        imprime_decrescente(a->_esq);
    }
}

int max2(int a, int b)
{
    return  (a > b ? a : b);
}

int maior_ramo (Arvore *a)
{
    if(verifica_arv_vazia(a))
        return 0;
    else
    {
        return max2(maior_ramo(a->_dir), maior_ramo(a->_esq)) + a->_info;
    }
}

int ancestral (Arvore *a, int e1, int e2)
{
    if(verifica_arv_vazia(a))
        return 0;
    else if (ancestral(a->_dir, e1, e2) == ancestral(a->_esq, e1, e2))
    {
        return a->_info;
    }
    return a->_info;
}






