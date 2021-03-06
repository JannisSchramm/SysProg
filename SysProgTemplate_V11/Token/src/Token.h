/*
 * Token.h
 *
 *  Created on: 17.10.2014
 *      Author: rebecca
 */

#ifndef TOKEN_H_
#define TOKEN_H_
#include "../../Automat/src/Event.h"
#include <stdlib.h>
#include <stdio.h>


class Token {
public:
	Token(Tokentyp iD, char* content, int myline, int mycolumn);
	virtual ~Token();
	Tokentyp getName();
	char* getContent();
	int getContentInt();
	int getLine();
	int getColumn();
	int getKeyIndex();
	int getKeyOffset();
	void setKey(int myKeyIndex, int myKeyOffset);
private:
	Tokentyp iD;
	char* content;
	int contentInt;
	int line;
	int column;
	int keyIndex;
	int keyOffset;
};

#endif /* TOKEN_H_ */
