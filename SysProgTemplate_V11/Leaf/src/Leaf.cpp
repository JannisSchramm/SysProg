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
Leaf::Leaf(int symtabEntryKeyIndex, int symtabEntryKeyOffset, Symboltable* symboltable, grammarType grammartype, int line, int column): SuperTree(grammartype, line, column)  {

	gt = grammartype;
	symboltab = symboltable;
	symtabEntryKIndex = symtabEntryKeyIndex;
	symtabEntryKOffset = symtabEntryKeyOffset;

	if (symtabEntryKIndex > 0) {
		printf("<<<<<<<<<<<<<< in Leaf symtabEntryKIndex: %d \n", symtabEntryKIndex);
	} else {
		printf("<<<<<<<<<<<<<< in Leaf symtabEntryKIndex ist null\n");
	}


/*	try {
		printf("<<<<<<<<<<<<<< in Leaf %d \n", *symtabEntryK);
	} catch (const Exception e) {
		printf("<<<<<<<<<<<<<< in Leaf %d \n", );
	} */


	if(symtabEntryKeyIndex > 0){
		information =	symboltable->lookup(symtabEntryKIndex, symtabEntryKOffset);
	}

	value = "0";
	type = noType;

}

void Leaf::store(Type t){
	type = t;
	if(symtabEntryKIndex > 0){
		information = symboltab->lookup(symtabEntryKIndex, symtabEntryKOffset);
		if (t == intType) {
			symboltab->insert(information->getName(), "intType\0");
		}
		else if (t == intArrayType) {
			symboltab->insert(information->getName(), "intArrayType\0");
		}
		information = symboltab->lookup(symtabEntryKIndex, symtabEntryKOffset);
	}

}




Leaf::~Leaf() {
}

Information* Leaf::getInformation() {
	return information;
}

Type Leaf::getType() {
	type = noType; //TODO?
	if(symtabEntryKIndex > 0){
		information = symboltab->lookup(symtabEntryKIndex, symtabEntryKOffset);
		char* gtChar = information->getType();
		if (gtChar == "intType\0") {
			type = intType;
		}
		else if (gtChar == "intArrayType\0") {
			type = intArrayType;
		}
	}

	if (symtabEntryKIndex > 0) {
		printf("<<<<<<<<<<<<<< in Leaf getType symtabEntryKIndex: %d \n", symtabEntryKIndex);
	} else {
		printf("<<<<<<<<<<<<<< in Leaf getType symtabEntryKIndex ist null\n");
	}


	return type;
}

char* Leaf::getValue() {
	return value;
}

void Leaf::setValue(char* myValue) {
	value = myValue;
}

