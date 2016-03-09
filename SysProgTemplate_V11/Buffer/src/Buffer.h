/*
 * Buffer.h
 *
 *  Created on: 16.10.2014
 *      Author: rebecca
 */

#ifndef BUFFER_H_
#define BUFFER_H_
#include <stdio.h>
#include <iostream>
#include <fstream>

class Buffer {
public:
	Buffer(int size, char* input);
	virtual ~Buffer();
	char getNextChar();
	void setChar();
	void loadNewChars();
	int offset;            // Stelle in der Datei
private:
	char* currentChar;
	char* previousChar;
	int position;         // aktuelle Stelle im Buffer
	int arrayLength;
	char* inputTxt;


	void loadOldChars();

};

#endif /* BUFFER_H_ */
