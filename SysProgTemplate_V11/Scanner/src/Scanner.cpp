/*
 * Scanner.cpp
 *
 *  Created on: 16.10.2014
 *      Author: Rebecca Sigmund
 */

#include "Scanner.h"
/**
 * Konstruktor für einen neuen Scanner und dieser erstellt einen Buffer,
 * eine Symboltabelle und einen Automaten.
 */
Scanner::Scanner(char* input) {
	arrayLength = 1024;
	automat = new Automat();
	buffer = new Buffer(arrayLength, input);
	temporaryChars = new char[arrayLength];
	resetTemporaryChars();
	symboltable = new Symboltable();
	position = 0;

}

Scanner::~Scanner(){
	delete automat;
	delete buffer;
	delete symboltable;
	delete temporaryChars;
}

Symboltable* Scanner::getSymboltable() {
	return symboltable;
}



/**
 * Setzt alle Werte im Array auf NULL.
 */
void Scanner::resetTemporaryChars() {
	temporaryChars = new char[arrayLength];
	for (int i = 0; i < arrayLength; i++) {
		temporaryChars[i] = '\0';
	}
	position = 0;
}

/**
 * Gibt das nächste Token zurück.
 */
Token* Scanner::getNextToken() {
	Tokentyp state;
	do {
		state = calculateTokentyp();
	} while (state == EmptyToken);
	int line = automat->getLine();
	int column = automat->getColumn();

	return createToken(state, line, column);
}

/**
 * Fügt Chars in den Automaten ein, bis dieser false zurück gibt und fragt dann
 * nach dem zuletzt akzeptierten Zustand. Das Lexem steht danach in temporaryChars
 */
// geändert!! berechneTokentyp -> calculateTokentyp 31.03.15
Tokentyp Scanner::calculateTokentyp() {
	Tokentyp state = FailToken;
	resetTemporaryChars();
	char nextChar = '\0';
	int stepsBack = 0;
	bool fehler = false;
	// geändert anzahlZeichen -> numberCharacters
	int numberCharacters = 0;
	//Zeichen vom Buffer holen und mit Automat prüfen.
	do {
		nextChar = buffer->getNextChar();
		numberCharacters++;
		if(nextChar == NULL){
			printf("<<<<<<<<<<<<<<<<<<< Ende \n");
			return EndToken;
		}
		temporaryChars[position] = nextChar;
		position++;
		if (position == arrayLength) {
			fehler = true;
			break;
		}
	} while(automat->isOk(nextChar));
	if (numberCharacters > 1) {
		buffer->setChar();
		position--;
		temporaryChars[position] = '\0';
	}



	//Automat nach akzeptierten Zustand fragen
	state = automat->getLastAcceptedState();
	stepsBack = automat->getStepsBack();
	while (stepsBack > 0) {
		buffer->setChar();
		position--;
		temporaryChars[position] = '\0';
		//position--;
		stepsBack--;
	}


	//Nach Fehler schauen
	if (state == 'FailToken') {
		resetTemporaryChars();
		temporaryChars = "Fehlermeldung: Es wurde ein unbekantes Wort eingegeben.";
	} else if (fehler) {
		state = FailToken;
		resetTemporaryChars();
		temporaryChars = "Fehlermeldung: Ein zu langes Wort wurde eingegeben.";
	}

	return state;
}

/**
 * Erstellt das nächste Token.
 */
// ### Name geändert createToken -> createToken
Token* Scanner::createToken(Tokentyp state, int line, int column) {
	Token* token;
	long long key = NULL;
	if (state == IdentifierToken) {
		key = symboltable->insert(temporaryChars);
	}
	else if (state == PlusToken) {
		key = symboltable->insert("+\0", "+\0");
	}
	else if (state == MinusToken) {
		key = symboltable->insert("-\0", "-\0");
	}
	else if (state == ExclamationToken) {
		key = symboltable->insert("!\0", "!\0");
	}
	else if (state == MultiplyToken) {
		key = symboltable->insert("*\0", "*\0");
	}
	else  if (state == DivideToken) {
		key = symboltable->insert("/\0", "/\0");
	}
	else if (state == SmallToken) {
		key = symboltable->insert("<\0", "<\0");
	}
	else if (state == BigToken) {
		key = symboltable->insert(">\0", ">\0");
	}
	else if (state == EqualsToken) {
		key = symboltable->insert("=\0", "=\0");
	}
	else if (state == SmallerDoubleBiggerToken) {
		key = symboltable->insert("<:>\0", "<:>\0");
	}
	else if (state == AndToken) {
		key = symboltable->insert("&\0", "&\0");
	}
	/** 19.3.15
	if (state == IntegerToken){
		int x = atoi(temporaryChars);
	}
	**/
	token = new Token(state, temporaryChars, line, column);
	token->setKey(key);
	resetTemporaryChars();
	return token;
}
