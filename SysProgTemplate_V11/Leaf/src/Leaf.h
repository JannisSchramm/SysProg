/*
 * Leaf.h
 *
 *  Created on: 17.10.2014
 *      Author: rebecca
 */

#ifndef LEAF_H_
#define LEAF_H_
#include "../../Tree/src/SuperTree.h"
#include "../../Symboltable/src/Symboltable.h"
#include "../../Symboltable/src/Information.h"
#include "../../Symboltable/src/Element.h"


class Leaf :public SuperTree{
public:
	Leaf(int* symtabEntryKey, Symboltable*  symboltable, grammarType grammartype, int line, int column);
	virtual ~Leaf();
	Information* getInformation();
	void store(Type t);
	Type getType();
	char* getValue();
	void setValue(char* myValue);

private:
	Information* information;
	Symboltable* symboltab;
	int* symtabEntryK;
	char* value;

};

#endif /* LEAF_H_ */
