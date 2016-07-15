#include "Montador.h"

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <vector>


using namespace std;

Montador::Montador()
{
    this->POT.push_back("PAGE");
    this->POT.push_back("*");
    this->POT.push_back("$");

    this->i0.i_name = "AND";this->i0.n_operands = 1;this->i0.m_code = 0;this->i1.i_name = "TAD";this->i1.n_operands = 1;this->i1.m_code = 1;
    this->i2.i_name = "ISZ";this->i2.n_operands = 1;this->i2.m_code = 2;this->i3.i_name = "DCA";this->i3.n_operands = 1;this->i3.m_code = 3;
    this->i4.i_name = "JMS";this->i4.n_operands = 1;this->i4.m_code = 4;this->i5.i_name = "JMP";this->i5.n_operands = 1;this->i5.m_code = 5;
    this->i6.i_name = "CLA";this->i6.n_operands = 0;this->i6.m_code = 6;this->i7.i_name = "CMA";this->i7.n_operands = 0;this->i7.m_code = 7;
    this->i8.i_name = "RAR";this->i8.n_operands = 0;this->i8.m_code = 8;this->i9.i_name = "RAL";this->i9.n_operands = 0;this->i9.m_code = 9;
    this->i10.i_name = "RTR";this->i10.n_operands = 0;this->i10.m_code = 10;this->i11.i_name = "RTL";this->i11.n_operands = 0;this->i11.m_code = 11;
    this->i12.i_name = "IAC";this->i12.n_operands = 0;this->i12.m_code = 12;this->i13.i_name = "NOP";this->i13.n_operands = 0;this->i13.m_code = 13;
    this->i14.i_name = "SPA";this->i14.n_operands = 0;this->i14.m_code = 14;this->i15.i_name = "SMA";this->i15.n_operands = 0;this->i15.m_code = 15;
    this->i16.i_name = "SNA";this->i16.n_operands = 0;this->i16.m_code = 16;this->i17.i_name = "SZA";this->i17.n_operands = 0;this->i17.m_code = 17;
    this->i18.i_name = "SKP";this->i18.n_operands = 0;this->i18.m_code = 18;this->i19.i_name = "OSR";this->i19.n_operands = 0;this->i19.m_code = 19;
    this->i20.i_name = "HLT";this->i20.n_operands = 0;this->i20.m_code = 20;this->i21.i_name = "IOK";this->i21.n_operands = 0;this->i21.m_code = 21;
    this->i22.i_name = "OOM";this->i22.n_operands = 0;this->i22.m_code = 22;this->i23.i_name = "JMPI";this->i23.n_operands = 1;this->i23.m_code = 23;
    this->i24.i_name = "CLL";this->i24.n_operands = 0;this->i24.m_code = 24;this->i25.i_name = "CML";this->i25.n_operands = 0;this->i25.m_code = 25;
    this->i26.i_name = "SZL";this->i26.n_operands = 0;this->i26.m_code = 26;this->i27.i_name = "SNL";this->i27.n_operands = 0;this->i27.m_code = 27;

    this->MOT.push_back(i0);this->MOT.push_back(i1);this->MOT.push_back(i2);this->MOT.push_back(i3);this->MOT.push_back(i4);this->MOT.push_back(i5);this->MOT.push_back(i6);
    this->MOT.push_back(i7);this->MOT.push_back(i8);this->MOT.push_back(i9);this->MOT.push_back(i10);this->MOT.push_back(i11);this->MOT.push_back(i12);this->MOT.push_back(i13);
    this->MOT.push_back(i14);this->MOT.push_back(i15);this->MOT.push_back(i16);this->MOT.push_back(i17);this->MOT.push_back(i18);this->MOT.push_back(i19);this->MOT.push_back(i20);
    this->MOT.push_back(i21);this->MOT.push_back(i22);this->MOT.push_back(i23);this->MOT.push_back(i24);this->MOT.push_back(i25);this->MOT.push_back(i26);this->MOT.push_back(i27);
}

Montador::~Montador()
{
    //dtor
}

