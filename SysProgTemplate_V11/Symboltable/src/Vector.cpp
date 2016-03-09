/*
 * Vector.cpp
 *
 *  Created on: 22.11.2014
 *      Author: dennis
 */

#include "Vector.h"

Vector::Vector(){
	size = 0;
	firstElement = 0;
}
Vector::~Vector() {
	delete firstElement;
}

/**
 * Fügt ein neues Element in den Vector ein und gibt den Index zurück.
 */
int Vector::addElement(char* lexem, char* typ){
	int index = 0;
	if(firstElement == 0) {
		firstElement = new Element(lexem, typ);
		size = 1;
	} else {
		Element* e = firstElement;
		index = 1;
		while(e->hasNextElement()) {
			if(e->getInformation()->compareLex(lexem)) {
				e->getInformation()->setType(typ);
				return index;
			}
			index++;
			e = e->getNextElement();
		}
		if(e->getInformation()->compareLex(lexem)) {
			e->getInformation()->setType(typ);
			return index;
		} else {
			e->setNextElement(new Element(lexem, typ));
		}
	}
	return ++index;
}

Element* Vector::getFirstElement(){
	return firstElement;
}

/*
 * ist n höher als wir Elemente in der Liste haben, wird das erste Element zurückgegeben
 */
Element* Vector::getElement(int n){
	Element* e = firstElement;
	if(n <= size){
	//	Element e = firstElement;
		for(int i=0; i < n; i++){
			e = e->getNextElement();
		}
	}

	return e;
}



