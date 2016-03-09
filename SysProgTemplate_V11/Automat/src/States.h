/*
 * States.h
 *
 *  Created on: 29.10.2014
 *      Author: rebecca
 */

#ifndef STATES_H_
#define STATES_H_

/**
 * Die verschiedenen Zustände des Automats.
 */
enum State {PlusState, MinusState, StarState,
			ExclamationState, AndState, SemicolonState,
			OpenedBracketState, ClosedBracketState, OpenedCurlyState,
			ClosedCurlyState, OpenedSquareState, ClosedSquareState,
			SpaceState, IdentifierState, IntegerState, SmallerState, BiggerState, StartState, EqualState,
			DoublepointState, DoubleequalState, SmallerDoubleState, SmallerDoubleBiggerState,
			CommentStartState, CommentState, CommentFinishState, CommentEndState,
			FailState};

#endif /* STATES_H_ */
