/*
 * Automat.h
 *
 *  Created on: 16.10.2014
 *      Author: rebecca
 */

#ifndef AUTOMAT_H_
#define AUTOMAT_H_
#include "States.h"
#include "Event.h"
#include "Transformation.h"

class Automat {
public:
	Automat();
	virtual ~Automat();
	bool isOk(char nextChar);
	Tokentyp getLastAcceptedState();
	int getStepsBack();
	int getLine();
	int getColumn();
private:
	Signal currentEvent;
	State currentState;
	State lastAcceptedState;
	State lastAcceptedStateBuffer;
	State startState;
	Transformation* transformationTable[72];
	int line;
	int column;
	int startColumn;
	int lengthLexem;
	int stepsBack;
	void isSignal(char nextChar);
	bool isAccepted();
	bool searchUseTransformation();

};

#endif /* AUTOMAT_H_ */
