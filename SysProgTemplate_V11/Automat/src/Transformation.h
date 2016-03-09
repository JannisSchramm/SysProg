/*
 * Transformations.h
 *
 *  Created on: 04.11.2014
 *      Author: jannis
 */

#ifndef TRANSFORMATIONS_H_
#define TRANSFORMATIONS_H_

#include "States.h"

enum Signal {LetterTrans, DigitTrans, SmallerTrans, BiggerTrans, EqualTrans, DoublepointTrans, EmptyTrans, NewLineTrans, SlashTrans,
	StarTrans, PlusTrans, MinusTrans, ExclamationTrans, AndTrans, SemicolonTrans, OpenedBracketTrans, ClosedBracketTrans,
				OpenedSquareTrans, ClosedSquareTrans, OpenedCurlyTrans, ClosedCurlyTrans, FailTrans};

class Transformation {


public:

	Transformation(State currentState, State nextState, Signal neededSignal);
	virtual ~Transformation();
	State getNeededState();
	State getNextState();
	Signal getNeededSignal();
private:
	State neededState;
	State nextState;
	Signal neededSignal;
};





#endif /* TRANSFORMATIONS_H_ */
