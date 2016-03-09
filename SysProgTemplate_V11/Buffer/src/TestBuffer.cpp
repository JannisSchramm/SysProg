#include "Buffer.h"
#include <stdio.h>

int main(int argc, char *argv[]) {



	Buffer*  buffer;

	buffer = new Buffer(2, "int.txt");


	for(int i=0; i<55; i++){
		char a = buffer->getNextChar();
		//printf("%c\n",a);
		//printf("%d",buffer->offset);
	}






	return 0;
}
