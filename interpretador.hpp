
//#ifndef INTERPRETADOR_HPP
#define INTERPRETADOR_HPP

#include <iostream>
#include <string.h>
#include <fstream>
#include <list>
#include <stdio.h>
#include <vector>

using namespace std;


class Interpretador{

    public:
		Interpretador(){ // Construtor default da classe
		}

    vector<int> symbolTable;
    int ACC;

    void processaCodigo(vector<int> listaComandos){

    int i;// i simboliza o indereço de memoria
        for(i=0;i<listaComandos.size();i++){
                    if(listaComandos[i] == 11){ //LDA
                        ACC = symbolTable[listaComandos[i+1]];
                    }
                    if(listaComandos[i] == 12){//STA
                       symbolTable[listaComandos[i+1]]= ACC;

                   }
                    if(listaComandos[i] == 21){//ADD
                        ACC = ACC + symbolTable[listaComandos[i+1]];
                   }
                    if(listaComandos[i] == 22){//SUB
                        ACC = ACC - symbolTable[listaComandos[i+1]];
                   }
                    if(listaComandos[i] == 23){//MULL
                        ACC = ACC * symbolTable[listaComandos[i+1]];
                   }
                    if(listaComandos[i] == 24){//DIV
                        ACC = ACC / symbolTable[listaComandos[i+1]];
                   }
                    if(listaComandos[i] == 25){//REM
                        ACC = ACC%symbolTable[listaComandos[i+1]];
                   }
                    if(listaComandos[i] == 29){//REV
                        ACC = -ACC;
                   }
                    if(listaComandos[i] == 31){//INN
                        cin >> symbolTable[listaComandos[i+1]];
                   }
                    if(listaComandos[i] == 41){//PRN
                        cout << symbolTable[listaComandos[i+1]];
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
                        if (ACC < 0)
                            i = listaComandos[i+1];
                   }
                    if(listaComandos[i] == 57){//JGE
                        if (ACC >= 0)
                            i = listaComandos[i+1];
                   }
                    if(listaComandos[i] == 70){//
                        cout << "FIM DE PROGRAMA";
                   }
        }
    }

    int findStop(vector<int> listaComandos){
        int i;
        for(i=0;i<listaComandos.size();i++){
            if (listaComandos[i]==70)
                return i;
        }
    }

};
