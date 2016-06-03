// Programa principal para testar o analisador léxico

#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>

// Inclui o Header da classe lexico.h
#include "lexico.hpp"

using namespace std;

Lexico::Lexico(){ }// Construtor default da classe

int Lexico::lerEntrada(ifstream *arq){ // Realiza a leitura do arquivo de entrada separando os tokens em cada posição da lista
  char ch;
  string retorno;
  if(arq){  // Verifica se o ponteiro é válido
    while(arq->get(ch)){ // percorre o arquivo caracter a caracter
      if(ch == ';' || ch == '\n'){ // verifica se o caracter encontrado é um ; ou \n
        push(retorno);  // adiciona a string a ultima posicao da lista
        retorno = ""; // gera o conteúdo da string
      }else{
        retorno += ch; // Gera a string até achar um ; ou \n
      }
    }
    return 1;
  }else{
      return 0;
  }
}

void Lexico::push(string valor){ // Adiciona uma string ao final da lista
  lista.push_back(valor);
}

void Lexico::pop(){ // remove a primeira string da lista
  lista.pop_front();
}

string Lexico::top(){ // retorna o valor no topo da lista
  return lista.front();
}

void Lexico::imprimeLista(){ // imprime a lista
  for ( ptr = lista.begin(); ptr != lista.end(); ptr++ )
    cout << *ptr << endl;
}

int Lexico::stringToInt(string str){ // onde a mágica acontece
  int retorno;
  retorno = (str[0] - 0) % 48;
  if(str[1] >= '0' && str[1] <= '9')
    for(int i = 1; i < str.size(); i++){
      retorno *= 10;
      retorno += (str[i] - 0) % 48;
    }
  return retorno;
}

vector <vector<int> > Lexico::identificaToken(vector< vector<int> > interpretadorVector){//   função de identifica os token presentes na lista

  string comando,instr,ender;
  int i = 0, inteiro, linha;

  // Remove os dois primeiros elementos que são o numero de linhas e a linha que começa a execução
  pop();
  pop();

  while(!(lista.empty())){

    linha=stringToInt(top());
    pop();

    comando = top();    //copia o conteudo da lista para a variavel

    // Pega a instrução
    instr = comando[1]; //serpara o conteudo, para realizar o teste e descobrir o comando
    instr += comando[2];//serpara o conteudo, para realizar o teste e descobrir o comando
    inteiro = stringToInt(instr);
    interpretadorVector[linha][0] = inteiro;
    cout << inteiro << " ";
    // =================

    // Pega endereco de memoria
    ender = comando[3]; //separa o conteudo, para receber o endereço
    ender += comando[4];
    inteiro = stringToInt(ender);
    interpretadorVector[linha][1] = inteiro;
    cout << inteiro << " " << endl;
    //==================
    //i++;
    // Remove comentario
    pop();
    pop();//Descarta o comentário

  }
  return interpretadorVector;
}
