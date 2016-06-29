/*
 * Automat.cpp
 *
 *  Created on: 16.10.2014
 *      Author: Rebecca Sigmund
 */

#include "Automat.h"
#include <stdio.h>

/**
 * Konstruktor, um einen neuen Automaten im Startzustand zu erstellen.
 */
Automat::Automat() {
	lastAcceptedState = FailState;
	lastAcceptedStateBuffer = FailState;
	startState = StartState;
	currentState = startState;
	currentEvent = EmptyTrans;
	stepsBack = 0;
	line = 1;			//zeile-> line 31.03.15
	column = 1;        //spalte -> column 31.03.15
	startColumn = 1;   //startSpalte -> startColumn 31.03.15

	//Transformationen festlegen
	transformationTable[0] = new Transformation(StartState, SpaceState, EmptyTrans);
	transformationTable[1] = new Transformation(StartState, SpaceState, NewLineTrans);
	transformationTable[2] = new Transformation(StartState, IdentifierState, LetterTrans);
	transformationTable[3] = new Transformation(StartState, IntegerState, DigitTrans);
	transformationTable[4] = new Transformation(StartState, EqualState, EqualTrans);
	transformationTable[5] = new Transformation(StartState, PlusState, PlusTrans);
	transformationTable[6] = new Transformation(StartState, MinusState, MinusTrans);
	transformationTable[7] = new Transformation(StartState, ExclamationState, ExclamationTrans);
	transformationTable[8] = new Transformation(StartState, AndState, AndTrans);
	transformationTable[9] = new Transformation(StartState, SemicolonState, SemicolonTrans);
	transformationTable[10] = new Transformation(StartState, OpenedBracketState, OpenedBracketTrans);
	transformationTable[11] = new Transformation(StartState, ClosedBracketState, ClosedBracketTrans);
	transformationTable[12] = new Transformation(StartState, OpenedSquareState, OpenedSquareTrans);
	transformationTable[13] = new Transformation(StartState, ClosedSquareState, ClosedSquareTrans);
	transformationTable[14] = new Transformation(StartState, OpenedCurlyState, OpenedCurlyTrans);
	transformationTable[15] = new Transformation(StartState, ClosedCurlyState, ClosedCurlyTrans);
	transformationTable[16] = new Transformation(StartState, DoublepointState, DoublepointTrans);
	transformationTable[17] = new Transformation(StartState, CommentStartState, SlashTrans);
	transformationTable[18] = new Transformation(StartState, StarState, StarTrans);
	transformationTable[19] = new Transformation(IdentifierState, IdentifierState, DigitTrans);
	transformationTable[20] = new Transformation(IntegerState, IntegerState, DigitTrans);
	transformationTable[21] = new Transformation(SmallerState, SmallerDoubleState, DoublepointTrans);
	transformationTable[22] = new Transformation(DoublepointState, DoubleequalState, EqualTrans);
	transformationTable[23] = new Transformation(SmallerDoubleState, SmallerDoubleBiggerState, BiggerTrans);
	transformationTable[24] = new Transformation(CommentFinishState, CommentFinishState, StarTrans);
	transformationTable[25] = new Transformation(IdentifierState, IdentifierState, LetterTrans);
	transformationTable[26] = new Transformation(CommentStartState, CommentState, StarTrans);
	transformationTable[27] = new Transformation(CommentState, CommentFinishState, StarTrans);
	transformationTable[28] = new Transformation(CommentFinishState, CommentEndState, SlashTrans);
	transformationTable[29] = new Transformation(CommentState, CommentState, LetterTrans);
	transformationTable[30] = new Transformation(CommentState, CommentState, DigitTrans);
	transformationTable[31] = new Transformation(CommentState, CommentState, PlusTrans);
	transformationTable[32] = new Transformation(CommentState, CommentState, MinusTrans);
	transformationTable[33] = new Transformation(CommentState, CommentState, ExclamationTrans);
	transformationTable[34] = new Transformation(CommentState, CommentState, AndTrans);
	transformationTable[35] = new Transformation(CommentState, CommentState, SemicolonTrans);
	transformationTable[36] = new Transformation(CommentState, CommentState, OpenedBracketTrans);
	transformationTable[37] = new Transformation(CommentState, CommentState, ClosedBracketTrans);
	transformationTable[38] = new Transformation(CommentState, CommentState, OpenedSquareTrans);
	transformationTable[39] = new Transformation(CommentState, CommentState, ClosedSquareTrans);
	transformationTable[40] = new Transformation(CommentState, CommentState, OpenedCurlyTrans);
	transformationTable[41] = new Transformation(CommentState, CommentState, ClosedCurlyTrans);
	transformationTable[42] = new Transformation(CommentState, CommentState, SmallerTrans);
	transformationTable[43] = new Transformation(CommentState, CommentState, BiggerTrans);
	transformationTable[44] = new Transformation(CommentState, CommentState, EqualTrans);
	transformationTable[45] = new Transformation(CommentState, CommentState, DoublepointTrans);
	transformationTable[46] = new Transformation(CommentState, CommentState, EmptyTrans);
	transformationTable[47] = new Transformation(CommentState, CommentState, NewLineTrans);
	transformationTable[48] = new Transformation(CommentState, CommentState, SlashTrans);
	transformationTable[49] = new Transformation(CommentFinishState, CommentState, LetterTrans);
	transformationTable[50] = new Transformation(CommentFinishState, CommentState, DigitTrans);
	transformationTable[51] = new Transformation(CommentFinishState, CommentState, PlusTrans);
	transformationTable[52] = new Transformation(CommentFinishState, CommentState, MinusTrans);
	transformationTable[53] = new Transformation(CommentFinishState, CommentState, ExclamationTrans);
	transformationTable[54] = new Transformation(CommentFinishState, CommentState, AndTrans);
	transformationTable[55] = new Transformation(CommentFinishState, CommentState, SemicolonTrans);
	transformationTable[56] = new Transformation(CommentFinishState, CommentState, OpenedBracketTrans);
	transformationTable[57] = new Transformation(CommentFinishState, CommentState, ClosedBracketTrans);
	transformationTable[58] = new Transformation(CommentFinishState, CommentState, OpenedSquareTrans);
	transformationTable[59] = new Transformation(CommentFinishState, CommentState, ClosedSquareTrans);
	transformationTable[60] = new Transformation(CommentFinishState, CommentState, OpenedCurlyTrans);
	transformationTable[61] = new Transformation(CommentFinishState, CommentState, ClosedCurlyTrans);
	transformationTable[62] = new Transformation(CommentFinishState, CommentState, SmallerTrans);
	transformationTable[63] = new Transformation(CommentFinishState, CommentState, BiggerTrans);
	transformationTable[64] = new Transformation(CommentFinishState, CommentState, EqualTrans);
	transformationTable[65] = new Transformation(CommentFinishState, CommentState, DoublepointTrans);
	transformationTable[66] = new Transformation(CommentFinishState, CommentState, EmptyTrans);
	transformationTable[67] = new Transformation(CommentFinishState, CommentState, NewLineTrans);
	transformationTable[68] = new Transformation(StartState, SmallerState, SmallerTrans);
	transformationTable[69] = new Transformation(StartState, BiggerState, BiggerTrans);
	transformationTable[70] = new Transformation(CommentState, CommentState, FailTrans);
	transformationTable[71] = new Transformation(CommentFinishState, CommentState, FailTrans);


}
 
