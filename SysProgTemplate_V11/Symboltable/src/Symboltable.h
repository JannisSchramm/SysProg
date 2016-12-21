/*
 * Symboltable.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include "Information.h"
#include "Vector.h"
#include "../../Symboltable/src/Element.h"

class Symboltable {
public:
	Symboltable();
	virtual ~Symboltable();
	int* insert(char* lexem);
	Information* lookup(int* key);
	int* insert(char* lexem, char* typ);
private:
	int length;
	Vector* symtabEntry;

};

#endif /* SYMBOLTABLE_H_ */
