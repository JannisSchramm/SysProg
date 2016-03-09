/*
 * Transformation.cpp
 *
 *  Created on: 04.11.2014
 *      Author: jannis
 */

#include "Transformation.h"


/**
 * Erstellt einen neuen Übergang.
 */
Transformation::Transformation(State currentState, State nextState,
			Signal neededSignal) {
	this->neededState = currentState;
	this->nextState = nextState;
	this->neededSignal = neededSignal;
}


Transformation::~Transformation() {


}


State Transformation::getNeededState() {
	return neededState;
}

State Transformation::getNextState() {
	return nextState;
}

Signal Transformation::getNeededSignal() {
	return neededSignal;
}
