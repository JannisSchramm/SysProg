#include "Automat.h"
#include <stdio.h>

/*
* Main Methode
*/
int main (int argc, char* argv[]){
	printf("Test\n");
	Automat* automat;

	automat = new Automat();

	//automat->isOk('H');
	if(automat->isOk('/')){
		printf("Ja\n");
	}
	else{
		printf("Nein\n");
	}


	if(automat->isOk('*')){
		printf("Ja\n");
	}
	else{
		printf("Nein\n");
	}

	if(automat->isOk(' ')){
			printf("Ja\n");
		}
		else{
			printf("Nein\n");
	}

	if(automat->isOk('B')){
			printf("Ja\n");
		}
		else{
			printf("Nein\n");
	}

	if(automat->isOk(' ')){
			printf("Ja\n");
		}
		else{
			printf("Nein\n");
	}


	if(automat->isOk('*')){
			printf("Ja\n");
		}
		else{
			printf("Nein\n");
	}

	if(automat->isOk('/')){
			printf("Ja\n");
		}
		else{
			printf("Nein\n");
	}

	if(automat->isOk('A')){
			printf("Ja\n");
		}
		else{
			printf("Nein\n");
	}


	if(automat->getLastAcceptedState() == EmptyToken) {
		printf("Stimmt");
	}
	else {
		printf("falsch");
	}

	printf("%d", automat->getStepsBack());


	return 0;
}
