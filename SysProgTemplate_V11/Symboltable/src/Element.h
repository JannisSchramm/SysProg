/*
 * Element.h
 *
 *  Created on: Nov 19, 2014
 *      Author: mude1013
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_
#include "Information.h"

class Element{
private:
	Information* information;
	Element* nextElement;
public:
	Element(char* lexem, char* typ);
	virtual ~Element();
	Information* getInformation();
	Element* getNextElement();
	bool hasNextElement();
	void setNextElement(Element* element);

};


#endif /* ELEMENT_H_ */
