// Header do Interpretador
// interpretador.hpp

#ifndef INTERPRETADOR_H
#define INTERPRETADOR_H

#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <list>
#include <stdio.h>
#include <vector>

using namespace std;


class Interpretador{

    public:
		Interpretador(); // Construtor default da classe

    void iniciaTabela(vector < vector<int> > listaComandos); // Inicia a tabela de simbolos toda com zero

    int processaCodigo(void *step, vector < vector<int> > listaComandos); // Processa as instruções passadas do código de entrada

    int* getSymbolTable(); // Get para a tabela de simbolos

    vector < vector<int> > getListaComandos();
    void RefreshSimbolTable(void *step);
    int getACC(); // Get para o acumulador
    std::ostringstream text[3];
    int mValue;
  protected:
    int symbolTable[100]; // tabela de simbolos
    vector < vector<int> > listaComandos;
    int Acc;  // acumulador
    int id; //indice global of symbolTable
};
#endif
