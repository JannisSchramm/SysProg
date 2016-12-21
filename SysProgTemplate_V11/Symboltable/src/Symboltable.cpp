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
int* Symboltable::insert(char* lexem, char* type){
	int index = 0;
	int offset = 0;
	static int key[2];

	for(int i = 0; lexem[i] != '\0'; i++) {
		index += lexem[i];
	}
	index = index % length;
	key[0] = index;
	offset = symtabEntry[index].addElement(lexem, type);
	key[1] = offset;

	//printf("<<<<<<<<<<<<<<<< in symboltabelle insert pointer: %d %d\n", key[0], key[1]);
	//printf("<<<<<<<<<< in symboltabelle insert lexem: %s \n", lexem);

	return key;
}

/**
 * Fügt ein neues Lexem mit Typ Bezeichner ein und gibt den Key zurück.
 */
int* Symboltable::insert(char* lexem){

	return insert(lexem, "Identifier");
}

/**
 * Gibt die Information zu einem bestimmten Key zurück.
 */
Information* Symboltable::lookup(int* key) {
	//printf("<<<<<<<<<<<<<<<< in symboltabelle lookup pointer longlong: %lld \n",key);
	//int keyArray = ((int)key);
	//int* keyPointer = &keyArray;

	int* keyPointer;
	keyPointer = key;

	printf("<<<<<<<<<<<<<<<< in symboltabelle lookup pointer: %d %d\n", *keyPointer, *(keyPointer+1));
	Element* e = symtabEntry[*keyPointer].getElement(*(keyPointer+1));

	if(e != NULL){
		Information* info = e->getInformation();
		//printf("<<<<<<<<<<<<< in symboltabelle lookup name: %s \n", info->getName());
		return info;
	}
	else
	{
		printf("e ist null\n");
	}

	return new Information("ich bin ein Fehler", "Fehler");
}

