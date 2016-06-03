/* 
 * File:   arvore.h
 * Author: alysson
 *
 * Created on 16 de Setembro de 2015, 18:50
 */

#ifndef ARVORE_H
#define	ARVORE_H
//biblioteca.h

struct descritor_arvore{
int tamanho;
struct nodo *raiz;
};

struct nodo{
int aberto;  //0 - aberto, 1 - fechado   
int Puzzle[9];
struct nodo* pai;
struct nodo* esquerda;
struct nodo* direita;
struct nodo* cima;
struct nodo* baixo;
};

struct nodo* cria_nodo(int *x);
void iniciaArvore(struct descritor_arvore* arvore);
void insert(struct descritor_arvore* arvore, int *x);
struct nodo * inserir(struct descritor_arvore* arvore, struct nodo * T, int *x, int limite);
struct nodo * deleta(struct descritor_arvore* A,struct nodo * T, int *x);
struct nodo * find(struct nodo * T, int *x);
void menu(struct descritor_arvore *arvore, struct nodo *nodos);
void mostrar(struct nodo* T); 
struct nodo* sucessor(struct nodo* T);
struct nodo* predecessor(struct nodo* T);
struct nodo* maximum(struct nodo* r);
struct nodo* minimum(struct nodo* T);

/*Pecas*/
void posicao0(struct descritor_arvore* arvore, struct nodo* T, int *x, int limite);
void posicao1(struct descritor_arvore* arvore,struct nodo* T, int *x, int limite);
void posicao2(struct descritor_arvore* arvore,struct nodo* T, int *x, int limite);
void posicao3(struct descritor_arvore* arvore,struct nodo* T, int *x, int limite);
void posicao4(struct descritor_arvore* arvore,struct nodo* T, int *x, int limite);
void posicao5(struct descritor_arvore* arvore,struct nodo* T, int *x, int limite);
void posicao6(struct descritor_arvore* arvore,struct nodo* T, int *x, int limite);
void posicao7(struct descritor_arvore* arvore,struct nodo* T, int *x, int limite);
void posicao8(struct descritor_arvore* arvore,struct nodo* T, int *x, int limite);

//puzzle
int ganhou(int *Puzzle);
//int *mostrar(struct nodo* T);

#endif	/* ARVORE_H */

