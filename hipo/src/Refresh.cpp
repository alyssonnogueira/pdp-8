/*
 * Refresh.cpp
 *
 *  Created on: 05/06/2016
 *      Author: alysson
 */
#include <fstream>
#include <cmath>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <gtkmm/messagedialog.h>
#include <vector>
#include "Refresh.h"
#include "step.h"

using namespace std;

Refresh::Refresh() {
	// TODO Auto-generated constructor stub

}

Refresh::~Refresh() {
	// TODO Auto-generated destructor stub
}

void Refresh::Refresh_StepWindow(void *ptr_step, int id, int operacao, int operando){
	Step *mStep = reinterpret_cast<Step*>(ptr_step);
	mStep->RefreshScreen(id, operacao, operando);
}

int Refresh::Refresh_NewValue(void *ptr_step, string label){
	Step *mStep = reinterpret_cast<Step*>(ptr_step);
	int retorno = mStep->NewValue(label);
	return retorno;
}
