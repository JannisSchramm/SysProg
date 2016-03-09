/*
 * Scanner.h
 *
 *  Created on: 16.10.2014
 *      Author: rebecca
 */

#ifndef SCANNER_H_
#define SCANNER_H_
#include "../../Token/src/Token.h"
#include "../../Buffer/src/Buffer.h"
#include "../../Automat/src/Automat.h"
#include "../../Automat/src/Event.h"
#include "../../Symboltable/src/Symboltable.h"

class Scanner {
public:
	Scanner(char* input);
	virtual ~Scanner();
	Token* getNextToken();
	Symboltable* getSymboltable();
private:
	char* temporaryChars;
	void resetTemporaryChars();
	Token* createToken(Tokentyp state, int line, int column);
	Tokentyp calculateTokentyp();

	Automat* automat;
	Buffer* buffer;
	int position;
	int arrayLength;
	Symboltable* symboltable;
};

#endif /* SCANNER_H_ */
