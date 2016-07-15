// Header do Processador De Macros
// processador_macros.hpp

#ifndef PROCESSADOR_HPP
#define PROCESSADOR_HPP

#include <iostream>
#include <string.h>
#include <fstream>
#include <list>
#include <stdio.h>
#include <vector>

using namespace std;


class Processador_macros{

    public:
		Processador_macros(); // Construtor default da classe

		int lerEntrada(ifstream *arq); // Realiza a leitura do arquivo de entrada separando os tokens em cada posição da macro

		void push(string valor); // Adiciona uma string ao final da macro
			
		void imprimeMacro(); // imprime a macro

		void imprimeEntrada();

		void imprimeNomes();

		void imprimeSaida();

		void passOne();		// Passa primeira vez pela macro

		void passTwo();		// Passa segunda vez pela macro

		void troca(int i, int j);

		void saidaTeste();

		void getMacro(ifstream *arq);


	protected:
		vector<string> saida;
		vector<string> entrada;
		vector<string> macro;				// Cria a macro com a macro
		vector<string> expansao;			// Cria a macro da macro expandida
		vector<string> nomes;
		vector<string> chamada;
		vector<string> variaveis;
		ofstream outFile;
		//list<string>::iterator ptr;  // cria um iterador de float
};
#endif