// Programa principal para testar o analisador léxico

#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>

// Inclui o Header da classe lexico.h
#include "lexico.cpp"
#include "interpretador.hpp"

using namespace std;

int main(){
  Interpretador processador;  // Interpretador das instruções e endereços
	Lexico lexico; // Analisador lexico
  vector<int> interpretador;  // Vector inteiro que armazena intruções e endereços como inteiros

	// Cria ponteiro e abre o arquivo de entrada
	ifstream entrada;
	entrada.open("teste.txt", ios_base::in);
 	
    if (!entrada){
     		cout << "Não foi possível abrir o arquivo!" << endl;
     		return 0;
  	}

  	if(!lexico.lerEntrada(&entrada)){ // Le o arquivo de entrada e adiciona ao analisador lexico os tokens separados
  		cout << "Não foi possivel ler o arquivo! " << endl;
  	}
    
    // Impressão utilizada apenas para debug
    // ========================================
    cout << "SAIDA DA LISTA DO LEXICO" << endl;
  	lexico.imprimeLista();
    cout << endl;
  	// ========================================


    lexico.identificaToken(&interpretador); // Adiciona as instruções e os endereços no vector de inteiros
    
    
    // Impressão utilizada apenas para debug
    // ========================================
    cout << "SAIDA DO VECTOR COM INTRUCOES E ENDERECOS" << endl; 
    for(int i = 0; i < interpretador.size(); i++){
      if(i % 2 == 1)
          cout << interpretador[i] << endl;
      else
          cout << interpretador[i] << " "; 
    }
    cout << endl;
    // ========================================


    processador.processaCodigo(interpretador);

  	entrada.close(); // Fecha o arquivo

	return 0;
}
