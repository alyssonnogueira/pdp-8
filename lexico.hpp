// Header Analisador Léxico
// lexico.h

#ifndef LEXICO_HPP
#define LEXICO_HPP

#include <iostream>
#include <string.h>
#include <fstream>
#include <list>

using namespace std;

class Lexico{
	public:
		Lexico(){ // Construtor default da classe
		}
		
		int lerEntrada(ifstream *arq){ // Realiza a leitura do arquivo de entrada separando os tokens em cada posição da lista
			char ch;
			string retorno;
			if(arq){	// Verifica se o ponteiro é válido
			  	while(arq->get(ch)){ // percorre o arquivo caracter a caracter
			  		if(ch == ';' || ch == '\n'){ // verifica se o caracter encontrado é um ; ou \n
			  			push(retorno);	// adiciona a string a ultima posicao da lista
			  			retorno = "";	// gera o conteúdo da string
			  		}else{
			  			retorno += ch; // Gera a string até achar um ; ou \n
			  		}
			  	}
				return 1;
			}else{
				return 0;
			}
		}

		void push(string valor){ // Adiciona uma string ao final da lista
			lista.push_back(valor);
		}
		void pop(){	// remove a primeira string da lista
			lista.pop_front();
		}
		string top(){ // retorna o valor no topo da lista
			return lista.front();
		}
		void imprimeLista(){ // imprime a lista
			for ( ptr = lista.begin(); ptr != lista.end(); ptr++ )
    			cout << *ptr << endl;
		}
		
	protected:
		list<string> lista;				// Cria a lista léxica
		std::list<string>::iterator ptr;  // cria um iterador de float
};

#endif