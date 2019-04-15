#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
   char chave[20];
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
Arvore* inserir (Arvore *a, char chave[]) {
   if(a == NULL)
   {
     a = (No*)malloc(sizeof(No));
     strcpy(a->chave, chave);
     //a->chave = chave;
     a->altura = 0;
     a->dir = NULL;
     a->esq = NULL;
   }
   else if(strcmp(chave, a->chave) > 0)
   //else if (chave > a->chave)
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
Arvore* remover (Arvore *a, char chave[]) {
   if (a == NULL) {
      return NULL;
   }
   else {
      if (strcmp(chave, a->chave) < 0) {
         a->esq = remover (a->esq, chave);
         a = atualizar_fb_dir (a);
      }
      else if (strcmp(chave, a->chave) > 0) {
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
            strcpy(a->chave, tmp->chave);
            strcpy(tmp->chave, chave);
            //a->chave = tmp->chave;
            //tmp->chave = chave;
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
      printf("Chave: %s (altura: %d, fb: %+d) no nível: %d\n", a->chave, a->altura, balanceamento(a), nivel);
      imprimir_in_order (a->esq, nivel + 1);
      imprimir_in_order (a->dir, nivel + 1);
   }
}

/*----------------------*/
int main () {

   Arvore *AVL = NULL;

  AVL = inserir(AVL, "Pedro");
  AVL = inserir(AVL, "Joaquim");
  AVL = inserir(AVL, "Sandra");
  AVL = inserir(AVL, "Daniele");
  AVL = inserir(AVL, "Jhony");
  AVL = inserir(AVL, "Bruna");
  AVL = inserir(AVL, "Roberto");
  AVL = inserir(AVL, "Ricardo");
  AVL = inserir(AVL, "Rafael");
  AVL = inserir(AVL, "Hayana");
  AVL = inserir(AVL, "Lorena");
  AVL = inserir(AVL, "Mariana");
  AVL = inserir(AVL, "Marina");
  AVL = inserir(AVL, "Roberta");
  AVL = inserir(AVL, "Chayene");
  AVL = inserir(AVL, "Edmundo");

   imprimir_in_order (AVL, 0);

   getchar();

   return 0;
}
