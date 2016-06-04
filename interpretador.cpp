// Construção das funções declaradas em interpretador.hpp

#include <iostream>
#include <string.h>
#include <fstream>
#include <list>
#include <stdio.h>
#include <vector>

// Inclui o header do interpretador.hpp
#include "interpretador.hpp"

using namespace std;

Interpretador::Interpretador(){ } // Construtor default da classe

int Interpretador::getACC(){ // Get para o acumulador
    return ACC;
}

int* Interpretador::getSymbolTable(){ // Get para a tabela de simbolos
    return symbolTable;
}

void Interpretador::iniciaTabela(vector < vector<int> > listaComandos){ // Inicia a tabela de simbolos toda com zero 
    int i;
    for(i=0;i<100;i++){
            symbolTable[i]=0;
            if(listaComandos[i][0] == 00 && listaComandos[i][1] != 00)
                symbolTable[i] = listaComandos[i][1];
    }
}

void Interpretador::processaCodigo(vector < vector<int> > listaComandos){ // Processa as instruções passadas do código de entrada 
    ACC=0;
    iniciaTabela(listaComandos); // Inicia a tabela de simbolos
    int i; // i simboliza o indereço de memoria
        
    for(i=0;i<listaComandos.size();i++){
        cout << listaComandos[i][0]<<" ";
        cout << listaComandos[i][1];
        cout << " ACC: " << ACC << endl;

        if(listaComandos[i][0] == 11){ //LDA
            ACC = symbolTable[listaComandos[i][1]];
        }
        if(listaComandos[i][0] == 12 || listaComandos[i][0] == 00){//STA
            if(listaComandos[i][0] == 00 && listaComandos[i][1] != 00){
            	symbolTable[listaComandos[i][1]] = listaComandos[i][1];
            }
            else{
            	symbolTable[listaComandos[i][1]] = ACC;
            }
        }
        if(listaComandos[i][0] == 21){//ADD
            ACC += symbolTable[listaComandos[i][1]];
        }
        if(listaComandos[i][0] == 22){//SUB
            ACC = ACC - symbolTable[listaComandos[i][1]];
        }
        if(listaComandos[i][0] == 23){//MULL
            ACC = ACC * symbolTable[listaComandos[i][1]];
        }
        if(listaComandos[i][0] == 24){//DIV
            ACC = ACC / symbolTable[listaComandos[i][1]];
        }
        if(listaComandos[i][0] == 25){//REM
            ACC = ACC%symbolTable[listaComandos[i][1]];
        }
        if(listaComandos[i][0] == 29){//REV
            ACC = -ACC;
        }
        if(listaComandos[i][0] == 31){//INN
            cout << endl;
            cout <<"Digite um valor: ";
            cin >> symbolTable[listaComandos[i][1]];
            cout << endl;
            cout << "Tabela: " << symbolTable[listaComandos[i][1]] << endl;
            cout << endl;
        }
        if(listaComandos[i][0] == 41){//PRN
            cout << endl;
            cout <<"Valor: ";
            cout << symbolTable[listaComandos[i][1]]<<endl;
        }
        if(listaComandos[i][0] == 50){//NOP
            //COMANDO VAZIO, APENAS PASSA PARA O PROXIMO
        }
        if(listaComandos[i][0] == 51){//JMP
            i = (listaComandos[i][1]) - 1;
        }
        if(listaComandos[i][0] == 52){//JLE
            if (ACC<=0)
                i = (listaComandos[i][1]) - 1;
        }
        if(listaComandos[i][0] == 53){//JDZ
            if (ACC!=0)
                i = (listaComandos[i][1]) - 1;
        }
       	if(listaComandos[i][0] == 54){//JGT
          	if (ACC>0)
              	i = (listaComandos[i][1]) - 1;
        }
        if(listaComandos[i][0] == 55){//JEQ
           	if(ACC == 0)
           	    i = (listaComandos[i][1]) - 1;
        }
        if(listaComandos[i][0] == 56){//JLT
	       	if (ACC < 0){
                i = (listaComandos[i][1]) - 1;
           	}
        }
        if(listaComandos[i][0] == 57){//JGE
           	if (ACC >= 0)
           	    i = (listaComandos[i][1]) - 1;
        }
        if(listaComandos[i][0] == 70){ //STOP
           	cout << endl;
           	cout << "FIM DE PROGRAMA" << endl;
           	cout << endl;
           	return;
        }
        getchar();
    }
}