#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "btree.h"
/*
 *                  1
 *            2           3
 *         4     5     6     7
 *       08 09 10 11 12 13 14 15
 */       

/*
 *                  1
 *            2           3
 *        17  21    6     7
 *       0 0 0  0 12 13 14 15
 */       
int main(void)
{
  struct Tree *T, *A;
  newTree(&T);
  newTree(&A);

  int i; 
  for (i = 1; i <16; i++)
    insertNodeLL(T, newNode(i));

  for (i = 1; i <16; i++)
    insertNodeLL(A, newNode(i));
  
  atualizaAltura(T->root);
  atualizaNivel(T->root);
  atualizaSomaChaveD(T->root);
  atualizaSomaChaveD2(T->root);
  atualizaSomaChaveA(T->root);
  atualizaSomaChaveA2(T->root);
  // atualizaPNivel(T->root);

  // printf("Val de T é %d\n", T->root->val);
  // printf("Val de T>e>e>e é %d\n", T->root->left->left->left->val);
  // printf("Altura de T é %d\n", T->root->Altura);
  // printf("Altura de T>e>e>e é %d\n", T->root->left->left->left->Altura);
  // printf("Nivel de T é %d\n", T->root->Nivel);
  // printf("Nivel de T>e>e>e é %d\n", T->root->left->left->left->Nivel);
  // printf("SomaD de T é %d\n", T->root->SomaChaveD);
  // printf("SomaD de T>e>e>e é %d\n", T->root->left->left->left->SomaChaveD);
  // printf("SomaD2 de T é %d\n", T->root->SomaChaveD2);
  // printf("SomaD2 de T>e>e>e é %d\n", T->root->left->left->left->SomaChaveD2);
  // printf("SomaA de T é %d\n", T->root->SomaChaveA);
  // printf("SomaA de T>e>e>e é %d\n", T->root->left->left->left->SomaChaveA);
  // printf("SomaA2 de T é %d\n", T->root->SomaChaveA2);
  // printf("SomaA2 de T>e>e>e é %d\n", T->root->left->left->left->SomaChaveA2);
  // // printf("SomaPN de T é %d\n", T->root->PNivel);
  // // printf("SomaPN de T>e>e>e é %d\n", T->root->left->left->left->PNivel);

  // printf("Altu  Val SomD SoD2\n");
  // walkTreeLevel(T->root);
  // walkTreeLevelR(T->root);
  //
  
  int j;
  j=-1;
  j=compareTree(T->root, A->root);
  printf("Igual %d\n",j);

  // Adding a difference
  A->root->left->left->left->val = 1000;
  j=-1;
  j=compareTree(T->root, A->root);
  printf("Igual %d\n",j);

  printf("A->root->left->val %d\n",A->root->left->val);
  printf("T->root->left->val %d\n",T->root->left->val);

  printf("E' folha T->root? %d", eFolha(T->root->left->left->left));
  printf("soma folha %d", somaFolha(T->root));

  destroyTree(&T);

  return 0;
}
