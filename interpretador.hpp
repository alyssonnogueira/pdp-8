
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

    int findStop(vector < vector<int> > listaComandos);

    void iniciaTabela();

    void constroiTabela (vector < vector<int> > listaComandos);

    void processaCodigo(vector < vector<int> > listaComandos);

  protected:
    int symbolTable[100];
    int ACC;
};
#endif
