/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ligador.cpp
 * Author: alysson
 * 
 * Created on 12 de Julho de 2016, 20:28
 */

#include "Ligador.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <list>
#include <stdio.h>
#include <vector>
#include "Montador.h"

using namespace std;

Ligador::Ligador() {
}

Ligador::Ligador(const Ligador& orig) {
}

int Ligador::getlinhas(){
    return this->linhas;
}

int Ligador::Linker(list<string> obj, vector<struct st> ERS, vector<struct eds> EDS) {
    int posicao;
    int instr[3];
    this->linhas = 0;
    list<string> objs;
    //Conta as linhas
    while (obj.size() != 0){
    ifstream arq;
        arq.open(obj.front().c_str());
        objs.push_back(obj.front());    
        obj.pop_front();
        if (arq) { // Verifica se o ponteiro é válido
            while (arq >> posicao >> instr[0] >> instr[1] >> instr[2]) { // percorre o arquivo caracter a caracter
                linhas++;
            }
            linhas++;
        }
        //linhas = posicao;
    }
    
    LeObj(objs, linhas, linhas);
    
    for (int i = 0; i < EDS.size(); i++){
        if (EDS[i].adress == -1){
            for (int j = 0; j < ERS.size(); i++){
                if (ERS[j].symbol == EDS[i].symbol){
                    EDS[i].adress = ERS[j].adress;
                    for (int x = 0; x < Codigo.size(); x++){
                        if (Codigo[x][1] == EDS[i].id){
                            cout << "TROCA " << Codigo[x][3] << EDS[i].adress; 
                            Codigo[x][3] = EDS[i].adress;
                        }
                    }
                }
            }
        }
    }
    
    //Gera o executavel .pdp
    geraExec();
    return 0;

}

int Ligador::LeObj(list<string> obj, int TCodigo, int Ttsg) {
    int posicao;
    int instr[3];
    Codigo.resize(TCodigo, vector<int>(4, -1));
    //TSG.resize(Ttsg, vector<int>(3, -1));
    cout << "Lendo Objs" << endl;
    int i = 0;
    while (obj.size() != 0) {
        ifstream arq;
        arq.open(obj.front().c_str());
        obj.pop_front();
        if (arq) { // Verifica se o ponteiro é válido
            int addr = 0;
            while (arq >> posicao >> instr[0] >> instr[1] >> instr[2]) { // percorre o arquivo caracter a caracter
                cout << posicao << " " << instr[0] << " " << instr[1] << " " << instr[2] << endl;
                //if (posicao > 1) {
                    //TSG.resize(posicao, vector<int>(4, -1));
                    //TU.resize(posicao, vector<int>(3, -1));
                //}
                if (i <= Codigo.size()) {
                    Codigo[i][0] = posicao;
                    //addr++;
                    Codigo[i][1] = instr[0];
                    //addr++;
                    Codigo[i][2] = instr[1];
                    //addr++;
                    Codigo[i][3] = instr[2];
                    addr++;
                  /*  if (instr[0] != -1) {
                        TSG.at(0).push_back(instr[1]);
                        TSG.at(1).push_back(addr);
                        TSG.at(2).push_back(1); //1 indica + e -1 indica -
                    }*/
                } else {
                    cout << "Impossível proseguir, não há mais memória!" << endl;
                }
                i++;
            }
        } else {
            cout << "Impossível Abrir Obj!" << endl;
            return 0;
        }
    }
    return 1;
}

int Ligador::geraExec() {
    ofstream saida;
    saida.open("programa.pdp", ios_base::out); //, ios_base::in
    cout << "Gerando Executavel" << endl;
    for (int i = 0; i < this->Codigo.size()-1; i++) { // percorre o arquivo caracter a caracter
    cout << Codigo[i][0] << ";" << Codigo[i][1] << ";" << Codigo[i][2] << ";" << Codigo[i][3] << endl;
    saida << Codigo[i][0] << ";" << Codigo[i][1] << ";" << Codigo[i][2] << ";" << Codigo[i][3] << endl;
    }
    
    
    return 0;
}

Ligador::~Ligador() {
}

