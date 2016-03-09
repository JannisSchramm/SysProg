/*
 * Vector.h
 *
 *  Created on: Nov 19, 2014
 *      Author: mude1013
 */

#ifndef VECTOR_H_
#define VECTOR_H_
#include "Element.h"

class Vector{

public:
	Vector();
	virtual ~Vector();
	int addElement(char* lexem, char* typ);
	Element* getFirstElement();
	Element* getElement(int index);

private:
	int size;
	Element* firstElement;

};


#endif /* VECTOR_H_ */
