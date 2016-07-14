// Programa principal para testar o analisador léxico

#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include "Carregador.h"
#include "Ligador.h"
#include "Simulador.hpp"
#include "Montador.h"

using namespace std;

int main() {
    Ligador ligador;
    Carregador carregador; // Analisador lexico

    //MONTADOR
    Montador m;

    m.assemblerOne("Entrada7.txt");
    m.printObjectCode();
    cout << "\n";
    m.printEDSTable();
    cout << "\n";
    m.printERS();
    
    //LIGADOR
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
    ifstream entrada0;
    entrada0.open("programa.pdp"); //, ios_base::in
    if (!entrada0) {
        cout << "Não foi possível abrir o arquivo!" << endl;
        return 0;
    }

    if (!carregador.lerEntrada(&entrada0)) { // Le o arquivo de entrada e adiciona ao analisador lexico os tokens separados
        cout << "Não foi possivel ler o arquivo! " << endl;
    }

    
    //SIMULADOR
    Simulador simulador;
    vector <vector<int> > interpretador;  // Vector inteiro que armazena intruções e endereços como inteiros

    interpretador.resize(500); // Cria 100 posição no vetor
    for (int i = 0; i < 500; ++i)
        interpretador[i].resize(4); // Gera uma matriz 100 x 2

    // Cria ponteiro e abre o arquivo de entrada
    ifstream entrada;
    entrada.open("programa.pdp", ios_base::in);

    if (!entrada)
    {
        cout << "Não foi possível abrir o arquivo!" << endl;
        return 0;
    }

    list<string> lista;
    char ch;
    string PC;
    int intPC;
    while(!entrada.eof())
    {
        while(entrada.get(ch))  // percorre o arquivo caracter a caracter
        {
            if(ch == ';' || ch == '\n')  // verifica se o caracter encontrado é um ; ou \n
            {
                lista.push_back(PC);  // adiciona a string a ultima posicao da lista
                cout << endl<<"STRING "<< PC << endl;
                PC= "";
            }
            else
            {
                PC += ch; // Gera a string até achar um ; ou \n
            }
        }
    }

    int EXEC,OP,OPER;
    while(!(lista.empty()))
    {

        PC=lista.front();
        intPC=simulador.stringToInt(PC);
        lista.pop_front();

        PC=lista.front();
        if(PC=="-1")
            EXEC=-1;
        else
            EXEC=simulador.stringToInt(PC);
        lista.pop_front();

        PC=lista.front();
        OP=simulador.stringToInt(PC);
        lista.pop_front();

        PC=lista.front();
        OPER=simulador.stringToInt(PC);
        lista.pop_front();

        interpretador[intPC][0]=intPC;
        interpretador[intPC][1]=EXEC;
        interpretador[intPC][2]=OP;
        interpretador[intPC][3]=OPER;
        cout<< interpretador[intPC][0] << " " << interpretador[intPC][1] << " " << interpretador[intPC][2] << " " << interpretador[intPC][3]<< endl;
    }
    cout << "INICIANDO PROGRAMA, PRESSIONE ENTER" << endl;
    simulador.processaCodigo(interpretador);
    entrada.close(); // Fecha o arquivo

    return 0;
}
