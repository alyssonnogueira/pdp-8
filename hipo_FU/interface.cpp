//biblioteca.c
#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

struct nodo* cria_nodo(int *x) //novoNodo
{
    struct nodo* Nodo;
    Nodo = (struct nodo*) malloc(sizeof (struct nodo));
    if (Nodo != NULL) {
        for (int i = 0; i < 9; i++) {
            Nodo->Puzzle[i] = x[i];
            //   printf("%d ", Nodo->Puzzle[i]);
            //   if ((i == 2) || (i == 5) || (i == 8)) {
            //       printf("\n");
            // }
        }
        // printf("\n");
        Nodo->pai = NULL;
        Nodo->esquerda = NULL;
        Nodo->direita = NULL;
        Nodo->cima = NULL;
        Nodo->baixo = NULL;
    } else {
        printf("Erro na alocacao\n");
    }
    return Nodo;
}

void insert(struct descritor_arvore* arvore, int *x) {
    if (arvore->raiz == NULL) {
        arvore->raiz = inserir(arvore, arvore->raiz, x, 0); //cria_nodo(x);//
        //inserir(arvore, arvore->raiz, x);
    } else {
        inserir(arvore, arvore->raiz, x, 0);
    }
}

struct nodo* inserir(struct descritor_arvore* arvore, struct nodo* T, int *x, int limite) {
    limite++;
    
    if ((limite > 30) || (arvore->tamanho > 100000)) {
        //  printf("%d, é! %d \n",arvore->tamanho, ganhou(x));
        return T;
    } else {
        if (T == NULL) { //Aqui ta bem!
            T = cria_nodo(x);
            arvore->tamanho++;
            //return T;
        }
        //Se 0 na posicao 0
        if (x[0] == 0) {
            posicao0(arvore, T, x, limite);
        }
        //Se 0 na posicao 1
        if (x[1] == 0) {
            posicao1(arvore, T, x, limite);
        }
        //Se 0 na posicao 2
        if (x[2] == 0) {
            posicao2(arvore, T, x, limite);
        }
        //Se 0 na posicao 3
        if (x[3] == 0) {
            posicao3(arvore, T, x, limite);
        }
        //Se 0 na posicao 4
        if (x[4] == 0) {
            posicao4(arvore, T, x, limite);
        }
        //Se 0 na posicao 5
        if (x[5] == 0) {
            posicao5(arvore, T, x, limite);
        }
        //Se 0 na posicao 6
        if (x[6] == 0) {
            posicao6(arvore, T, x, limite);
        }
        //Se 7 na posicao 1
        if (x[7] == 0) {
            posicao7(arvore, T, x, limite);
        }
        //Se 0 na posicao 8
        if (x[8] == 0) {
            posicao8(arvore, T, x, limite);
        }
    }
    return T;
}

void iniciaArvore(struct descritor_arvore* arvore) {

    arvore->tamanho = 0;
    arvore->raiz = NULL;
}

struct nodo * deleta(struct descritor_arvore* A, struct nodo * T, int *x) {
    struct nodo * tmp_cell, * child;

    if (T == NULL) {
        printf("Elemento não encontrado");
    } else {
        if (x < T->Puzzle) { /* esquerda */
            T->esquerda = deleta(A, T->esquerda, x);
        } else {
            if (x > T->Puzzle) { /*Direita */
                T->direita = deleta(A, T->direita, x);
            } else { /*Encontrou Elemento */
                if (T->esquerda && T->direita) { /*caso dois filhos */
                    /*escolhe menor da subarvore direita */
                    tmp_cell = minimum(T->direita);
                    T->Puzzle[9] = tmp_cell->Puzzle[9];
                    T->direita = deleta(A, T->direita, T->Puzzle);
                } else { /*filho único */
                    tmp_cell = T;
                    if (T->esquerda == NULL) { /*Só filho á direita */
                        child = T->direita;
                    }
                    if (T->direita == NULL) { /*Só à direita */
                        child = T->esquerda;
                    }
                    free(tmp_cell);
                    A->tamanho--;
                    return child;
                }
            }
        }
        printf("Excluido com Sucesso!");
        return T;
    }
}
//Busca 1 elemento da Árvore

struct nodo * find(struct nodo * T, int *x) {
    if (T == NULL) {
        return NULL;
    } else {
        if (T->Puzzle == x) {
            return T;
        } else {
            if (T->Puzzle > x) {
                return find(T->esquerda, x);
            } else {
                return find(T->direita, x);
            }
        }
    }
}

