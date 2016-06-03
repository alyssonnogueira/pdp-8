// Header Analisador Léxico
// lexico.h

#ifndef LEXICO_HPP
#define LEXICO_HPP

#include <iostream>
#include <string.h>
#include <fstream>
#include <list>
#include <stdio.h>
#include <vector>

using namespace std;

class Lexico{
	public:
		Lexico(); // Construtor default da classe

		int lerEntrada(ifstream *arq); // Realiza a leitura do arquivo de entrada separando os tokens em cada posição da lista

		void push(string valor); // Adiciona uma string ao final da lista

		void pop();	// remove a primeira string da lista

		string top(); // retorna o valor no topo da lista

		void imprimeLista(); // imprime a lista

        int stringToInt(string str);// onde a mágica acontece

        void identificaToken(vector<int> *interpretadorVector); //   função de identifica os token presentes na lista
        list<string> getLista();
        list<string>::iterator getPonteiro();
	protected:
		list<string> lista;				// Cria a lista léxica
		std::list<string>::iterator ptr;  // cria um iterador de float
};

#endif
