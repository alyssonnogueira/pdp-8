// Programa principal para testar o analisador léxico

#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include "processador_macros.cpp"

using namespace std;

int main(){
	Processador_macros macro; // Analisador lexico

	// Cria ponteiro e abre o arquivo de entrada
	ifstream entrada;
	entrada.open("entrada_teste.txt");
 	
    if (!entrada){
     		cout << "Não foi possível abrir o arquivo!" << endl;
     		return 0;
  	}

  	if(!macro.lerEntrada(&entrada)){ // Le o arquivo de entrada e adiciona ao analisador lexico os tokens separados
  		  cout << "Não foi possivel ler o arquivo! " << endl;
  	}
   
    macro.passOne();
    macro.passTwo();
    
    // Impressão utilizada apenas para debug
    // ========================================
    cout << "SAIDA DA LISTA DO PROCESSADOR DE MACROS" << endl << endl;
  	macro.imprimeEntrada();

    cout << "============= SAIDA SEM DEFINICAO ===============" << endl;
    macro.imprimeSaida();
    cout << endl;
    cout << " =========== Valor contido na Macro ============" << endl;
    macro.imprimeMacro();
    cout << endl;
    cout << "============== Nomes das macros =================" << endl;
    cout << endl;
    macro.imprimeNomes();
    cout << endl;
  	// ========================================
    
  	entrada.close(); // Fecha o arquivo
    
	return 0;
}
