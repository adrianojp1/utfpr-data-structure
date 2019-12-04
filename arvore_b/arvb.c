#include "arvb.h"

/* ============================================================================================ */
/* --- Alocação --- */

/*Função para criar e inicializar uma árvore B:*/
Arvore *criar()
{
   Arvore *a = (Arvore *)malloc(sizeof(Arvore));
   a->n = 0;
   a->folha = TRUE;
   return a;
}

/* ============================================================================================ */
/* --- Impressão --- */

void imprimir(Arvore *a, int nivel)
{

   int i;

   /*Imprime recuo para definir o nível do nó: */
   for (i = 0; i < nivel; i++)
   {
      printf("  ");
   }

   /*Imprime as chaves armazenadas no nó: */
   printf("|");
   for (i = 0; i < a->n; i++)
   {
      printf("%c|", a->chaves[i]);
      //printf("%02d|", a->chaves[i]);
   }
   printf("\n");

   /*Recursivamente imprime as chaves dos filhos: */
   for (i = 0; i <= a->n; i++)
   {
      if (a->folha == FALSE)
      {
         imprimir(a->filhos[i], nivel + 1);
      }
   }
}

/* ============================================================================================ */
/* --- Busca --- */

/*Função para buscar uma chave em uma árvore B:*/
int buscar(Arvore *a, TIPO chave)
{
   /*Procurando a chave no vetor de chaves: */
   int i = indice_da_chave_em_no(a, chave);

   if (chave == a->chaves[i])
   {
      /*Achou a chave!*/
      return i;
   }
   else if (a->folha)
   {
      /*Não achou a chave!*/
      return NOT_FOUND;
   }
   else
   {
      /*Buscando a chave no filho: */
      if (a->folha == FALSE)
      {
         return buscar(a->filhos[i], chave);
      }
   }
}

/* ============================================================================================ */
/* --- Remoção --- */
int indice_da_chave_em_no(Arvore *a, TIPO chave)
{
   int i = 0;
   while ((i < a->n) && (chave > a->chaves[i]))
   {
      i++;
   }
   return i;
}

Arvore *remover(Arvore *raiz, TIPO chave)
{

   /*Procurando a chave no vetor de chaves: */
   int i = indice_da_chave_em_no(raiz, chave);

   if (chave == raiz->chaves[i])
   {
      /* Caso 1 com raiz */
      if (isFolha(raiz))
      {
         raiz = remove_chave_folha(raiz, i);
      }
      else
      {
         /* Caso 2 */
         raiz = remove_chave_interno(raiz, i);
      }
   }
   else if (isFolha(raiz))
   {
      /*Não achou a chave!*/
      printf("Chave de remocao nao encontrada!\n");
   }
   else
   {
      /*Buscando a chave no filho: */
      if (!isFolha(raiz))
      {
         raiz->filhos[i] = remover_de_filho(raiz->filhos[i], chave);
      }
   }
   return raiz;
}

Arvore *remover_de_filho(Arvore *a, TIPO chave)
{
   /*Procurando a chave no vetor de chaves: */
   int i = indice_da_chave_em_no(a, chave);

   if (chave == a->chaves[i])
   {
      /* Caso 1 e 2*/
      if (a->n > T - 1)
      {
         /* Caso 1 */
         if (isFolha(a))
         {
            a = remove_chave_folha(a, i);
         }
         /* Caso 2 */
         else
         {
            a = remove_chave_interno(a, i);
         }
      }
      /* Caso 3 */
      else if (a->n == T - 1)
      {
         printf("Erro: caso 3 de remocao nao suportado!\n");
      }
      else
      {
         printf("Erro: no possui menos que T - 1 chaves!\n");
      }
   }
   else if (isFolha(a))
   {
      /*Não achou a chave!*/
      printf("Chave de remocao nao encontrada!\n");
   }
   else
   {
      /*Buscando a chave no filho: */
      if (!isFolha(a))
      {
         a->filhos[i] = remover_de_filho(a->filhos[i], chave);
      }
   }
   return a;
}

Arvore *remove_chave_folha(Arvore *a, int k)
{
   a->n--;
   /* Rearranja vetor começando da chave removida */
   int i = k;
   while (i < a->n)
   {
      a->chaves[i] = a->chaves[i + 1];
      i++;
   }
   return a;
}

