// FUNÇÕES DO SIMULADOR

#include <iostream>
#include <string.h>
#include <fstream>
#include <list>
#include <stdio.h>
#include <vector>

#include "simulador.hpp"

using namespace std;


Simulador::Simulador() { } //construtor

void Simulador::processaCodigo(vector < vector<int> > matrizComandos)
{


    int PC,EXEC,OP,OPER,ACC,Y,X,REGPC;
//INICIA NA PRIMEIRA LINHA DA MATRIZ DE COMANDOS
    PC=0;

    while(OP!=20)
    {
        getchar();
        EXEC=matrizComandos[PC][1];
        OP=matrizComandos[PC][2];
        OPER=matrizComandos[PC][3];

        if(EXEC!=-1)
        {
            cout<< PC << " " << matrizComandos[PC][1] << " " << matrizComandos[PC][2] << " " << matrizComandos[PC][3]<< endl;

            switch(OP)
            {
            case 0://AND Y (ACC <- ACC ^ Y)
                ACC=ACC&matrizComandos[OPER][2];
                PC++;
                break;

            case 1://TAD Y (ACC <- ACC + Y)
                Y=matrizComandos[PC][3];
                ACC=ACC+matrizComandos[Y][2];
                PC++;
                break;

            case 2://ISZ Y        Y <- Y + 1
                Y=matrizComandos[PC][3];
                matrizComandos[Y][2]=matrizComandos[Y][2]+1;
                PC++;
                break;

            case 3://DCA Y        Y <- ACC, então ACC <- 0
                Y=matrizComandos[PC][3];
                matrizComandos[Y][2]=ACC;
                ACC=0;
                PC++;
                break;

            case 4://JMS Y        salta para uma sub-rotina   Y <- PC + 1  ,  PC <- Y + 1
                REGPC=matrizComandos[PC][3];
                matrizComandos[REGPC][2]=PC+1;
                PC=REGPC+1;
                break;

            case 5://JMP Y        PC <- Y
                PC = matrizComandos[OPER][2];
                break;

            case 6://CLA    limpa o Acumulador
                ACC=0;
                PC++;
                break;

            case 7://CMA complementa o Acumulador
                ACC = -ACC;
                PC++;
                break;

            case 8://RAR    rotaciona o Acumalador para a direita
                ACC = ACC >> 1;
                PC++;
                break;

            case 9://RAL    rotaciona o Acumalador para a esquerda
                ACC = ACC << 1;
                PC++;
                break;

            case 10://RTR   rotaciona o Acumalador 2X para a direita
                ACC = ACC >> 2;
                PC++;
                break;

            case 11://RTL   rotaciona o Acumalador 2X para a esquerda
                ACC = ACC << 2;
                PC++;
                break;

            case 12://IAC         ACC <- ACC + 1
                ACC = ACC + 1;
                PC++;
                break;

            case 13://NOP   faz nada
                PC++;
                break;

            case 14://SPA   if ACC > 0, pula a próxima instrução
                if(ACC>0)
                    PC=PC+2;
                else
                    PC++;
                break;

            case 15://SMA   if ACC < 0, pula a próxima instrução
                if(ACC<0)
                    PC=PC+2;
                else
                    PC++;
                break;

            case 16://SNA   if ACC != 0, pula a próxima instrução
                if(ACC!=0)
                    PC=PC+2;
                else
                    PC++;
                break;

            case 17://SZA   if ACC = 0, pula a próxima instrução
                if(ACC==0)
                    PC=PC+2;
                else
                    PC++;
                break;

            case 18://SKP   pula proxima instrução
                PC=PC+2;
                break;

            case 19://OSR   ACC <- ACC v SE (SE Ã© switch register)
                PC++;
                break;

            case 20://HLT      para a execução do programa
                PC++;
                break;

            case 21://IOK   ACC <- TECLADO
                cout << "ENTRE COM UM VALOR :";
                cin >>ACC;
                PC++;
                break;

            case 22://OOM   MONITOR <- ACC
                cout <<"SAIDA: "<< ACC << endl;
                PC++;
                break;

            case 23:// JMP I Y PC <- Y (diferente do JMP comum, o PC nÃ£o vai apontar para Y e sim para o valor que Y armazena)
                PC=matrizComandos[REGPC][2];
                break;
            }
        }else{
        PC++;
        }
    }
}

int Simulador::stringToInt(string str){ // onde a mágica acontece
  int retorno;
  retorno = (str[0] - 0) % 48;
  if(str[1] >= '0' && str[1] <= '9')
    for(int i = 1; i < str.size(); i++){
      retorno *= 10;
      retorno += (str[i] - 0) % 48;
    }
  return retorno;
}





