/*
 * Leaf.cpp
 *
 *  Created on: 17.10.2014
 *      Author: rebecca
 */

#include "Leaf.h"
#include "../../Parser/src/Parser.h"


/**
 * Erstellt einen neuen Leaf.
 */
Leaf::Leaf(long long symtabEntryKey, Symboltable* symboltable, grammarType grammartype, int line, int column): SuperTree(grammartype, line, column)  {

	gt = grammartype;
	symboltab = symboltable;
	symtabEntryK = symtabEntryKey;

	if(symtabEntryKey > 0){
		information =	symboltable->lookup(symtabEntryKey);
	}

	value = "0";

}

void Leaf::store(Type t){
	type = t;
	if(symtabEntryK > 0){
		information = symboltab->lookup(symtabEntryK);
		if (t == intType) {
			symboltab->insert(information->getName(), "intType\0");
		}
		else if (t == intArrayType) {
			symboltab->insert(information->getName(), "intArrayType\0");
		}
		information = symboltab->lookup(symtabEntryK);
	}

}




Leaf::~Leaf() {
}

Information* Leaf::getInformation() {
	return information;
}

Type Leaf::getType() {
	if(symtabEntryK > 0){
		information = symboltab->lookup(symtabEntryK);
		char* gtChar = information->getType();
		if (gtChar == "intType\0") {
			type = intType;
		}
		else if (gtChar == "intArrayType\0") {
			type = intArrayType;
		}
	}
	return type;
}

char* Leaf::getValue() {
	return value;
}

void Leaf::setValue(char* myValue) {
	value = myValue;
}

