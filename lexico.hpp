// Header Analisador Léxico
// lexico.h

#ifndef LEXICO_HPP
#define LEXICO_HPP

#include <iostream>
#include <string.h>
#include <fstream>
#include <list>
#include <stdio.h>

using namespace std;

class Lexico{
	public:
		Lexico(){ // Construtor default da classe
		}

		int lerEntrada(ifstream *arq){ // Realiza a leitura do arquivo de entrada separando os tokens em cada posição da lista
			char ch;
			string retorno;
			if(arq){	// Verifica se o ponteiro é válido
			  	while(arq->get(ch)){ // percorre o arquivo caracter a caracter
			  		if(ch == ';' || ch == '\n'){ // verifica se o caracter encontrado é um ; ou \n
			  			push(retorno);	// adiciona a string a ultima posicao da lista
			  			retorno = "";	// gera o conteúdo da string
			  		}else{
			  			retorno += ch; // Gera a string até achar um ; ou \n
			  		}
			  	}
				return 1;
			}else{
				return 0;
			}
		}

		void push(string valor){ // Adiciona uma string ao final da lista
			lista.push_back(valor);
		}
		void pop(){	// remove a primeira string da lista
			lista.pop_front();
		}
		string top(){ // retorna o valor no topo da lista
			return lista.front();
		}
		void imprimeLista(){ // imprime a lista
			for ( ptr = lista.begin(); ptr != lista.end(); ptr++ )
    			cout << *ptr << endl;
		}

        void identificaToken(){//   função de identifica os token presentes na lista

            string comando,sinal,instr,ender,totalDeLinhas,linhaInicial;
            int i;

            totalDeLinhas = top();
            cout << "Numero total de linhas do codigo: ";
            cout << top() << endl;// primeiro token representa o "tamanho do codigo"
            pop();

            linhaInicial = top();
            cout << "Linha inicial do codigo: ";
            cout << top() << endl;// segundo token representa a linha inicial do programa
            pop();


            //após identificar os dois primeiros tokens, ele entra em um padrao, que é o codigo
            //nesse padrão, o primeiro token representa a linha atuali do codigo
            //o segundo token é o codigo em sim, com sinal, comando (2 valores), e operando (2 valores)
            //o terceiro token é o comentario

            cout << "COMANDOS!!" << endl;

            while(!(lista.empty())){
                    //cout << "Linha" <<endl;
                    pop();

                    comando = top();    //copia o conteudo da lista para a variavel
                    sinal = comando[0]; //recebe o sinal
                    //cout << sinal <<endl;

                    instr = comando[1]; //serpara o conteudo, para realizar o teste e descobrir o comando
                    instr += comando[2];//serpara o conteudo, para realizar o teste e descobrir o comando
                    //cout << instr <<endl;

                    ender = comando[3]; //separa o conteudo, para receber o endereço
                    ender += comando[4];
                    //cout << ender <<endl;

                    //a partir daqui, inicia uma sequencia de ifs que identificam a instrução e o endereço
                    if(instr == "11"){
                        cout << "LDA " ;
                        cout << ender << endl;
                    }
                    if(instr == "12"){
                        cout << "STA " ;
                        cout << ender << endl;
                   }
                    if(instr == "21"){
                        cout << "ADD " ;
                        cout << ender << endl;
                   }
                    if(instr == "22"){
                        cout << "SUB " ;
                        cout << ender << endl;
                   }
                    if(instr == "23"){
                        cout << "MUL " ;
                        cout << ender << endl;
                   }
                    if(instr == "24"){
                        cout << "DIV " ;
                        cout << ender << endl;
                   }
                    if(instr == "25"){
                        cout << "REM " ;
                        cout << ender << endl;
                   }
                    if(instr == "29"){
                        cout << "REV " ;
                        cout << ender << endl;
                   }
                    if(instr == "31"){
                        cout << "INN " ;
                        cout << ender << endl;
                   }
                    if(instr == "41"){
                        cout << "PRN " ;
                        cout << ender << endl;
                   }
                    if(instr == "50"){
                        cout << "NOP " ;
                        cout << ender << endl;
                   }
                    if(instr == "51"){
                        cout << "JMP " ;
                        cout << ender << endl;
                   }
                    if(instr == "52"){
                        cout << "JLE " ;
                        cout << ender << endl;
                   }
                    if(instr == "53"){
                        cout << "JDZ " ;
                        cout << ender << endl;
                   }
                    if(instr == "54"){
                        cout << "JGT " ;
                        cout << ender << endl;
                   }
                    if(instr == "55"){
                        cout << "JEQ " ;
                        cout << ender << endl;
                   }
                    if(instr == "56"){
                        cout << "JLT " ;
                        cout << ender << endl;
                   }
                    if(instr == "57"){
                        cout << "JGE " ;
                        cout << ender << endl;
                   }
                    if(instr == "70"){
                        cout << "STP ";
                   }

                    pop();
                    cout << top() <<endl;
                    pop();

            }

        }

	protected:
		list<string> lista;				// Cria a lista léxica
		std::list<string>::iterator ptr;  // cria um iterador de float
        list<string> interpretadorLista;   // Cria interpretador da lista léxica
};

#endif
