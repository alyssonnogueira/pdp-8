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
/*
    // cout << "STOP > ";
    int i;
    for(i=0;i<listaComandos.size();i++){
        if (listaComandos[i]==70){
            // cout << i << endl;
            return i;
        }
    }
    */
}

void Interpretador::iniciaTabela(){

    int i;
    for(i=0;i<100;i++){
        symbolTable[i]=0;
    }

}

void Interpretador::constroiTabela (vector < vector<int> > listaComandos){
   /*
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
    */
}

void Interpretador::processaCodigo(vector < vector<int> > listaComandos){
    ACC=0;
    int stopPosition = findStop(listaComandos);
    iniciaTabela();
    constroiTabela(listaComandos);
    int i;// i simboliza o indereço de memoria

    for(i=0;i<listaComandos.size();i++){
        cout << listaComandos[i][0]<<" ";
        cout << listaComandos[i][1];


        if(listaComandos[i][0] == 11){ //LDA
            ACC = symbolTable[listaComandos[i][1]];
        }

        if(listaComandos[i][0] == 12 || listaComandos[i][0] == 00){//STA
            if(listaComandos[i][0] == 00){
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
            i++;
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
            i = listaComandos[i][1]-2; //I  nesse caso está representando o indice no vetor de inteiros, que é o codigo
        }
        if(listaComandos[i][0] == 52){//JLE
            if (ACC<=0)
                i = listaComandos[i][1]-2;
        }
        if(listaComandos[i][0] == 53){//JDZ
            if (ACC!=0)
                i = listaComandos[i][1]-2;
        }
       	if(listaComandos[i][0] == 54){//JGT
          	if (ACC>0)
              	i = listaComandos[i][1]-2;
        }
        if(listaComandos[i][0] == 55){//JEQ
           	if(ACC == 0)
           	    i = listaComandos[i][1]-2;
        }
        if(listaComandos[i][0] == 56){//JLT
	       	if (ACC < 0){
      	   		/*for(int k = i; k < listaComandos.size(); k++)
               		if(listaComandos[k] == 41)*/
                		i = listaComandos[i][1] - 2;
           	    	//cout << i << endl;
           	}
           	else{
           	}
        }
        if(listaComandos[i][0] == 57){//JGE
           	if (ACC >= 0)
           	    i = listaComandos[i][1] - 2;
        }
        if(listaComandos[i][0] == 70){//
           	cout << endl;
           	cout << "FIM DE PROGRAMA" << endl;
           	cout << endl;
           	return;
        }
        cout << " ACC: " << ACC << endl;
        getchar();
    }
}
