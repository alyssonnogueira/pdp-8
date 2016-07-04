#ifndef MONTADOR_H
#define MONTADOR_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Montador
{
    typedef struct mot {
        string i_name;
        int n_operands;
        int m_code;
    };

    typedef struct st {
        string symbol;
        int adress = -1;
    };

    typedef struct lt {
        string literal;
        int adress = -1;
    };

    public:
        Montador();
        virtual ~Montador();
        void assemblerOne(string source);
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
    protected:
    private:
        ifstream file;

        vector<string> POT;
        vector<struct mot> MOT;
        vector<struct st> ST;
        vector<struct lt> LT;

        struct mot i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14,
            i15, i16, i17, i18, i19, i20, i21, i22, i23, i24, i25, i26, i27;


};

#endif // MONTADOR_H
