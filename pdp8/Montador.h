#ifndef MONTADOR_H
#define MONTADOR_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

 struct eds { // tipo para a tabela de simbolos definidos externamente
     int id;
     string symbol;
     int adress;
};

 struct mot {
    string i_name; // o tipo que vai ser a tabela de instruções de máquinas
    int n_operands;
    int m_code;
};

struct st {
    string symbol; // tipo para a tabela de símbolos
    int adress = -1;
};

struct lt {
    string literal; // tipo para a tabela de literais
    int adress = -1;
};

struct oc { // tipo da saida do montador
    int adress;
    int id;
    int opcode;
    int operand;
};


class Montador
{
    public:
        Montador();
        virtual ~Montador();
        void assemblerOne(string source); // realiza o passo 1
        string getInstruction(ifstream *f);
        string getLabel(string instruction);
        string getOperation(string instruction);
        string getOperand(string instruction);
        bool findPOT(string opcode);
        bool findMOT(string opcode);
        int getOperandValue(string operand);
        void processOperand(string operand);
        void insertTable(string label, int value);
        int getAbsoluteAdress(string operand);
        void printSymbolTable();
        void printLiteralTable();
        void setLiteralTable(int begin);
        void assemblerTwo(string source); // realiza o passo 2
        void generatedEDS();
        void printEDSTable();
        void generatedObjectCode(int m_position, string opcode, string operand);
        void assembleObjectCode(int m_position, int id, int m_opcode, int m_operand);
        void printObjectCode();
        void addLiteralPool();
        void generateERS();
        void printERS();
        vector<struct eds> getEDS();
        vector<struct st> getERS();
        vector<struct oc> getObjectCode();
        vector<struct mot> MOT; // tabela de instruções de máquina
    protected:
    private:
        ifstream file;

        vector<string> POT; // tabela de pseudo-instruções
        //vector<struct mot> MOT; // tabela de instruções de máquina
        vector<struct st> ST; // tabela de simbolos
        vector<struct lt> LT; // tabela de literais
        vector<struct eds> EDS; // tabela de simbolos definidos externamente
        vector<struct oc> objectCode; // estrutura que contém a saída do montador
        vector<struct st> ERS; // simbolos que podem ser referenciados em outros arquivos

        struct mot i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14,
            i15, i16, i17, i18, i19, i20, i21, i22, i23, i24, i25, i26, i27;


};

#endif // MONTADOR_H
