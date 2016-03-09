/*
 * Information.h
 *
 *  Created on: Nov 19, 2014
 *      Author: mude1013
 */

#ifndef INFORMATION_H_
#define INFORMATION_H_
#include <stdio.h>

class Information {
public:
	Information(char* myName, char* myType);
	virtual ~Information();
	bool compareLex(char* lexem);
	char* getName();
	char* getType();
	void setType(char* myType);

private:
	char* name;
	char* type;





};


#endif /* INFORMATION_H_ */
