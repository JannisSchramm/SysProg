/*
 * Symboltable.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "Symboltable.h"
#include "../../Parser/src/Parser.h"

//TODO: in Datentyp Integer umwandeln

/**
 * Erstellt eine neue Symboltabelle und fügt if und while ein.
 */
Symboltable::Symboltable() {
	length = 1024;
	symtabEntry = new Vector[length];
	insert("if\0", "if\0");
	insert("IF\0", "if\0");
	insert("while\0", "while\0");
	insert("WHILE\0", "while\0");
	insert("write\0", "write\0");
	insert("else\0", "else\0");
	insert("ELSE\0", "else\0");
	insert("read\0", "read\0");
	insert("int\0", "int\0");
	insert(";\0", ";\0");
	insert(":=\0", ":=\0");




}

Symboltable::~Symboltable() {
	delete[] symtabEntry;

}

/**
 * Fügt ein neues Lexem mit angegebenem Typ ein und gibt den Key zurück.
 */
long long Symboltable::insert(char* lexem, char* type){
	int index = 0;
	int offset = 0;
	int key[2] = {0,0};

	for(int i = 0; lexem[i] != '\0'; i++) {
		index += lexem[i];
	}
	index = index % length;
	key[0] = index;
	offset = symtabEntry[index].addElement(lexem, type);
	key[1] = offset;

	return (long long)*key;
}

/**
 * Fügt ein neues Lexem mit Typ Bezeichner ein und gibt den Key zurück.
 */
long long Symboltable::insert(char* lexem){
	return (long long) insert(lexem, "Identifier");
}

/**
 * Gibt die Information zu einem bestimmten Key zurück.
 */
Information* Symboltable::lookup(long long key) {

	int keyArray = ((int)key);
	int* keyPointer = &keyArray;
	printf("%d\n", keyPointer[0]);
	Element* e = symtabEntry[keyPointer[0]].getElement(keyPointer[1]);

	if(e != NULL){
		Information* info = e->getInformation();
		printf(info->getName());
		printf("\n");
		return info;
	}
	else
	{
		printf("e ist null\n");
	}

	return new Information("ich bin ein Fehler", "Fehler");
}