void Montador::assemblerOne(string source) {
    int LC = 0;

    this->file.open(source.c_str());

    if (!this->file){
        cout << "Unable to open file!" << endl;
        return ;
  	}


    while(!this->file.eof()) {
        string instruction = this->getInstruction(&this->file);
        string label = this->getLabel(instruction);
        string opcode = this->getOperation(instruction);
        string operand = this->getOperand(instruction);

        this->processOperand(operand);

        if(this->findPOT(opcode)) {
            if(opcode[0] == '*') {
                LC = this->getOperandValue(opcode.erase(0, 1));
            }
            else if(opcode == "PAGE") {
                 LC += this->getAbsoluteAdress(operand);
            }
            else if(opcode == "$") {
                this->file.close();
                this->setLiteralTable(LC);
                this->generatedEDS();
                assemblerTwo(source);
                return;
            }
            else {
                this->insertTable(label, LC);
                LC++;
            }
        }
        else {
            if(this->findMOT(opcode)) {
                if(label.size() != 0) {
                    this->insertTable(label, LC);
                }
                LC++;
            }
            else {
                cout << opcode << "Invalid opcode!" << "\n";
                //this->file.close();
                //return;
            }
        }
  	}
}

void Montador::assemblerTwo(string source) {
    int LC = 0;

    this->file.open(source.c_str());

    if (!this->file){
        cout << "Unable to open file!" << endl;
        return ;
  	}

  	while(!this->file.eof()) {
        string instruction = this->getInstruction(&this->file);
        string opcode = this->getOperation(instruction);
        string operand = this->getOperand(instruction);

        if(opcode[0] == '*') {
            LC = this->getOperandValue(opcode.erase(0, 1));
        }
        else if(opcode == "PAGE") {
            LC += this->getAbsoluteAdress(operand);
        }
        else if(opcode == "$") {
            this->addLiteralPool();
            this->generateERS();
            this->file.close();
            return;
        }
        else {
            this->generatedObjectCode(LC, opcode, operand);
            LC++;
        }
  	}
}

vector<struct eds> Montador::getEDS() {
    return this->EDS;
}

vector<struct st> Montador::getERS() {
    return this->ERS;
}

vector<struct oc> Montador::getObjectCode() {
    return this->objectCode;
}

void Montador::printERS() {
    for(int i = 0; i < this->ERS.size(); i++) {
        cout << this->ERS[i].symbol << "  " << this->ERS[i].adress << "\n";
    }
}

void Montador::generateERS() {
    for(int i = 0; i < this->ST.size(); i++) {
        if(this->ST[i].adress != -1) {
            struct st s;
            s.symbol = this->ST[i].symbol;
            s.adress = this->ST[i].adress;
            this->ERS.push_back(s);
        }
    }
}

void Montador::addLiteralPool() {
    for(int i = 0; i < this->LT.size(); i++) {
        struct oc l;
        l.adress = this->LT[i].adress;
        l.id = -1;
        l.opcode = this->getOperandValue(this->LT[i].literal.substr(1, this->LT[i].literal.size() - 2));
        l.operand = 0;
        this->objectCode.push_back(l);
    }
}

void Montador::printObjectCode() {
    for(int i = 0; i < this->objectCode.size(); i++) {
        cout << objectCode[i].adress << "\t";
        cout << objectCode[i].id << "\t";
        cout << objectCode[i].opcode << "\t";
        cout << objectCode[i].operand << "\n";
    }
}

void Montador::assembleObjectCode(int m_position, int id, int m_opcode, int m_operand) {
    struct oc o;

    o.adress = m_position;
    o.id = id;
    o.opcode = m_opcode;

    if(m_operand == -1) {
        o.operand = 0;
    }
    else {
        o.operand = m_operand;
    }

    this->objectCode.push_back(o);
}

void Montador::generatedObjectCode(int m_position, string opcode, string operand) {
    int m_opcode, m_operand, id;

    if(opcode[0] >= 48 && opcode[0] <= 57) {
        m_opcode = this->getOperandValue(opcode);
        id = -1;
    }
    else {
        for(int i = 0; i < this->MOT.size(); i++) {
            if(this->MOT[i].i_name == opcode) {
                m_opcode = this->MOT[i].m_code;
                id = 0;
                break;
            }
        }
    }

    if(operand.size() == 0) {
        m_operand = -1;
    }
    else {
        if(operand[0] == '(') {
            for(int i = 0; i < this->LT.size(); i++) {
                if(this->LT[i].literal == operand) {
                    m_operand = this->LT[i].adress;
                break;
                }
            }
        }
        else if(opcode[0] >= 48 && opcode[0] <= 57) {
            m_operand = this->getOperandValue(operand);
        }
        else {
            for(int i = 0; i < this->ST.size(); i++) {
                if(this->ST[i].symbol == operand) {
                    m_operand = this->ST[i].adress;
                    if(m_operand == -1) {
                        for(int i = 0; i < this->EDS.size(); i++) {
                            if(this->EDS[i].symbol == operand) {
                                id = this->EDS[i].id;
                            }
                        }
                    }
                    break;
                }
            }
        }
    }

    this->assembleObjectCode(m_position, id, m_opcode, m_operand);
}

