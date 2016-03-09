/*
 * Element.cpp
 *
 *  Created on: Nov 19, 2014
 *      Author: mude1013
 */

#include "Element.h"
#include "Information.h"

/**
 * Erstellt ein neues Element mit der zugehörigen Information.
 */
Element::Element(char* lexem, char* type) {
	information = new Information(lexem, type);
	nextElement = 0;
}

Element::~Element() {
	delete information;
}

/**
 * Setzt einen Pointer auf das nächste Element.
 */
void Element::setNextElement(Element* element){
	nextElement = element;
}

/**
 * gibt das nächste Element zurück, Ist 0 wenn es kein nächstes Element gibt.
 */
Element* Element::getNextElement(){
	return nextElement;
}

/**
 * Gibt zurück, ob es ein nächstes Element gibt.
 */
bool Element::hasNextElement(){
	if(nextElement != 0){
		return true;
	}
	return false;
}

/**
 * Gibt die Information des Elements zurück.
 */
Information* Element::getInformation() {
	return information;
}