struct nodo* minimum(struct nodo* T) {
    while (T->esquerda != NULL)
        T = T->esquerda;
    return T;
}

/*
void mostrar(struct nodo* T) {
    if (T != NULL) {
     /*   for (int i = 0; i < 9; i++) {
            printf(" %d,", T->Puzzle[i]);
        }
       
       Atualiza_Puzzle(*T->Puzzle);
       // printf("\n");
        mostrar(T->esquerda);
        mostrar(T->direita);
        mostrar(T->cima);

        mostrar(T->baixo);
    }
}
 */
struct nodo* maximum(struct nodo* T) {
    while (T->direita != NULL)
        T = T->direita;
    return T;
}

struct nodo* predecessor(struct nodo* T) {
    struct nodo* temp;
  //  if (T->esquerda != NULL)
    //    return maximum(T->esquerda);
    temp = T->pai;
    
    while ((temp != NULL) && (T == temp->esquerda)) {
        T = temp;
        temp = T->pai;
    }
    return temp;
}

struct nodo* sucessor(struct nodo* T) {
    struct nodo* temp;
    if (T->direita != NULL)
        return minimum(T->direita);
    temp = T->pai;
    while ((temp != NULL)&&(T == temp->direita)) {
        T = temp;
        temp = T->pai;
    }
    return temp;
}

void posicao0(struct descritor_arvore* arvore, struct nodo* T, int *x, int limite) {
    struct nodo* temp, *temp2, *temp3;
    int aux;
    int *aux_vet2 = new int[9];
    int *aux_vet3 = new int[9];
    for (int i = 0; i < 9; i++) {
        aux_vet2[i] = x[i];
        aux_vet3[i] = x[i];
    }

    aux = aux_vet2[1];
    aux_vet2[1] = aux_vet2[0];
    aux_vet2[0] = aux;
    temp2 = inserir(arvore, T->direita, aux_vet2, limite);
    if (temp2 != NULL) {
        T->direita = temp2;
        temp2->pai = T;
    }

    aux = aux_vet3[3];
    aux_vet3[3] = aux_vet3[0];
    aux_vet3[0] = aux;
    temp3 = inserir(arvore, T->baixo, aux_vet3, limite);
    if (temp3 != NULL) {
        T->baixo = temp3;
        temp3->pai = T;
    }

}

void posicao1(struct descritor_arvore* arvore, struct nodo* T, int *x, int limite) {
    struct nodo* temp, *temp2, *temp3;
    int aux;
    int *aux_vet = new int[9];
    int *aux_vet2 = new int[9];
    int *aux_vet3 = new int[9];
    for (int i = 0; i < 9; i++) {
        aux_vet[i] = x[i];
        aux_vet2[i] = x[i];
        aux_vet3[i] = x[i];
    }
    aux = aux_vet[0];
    aux_vet[0] = aux_vet[1];
    aux_vet[1] = aux;
    temp = inserir(arvore, T->esquerda, aux_vet, limite);
    if (temp != NULL) {
        T->esquerda = temp;
        temp->pai = T;
    }

    aux = aux_vet2[2];
    aux_vet2[2] = aux_vet2[1];
    aux_vet2[1] = aux;
    temp2 = inserir(arvore, T->direita, aux_vet2, limite);
    if (temp2 != NULL) {
        T->direita = temp2;
        temp2->pai = T;
    }

    aux = aux_vet3[4];
    aux_vet3[4] = aux_vet3[1];
    aux_vet3[1] = aux;
    temp3 = inserir(arvore, T->baixo, aux_vet3, limite);
    if (temp3 != NULL) {
        T->baixo = temp3;
        temp3->pai = T;
    }

}

void posicao2(struct descritor_arvore* arvore, struct nodo* T, int *x, int limite) {
    struct nodo* temp, *temp2, *temp3;
    int aux;
    int *aux_vet2 = new int[9];
    int *aux_vet = new int[9];
    for (int i = 0; i < 9; i++) {
        aux_vet[i] = x[i];
        aux_vet2[i] = x[i];
    }
    aux = aux_vet[1];
    aux_vet[1] = aux_vet[2];
    aux_vet[2] = aux;
    temp = inserir(arvore, T->esquerda, aux_vet, limite);
    if (temp != NULL) {
        T->esquerda = temp;
        temp->pai = T;
    }

    aux = aux_vet2[5];
    aux_vet2[5] = aux_vet2[2];
    aux_vet2[2] = aux;
    temp2 = inserir(arvore, T->direita, aux_vet2, limite);
    if (temp2 != NULL) {
        T->direita = temp2;
        temp2->pai = T;
    }
}

