#ifndef LISTADUPLA_H_
#define LISTADUPLA_H_

#include <stdbool.h>

#include "elem.h"
#include "no.h"

// 04 - 41
typedef struct ListaDupla ListaDupla;
struct ListaDupla {
  size_t N;
  No *Inicio;
};

/* Constroi e inicializa a lista L */
void ListaDupla_Constroi(ListaDupla *L);

/* Destroi e libera memoria da lista L */
void ListaDupla_Destroi(ListaDupla *L);

/* Enuleara (lista) a chave de cada elemento de L */
void ListaDupla_Enumera(ListaDupla *L);


/* Obtem o elemento de L com chave c ou "NULO" se inexistente */
TElem* ListaDupla_Busca_Ordenada(ListaDupla *L, TChave c, No *noAnt);
TElem* ListaDupla_Busca_NaoOrdenada(ListaDupla *L, TChave c);

/* Obtem o elemento L com pos Pos */
TElem* ListaDupla_BuscaEm(ListaDupla *L, int Pos);

/* Insere x com chave c em L */
void ListaDupla_Insere(ListaDupla *L, int Pos);

/* Insere x em L na posicao Pos (deslocando os elemento a partir de Pos a
 * direita
 */
void ListaDupla_InsereEm(ListaDupla *L, int Pos, TChave c, TElem *x);

/* Remove e retorna o elemento de L com chave c */
TElem* ListaDupla_Remove(ListaDupla *L, TChave c);

/* Remove o elemento na posicao Pos de L (deslocando os elementos a partir de
 * pos+1 para esquerda
 */
TElem* ListaDupla_RemoveEm(ListaDupla *L, int Pos);

/* Obtem o numero de elementos de L */
int ListaDupla_Tamanho(ListaDupla *L);

#endif
