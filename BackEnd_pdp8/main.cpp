// Programa principal para testar o analisador léxico

#include <iostream>
#include <sstream>
#include <string.h>
#include <fstream>
#include <vector>
#include "Carregador.h"
#include "Ligador.h"
#include "Simulador.hpp"
#include "Montador.h"
#include "Processador_macros.h"

using namespace std;

int main() {
    Ligador ligador;
    Carregador carregador; // Analisador lexico
    Processador_macros macro; // Analisador lexico

    //------------------------------------MACRO------------------------------------
    // Cria ponteiro e abre o arquivo de entrada
    ifstream entrada1;
    entrada1.open("entrada_teste.txt");

    if (!entrada1) {
        cout << "Não foi possível abrir o arquivo!" << endl;
        //return 0;
    }

    if (!macro.lerEntrada(&entrada1)) { // Le o arquivo de entrada e adiciona ao analisador lexico os tokens separados
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

    entrada1.close(); // Fecha o arquivo

    //-----------------------------MONTADOR------------------------------------
    Montador m;

    m.assemblerOne("Entrada7.txt");
    m.printObjectCode();
    cout << "\n";
    m.printEDSTable();
    cout << "\n";
    m.printERS();

    vector<struct eds> eds = m.getEDS();
    //std::copy( m.getEDS().begin(), m.getEDS().end(), std::back_inserter( eds ) );
    list<struct st> ers; 
    //std::copy( m.getERS().begin(), m.getERS().end(), std::back_inserter( ers ) );
    vector<struct oc> obj = m.getObjectCode();
    //std::copy( m.getObjectCode().begin(), m.getObjectCode().end(), std::back_inserter( obj ) );
    int i = 0;
    
    cout << "novos" << endl;
    list<string> lobj;
    ofstream saida;
    string objn = "objeto.o";
    saida.open("objeto.o", ios_base::out); //, ios_base::in
    
    for (int i = 0; i < obj.size(); i++) {
        oc octable = obj[i];
        saida << octable.adress << " " << octable.adress << " " << octable.opcode << " " << octable.operand << endl;
        i++;
        //obj.pop_front();
    }
    lobj.push_back(objn);
    
    //------------------------------------LIGADOR------------------------------------
    //string obj1, obj2;
    //string obj1 = "arquivo1.o";
    //string obj2 = "arquivo2.o";
    //Ligador
    //list<string> obj;
    //lobj.push_back(obj1);
    //obj.push_back(obj2);

    ligador.Linker(lobj, m.getERS(), m.getEDS());

    //------------------------------------Carregador------------------------------------
    // Cria ponteiro e abre o arquivo de entrada
    ifstream entrada0;
    entrada0.open("programa.pdp"); //, ios_base::in
    if (!entrada0) {
        cout << "Não foi possível abrir o arquivo!" << endl;
        return 0;
    }

    if (!carregador.lerEntrada(&entrada0)) { // Le o arquivo de entrada e adiciona ao analisador lexico os tokens separados
        cout << "Não foi possivel ler o arquivo! " << endl;
    }


    //------------------------------------SIMULADOR------------------------------------
    Simulador simulador;
    vector <vector<int> > interpretador; // Vector inteiro que armazena intruções e endereços como inteiros

    interpretador.resize(500); // Cria 100 posição no vetor
    for (int i = 0; i < 500; ++i)
        interpretador[i].resize(4); // Gera uma matriz 100 x 2

    // Cria ponteiro e abre o arquivo de entrada
    ifstream entrada;
    entrada.open("programa.pdp", ios_base::in);

    if (!entrada) {
        cout << "Não foi possível abrir o arquivo!" << endl;
        return 0;
    }

    list<string> lista;
    char ch;
    string PC;
    int intPC;
    while (!entrada.eof()) {
        while (entrada.get(ch)) // percorre o arquivo caracter a caracter
        {
            if (ch == ';' || ch == '\n') // verifica se o caracter encontrado é um ; ou \n
            {
                lista.push_back(PC); // adiciona a string a ultima posicao da lista
                cout << endl << "STRING " << PC << endl;
                PC = "";
            } else {
                PC += ch; // Gera a string até achar um ; ou \n
            }
        }
    }

    int EXEC, OP, OPER;
    while (!(lista.empty())) {

        PC = lista.front();
        intPC = simulador.stringToInt(PC);
        lista.pop_front();

        PC = lista.front();
        if (PC == "-1")
            EXEC = -1;
        else
            EXEC = simulador.stringToInt(PC);
        lista.pop_front();

        PC = lista.front();
        OP = simulador.stringToInt(PC);
        lista.pop_front();

        PC = lista.front();
        OPER = simulador.stringToInt(PC);
        lista.pop_front();

        interpretador[intPC][0] = intPC;
        interpretador[intPC][1] = EXEC;
        interpretador[intPC][2] = OP;
        interpretador[intPC][3] = OPER;
        cout << interpretador[intPC][0] << " " << interpretador[intPC][1] << " " << interpretador[intPC][2] << " " << interpretador[intPC][3] << endl;
    }
    cout << "INICIANDO PROGRAMA, PRESSIONE ENTER" << endl;
    simulador.processaCodigo(interpretador);
    entrada.close(); // Fecha o arquivo

    return 0;
}
