#include <stdio.h>
#include <stdlib.h>

typedef struct node {
   int chave;
   int altura;
   struct node* esq;
   struct node* dir;
} No, Arvore;

/*----------------------*/
int maior (int esq, int dir) {
   return (esq > dir ? esq : dir);
}

/*----------------------*/
int altura (Arvore* a) {
   return (a == NULL? -1 : a->altura);
}

/*----------------------*/
int atualizar_altura (Arvore *a) {
   return ((maior(altura(a->esq), altura(a->dir))) + 1);
}

/*----------------------*/
int balanceamento (Arvore *a) {
   return (altura(a->dir) - altura(a->esq));
}

/*----------------------*/
Arvore* rotacao_simples_esq (Arvore* a) {
   No* t = a->dir;
   a->dir = t->esq;
   t->esq = a;
   a->altura = atualizar_altura(a);
   t->altura = atualizar_altura(t);
   return t;
}

/*----------------------*/
Arvore* rotacao_simples_dir (Arvore* a) {
   No* t = a->esq;
   a->esq = t->dir;
   t->dir = a;
   a->altura = atualizar_altura(a);
   t->altura = atualizar_altura(t);
   return t;
}

/*----------------------*/
Arvore* rotacao_dupla_esq (Arvore* a) {
   a->dir = rotacao_simples_dir(a->dir);
   return rotacao_simples_esq(a);
}

/*----------------------*/
Arvore* rotacao_dupla_dir (Arvore* a) {
   a->esq = rotacao_simples_esq(a->esq);
   return rotacao_simples_dir(a);
}

/*----------------------*/
Arvore* atualizar_fb_dir (Arvore *a) {
   a->altura = atualizar_altura(a);
   if(balanceamento(a) == 2)
   {
     if(balanceamento(a->dir) > 0)
     {
       a = rotacao_simples_esq(a);
     }
     else
     {
       a = rotacao_dupla_esq(a);
     }
   }
   return a;
}

/*----------------------*/
Arvore* atualizar_fb_esq (Arvore *a) {
   a->altura = atualizar_altura(a);
   if(balanceamento(a) == -2)
   {
     if(balanceamento(a->esq) < 0)
     {
       a = rotacao_simples_dir(a);
     }
     else
     {
       a = rotacao_dupla_dir(a);
     }
   }
   return a;
}

/*----------------------*/
Arvore* inserir (Arvore *a, int chave) {
   if(a == NULL)
   {
     a = (No*)malloc(sizeof(No));
     a->chave = chave;
     a->altura = 0;
     a->dir = NULL;
     a->esq = NULL;
   }
   else if (chave > a->chave)
   {
     a->dir = inserir(a->dir, chave);
     a = atualizar_fb_dir(a);
   }
   else
   {
     a->esq = inserir(a->esq, chave);
     a = atualizar_fb_esq(a);
   }
   return a;
}

/*----------------------*/
Arvore* remover (Arvore *a, int chave) {
   if (a == NULL) {
      return NULL;
   }
   else {
      if (chave < a->chave) {
         a->esq = remover (a->esq, chave);
         a = atualizar_fb_dir (a);
      }
      else if (chave > a->chave) {
         a->dir = remover (a->dir, chave);
         a = atualizar_fb_esq (a);
      }
      else {
         if ((a->esq == NULL) && (a->dir == NULL)) {
            free (a);
            a = NULL;
         }
         else if (a->esq == NULL) {
            No *tmp = a;
            a = a->dir;
            free (tmp);
         }
         else if (a->dir == NULL) {
            No *tmp = a;
            a = a->esq;
            free (tmp);
         }
         else {
            No *tmp = a->esq;
            while (tmp->dir != NULL) {
               tmp = tmp->dir;
            }
            a->chave = tmp->chave;
            tmp->chave = chave;
            a->esq = remover (a->esq, chave);
            a = atualizar_fb_dir (a);
         }
      }
      return a;
   }
}

/*----------------------*/
void imprimir_in_order (Arvore* a, int nivel) {
   if (a != NULL) {
      int i;
      for (i = 0; i < nivel; i++) {
         printf("      ");
      }
      printf("Chave: %d (altura: %d, fb: %+d) no nível: %d\n", a->chave, a->altura, balanceamento(a), nivel);
      imprimir_in_order (a->esq, nivel + 1);
      imprimir_in_order (a->dir, nivel + 1);
   }
}

/*----------------------*/
int main () {

   Arvore *AVL = NULL;

   AVL = inserir(AVL, 14);
   AVL = inserir(AVL, 28);
   AVL = inserir(AVL, 5);
   AVL = inserir(AVL, 33);
   AVL = inserir(AVL, 18);
   AVL = inserir(AVL, 8);
   AVL = inserir(AVL, 2);
   AVL = inserir(AVL, 38);
   AVL = inserir(AVL, 30);
   AVL = inserir(AVL, 20);
   AVL = inserir(AVL, 15);
   AVL = inserir(AVL, 11);
   AVL = inserir(AVL, 6);
   AVL = inserir(AVL, 3);
   AVL = inserir(AVL, 1);
   AVL = inserir(AVL, 39);
   AVL = inserir(AVL, 35);
   AVL = inserir(AVL, 31);
   AVL = inserir(AVL, 29);
   AVL = inserir(AVL, 21);
   AVL = inserir(AVL, 19);
   AVL = inserir(AVL, 16);
   AVL = inserir(AVL, 12);
   AVL = inserir(AVL, 10);
   AVL = inserir(AVL, 7);
   AVL = inserir(AVL, 4);
   AVL = inserir(AVL, 40);
   AVL = inserir(AVL, 36);
   AVL = inserir(AVL, 34);
   AVL = inserir(AVL, 32);
   AVL = inserir(AVL, 22);
   AVL = inserir(AVL, 13);
   AVL = inserir(AVL, 37);

   AVL = remover(AVL, 1);

   imprimir_in_order (AVL, 0);

   getchar();

   return 0;
}