Arvore *remove_chave_interno(Arvore *a, int k)
{
   /* Verifica se algum filho de k tem pelo menos T - 1 chaves */
   /* Caso 2A */
   if (a->filhos[k]->n > T - 1)
   {
      No *no_filho = a->filhos[k];
      int maior_chave_do_filho = no_filho->n - 1;

      /* Substitui chave em k pela maior do filho */
      a->chaves[k] = no_filho->chaves[maior_chave_do_filho];

      /* Remove a chave do filho recursivamente */
      if (isFolha(no_filho))
      {
         no_filho = remove_chave_folha(no_filho, maior_chave_do_filho);
      }
      else
      {
         no_filho = remove_chave_interno(no_filho, maior_chave_do_filho);
      }
   }
   /* Caso 2B (simétrico de 2A)*/
   else if (a->filhos[k + 1]->n > T - 1)
   {
      No *no_filho = a->filhos[k + 1];
      int menor_chave_do_filho = 0;

      /* Substitui chave em k pela maior do filho */
      a->chaves[k] = no_filho->chaves[menor_chave_do_filho];

      /* Remove a chave do filho recursivamente */
      if (isFolha(no_filho))
      {
         a->filhos[k + 1] = remove_chave_folha(no_filho, menor_chave_do_filho);
      }
      else
      {
         a->filhos[k + 1] = remove_chave_interno(no_filho, menor_chave_do_filho);
      }
   }
   /* Caso 2C: os filhos de k tem T - 1 chaves */
   else
   {
      printf("Erro: caso 2C de remocao nao suportado!\n");
   }
   return a;
}

/* ============================================================================================ */
/* --- Inserção --- */

Arvore *dividir_no(Arvore *x, int nodeIndex)
{

   Arvore *new_node = criar();               //NO para as maiores chaves
   Arvore *full_node = x->filhos[nodeIndex]; //NO para permancer as menores chaves
   new_node->folha = full_node->folha;
   new_node->n = T - 1;
   for (int i = 0; i < T - 1; i++)
   {
      new_node->chaves[i] = full_node->chaves[i + T];
   }
   if (!isFolha(full_node))
   {
      for (int i = 0; i < T; i++)
         new_node->filhos[i] = full_node->filhos[i + T];
   }
   full_node->n = T - 1;

   for (int i = x->n; i >= nodeIndex; i--)
   {
      x->filhos[i + 1] = x->filhos[i];
   }
   x->filhos[nodeIndex + 1] = new_node;

   for (int i = x->n - 1; i >= nodeIndex; i--)
   {
      x->chaves[i + 1] = x->chaves[i];
   }
   x->chaves[nodeIndex] = full_node->chaves[T - 1]; //retira a chave da posição mediana
   ++x->n;
   return x;
}

Arvore *inserir_arvore_nao_cheia(Arvore *x, TIPO k) // mudar nome para nó nao cheio
{
   int i = x->n - 1;
   if (isFolha(x))
   {
      // imprimir(x,0);
      //  printf("-----------%c\n",k);
      while (i >= 0 && k < x->chaves[i])
      {
         x->chaves[i + 1] = x->chaves[i]; //joga a chave uma posição pra frente >>
         --i;
      }
      x->chaves[++i] = k;
      ++x->n;
      // imprimir(x,1);
      return x;
   }
   else
   {
      while (i >= 0 && k < x->chaves[i])
         --i;
      ++i; // paramos uma posição atrás do node a inserir
      if (isFull(x->filhos[i]))
      {
         x = dividir_no(x, i);
         if (k > x->chaves[i])
            i++;
      }
      inserir_arvore_nao_cheia(x->filhos[i], k);
   }
   return x;
}

Arvore *inserir(Arvore *raiz, TIPO chave)
{
   Arvore *r = raiz;
   if (isFull(r))
   {
      Arvore *temp = criar();
      raiz = temp;
      temp->folha = FALSE;
      temp->n = 0;
      temp->filhos[0] = r;
      dividir_no(temp, 0);
      return inserir_arvore_nao_cheia(temp, chave);
   }
   else
   {
      Arvore *e = inserir_arvore_nao_cheia(r, chave);
      //imprimir(e,0);
      return e;
   }
}

/* ============================================================================================ */
/* --- Tools --- */

int isFull(Arvore *a)
{
   if (a->n == 2 * T - 1)
      return TRUE;
   else
      return FALSE;
}

int isFolha(Arvore *a)
{
   return a->folha;
}
