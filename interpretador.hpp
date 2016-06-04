// Header do Interpretador
// interpretador.hpp

#ifndef INTERPRETADOR_HPP
#define INTERPRETADOR_HPP

#include <iostream>
#include <string.h>
#include <fstream>
#include <list>
#include <stdio.h>
#include <vector>

using namespace std;


class Interpretador{

    public:
		Interpretador(); // Construtor default da classe

    void iniciaTabela(vector < vector<int> > listaComandos); // Inicia a tabela de simbolos toda com zero

    void processaCodigo(vector < vector<int> > listaComandos); // Processa as instruções passadas do código de entrada

    int* getSymbolTable(); // Get para a tabela de simbolos

    int getACC(); // Get para o acumulador

  protected:
    int symbolTable[100]; // tabela de simbolos
    int ACC;  // acumulador
};
#endif