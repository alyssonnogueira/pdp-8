// Construção das funções declaradas em interpretador.hpp

#include <iostream>
#include <string.h>
#include <fstream>
#include <list>
#include <stdio.h>
#include <vector>

// Inclui o header do interpretador.hpp
#include "interpretador.h"
#include "Refresh.h"
//#include "Refresh.h"
using namespace std;

Interpretador::Interpretador(){ } // Construtor default da classe

int Interpretador::getACC(){ // Get para o acumulador
    return this->ACC;
}

int* Interpretador::getSymbolTable(){ // Get para a tabela de simbolos
    return symbolTable;
}

vector < vector<int> > Interpretador::getListaComandos(){ return this->listaComandos;}

void Interpretador::iniciaTabela(vector < vector<int> > listaComandos){ // Inicia a tabela de simbolos toda com zero
    int i;
    for(i=0;i<100;i++){
            symbolTable[i]=0;
            if(listaComandos[i][0] == 00 && listaComandos[i][1] != 00)
                symbolTable[i] = listaComandos[i][1];
    }
}

int Interpretador::processaCodigo(void *step, vector < vector<int> > listaComandos){ // Processa as instruções passadas do código de entrada
    Refresh refresh;
	ACC=0;
    iniciaTabela(listaComandos); // Inicia a tabela de simbolos
    static int i = 0; // i simboliza o indereço de memoria
    if (i == 0){
    this->listaComandos = listaComandos;
    }
    if (this->mValue == true){
    	cout << "Tabela: " << symbolTable[this->listaComandos[i][1]] << endl;
    	            std::ostringstream label2;
    	            label2 << "Tabela: " << symbolTable[this->listaComandos[i][1]] << endl;
    	            refresh.Refresh_NewValue(step, label2.str());
    	            cout << endl;
    }
    if (i<this->listaComandos.size()){
    //for(i; i < this->listaComandos.size(); i++){
    	cout << this->listaComandos[i][0]<<" ";
    	cout << this->listaComandos[i][1]<< " ";
    	cout << "Acumulador" << ACC << endl;
    	refresh.Refresh_StepWindow(step, i, this->listaComandos[i][0], this->listaComandos[i][1]);
        if(listaComandos[i][0] == 11){ //LDA
            ACC = symbolTable[this->listaComandos[i][1]];
        }
        if(this->listaComandos[i][0] == 12 || this->listaComandos[i][0] == 00){//STA
            if(listaComandos[i][0] == 00 && this->listaComandos[i][1] != 00){
            	symbolTable[this->listaComandos[i][1]] = this->listaComandos[i][1];
            }
            else{
            	symbolTable[this->listaComandos[i][1]] = ACC;
            }
        }
        if(this->listaComandos[i][0] == 21){//ADD
            ACC += symbolTable[this->listaComandos[i][1]];
        }
        if(this->listaComandos[i][0] == 22){//SUB
            ACC = ACC - symbolTable[this->listaComandos[i][1]];
        }
        if(this->listaComandos[i][0] == 23){//MULL
            ACC = ACC * symbolTable[this->listaComandos[i][1]];
        }
        if(this->listaComandos[i][0] == 24){//DIV
            ACC = ACC / symbolTable[this->listaComandos[i][1]];
        }
        if(this->listaComandos[i][0] == 25){//REM
            ACC = ACC%symbolTable[this->listaComandos[i][1]];
        }
        if(this->listaComandos[i][0] == 29){//REV
            ACC = -ACC;
        }
        if(this->listaComandos[i][0] == 31){//INN
            cout << endl;
            cout <<"Digite um valor: ";
            string label = "Digite um valor: ";
            //cin >> symbolTable[this->listaComandos[i][1]];
            ValueOk = false;
            int retorno = refresh.Refresh_NewValue(step, label);
            cout << endl;
          }
        if(this->listaComandos[i][0] == 41){//PRN
            cout << endl;
            cout <<"Valor: ";
            cout << symbolTable[this->listaComandos[i][1]]<<endl;
        }
        if(this->listaComandos[i][0] == 50){//NOP
            //COMANDO VAZIO, APENAS PASSA PARA O PROXIMO
        }
        if(this->listaComandos[i][0] == 51){//JMP
            i = (this->listaComandos[i][1]) - 1;
        }
        if(this->listaComandos[i][0] == 52){//JLE
            if (ACC<=0)
                i = (this->listaComandos[i][1]) - 1;
        }
        if(this->listaComandos[i][0] == 53){//JDZ
            if (ACC!=0)
                i = (this->listaComandos[i][1]) - 1;
        }
       	if(this->listaComandos[i][0] == 54){//JGT
          	if (ACC>0)
              	i = (this->listaComandos[i][1]) - 1;
        }
        if(this->listaComandos[i][0] == 55){//JEQ
           	if(ACC == 0)
           	    i = (this->listaComandos[i][1]) - 1;
        }
        if(this->listaComandos[i][0] == 56){//JLT
	       	if (ACC < 0){
                i = (this->listaComandos[i][1]) - 1;
           	}
        }
        if(this->listaComandos[i][0] == 57){//JGE
           	if (ACC >= 0)
           	    i = (this->listaComandos[i][1]) - 1;
        }
        if(this->listaComandos[i][0] == 70){ //STOP
           	cout << endl;
           	cout << "FIM DE PROGRAMA" << endl;
           	cout << endl;
            std::ostringstream label2;
            label2 << "FIM DE PROGRAMA" << endl;
            refresh.Refresh_NewValue(step, label2.str());
           	return 0;
        }
        i++;
        //getchar();
    } /*else {
    	cout << "FIM DE PROGRAMA" << endl;
    	cout << endl;
    	return 0;
    }*/
}