Automat::~Automat() {
	for (int i = 71; i >= 0; i--) {
		delete transformationTable[i];
	}


}

/**
 * Gibt zurück, ob der nächste übergebene Buchstabe akzeptiert ist
 */
bool Automat::isOk(char nextChar) {
	bool ok = false;
	isSignal(nextChar);
	ok = searchUseTransformation();
	if(ok) {
		if(isAccepted() || currentState == DoublepointState) {
			lastAcceptedState = currentState;
			stepsBack = 0;
		}
		else {
			stepsBack++;
		}
	}
	return ok;
}

/**
 * Gibt zurück, ob sich der Automat momentan in einem akzeptierten Zustand befindet.
 */
bool Automat::isAccepted() {
	if((currentState == IdentifierState) || (currentState == IntegerState) || (currentState == PlusState)
			|| (currentState == SmallerState) || (currentState == SpaceState) || (currentState == MinusState)
			|| (currentState == StarState) || (currentState == BiggerState)
			|| (currentState == EqualState) || (currentState == DoubleequalState) || (currentState == SmallerDoubleBiggerState)
			|| (currentState == ExclamationState) || (currentState == AndState) || (currentState == SemicolonState)
			|| (currentState == OpenedBracketState) || (currentState == ClosedBracketState) || (currentState == OpenedSquareState)
			|| (currentState == ClosedSquareState) || (currentState == OpenedCurlyState) || (currentState == ClosedCurlyState)
			|| (currentState == CommentEndState) || (currentState == CommentStartState)){
		return true;
	}
	return false;
}

/**
 * Setzt currentEvent auf den richtigen Typ. Unterscheidet zwischen Buchstabe,
 * Ziffer und verschiedenen Symbolen.
 */
