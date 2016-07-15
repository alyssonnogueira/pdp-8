/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ligador.h
 * Author: alysson
 *
 * Created on 12 de Julho de 2016, 20:28
 */

#ifndef LIGADOR_H
#define LIGADOR_H

#include <iostream>
#include <string.h>
#include <fstream>
#include <list>
#include <stdio.h>
#include <vector>
#include "Montador.h"

using namespace std;

class Ligador {
public:
    Ligador();
    Ligador(const Ligador& orig);
    virtual ~Ligador();
    //A implementar.
    int Linker(list<string> obj, vector<struct st> ERS, vector<struct eds> EDS);
    int LeObj(list<string> obj, int TCodigo, int Ttsg);
    int geraExec();
    int getlinhas();
private:
protected:
    vector <vector<int> > SDE; //Tabela de simbolos globais
    vector <vector<int> > SRE; //Tabela de Uso
    vector <vector<int> > Codigo; //Tabela com o codigo
    list<string> lista; // Cria a lista léxica
    std::list<string>::iterator ptr; // cria um iterador de float
    int linhas;
};

#endif /* LIGADOR_H */

