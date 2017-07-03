#ifndef LISTALINEAR_H_
#define LISTALINEAR_H_

#include <stdbool.h>

#include "elem.h"
#include "no.h"

// 04 - 41
typedef struct ListaLinear ListaLinear;
struct ListaLinear {
  size_t N;
  No *Inicio;
};

/* Constroi e inicializa a lista L */
void ListaLinear_Constroi(ListaLinear *L);

/* Destroi e libera memoria da lista L */
void ListaLinear_Destroi(ListaLinear *L);

/* Enuleara (lista) a chave de cada elemento de L */
void ListaLinear_Enumera(ListaLinear *L);


/* Obtem o elemento de L com chave c ou "NULO" se inexistente */
TElem* ListaLinear_Busca_Ordenada(ListaLinear *L, TChave c, No *noAnt);
TElem* ListaLinear_Busca_NaoOrdenada(ListaLinear *L, TChave c);

/* Obtem o elemento L com pos Pos */
TElem* ListaLinear_BuscaEm(ListaLinear *L, int Pos);

/* Insere x com chave c em L */
void ListaLinear_Insere(ListaLinear *L, int Pos);

/* Insere x em L na posicao Pos (deslocando os elemento a partir de Pos a
 * direita
 */
void ListaLinear_InsereEm(ListaLinear *L, int Pos, TChave c, TElem *x);

/* Remove e retorna o elemento de L com chave c */
TElem* ListaLinear_Remove(ListaLinear *L, TChave c);

/* Remove o elemento na posicao Pos de L (deslocando os elementos a partir de
 * pos+1 para esquerda
 */
TElem* ListaLinear_RemoveEm(ListaLinear *L, int Pos);

/* Obtem o numero de elementos de L */
int ListaLinear_Tamanho(ListaLinear *L);

#endif