void Automat::isSignal(char nextChar) {
	currentEvent = FailTrans;
	int myChar = nextChar;
	//printf("Intwert zu char %c %d \n", nextChar, myChar);
	if ((nextChar >= 65 && nextChar <= 90) || (nextChar >= 97 && nextChar <= 122)) {
		currentEvent = LetterTrans;
	}
	if (nextChar >= 48 && nextChar <= 57) {
		currentEvent = DigitTrans;
	}
	switch(nextChar) {
		case('<') : currentEvent = SmallerTrans;
			break;
		case('>') : currentEvent = BiggerTrans;
			break;
		case('=') : currentEvent = EqualTrans;
			break;
		case(':') : currentEvent = DoublepointTrans;
			break;
		case(' ') : currentEvent = EmptyTrans;
			break;
		case('\n') : currentEvent = NewLineTrans;
			break;
		/*case('\r\n') : currentEvent = NewLineTrans;
			break;
		case('\015\012') : currentEvent = NewLineTrans;
			break; */
		case(9) : currentEvent = EmptyTrans;
			break;
		case('\015') : currentEvent = EmptyTrans;
			break;
		case(15) : currentEvent = EmptyTrans;
			break;
		case('\0') : currentEvent = EmptyTrans;
			break;
		case('/') : currentEvent = SlashTrans;
			break;
		case('*') : currentEvent = StarTrans;
			break;
		case('+') : currentEvent = PlusTrans;
			break;
		case('-') : currentEvent = MinusTrans;
			break;
		case('!') : currentEvent = ExclamationTrans;
			break;
		/*case('&') : currentEvent = AndTrans;
			break;*/
		case('&') : currentEvent = AndTrans;
			break;
		case(';') : currentEvent = SemicolonTrans;
			break;
		case('(') : currentEvent = OpenedBracketTrans;
			break;
		case(')') : currentEvent = ClosedBracketTrans;
			break;
		case('[') : currentEvent = OpenedSquareTrans;
			break;
		case(']') : currentEvent = ClosedSquareTrans;
			break;
		case('{') : currentEvent = OpenedCurlyTrans;
			break;
		case('}') : currentEvent = ClosedCurlyTrans;
			break;

	}
}

/**
 * Prüft, ob es einen gültigen Übergang mit currentEvent gibt
 * und ändert gegebenenfals den aktuellen Zustand.
 */
bool Automat::searchUseTransformation() {
	bool richtig = false;
	for(unsigned int i = 0; i < 72; i++) { //transformationTable size?
		if(transformationTable[i]->getNeededState() == currentState
				&& transformationTable[i]->getNeededSignal() == currentEvent) {
			currentState = transformationTable[i]->getNextState();
			//spalte++;

			if(currentEvent == NewLineTrans) {
				line++;
				column = 1;
			}
			else if (currentState == CommentEndState) {
				column++;
				lengthLexem = 0;
			}
			else if(currentEvent != EmptyTrans) {
				column++;
				lengthLexem++;
			}
			else {
				column++;
			}
			return true;
		}
	}
	if(currentEvent == FailTrans && currentState == StartState) {
		column++;
		lengthLexem++;
	}
	return false;
}

/**
 *Gibt den letzten akzeptierten Zustand zurück.
 */
Tokentyp Automat::getLastAcceptedState() {
	Tokentyp tokentyp = FailToken ;
	switch(lastAcceptedState) {
		case(IdentifierState) : tokentyp = IdentifierToken;
		break;
		case(IntegerState) : tokentyp = IntegerToken;
		break;
		case(PlusState) : tokentyp = PlusToken;
		break;
		case(MinusState) : tokentyp = MinusToken;
		break;
		case(StarState) : tokentyp = MultiplyToken;
		break;
		case(CommentStartState) : tokentyp = DivideToken;
		break;
		case(SmallerState) : tokentyp = SmallToken;
		break;
		case(BiggerState) : tokentyp = BigToken;
		break;
		case(EqualState) : tokentyp = EqualsToken;
		break;
		case(DoubleequalState) : tokentyp = DoubleEqualsToken;
		break;
		case(SmallerDoubleBiggerState) : tokentyp = SmallerDoubleBiggerToken;
		break;
		case(ExclamationState) : tokentyp = ExclamationToken;
		break;
		case(AndState) : tokentyp = AndToken;
		break;
		case(SemicolonState) : tokentyp = SemicolonToken;
		break;
		case(OpenedBracketState) : tokentyp = OpenBracketToken;
		break;
		case(ClosedBracketState) : tokentyp = CloseBracketToken;
		break;
		case(OpenedSquareState) : tokentyp = OpenSquareToken;
		break;
		case(ClosedSquareState) : tokentyp = CloseSquareToken;
		break;
		case(OpenedCurlyState) : tokentyp = OpenCurlyToken;
		break;
		case(ClosedCurlyState) : tokentyp = CloseCurlyToken;
		break;
		case(SpaceState) : tokentyp = EmptyToken;
		break;
		case(CommentEndState) : tokentyp = EmptyToken;
		break;
	}

	if(lastAcceptedState != SpaceState && lastAcceptedState != CommentEndState && ( lastAcceptedState != FailState || (lastAcceptedState == FailState && currentState ==  StartState))){
			startColumn = column - lengthLexem;
		}
	else {
			startColumn = column;
	}


	currentState = StartState;
	lastAcceptedState = FailState;
	return tokentyp;
}

/**
 * Gibt zurück wie viele Schritte zum letzten akzeptierten Zustand zurück gegangen werden müssen.
 */
int Automat::getStepsBack() {
	int back = stepsBack;
	column = column - stepsBack;
	stepsBack = 0;
	return back;
}

/**
 * Gibt die Zeile des Tokens zurück.
 */
// geändert: getZeile -> getLine 31.03.15
int Automat::getLine() {
	return line;
}

/**
 * Gibt die Spalte des Tokens zurück.
 */
// geändert: getSpalte -> getColumn
int Automat::getColumn() {
	lengthLexem = 0;
	//hier umgedreht
	return startColumn;
}
