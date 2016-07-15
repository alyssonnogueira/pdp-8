// Construção das funções declaradas em processador_macros.hpp

#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include "processador_macros.hpp"

using namespace std;

Processador_macros::Processador_macros(){ } // Construtor default da classe

int Processador_macros::lerEntrada(ifstream *arq){ // Realiza a leitura do arquivo de entrada separando os tokens em cada posição da entrada
  char ch;
  string retorno;
  if(arq){  // Verifica se o ponteiro é válido
    while(arq->get(ch)){ // percorre o arquivo caracter a caracter
      if(ch == '_' || ch == '\n' || ch == '<' || ch == '>' || ch == ' '){ // verifica se o caracter encontrado é um ; ou \n
        switch(ch){
          case '<':
            push(retorno);
            push("<");
            break;
          case '>':
            push(retorno);
            push(">");
            break;
          default:
            if(retorno != "")
                push(retorno);
            break;
        }          
        retorno = ""; // zera o conteúdo da string
      }else{
        retorno += ch; // Gera a string até achar um _ ou \n
      }
    }
    return 1;
  }else{
    return 0;
  }
}

void Processador_macros::passTwo(){
  int aux;
  int aux2;
  for(int i=0; i < saida.size(); i++){
    for(int j=0; j < nomes.size(); j++){
      if(saida[i]==nomes[j]){
        troca(i+1,j+1);
        aux=j+1;
        aux2=i+1;
        while(nomes[aux]!= "" && aux2 != saida.size()){
          saida[aux2].erase();
          aux++;
          aux2++;
        }
      }
    }
  } 
}

void Processador_macros::troca(int i, int j){
  for(int k=j; k<nomes.size(); k++){
    for(int t=0; t < macro.size(); t++){
      if(macro[t]==nomes[k] && macro[t]!= ""){
        macro[t]=saida[i];
      }
    }
    if(i < saida.size()-1){
      i++;
    }
  }
}

void Processador_macros::passOne(){
    int t=0;
    for(int i = 0; i < entrada.size(); i++){
      if(entrada[i] == "DEFINE"){
        t=i+1;
        while(entrada[t] != "<"){
          nomes.push_back(entrada[t]);
          t++;
        }
        nomes.push_back("_");
        for(int j = i; entrada[j] != ">"; j++){
          macro.push_back(entrada[j]);
          entrada[j].erase();
          t=j;
        }
        macro.push_back(">");
        entrada[t+1].erase();
      }   
    }
    for(int i = 0; i < entrada.size(); i++){
      if(entrada[i] != ""){
        saida.push_back(entrada[i]);
      }
    }
}

void Processador_macros::saidaTeste(){
  int t=0;
  for(int i=0; i < saida.size(); i++){
    for(int j=0; j < nomes.size(); j++){
      if(saida[i]==nomes[j]){
       saida[i].erase();
       for(int k = j; k < macro.size();k++){
          if(macro[k]==">")
            t=0;
          if(t==1){
            saida.push_back(macro[k]);
          }
          if(macro[k]=="<"){
            t=1;
          }
       }
       return;
      }
    }
  } 
}

void Processador_macros::expansaoFinal(){
  outFile.open("saida.txt");
  for(int i=0; i < saida.size(); i++){
    if(saida[i]!=""){
      outFile << saida[i] << " ";
    }
  }
}

void Processador_macros::push(string valor){ // Adiciona uma string ao final da entrada
  entrada.push_back(valor);
}

void Processador_macros::imprimeEntrada(){ // imprime a entrada
  for (int i = 0; i != entrada.size(); i++ )
    cout << entrada[i]<< endl;
}
    
void Processador_macros::imprimeSaida(){ // imprime a entrada
  for (int i = 0; i != saida.size(); i++ )
    cout << saida[i]<< endl;
}

void Processador_macros::imprimeMacro(){ // imprime a entrada
  for (int i = 0; i != macro.size(); i++ )
    cout << macro[i]<< endl;
}

void Processador_macros::imprimeNomes(){ // imprime a entrada
  for (int i = 0; i != nomes.size(); i++ )
    cout << nomes[i]<< endl;
}