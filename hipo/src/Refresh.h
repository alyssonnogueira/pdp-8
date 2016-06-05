/*
 * Refresh.h
 *
 *  Created on: 05/06/2016
 *      Author: alysson
 */
#include "step.h"

#ifndef REFRESH_H_
#define REFRESH_H_

class Refresh {
public:
	Refresh();
	virtual ~Refresh();
	void Refresh_StepWindow(void *ptr_step, int id, int operacao, int operando);
	int Refresh_NewValue(void *ptr_p, string label);

};

#endif /* REFRESH_H_ */
