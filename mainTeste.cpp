// Programa principal para testar o analisador léxico

#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>

// Inclui o Header da classe lexico.h
#include "lexico.cpp"

using namespace std;

int main(){

	Lexico lexico;
	string retorno;
  vector<int> interpretador;

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
    cout << endl;
    cout << "SAIDA DA LISTA DO LEXICO" << endl;
  	lexico.imprimeLista();
    cout << endl;
  	
    lexico.identificaToken(&interpretador);
    
    cout << "SAIDA DO VECTOR COM INTRUCOES E ENDERECOS" << endl; 
    for(int i = 0; i < interpretador.size(); i++){
      if(i % 2 == 1)
          cout << interpretador[i] << endl;
      else
          cout << interpretador[i] << " "; 
    }
    cout << endl;
  	entrada.close();

	return 0;
}