void posicao3(struct descritor_arvore* arvore, struct nodo* T, int *x, int limite) {
    struct nodo* temp, *temp2, *temp3;
    int aux;
    int *aux_vet = new int[9];
    int *aux_vet2 = new int[9];
    int *aux_vet3 = new int[9];
    for (int i = 0; i < 9; i++) {
        aux_vet[i] = x[i];
        aux_vet2[i] = x[i];
        aux_vet3[i] = x[i];
    }
    aux = aux_vet[0];
    aux_vet[0] = aux_vet[3];
    aux_vet[3] = aux;
    temp = inserir(arvore, T->cima, aux_vet, limite);
    if (temp != NULL) {
        T->cima = temp;
        temp->pai = T;
    }

    aux = aux_vet2[4];
    aux_vet2[4] = aux_vet2[3];
    aux_vet2[3] = aux;
    temp2 = inserir(arvore, T->direita, aux_vet2, limite);
    if (temp2 != NULL) {
        T->direita = temp2;
        temp2->pai = T;
    }

    aux = aux_vet3[6];
    aux_vet3[6] = aux_vet3[3];
    aux_vet3[3] = aux;
    temp3 = inserir(arvore, T->baixo, aux_vet3, limite);
    if (temp3 != NULL) {
        T->baixo = temp3;
        temp3->pai = T;
    }

}

void posicao4(struct descritor_arvore* arvore, struct nodo* T, int *x, int limite) {
    struct nodo* temp, *temp2, *temp3, *temp4;
    int aux;
    int *aux_vet = new int[9];
    int *aux_vet2 = new int[9];
    int *aux_vet3 = new int[9];
    int *aux_vet4 = new int[9];

    for (int i = 0; i < 9; i++) {
        aux_vet[i] = x[i];
        aux_vet2[i] = x[i];
        aux_vet3[i] = x[i];
        aux_vet4[i] = x[i];
    }
    aux = aux_vet[3];
    aux_vet[3] = aux_vet[4];
    aux_vet[4] = aux;
    temp = inserir(arvore, T->esquerda, aux_vet, limite);
    if (temp != NULL) {
        T->esquerda = temp;
        temp->pai = T;
    }

    aux = aux_vet2[5];
    aux_vet2[5] = aux_vet2[4];
    aux_vet2[4] = aux;
    temp2 = inserir(arvore, T->direita, aux_vet2, limite);
    if (temp2 != NULL) {
        T->direita = temp2;
        temp2->pai = T;
    }

    aux = aux_vet3[7];
    aux_vet3[7] = aux_vet3[4];
    aux_vet3[4] = aux;
    temp3 = inserir(arvore, T->baixo, aux_vet3, limite);
    if (temp3 != NULL) {
        T->baixo = temp3;
        temp3->pai = T;
    }

    aux = aux_vet4[1];
    aux_vet3[1] = aux_vet3[4];
    aux_vet3[4] = aux;
    temp3 = inserir(arvore, T->cima, aux_vet3, limite);
    if (temp3 != NULL) {
        T->cima = temp3;
        temp3->pai = T;
    }

}

void posicao5(struct descritor_arvore* arvore, struct nodo* T, int *x, int limite) {
    struct nodo* temp, *temp2, *temp3;
    int aux;
    int *aux_vet = new int[9];
    int *aux_vet2 = new int[9];
    int *aux_vet3 = new int[9];
    for (int i = 0; i < 9; i++) {
        aux_vet[i] = x[i];
        aux_vet2[i] = x[i];
        aux_vet3[i] = x[i];
    }
    aux = aux_vet[4];
    aux_vet[4] = aux_vet[5];
    aux_vet[5] = aux;
    temp = inserir(arvore, T->esquerda, aux_vet, limite);
    if (temp != NULL) {
        T->esquerda = temp;
        temp->pai = T;
    }

    aux = aux_vet2[2];
    aux_vet2[2] = aux_vet2[4];
    aux_vet2[4] = aux;
    temp2 = inserir(arvore, T->cima, aux_vet2, limite);
    if (temp2 != NULL) {
        T->cima = temp2;
        temp2->pai = T;
    }

    aux = aux_vet3[8];
    aux_vet3[8] = aux_vet3[5];
    aux_vet3[5] = aux;
    temp3 = inserir(arvore, T->baixo, aux_vet3, limite);
    if (temp3 != NULL) {
        T->baixo = temp3;
        temp3->pai = T;
    }

}

