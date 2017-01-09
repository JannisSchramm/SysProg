/*
 * Token.cpp
 *
 *  Created on: 17.10.2014
 *      Author: rebecca
 */

#include "Token.h"


/**
 * Erstellt einen neuen Token.
 */
Token::Token(Tokentyp name, char* myContent, int myline, int mycolumn) {
	iD = name;
	content = myContent;
	contentInt = 0;
	line = myline;
	column = mycolumn;
	// Die folgenden Verzweigungen prüfen, ob der Integer-Bereich überschritten wird und wenn ja, wird aus dem
	// IntegerToken ien FailToken
	if(name == IntegerToken){
		contentInt = strtol(myContent, NULL, 10);


	}
	if(contentInt == -1){
		iD = FailToken;
		printf("%d", getContentInt());
	}
	keyIndex = 0;
	keyOffset = 0;
}

Token::~Token() {
}

Tokentyp Token::getName(){
	return iD;
}

char* Token::getContent(){
	return content;
}

int Token::getContentInt(){
	return contentInt;
}

int Token::getLine(){
	return line;
}

int Token::getColumn(){
	return column;
}

int Token::getKeyIndex() {
	return keyIndex;
}

int Token::getKeyOffset() {
	return keyOffset;
}

void Token::setKey(int myKeyIndex, int myKeyOffset) {
	keyIndex = myKeyIndex;
	keyOffset = myKeyOffset;
}


