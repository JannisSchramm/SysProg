/*
 * Info.cpp
 *
 *  Created on: Nov 19, 2014
 *      Author: mude1013
 */

#include "Information.h"

Information::Information(char* myName, char* myType){
	name = myName;
	type  = myType;
}

Information::~Information() {

}

char* Information::getName() {
	return name;
}

char* Information::getType() {
	return type;
}

void Information::setType(char* myType) {
	type = myType;
}

/**
 * Gibt zurück, ob das mitgegebene Lexem mit dem eigenen identisch ist.
 */
bool Information::compareLex(char* lexem) {
	char* ownLexem = this->getName();
	if (*lexem == '\0') {
		if (*ownLexem == '\0') {
			return true;
		}
		return false;
	}
	while (*lexem != '\0') {
		if (*lexem != *ownLexem) {
			return false;
		}
		lexem++;
		ownLexem++;
	}
	while (*ownLexem != '\0') {
		if (*ownLexem != *lexem) {
			return false;
		}
		lexem++;
		ownLexem++;
	}
	if (*lexem == *ownLexem) {
		return true;
	} else {
		return false;
	}
}

