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
	long long getKey();
	void setKey(long long myKey);
private:
	Tokentyp iD;
	char* content;
	int contentInt;
	int line;
	int column;
	long long key;
};

#endif /* TOKEN_H_ */
