// Programa principal para testar o analisador léxico

#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>

// Inclui a classe lexico
#include "lexico.cpp"
// Inclui a classe Interpretador
#include "interpretador.cpp"

using namespace std;

int main(){
    Interpretador processador;  // Interpretador das instruções e endereços
	Lexico lexico; // Analisador lexico
  vector <vector<int> > interpretador;  // Vector inteiro que armazena intruções e endereços como inteiros

  interpretador.resize(30);
  for (int i = 0; i < 30; ++i)
    interpretador[i].resize(2);

  /*interpretador[0][0] = 0;
  interpretador[0][1] = 1;
  interpretador[1][0] = 2;
  interpretador[1][1] = 3;
  interpretador[2][0] = 4;
  interpretador[2][1] = 5;

  for(int i = 0; i < 3 ; i++){
      for(int k = 0; k < 2; k++)
        cout << interpretador[i][k];
      cout << endl;
  }*/

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

    interpretador = lexico.identificaToken(interpretador); // Adiciona as instruções e os endereços no vector de inteiros


    /// Impressão utilizada apenas para debug
    // ========================================
    cout << "SAIDA DO VECTOR COM INTRUCOES E ENDERECOS" << endl;
    for(int i = 0; i < interpretador.size(); i++){
        cout << interpretador[i][0]<< " ";
        cout << interpretador[i][1] << endl;
    }
    cout << endl;
    // ========================================g

    processador.processaCodigo(interpretador);

  	entrada.close(); // Fecha o arquivo

	return 0;
}
