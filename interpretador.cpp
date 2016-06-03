#include <iostream>
#include <string.h>
#include <fstream>
#include <list>
#include <stdio.h>
#include <vector>

// Inclui o header do interpretador.hpp
#include "interpretador.hpp"

using namespace std;

Interpretador::Interpretador(){ }// Construtor default da classe

int Interpretador::findStop(vector < vector<int> > listaComandos){

    // cout << "STOP > ";
    int i;
    for(i=0;i<listaComandos.size();i++){
        if (listaComandos[i]==70){
            // cout << i << endl;
            return i;
        }
    }
}

void Interpretador::iniciaTabela(){
    int i;
    for(i=0;i<100;i++){
        symbolTable[i]=0;
    }
}

void Interpretador::constroiTabela (vector < vector<int> > listaComandos){
    int stopPosition = findStop(listaComandos);
    iniciaTabela();
    int i;
    for(i=0;i<listaComandos.size();i++){// PULA DE 2 EM 2, IDENTIFICANDO OS ENDEREÇOS DAS OPERAÇOES
        if(listaComandos[i]!=11||12||21||22||23||24||25||29||31||41||50||51||52||53||54||55||56||57||70){//TESTANDO POSIÇÃO POR POSIÇÃO, ELE VERIFICA SE NÃO É UM COMANDO
            if (listaComandos[i]>stopPosition){//SE MAIOR QUE A POSIÇÃO DO STOP, SIGNIFICA QUE ESTOU ME REFERENCIANDO A TABELA
                symbolTable[listaComandos[i]]=0;
            }
        }
    }
}

void Interpretador::processaCodigo(vector < vector<int> > listaComandos){
    ACC=0;
    int stopPosition = findStop(listaComandos);
    constroiTabela(listaComandos);
    int i;// i simboliza o indereço de memoria
        
    for(i=0;i<listaComandos.size();i++){
        cout << listaComandos[i]<<" ";
        cout << listaComandos[i+1];
        cout << " ACC: " << ACC << endl;

        if(listaComandos[i] == 11){ //LDA
            i++;
            ACC = symbolTable[listaComandos[i]];
        }
        if(listaComandos[i] == 12 || listaComandos[i] == 00){//STA
            if(listaComandos[i] == 00){
            	i++;
            	symbolTable[listaComandos[i]] = listaComandos[i];
            }
            else{
            	i++;
            	symbolTable[listaComandos[i]] = ACC;
            }
        }
        if(listaComandos[i] == 21){//ADD
            i++;
            ACC += symbolTable[listaComandos[i]];
        }
        if(listaComandos[i] == 22){//SUB
            i++;
            ACC = ACC - symbolTable[listaComandos[i]];
        }
        if(listaComandos[i] == 23){//MULL
            i++;
            ACC = ACC * symbolTable[listaComandos[i]];
        }
        if(listaComandos[i] == 24){//DIV
            i++;
            ACC = ACC / symbolTable[listaComandos[i]];
        }
        if(listaComandos[i] == 25){//REM
            i++;
            ACC = ACC%symbolTable[listaComandos[i]];
        }
        if(listaComandos[i] == 29){//REV
            ACC = -ACC;
        }
        if(listaComandos[i] == 31){//INN
            i++;
            cout << endl;
            cout <<"Digite um valor: ";
            cin >> symbolTable[listaComandos[i]];
            cout << endl;
            cout << "Tabela: " << symbolTable[listaComandos[i]] << endl;
            cout << endl;
        }
        if(listaComandos[i] == 41){//PRN
            i++;
            cout << endl;
            cout <<"Valor: ";
            cout << symbolTable[listaComandos[i]]<<endl;
        }
        if(listaComandos[i] == 50){//NOP
            //COMANDO VAZIO, APENAS PASSA PARA O PROXIMO
        }
        if(listaComandos[i] == 51){//JMP
            i = listaComandos[i+1]; //I  nesse caso está representando o indice no vetor de inteiros, que é o codigo
        }
        if(listaComandos[i] == 52){//JLE
            if (ACC<=0)
                i = listaComandos[i+1];
        }
        if(listaComandos[i] == 53){//JDZ
            if (ACC!=0)
                i = listaComandos[i+1];
        }
       	if(listaComandos[i] == 54){//JGT
          	if (ACC>0)
              	i = listaComandos[i+1];
        }
        if(listaComandos[i] == 55){//JEQ
           	if(ACC == 0)
           	    i = listaComandos[i+1];
        }
        if(listaComandos[i] == 56){//JLT
	       	if (ACC < 0){
      	   		for(int k = i; k < listaComandos.size(); k++)
               		if(listaComandos[k] == 41)
                		i = k - 3;
           	    	cout << i << endl;
           	}
           	else{
               	i++;
           	}
        }
        if(listaComandos[i] == 57){//JGE
           	if (ACC >= 0)
           	    i = listaComandos[i+1];
        }
        if(listaComandos[i] == 70){//
           	cout << endl;
           	cout << "FIM DE PROGRAMA" << endl;
           	cout << endl;
           	return;
        }
        getchar();
    }
}