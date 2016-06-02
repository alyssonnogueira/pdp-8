// Programa principal para testar o analisador léxico

#include <iostream>
#include <string.h>
#include <fstream>

// Inclui o Header da classe lexico.h
#include "lexico.hpp"
#include "interpretador.hpp"

using namespace std;

int main(){

	Lexico lexico;
	string retorno;

	// Cria ponteiro e abre o arquivo de entrada
	ifstream entrada;
	entrada.open("teste.txt", ios_base::in);
 	if (!entrada){
     		cout << "Não foi possível abrir o arquivo!" << endl;
     		return 0;
  	}

  	if(!lexico.lerEntrada(&entrada)){ // Le o arquivo de entrada
  		cout << "Não foi possivel ler o arquivo! " << endl;
  	}

  	//lexico.imprimeLista();
  	lexico.identificaToken();



  	entrada.close();

	return 0;
}
