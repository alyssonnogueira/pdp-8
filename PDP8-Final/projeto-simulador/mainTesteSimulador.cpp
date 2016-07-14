// Programa principal para testar o analisador léxico

#include <iostream>
#include <string.h>
#include <fstream>
#include <list>
#include <stdio.h>
#include <vector>
// Inclui a classe lexico
#include "simulador.cpp"

using namespace std;

int main()
{
    Simulador simulador;
    vector <vector<int> > interpretador;  // Vector inteiro que armazena intruções e endereços como inteiros

    interpretador.resize(500); // Cria 100 posição no vetor
    for (int i = 0; i < 500; ++i)
        interpretador[i].resize(4); // Gera uma matriz 100 x 2

    // Cria ponteiro e abre o arquivo de entrada
    ifstream entrada;
    entrada.open("testeSimulador.txt", ios_base::in);

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
                //cout << endl<<"STRING "<< PC << endl;
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
       //cout<< interpretador[intPC][0] << " " << interpretador[intPC][1] << " " << interpretador[intPC][2] << " " << interpretador[intPC][3]<< endl;
    }
    //cout << "INICIANDO PROGRAMA, PRESSIONE ENTER" << endl;
    simulador.processaCodigo(interpretador);
    entrada.close(); // Fecha o arquivo

    return 0;
}
