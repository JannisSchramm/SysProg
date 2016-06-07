/*
 * Main.cpp
 *
 *  Created on: Nov 26, 2014
 *      Author: mude1013
 */

#include "../../Scanner/src/Scanner.h"
#include "../../Token/src/Token.h"
#include "../../Symboltable/src/Symboltable.h"
#include "../../Symboltable/src/Information.h"
#include <fstream>

//TODO Leerzeichen-Zähler
//TODO Fehler-Zähler

void ausgabe(char* token, int line, int column,  char* lexem, FILE* fp) {
	fprintf(fp, "Token ");
	fprintf(fp, token);
	fprintf(fp, "	Line: ");
	fprintf(fp, "%d", line);
	fprintf(fp, "	Column: ");
	fprintf(fp, "%d", column);
	fprintf(fp, "	Lexem: ");
	if(*lexem == '%') {
		fprintf(fp, "%%");
	}
	else {
		fprintf(fp, lexem);
	}
	fprintf(fp, "\n");
}

int main(int argc, char* argv[]) {

	argv[1] = "/home/rebecca/HS/SysProg/Test.txt";
	argv[2] = "/home/rebecca/HS/SysProg/TestOut.txt";
	argc = 2;

	printf("%d %s \n", argc, argv[1]);
	printf("%d %s \n", argc, argv[2]);
	if (argc < 2) {
		printf("Bitte Eingabedateipfad und Ausgabedateipfad mitgeben.");
		return 0;
	}
	Scanner* scanner = new Scanner(argv[1]); //"/home/stud/lkt/fbi/mude1013/Documents/testdatei2.txt" //
	Symboltable* symboltable = scanner->getSymboltable();

	FILE* fp; // Zeiger auf Datenstrom der Datei
	fp = fopen(argv[2],"w"); // Datei neu erzeugen bzw. ueberschreiben, wenn es sie schon gibt

	Token* token;
	Tokentyp tokentyp;
	do {
		token = scanner->getNextToken();
		int line = token->getLine();
		int column = token->getColumn();
		char* tokenName = "Fail                  ";
		tokentyp = token->getName();
		switch(tokentyp) {
			case(IdentifierToken) : {
				long long key = token->getKey();
				Information* info =  symboltable->lookup(key);
				tokenName = info->getType();
			}
			break;
			case(IntegerToken)              : tokenName = "Integer                  ";
			break;
			case(PlusToken)                 : tokenName = "Plus                     ";
			break;
			case(MinusToken)                : tokenName = "Minus                    ";
			break;
			case(MultiplyToken)             : tokenName = "Multiply                 ";
			break;
			case(DivideToken)               : tokenName = "Divide                   ";
			break;
			case(ExclamationToken)          : tokenName = "Exclamation              ";
			break;
			case(AndToken)                  : tokenName = "And                      ";
			break;
			case(SemicolonToken)            : tokenName = "Semicolon                ";
			break;
			case(OpenBracketToken)          : tokenName = "OpenBracket              ";
			break;
			case(CloseBracketToken)         : tokenName = "CloseBracket             ";
			break;
			case(OpenCurlyToken)            : tokenName = "OpenCurly                ";
			break;
			case(CloseCurlyToken)           : tokenName = "CloseCurly               ";
			break;
			case(OpenSquareToken)           : tokenName = "OpenSquare               ";
			break;
			case(CloseSquareToken)          : tokenName = "CloseSquare              ";
			break;
			case(SmallerDoubleBiggerToken)  : tokenName = "SmallerDoubleBigger      ";
			break;
			case(DoubleEqualsToken)         : tokenName = "DoubleEqual              ";
			break;
			case(EqualsToken)				: tokenName =  "Equal                   ";
			break;
			case(BigToken)					: tokenName = "Bigger                   ";
			break;
			case(SmallToken)				: tokenName = "Smaller					";
			break;
			case(EndToken)					: tokenName = "End                      ";
			break;


		}
		ausgabe(tokenName, line, column, token->getContent(), fp);
	} while(tokentyp != EndToken);

	fclose(fp); // Datei schließen
	delete scanner;

	return 0;
}