void posicao6(struct descritor_arvore* arvore, struct nodo* T, int *x, int limite) {
    struct nodo* temp, *temp2, *temp3;
    int aux;
    int *aux_vet2 = new int[9];
    int *aux_vet = new int[9];
    for (int i = 0; i < 9; i++) {
        aux_vet[i] = x[i];
        aux_vet2[i] = x[i];
    }
    aux = aux_vet[3];
    aux_vet[3] = aux_vet[6];
    aux_vet[6] = aux;
    temp = inserir(arvore, T->cima, aux_vet, limite);
    if (temp != NULL) {
        T->cima = temp;
        temp->pai = T;
    }

    aux = aux_vet2[7];
    aux_vet2[7] = aux_vet2[6];
    aux_vet2[6] = aux;
    temp2 = inserir(arvore, T->direita, aux_vet2, limite);
    if (temp2 != NULL) {
        T->direita = temp2;
        temp2->pai = T;
    }

}

void posicao7(struct descritor_arvore* arvore, struct nodo* T, int *x, int limite) {
    struct nodo* temp, *temp2, *temp3;
    int aux;
    int *aux_vet = new int[9];
    int *aux_vet2 = new int[9];
    int *aux_vet3 = new int[9];
    for (int i = 0; i < 9; i++) {
        aux_vet[i] = x[i];
        aux_vet2[i] = x[i];
        aux_vet3[i] = x[i];
    }
    aux = aux_vet[6];
    aux_vet[6] = aux_vet[7];
    aux_vet[7] = aux;
    temp = inserir(arvore, T->esquerda, aux_vet, limite);
    if (temp != NULL) {
        T->esquerda = temp;
        temp->pai = T;
    }

    aux = aux_vet2[4];
    aux_vet2[4] = aux_vet2[7];
    aux_vet2[7] = aux;
    temp2 = inserir(arvore, T->cima, aux_vet2, limite);
    if (temp2 != NULL) {
        T->cima = temp2;
        temp2->pai = T;
    }

    aux = aux_vet3[8];
    aux_vet3[8] = aux_vet3[7];
    aux_vet3[7] = aux;
    temp3 = inserir(arvore, T->direita, aux_vet3, limite);
    if (temp3 != NULL) {
        T->direita = temp3;
        temp3->pai = T;
    }

}

void posicao8(struct descritor_arvore* arvore, struct nodo* T, int *x, int limite) {
    struct nodo* temp, *temp2, *temp3;
    int aux;
    int *aux_vet = new int[9];
    int *aux_vet2 = new int[9];
    for (int i = 0; i < 9; i++) {
        aux_vet[i] = x[i];
        aux_vet2[i] = x[i];
    }
    aux = aux_vet[5];
    aux_vet[5] = aux_vet[8];
    aux_vet[8] = aux;
    // printf("cima!!\n");
    temp = inserir(arvore, T->cima, aux_vet, limite);
    if (temp != NULL) {
        T->cima = temp;
        temp->pai = T;
    }

    aux = aux_vet2[7];
    aux_vet2[7] = aux_vet2[8];
    aux_vet2[8] = aux;
    //printf("esquerda!!\n");
    temp2 = inserir(arvore, T->esquerda, aux_vet2, limite);
    if (temp2 != NULL) {
        arvore->tamanho++;
        T->esquerda = temp2;
        temp2->pai = T;
    }

}

int ganhou(int *Puzzle) {
    if (Puzzle != NULL) {
        int Puzzle_Final[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
        int i;
        i = 0;
        while ((Puzzle_Final[i] == Puzzle[i])&&(i < 9)) {
            i++;
        }
        if (i < 9) {
            return 0;
        } else {
            return 1;
        }
    } else {
        return 0;
    }
}
/*
int *mostrar(struct nodo* T) {
    if (T != NULL) {
        //        Atualiza_Puzzle(T->Puzzle);
        /*   for (int i = 0; i < 9; i++) {
               printf(" %d,", T->Puzzle[i]);
           }
         
        // printf("\n");
        if (ganhou(T->Puzzle) != 1) {
             printf("Aguarde..");
            //  Atualiza_Puzzle(T->Puzzle);
            mostrar(T->esquerda);
            mostrar(T->direita);
            mostrar(T->cima);
            mostrar(T->baixo);
        } else {
            
            printf("\nAchou Resposta!\n");
            
            return T->Puzzle; 

            //    Atualiza_Puzzle(T->Puzzle);
            //         flag++;
          
        }
    }
}
*/


