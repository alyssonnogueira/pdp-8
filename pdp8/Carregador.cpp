#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>

#include "Carregador.h"


using namespace std;

Carregador::Carregador(int size) {
    lProcessamento.resize(size); // Cria n posições no vetor
    for (int i = 0; i < size; ++i)
        lProcessamento[i].resize(2); // Gera uma matriz n x 2
    //ctor
}

Carregador::~Carregador() {
    //dtor
}

vector <vector<int> > Carregador::getList() { // Get para pegar a lista
    return lProcessamento;
}

int Carregador::lerEntrada(ifstream *arq) { // Realiza a leitura do arquivo de entrada separando os tokens em cada posição da lista
    int posicao;
    int instr1, instr2;

    if (arq) { // Verifica se o ponteiro é válido
        while (*arq >> posicao >> instr1 >> instr2) { // percorre o arquivo caracter a caracter
            //cout << posicao << " " << instr1 << " " << instr2 << endl;
            if (posicao < lProcessamento.size()) {
                lProcessamento[posicao][0] = instr1;
                lProcessamento[posicao][1] = instr2;
            } else {
                cout << "Impossível proseguir, não há mais memória!" << endl;
            }
        }

        return 1;
    } else {
        return 0;
    }
}

void Carregador::push(int operador, int operando) { // Adiciona uma string ao final da lista
    lProcessamento[0].push_back(operador);
    lProcessamento[1].push_back(operando);
}

void Carregador::pop() { // remove a primeira string da lista
    lProcessamento.pop_back();
}

vector<int> Carregador::top() { // retorna o valor no topo da lista
    return lProcessamento.front();
}

