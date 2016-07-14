// Programa principal para testar o analisador léxico

#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include "Carregador.h"
#include "Ligador.h"

using namespace std;

int main() {
    Ligador ligador;
    Carregador carregador; // Analisador lexico


    //string obj1, obj2;
    string obj1 = "arquivo1.o";
    string obj2 = "arquivo2.o";
    //Ligador
    list<string> obj;
    obj.push_back(obj1);
    obj.push_back(obj2);

    ligador.Linker(obj);

    //Carregador
    // Cria ponteiro e abre o arquivo de entrada
    ifstream entrada;
    entrada.open("arquivo.pdp"); //, ios_base::in
    if (!entrada) {
        cout << "Não foi possível abrir o arquivo!" << endl;
        return 0;
    }

    if (!carregador.lerEntrada(&entrada)) { // Le o arquivo de entrada e adiciona ao analisador lexico os tokens separados
        cout << "Não foi possivel ler o arquivo! " << endl;
    }


    return 0;
}
