// Header do Interpretador
// interpretador.hpp

#ifndef SIMULADOR_HPP
#define SIMULADOR_HPP

#include <iostream>
#include <string.h>
#include <fstream>
#include <list>
#include <stdio.h>
#include <vector>

using namespace std;


class Simulador{

    public:
		Simulador(); // Construtor default da classe

		 void processaCodigo(vector < vector<int> > matrizComandos);
		 int stringToInt(string str);

};
#endif
