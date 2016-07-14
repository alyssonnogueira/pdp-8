#ifndef CARREGADOR_H
#define CARREGADOR_H

#include <iostream>
#include <string.h>
#include <fstream>
#include <list>
#include <stdio.h>
#include <vector>

using namespace std;

class Carregador {
public:
    Carregador();
    vector <vector<int> > getList(); // Get para pegar a lista
    int lerEntrada(ifstream *arq); // Realiza a leitura do arquivo de entrada separando os tokens em cada posição da lista

    void push(int operador, int operando = 0); // Adiciona uma string ao final da lista

    void pop(); // remove a primeira string da lista

    vector<int> top(); // retorna o valor no topo da lista

    void imprimeLista(); // imprime a lista

    int stringToInt(string str); // onde a mágica acontece, converte string para inteiro

    virtual ~Carregador();

protected:
    vector <vector<int> > lProcessamento;
    list<string> lista; // Cria a lista léxica
    std::list<string>::iterator ptr; // cria um iterador de float

};

#endif // CARREGADOR_H
