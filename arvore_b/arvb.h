#include <stdio.h>
#include <stdlib.h>

#define TIPO char

#define T 2          /*Número que define mínimo e máximo de chaves!*/
#define NOT_FOUND -1 /*Valor retornado quando o nó não existe!*/
#define TRUE 1       /*Booleano para verdadeiro!*/
#define FALSE 0      /*Booleano para falso!*/

/*Estrutura básica para uma árvore B: */
typedef struct _node
{
    int n;                       /*Número de chaves armazenadas no nó!*/
    int folha;                   /*Booleano que indica se o nó é folha ou não!*/
    TIPO chaves[2 * T - 1];      /*Número máximo de chaves {tipo char} em um nó!*/
    struct _node *filhos[2 * T]; /*Ponteiros para os filhos de cada nó!*/
} No, Arvore;

/*Função para criar e inicializar uma árvore B:*/
Arvore *criar();

/*Função para buscar uma chave em uma árvore B:*/
void imprimir(Arvore *a, int nivel);

/*Função para buscar uma chave em uma árvore B:*/
int buscar(Arvore *a, TIPO chave);

/*Função que retorna o índice da chave no nó */
int indice_da_chave_em_no(Arvore *a, TIPO chave);

/*Função para remover uma chave em uma árvore B:*/
Arvore *remover(Arvore *raiz, TIPO chave);

/*Função para remover uma chave de um nó filho em uma árvore B:*/
Arvore *remover_de_filho(Arvore *a, TIPO chave);

/*Função para remover chave de uma folha com pelo menos t chaves */
Arvore *remove_chave_folha(Arvore *a, int k);

/*Função para remover chave de um nó interno com pelo menos t chaves */
Arvore *remove_chave_interno(Arvore *a, int k);

/*Função para dividir nó de uma árvore B quando este se enche*/
Arvore *dividir_no(Arvore *x, int i);

/*Função para inserir chave em uma árvore não cheia*/
Arvore *inserir_arvore_nao_cheia(Arvore *x, TIPO k);

/*Função para inserir uma chave em uma árvore B:*/
Arvore *inserir(Arvore *raiz, TIPO chave);

/*Função que retorna se o nó está cheio */
int isFull(Arvore *a);

/*Função que retorna se o nó está cheio */
int isFolha(Arvore *a);
