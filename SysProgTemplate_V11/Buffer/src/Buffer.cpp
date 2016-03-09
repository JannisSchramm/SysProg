/*
 * Buffer.cpp
 *
 *  Created on: 16.10.2014
 *      Author: Rebecca Sigmund
 */

#include "Buffer.h"



/**
 * Der Konstruktor erstellt die beiden Arrays.
 */
Buffer::Buffer(int size, char* input ) {
	offset = 0;
	position = -1;
	arrayLength = size;
	currentChar = new char[arrayLength];
	previousChar = new char[arrayLength];
	inputTxt = input;
	loadNewChars();
}

Buffer::~Buffer() {
	delete currentChar;
	delete previousChar;
}

/**
 * Läd das momentane Array mit neuen Werten und verschiebt
 * die vorherigen Werte in das andere Array.
 */
void Buffer::loadNewChars() {

	int k = 0;
	int temp = 0;



	for(int i=0; i < arrayLength; i++){

			previousChar[i] = NULL;

	}

	for(int i=0; i < arrayLength; i++){

			previousChar[i] = currentChar[i]  ;
			currentChar[i] = NULL;
	}


	FILE* datei;
	datei = fopen (inputTxt, "r"); //r = read

   // char text[arrayLength+1];

    if (datei != NULL)

    {
		 //fscanf (datei, "%100c", text);


    	fseek(datei,offset,SEEK_SET);
    	temp = fgetc(datei);
    	while((temp != EOF) && (k < arrayLength)){
    		//printf("%d\n",offset);
    		//printf("%c\n",temp);
    		currentChar[k] = temp;
    		k++;
    		temp = fgetc(datei);
    		offset++;


    	}
		//currentChar[arrayLength - 1] = '\0';

		//printf ("%s\n", text);
		fclose (datei);

    }

	else {
			  printf("Datei nicht gefunden\n");
	}


}

/*
 * lädt das alte Array in das aktuelle Array
 */

void Buffer::loadOldChars() {

	for(int i=0; i < arrayLength; i++){
		currentChar[i] = previousChar[i];
	}


}

/**
 * Gibt das nächste Zeichen zurück,
 *  wenn es keins mehr gibt, wird NULL zurück gegeben.
 */
char Buffer::getNextChar() {
	if (position + 1 < arrayLength) {
		position++;
	} else {
		loadNewChars();
		position = 0;
	}
	if(currentChar[position]!= NULL){
		return currentChar[position];
	} else {
		return NULL;
	}
}

/**
 * Nimmt das letzte herraus gegebene Zeichen zurück.
 */
void Buffer::setChar() {
	if (position >= 0) {
		position--;
	} else {
		loadOldChars();
		position = arrayLength - 2;
	}
}





