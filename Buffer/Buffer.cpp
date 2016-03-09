/*
 * Buffer.cpp
 *
 *  Created on: Nov 12, 2014
 *      Author: mude1013
 */

#include <stdio.h>
#include <iostream>
#include <fstream>

#include "Buffer.h"
using namespace std;

char speicher[1024];
int stelle = 0;

Buffer::Buffer() {
	// TODO Auto-generated constructor stub

}

Buffer::~Buffer() {
	// TODO Auto-generated destructor stub
}


void Buffer::read(){
	  int length = 2;
	  int temp;
	  int k = 0;

	  FILE *datei;

	  //char text[100+1];

	  datei = fopen ("testdatei.txt", "r");

	  if (datei != NULL)

	  {

	    //fscanf (datei, "%100c", text);

		  fseek(datei,stelle,SEEK_SET);
		  temp = fgetc(datei);
		  while((temp != EOF) && (k < length)){


			 	    	speicher[k] = temp;
			 	    	k++;
			 	    	temp = fgetc(datei);
			 	    	stelle++;
		  }
		  speicher[k] = '\0';

	    /* String muss mit Nullbyte abgeschlossen sein */

	//    text[100] = '\0';

	//    printf ("%s\n", text);

	/*   for(int i=0; i < 100 ;i++){
	    	speicher[i] = text[i];
	    }*/

	    fclose (datei);

	  }

}

char Buffer::getSpeicher(int i){

	   return speicher[i];
  }