void Montador::printEDSTable() {
    for(int i = 0; i < this->EDS.size(); i++) {
        cout << this->EDS[i].id << " " << this->EDS[i].symbol << "  " << this->EDS[i].adress << "\n";
    }
}

void Montador::generatedEDS() {
    for(int i = 0; i < this->ST.size(); i++) {
        if(this->ST[i].adress == -1) {
            struct eds e;
            e.id = this->EDS.size() + 1;
            e.symbol = this->ST[i].symbol;
            e.adress = this->ST[i].adress;
            this->EDS.push_back(e);
        }
    }
}

void Montador::setLiteralTable(int begin) {
    for(int i = 0; i < this->LT.size(); i++) {
        this->LT[i].adress = begin + i;
    }
}

void Montador::printLiteralTable() {
    for(int i = 0; i < this->LT.size(); i++) {
        cout << this->LT[i].literal << "  " << this->LT[i].adress << "\n";
    }
}

void Montador::printSymbolTable() {
    for(int i = 0; i < this->ST.size(); i++) {
        cout << this->ST[i].symbol << "  " << this->ST[i].adress << "\n";
    }
}
string Montador::getInstruction(ifstream *f) {
    string instruction;
    char ch;
    bool flag = true;

    while(f->get(ch)) {
        if(ch == ';' || ch == '\n') {
            return instruction;
        }else if(ch == '/'){
            flag = false;
        }
        else if(flag){
            instruction += ch;
        }
    }
}

string Montador::getLabel(string instruction) {
    string label;
    char ch;

    for(int i = 0; i < instruction.size(); i++) {
        ch = instruction[i];
        if(ch == ',') {
            break;
        }
        else if(ch == ' ') {

        }
        else {
            label += ch;
        }
    }

    if(ch == ',') {
        return label;
    }
    else {
        return "";
    }
}

string Montador::getOperation(string instruction) {
    string operation;
    char ch;
    int begin = 0;
    bool ignore = true;

    if(this->getLabel(instruction).size() != 0) {
        begin = instruction.find_last_of(',') + 1;
    }

    for(int i = begin; i < instruction.size(); i++) {
        ch = instruction[i];
        if(ch == ' ' && ignore) {

        }
        else {
            if(ch == ' ') {
                break;
            }
            operation += ch;
            ignore = false;
        }
    }

    return operation;
}

string Montador::getOperand(string instruction) {
    string operand;
    char ch;
    int begin;
    bool ignore = true;

    begin = instruction.rfind(this->getOperation(instruction))
        + this->getOperation(instruction).size() + 1;

    for(int i = begin; i < instruction.size(); i++) {
        ch = instruction[i];
        if(ch == ' ' && ignore) {

        }
        else {
            if(ch == ' ') {
                break;
            }
            operand += ch;
            ignore = false;
        }
    }

    return operand;
}

bool Montador::findPOT(string opcode) {
    if(opcode[0] >= 48 && opcode[0] <= 57) {
        return true;
    }
    if(opcode[0] == '*') {
        return true;
    }
    if(opcode == "PAGE") {
        return true;
    }
    if(opcode == "$") {
        return true;
    }

    return false;
}

bool Montador::findMOT(string opcode) {
    for(int i = 0; i < this->MOT.size(); i++) {
        if(this->MOT[i].i_name == opcode) {
            return true;
        }
    }

    return false;
}

int Montador::getOperandValue(string operand) {
    return atoi(operand.c_str());
}

void Montador::processOperand(string operand) {
    if(operand.size() == 0) {
        return;
    }
    if(operand[0] == '(') {
        for(int i = 0; i < this->LT.size(); i++) {
            if(this->LT[i].literal == operand) {
                return;
            }
        }

        struct lt l;

        l.literal = operand;
        this->LT.push_back(l);
    }
    else if(operand[0] >= 48 && operand[0] <=57) {

    }
    else {

        for(int i = 0; i < this->ST.size(); i++) {
            if(this->ST[i].symbol == operand) {
                return;
            }
        }

        struct st s;

        s.symbol = operand;
        this->ST.push_back(s);
    }
}

void Montador::insertTable(string label, int value) {
    this->processOperand(label);

    for(int i = 0; i < this->ST.size(); i++) {
        if(this->ST[i].symbol == label) {
            this->ST[i].adress = value;
            return;
        }
    }
}

int Montador::getAbsoluteAdress(string operand) {
    if(operand[0] == '0') {
        return 0;
    }
    if(operand[0] == '1') {
        return 128;
    }
    if(operand[0] == '2') {
        return 256;
    }
    if(operand[0] == '3') {
        return 384;
    }
}
