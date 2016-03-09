#include "Buffer.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>


int main(int argc, char **argv) {

	Buffer*  buffer;

	buffer = new Buffer();

	buffer->read();


	for (int i; i<7;i++){
		printf("%c\n", buffer->getSpeicher(i));
	}



	buffer->read();

	printf("ja\n");
		for (int i=0; i<7;i++){
			printf("%c\n", buffer->getSpeicher(i));


		}

		buffer->read();

			for (int i=0; i<7;i++){
				printf("%c\n", buffer->getSpeicher(i));


			}

		printf("rtggrgr\n");
	return 0;
}
