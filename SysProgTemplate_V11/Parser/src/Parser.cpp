/*
 * Parser.cpp
 *
 *  Created on: 17.10.2014
 *      Author: rebecca
 */

#include "Parser.h"


/**
 * Erstellt einen neuen Parser.
 */
Parser::Parser(char* input, char* output) {
	//TODO in richtiger Textdatei speichern
	fp = fopen(output,"w"); //"/home/rebecca/HS/SysProg/TestOut.txt" Datei neu erzeugen bzw. ueberschreiben, wenn es sie schon gibt


	scanner = new Scanner(input);    //TODO "/home/rebecca/HS/SysProg/Test.txt" man soll bei Start des Programms die Input-Datei eingeben können
	symTab = scanner->getSymboltable();
	printf("hier gehts los \n");
	parseTree = parse();

	typeCheckStart(parseTree);

	printf("\n makeCode: \n \n");
	labelCount = 0;
	makeCodeStart(parseTree);

	printf("Ende\n");
	fclose(fp); // Datei schließen

}

Parser::~Parser() {
	delete scanner;
	delete parseTree;
}

Tree* Parser::parse() {
	Tree* tree = prog();

	return tree;
}

//

Tree* Parser::prog() {
	printf("prog \n");
	Tree* tree = new Tree(PROG, 0, 0);

	currentToken = scanner->getNextToken();

	if((currentToken->getName() == IdentifierToken && compare(currentToken->getContent(), "int\0"))
		|| (currentToken->getName() == IdentifierToken && compare(currentToken->getContent(), "identifier\0"))
		|| (currentToken->getName() == IdentifierToken && compare(currentToken->getContent(),"write\0"))
		|| (currentToken->getName() == IdentifierToken && compare(currentToken->getContent(), "read\0"))
		|| (currentToken->getName() == IdentifierToken && compare(currentToken->getContent(), "if\0"))
		|| (currentToken->getName() == IdentifierToken && compare(currentToken->getContent(),"while\0"))
		|| (currentToken->getName() == IdentifierToken && compare(currentToken->getContent(), "IF\0"))
		|| (currentToken->getName() == IdentifierToken && compare(currentToken->getContent(),"WHILE\0"))
		|| currentToken->getName() == OpenCurlyToken || currentToken->getName() == EndToken){
		Node* nodeDecls = decls();
		Node* nodeStatements = statements();
		tree->addNode((SuperTree*)nodeDecls);
		tree->addNode((SuperTree*)nodeStatements);
	}
	else {
		error("in prog(): no IdentifierToken or OpenCurlyToken \0", currentToken->getLine(), currentToken->getColumn());
	}
	return tree;
}

Node* Parser::decls() {
	printf("decls \n");
	Node* nodeDecls = new Node(DECLS, currentToken->getLine(), currentToken->getColumn());

	if(currentToken->getName() == IdentifierToken && compare(currentToken->getContent(), "int\0")){
		Node* nodeDecl = decl();
		nodeDecls->addNode((SuperTree*)nodeDecl);
		if(currentToken->getName() == SemicolonToken){

			Leaf* leafSemicolon = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
			nodeDecls->addLeaf((SuperTree*)leafSemicolon);
			currentToken = scanner->getNextToken();
			Node* nodeDecls2 = decls();
			nodeDecls->addNode((SuperTree*)nodeDecls2);
			//currentToken = scanner->getNextToken();
		}
	} else if(currentToken->getName() == EndToken){

	} else if(currentToken->getName() == IdentifierToken){

	}
	else{
		error("in decls(): no IdentifierToken with int \0", currentToken->getLine(), currentToken->getColumn());
	}



	return nodeDecls;
}

Node* Parser::decl() {
	printf("decl \n");
	Node* node = new Node(DECL, currentToken->getLine(), currentToken->getColumn());

	if (currentToken->getName() == IdentifierToken && compare(currentToken->getContent(), "int\0")) {
		Leaf* leafInt = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
		leafInt->setValue(currentToken->getContent());
		node->addLeaf((SuperTree*)leafInt);
		currentToken = scanner->getNextToken();
		Node* nodeArray = array();

		node->addNode((SuperTree*)nodeArray);
		if(currentToken->getName() == IdentifierToken){
			Leaf* leafIdentifier = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
			// ist es ein Array?
			if(nodeArray->hasLeave()){

				symTab->insert(currentToken->getContent(), "Array");


				// Identifier in Symboltable als Array speichern
			}
			else {

				// Identifier in Symboltable als Variable speichern
				symTab->insert(currentToken->getContent(), "Integer");

			}
			node->addLeaf((SuperTree*)leafIdentifier);
			currentToken = scanner->getNextToken();

		} else {
			error("in decl(): no IdentifierToken \0", currentToken->getLine(), currentToken->getColumn());
		}

	} else{
		error("in decl(): no int \0", currentToken->getLine(), currentToken->getColumn());
	}

	return node;
}

Node* Parser::array() {
	printf("array \n");
	Node* nodeArray = new Node(ARRAY, currentToken->getLine(), currentToken->getColumn());



	if(currentToken->getName() == OpenSquareToken){

		Leaf* leafOpenSquare = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
		nodeArray->addLeaf((SuperTree*)leafOpenSquare);
		currentToken = scanner->getNextToken();
		if(currentToken->getName() == IntegerToken){
			Leaf* leafInteger = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
			leafInteger->setValue(currentToken->getContent());
//			printf("hier ist der Content: \n");
//			printf(currentToken->getContent());
//			printf("\n");
			nodeArray->addLeaf((SuperTree*)leafInteger);
			currentToken = scanner->getNextToken();
			if(currentToken->getName() == CloseSquareToken){
				Leaf* leafCloseSquare = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
				nodeArray->addLeaf((SuperTree*)leafCloseSquare);
				currentToken = scanner->getNextToken();
			}else{
				error("in array(): no CloseSquareToken \0", currentToken->getLine(), currentToken->getColumn());
			}

		}else{
			error("in array(): no IntegerToken \0", currentToken->getLine(), currentToken->getColumn());
		}

	}
	else if(currentToken->getName() == IdentifierToken ){

	}
	else{
		error("in array(): no IdentifierToken \0", currentToken->getLine(), currentToken->getColumn());
	}

	return nodeArray;
}

Node* Parser::statements() { //TODO verschachtelte if funktionieren nicht
	printf("statements \n");
	Node* nodeStatements = new Node(STATEMENTS, currentToken->getLine(), currentToken->getColumn());

	if(currentToken->getName() == EndToken || currentToken->getName() == CloseCurlyToken){
		//printf("closecurlytoken\n");
	}
	else  if ((currentToken->getName() == IdentifierToken)
			|| (currentToken->getName() == IdentifierToken && compare(currentToken->getContent(), "write\0"))
			|| (currentToken->getName() == IdentifierToken && compare(currentToken->getContent(), "read\0"))
			|| (currentToken->getName() == IdentifierToken && compare(currentToken->getContent(), "if\0"))
			|| (currentToken->getName() == IdentifierToken && compare(currentToken->getContent(), "while\0"))
			|| (currentToken->getName() == IdentifierToken && compare(currentToken->getContent(), "IF\0"))
			|| (currentToken->getName() == IdentifierToken && compare(currentToken->getContent(), "WHILE\0"))
			|| currentToken->getName() == OpenCurlyToken) {
		Node* nodeStatement = statement();

		nodeStatements->addNode((SuperTree*)nodeStatement);
		if(currentToken->getName() == SemicolonToken){
			Leaf* leafSemicolon = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
			nodeStatements->addLeaf((SuperTree*)leafSemicolon);
			currentToken = scanner->getNextToken();
			Node* nodeStatements2 = statements();
			nodeStatements->addNode((SuperTree*)nodeStatements2);
		} else {
			error("in statements(): no SemicolonToken \0", currentToken->getLine(), currentToken->getColumn());
		}
	} else {
		error("in statements(): no IdentifierToken \0", currentToken->getLine(), currentToken->getColumn());
	}
	return nodeStatements;
}

Node* Parser::statement() {
	printf("statement \n");
	Node* nodeStatement = new Node(STATEMENT, currentToken->getLine(), currentToken->getColumn());
	if (currentToken->getName() == IdentifierToken && (compare(currentToken->getContent(), "write\0"))) {
		Leaf* leafWrite = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
		nodeStatement->addLeaf((SuperTree*)leafWrite);
		currentToken = scanner->getNextToken();
		if (currentToken->getName() == OpenBracketToken) {
			Leaf* leafOpenBracket = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
			nodeStatement->addLeaf((SuperTree*)leafOpenBracket);
			currentToken = scanner->getNextToken();
			Node* nodeExp = exp();
			nodeStatement->addNode((SuperTree*)nodeExp);
			if (currentToken->getName() == CloseBracketToken) {
				Leaf* leafCloseBracket = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
				nodeStatement->addLeaf((SuperTree*)leafCloseBracket);
				currentToken = scanner->getNextToken();
			} else  {
				error("in statement(): no CloseBracketToken \0", currentToken->getLine(), currentToken->getColumn());
			}
		} else {
			error("in statement(): no OpenBracketToken \0", currentToken->getLine(), currentToken->getColumn());
		}
	} else if (currentToken->getName() == IdentifierToken && (compare(currentToken->getContent(), "read\0"))) {
		Leaf* leafRead = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
		nodeStatement->addLeaf((SuperTree*)leafRead);
		currentToken = scanner->getNextToken();
		if (currentToken->getName() == OpenBracketToken) {
			Leaf* leafOpenBracket = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
			nodeStatement->addLeaf((SuperTree*)leafOpenBracket);
			currentToken = scanner->getNextToken();
			if(currentToken->getName() == IdentifierToken /*&& compare(currentToken->getContent(), "Identifier\0")*/){
				Leaf* leafIdentifier = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
				nodeStatement->addLeaf((SuperTree*)leafIdentifier);
				currentToken = scanner->getNextToken();
				Node* nodeIndex = index();
				nodeStatement->addNode((SuperTree*)nodeIndex);
				if (currentToken->getName() == CloseBracketToken) {
					Leaf* leafCloseBracket = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
					nodeStatement->addLeaf((SuperTree*)leafCloseBracket);
					currentToken = scanner->getNextToken();
				} else {
					error("in statement(): no CloseBracketToken \0", currentToken->getLine(), currentToken->getColumn());
				}
			} else {
				error("in statement(): no IdentifierToken \0", currentToken->getLine(), currentToken->getColumn());
			}
		} else {
			error("in statement(): no OpenBracketToken \0", currentToken->getLine(), currentToken->getColumn());
		}
	} else if (currentToken->getName() == OpenCurlyToken) {
		//printf("Open Curly\n");
		Leaf* leafOpenCurly = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
		nodeStatement->addLeaf((SuperTree*)leafOpenCurly);
		currentToken = scanner->getNextToken();
		//printf(currentToken->getContent());		//Ausgabe: } und das ist richtig so
		//printf("\n");
		Node* nodeStatements = statements();
		nodeStatement->addNode(nodeStatements);
		if (currentToken->getName() == CloseCurlyToken) {
			//printf("Hier sollten wir sein\n");
			Leaf* leafCloseCurly = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
			nodeStatement->addLeaf((SuperTree*)leafCloseCurly);
			//printf("Token vor nextToken:\n");
			//printf(currentToken->getContent());
			//printf("\n");
			currentToken = scanner->getNextToken();

			//printf("Token nach nextToken:\n");
			//printf(currentToken->getContent());         // hier sollte ein End Token sein
			//printf("\n");
		} else {
			error("in statement(): no CloseCurlyToken or OpenCurlyToken \0", currentToken->getLine(), currentToken->getColumn());
		}
	} else if (currentToken->getName() == IdentifierToken && (compare(currentToken->getContent(), "if\0") || compare(currentToken->getContent(), "IF\0"))) {
		Leaf* leafIf = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
		nodeStatement->addLeaf((SuperTree*)leafIf);
		currentToken = scanner->getNextToken();
		if (currentToken->getName() == OpenBracketToken) {
			Leaf* leafOpenBracket = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
			nodeStatement->addLeaf((SuperTree*)leafOpenBracket);
			currentToken = scanner->getNextToken();
			Node* nodeExp = exp();
			nodeStatement->addNode(nodeExp);
			if (currentToken->getName() == CloseBracketToken) {
				Leaf* leafCloseBracket = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
				nodeStatement->addLeaf((SuperTree*)leafCloseBracket);
				currentToken = scanner->getNextToken();
				Node* nodeStatement2 = statement();

				printf("<<<<<<<<<<<<<<< in statement if: %s \n", currentToken->getContent());

				nodeStatement->addNode(nodeStatement2);

				if (currentToken->getName() == IdentifierToken && (compare(currentToken->getContent(), "else\0") || compare(currentToken->getContent(), "ELSE\0"))) {
					Leaf* leafElse = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
					nodeStatement->addLeaf((SuperTree*)leafElse);
					currentToken = scanner->getNextToken();
					Node* nodeStatement3 = statement();
					nodeStatement->addNode((SuperTree*)nodeStatement3);

				} else {
					error("in statement(): no else \0", currentToken->getLine(), currentToken->getColumn());
				}
			} else {
				error("in statement(): no CloseBracketToken \0", currentToken->getLine(), currentToken->getColumn());
			}
		} else {
			error("in statement(): no OpenBracketToken \0", currentToken->getLine(), currentToken->getColumn());
		}
	} else if (currentToken->getName() == IdentifierToken && (compare(currentToken->getContent(), "while\0")|| (compare(currentToken->getContent(), "WHILE\0")))) {
		Leaf* leafWhile = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
		nodeStatement->addLeaf((SuperTree*)leafWhile);
		currentToken = scanner->getNextToken();
		if (currentToken->getName() == OpenBracketToken) {
			Leaf* leafOpenBracket = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
			nodeStatement->addLeaf((SuperTree*)leafOpenBracket);
			currentToken = scanner->getNextToken();
			Node* nodeExp = exp();
			nodeStatement->addNode((SuperTree*)nodeExp);
			if (currentToken->getName() == CloseBracketToken) {
				Leaf* leafCloseBracket = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
				nodeStatement->addLeaf((SuperTree*)leafCloseBracket);
				currentToken = scanner->getNextToken();
				Node* nodeStatement2 = statement();
				nodeStatement->addNode((SuperTree*)nodeStatement2);
			} else {
				error("in statement(): no CloseBracketToken \0", currentToken->getLine(), currentToken->getColumn());
			}
		} else {
			error("in statement(): no OpenBracketToken \0", currentToken->getLine(), currentToken->getColumn());
		}
	} else if (currentToken->getName() == IdentifierToken) {
		Leaf* leafIdentifier = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
		nodeStatement->addLeaf((SuperTree*)leafIdentifier);
		currentToken = scanner->getNextToken();
		Node* nodeIndex = index();
		nodeStatement->addNode((SuperTree*)nodeIndex);
		if (currentToken->getName() == DoubleEqualsToken) {
			Leaf* leafDoubleEquals = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
			nodeStatement->addLeaf((SuperTree*)leafDoubleEquals);
			currentToken = scanner->getNextToken();
			Node* nodeExp = exp();
			nodeStatement->addNode((SuperTree*)nodeExp);
		} else {
			error("in statement(): no DoubleEqualsToken \0", currentToken->getLine(), currentToken->getColumn());
		}
	} else {
		error("in statement(): no IdentifierToken \0", currentToken->getLine(), currentToken->getColumn());
	}
	return nodeStatement;
}


Node* Parser::exp() {
	printf("exp \n");
	Node* nodeExp = new Node(EXP, currentToken->getLine(), currentToken->getColumn());
	if (currentToken->getName() == OpenBracketToken
		|| (currentToken->getName() == IdentifierToken)
		|| currentToken->getName() == IntegerToken
		|| currentToken->getName() == MinusToken
		|| currentToken->getName() == ExclamationToken ) {

		Node* nodeExp2 = exp2();
		nodeExp->addNode((SuperTree*)nodeExp2);
		Node* nodeOpExp = op_exp();
		nodeExp->addNode((SuperTree*)nodeOpExp);

	} else {
		error("in exp(): no IdentifierToken or OpenBracketToken or IntegerToken, or MinusToken, or ExclamationToken \0", currentToken->getLine(), currentToken->getColumn());
	}

	return nodeExp;
}


Node* Parser::exp2() {
	printf("exp2 \n");
	Node* node = new Node(EXP2, currentToken->getLine(), currentToken->getColumn());
	if (currentToken->getName() == OpenBracketToken) {
		Leaf* leafOpenB = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
		node->addLeaf((SuperTree*)leafOpenB);
		currentToken = scanner->getNextToken();
		Node* nodeExp = exp();
		node->addNode((SuperTree*)nodeExp);
		if (currentToken->getName() == CloseBracketToken) {
			Leaf* leafCloseB = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
			node->addLeaf((SuperTree*)leafCloseB);
			currentToken = scanner->getNextToken();
		} else {
			error("in exp2(): no CloseBracketToken \0", currentToken->getLine(), currentToken->getColumn());
		}
	} else if (currentToken->getName() == IdentifierToken /*&& compare(currentToken->getContent(), "Identifier\0")*/) {
		Leaf* leafIdentifier = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
		node->addLeaf((SuperTree*)leafIdentifier);
		currentToken = scanner->getNextToken();
		Node* nodeIndex = index();
		node->addNode((SuperTree*)nodeIndex);
	} else if (currentToken->getName() == IntegerToken) {
		Leaf* leafInteger = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
		leafInteger->setValue(currentToken->getContent());
		node->addLeaf((SuperTree*)leafInteger);
		currentToken = scanner->getNextToken();
	} else if (currentToken->getName() == MinusToken) {
		Leaf* leafMinus = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
		node->addLeaf((SuperTree*)leafMinus);
		currentToken = scanner->getNextToken();
		Node* nodeExp2 = exp2();
		node->addNode((SuperTree*)nodeExp2);
	} else if (currentToken->getName() == ExclamationToken) {
		printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< exp2!!!!!!!!!!!!!!!!!! \n");
		Leaf* leafExclamation = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
		node->addLeaf((SuperTree*)leafExclamation);
		currentToken = scanner->getNextToken();
		Node* nodeExp2 = exp2();
		node->addNode((SuperTree*)nodeExp2);
	} else {
		error("in exp2(): no OpenBracketToken or IdentifierToken or IntegerToken or MinusToken or ExclamationToken \0", currentToken->getLine(), currentToken->getColumn());
	}

	return node;
}

Node* Parser::index() {
	printf("index \n");
	Node* node = new Node(INDEX, currentToken->getLine(), currentToken->getColumn());

	if (currentToken->getName() == OpenSquareToken) {
		Leaf* leafOpenS = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
		node->addLeaf((SuperTree*)leafOpenS);
		currentToken = scanner->getNextToken();
		Node* nodeExp = exp();
		node->addNode((SuperTree*)nodeExp);
		if (currentToken->getName() == CloseSquareToken) {
			Leaf* leafCloseS = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
			node->addLeaf((SuperTree*)leafCloseS);
			currentToken = scanner->getNextToken();
		} else {
			error("in index(): no CloseSquareToken \0", currentToken->getLine(), currentToken->getColumn());
		}
	} else if (currentToken->getName() == PlusToken || currentToken->getName() == MinusToken || currentToken->getName() == MultiplyToken
			|| currentToken->getName() == DivideToken || currentToken->getName() == SmallToken || currentToken->getName() == BigToken
			|| currentToken->getName() == EqualsToken || currentToken->getName() == SmallerDoubleBiggerToken || currentToken->getName() == EndToken
			|| currentToken->getName() == AndToken || currentToken->getName() == DoubleEqualsToken || currentToken->getName() == CloseBracketToken
			|| currentToken->getName() == SemicolonToken || currentToken->getName() == CloseSquareToken
			|| (currentToken->getName() == IdentifierToken && (compare(currentToken->getContent(), "else\0")))) {


	} else {
		error("in index(): is IdentifierToken \0", currentToken->getLine(), currentToken->getColumn());
	}

	return node;
}

Node* Parser::op_exp(){
	printf("op_exp \n");
	Node* node = new Node(OP_EXP, currentToken->getLine(), currentToken->getColumn());
	if (currentToken->getName() == CloseBracketToken || currentToken->getName() == CloseSquareToken || currentToken->getName() == SemicolonToken
			|| (currentToken->getName() == IdentifierToken && (compare(currentToken->getContent(), "else\0")))	) {

	} else if (currentToken->getName() == PlusToken || currentToken->getName() == MinusToken || currentToken->getName() == MultiplyToken
			|| currentToken->getName() == DivideToken || currentToken->getName() == SmallToken || currentToken->getName() == BigToken
			|| currentToken->getName() == EqualsToken || currentToken->getName() == SmallerDoubleBiggerToken
			|| currentToken->getName() == AndToken || currentToken->getName() == EndToken) {

		Node* nodeOp = op();
		node->addNode((SuperTree*)nodeOp);
		Node* nodeExp = exp();
		node->addNode((SuperTree*)nodeExp);
	} else {
		error("in op_exp(): is IdentifierToken \0", currentToken->getLine(), currentToken->getColumn());
	}
	return node;
}

Node* Parser::op(){
	printf("op \n");
	Node* node = new Node(OP, currentToken->getLine(), currentToken->getColumn());
	if (currentToken->getName() == PlusToken) {
		Leaf* leafPlus = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
		node->addLeaf((SuperTree*)leafPlus);
		currentToken = scanner->getNextToken();
	}
	else if (currentToken->getName() == MinusToken) {
		Leaf* leafMinus = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
		node->addLeaf((SuperTree*)leafMinus);
		currentToken = scanner->getNextToken();
	}
	else if (currentToken->getName() == MultiplyToken) {
		Leaf* leafMultiply = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
		node->addLeaf((SuperTree*)leafMultiply);
		currentToken = scanner->getNextToken();
	}
	else  if (currentToken->getName() == DivideToken) {
		Leaf* leafDivide = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
		node->addLeaf((SuperTree*)leafDivide);
		currentToken = scanner->getNextToken();
	}
	else if (currentToken->getName() == SmallToken) {
		Leaf* leafSmall = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
		node->addLeaf((SuperTree*)leafSmall);
		currentToken = scanner->getNextToken();
	}
	else if (currentToken->getName() == BigToken) {
		Leaf* leafBig = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
		node->addLeaf((SuperTree*)leafBig);
		currentToken = scanner->getNextToken();
	}
	else if (currentToken->getName() == EqualsToken) {
		Leaf* leafEquals = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
		node->addLeaf((SuperTree*)leafEquals);
		currentToken = scanner->getNextToken();
	}
	else if (currentToken->getName() == SmallerDoubleBiggerToken) {
		Leaf* leafSmaller = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
		node->addLeaf((SuperTree*)leafSmaller);
		currentToken = scanner->getNextToken();
	}
	else if (currentToken->getName() == AndToken) {
		Leaf* leafAnd = new Leaf(currentToken->getKeyIndex(), currentToken->getKeyOffset(), symTab, LEAF, currentToken->getLine(), currentToken->getColumn());
		node->addLeaf((SuperTree*)leafAnd);
		currentToken = scanner->getNextToken();
	} else {
		error("in op(): no Operator \0", currentToken->getLine(), currentToken->getColumn());
	}


	return node;
}







void Parser::typeCheckStart(Tree* parseTree){

	printf("TypeCheckStart \n");

	SuperTreeList* list = parseTree->getNodesAndLeaves();

	if(parseTree->gt == PROG && list->getSuperTree(0)->gt == DECLS && list->getSuperTree(1)->gt == STATEMENTS) {
		typeCheckDecls((Node*)list->getSuperTree(0));
		typeCheckStatements((Node*)list->getSuperTree(1));
		parseTree->store(noType);
	}
}

void Parser::typeCheckDecls(Node* nodeDecls) {

	printf("TypeCheckDecls \n");

	SuperTreeList* list = nodeDecls->getNodesAndLeaves();
	int listSize = list->getSize();
	printf("listsize Decls: %d \n", listSize);

	if(listSize == 3) {
		if(list->getSuperTree(0)->gt == DECL && list->getSuperTree(1)->gt == LEAF && list->getSuperTree(2)->gt == DECLS) {

			typeCheckDecl((Node*)list->getSuperTree(0));
			typeCheckDecls((Node*)list->getSuperTree(2));
			nodeDecls->store(noType);
		}
	}
	else if(listSize == 0) {
		nodeDecls->store(noType);
	}
}

void Parser::typeCheckDecl(Node* nodeDecl) {

	printf("TypeCheckDecl \n");

	SuperTreeList* list = nodeDecl->getNodesAndLeaves();
	int listSize = list->getSize();

	printf("listsize Decl: %d \n", listSize);

	if(listSize == 3) {
		if(list->getSuperTree(0)->gt == LEAF && list->getSuperTree(1)->gt == ARRAY && list->getSuperTree(2)->gt == LEAF) {
			typeCheckArray((Node*)list->getSuperTree(1));

			printf("<<<<<<<<<<<<<<<< in typeCheckDecl  %d \n", ((Leaf*)list->getSuperTree(2))->getLine());


			if(((Leaf*)list->getSuperTree(2))->getType() != noType) {
					error("in typeCheckDecl(): identifier already defined \0", list->getSuperTree(2)->getLine(), list->getSuperTree(2)->getColumn() ); //identifier already defined
					nodeDecl->store(errorType);
			}
			else if(((Node*)list->getSuperTree(1))->getType() == errorType) {
				nodeDecl->store(errorType);
			}
			else {
				nodeDecl->store(noType);
				if(((Node*)list->getSuperTree(1))->getType() == arrayType) {
					((Leaf*)list->getSuperTree(2))->store(intArrayType);
				}
				else {
					((Leaf*)list->getSuperTree(2))->store(intType);
				}
			}
		}
	}
}

void Parser::typeCheckArray(Node* nodeArray) {

	printf("TypeCheckArray \n");

	SuperTreeList* list = nodeArray->getNodesAndLeaves();
	int listSize = list->getSize();

	printf("listsize Array: %d \n", listSize);

	if (listSize == 3) {
		if (list->getSuperTree(0)->gt == LEAF && list->getSuperTree(1)->gt == LEAF && list->getSuperTree(2)->gt == LEAF) {
			if (((Leaf*)list->getSuperTree(1))->getValue() > 0) {
				nodeArray->store(arrayType);
			}
			else {
				error("in typeCheckArray(): no valid dimension \0", list->getSuperTree(1)->getLine(), list->getSuperTree(1)->getColumn()); //no valid dimension
				nodeArray->store(errorType);
			}
		}
	}

	if (listSize == 0) {
		nodeArray->store(noType);
	}
}

void Parser::typeCheckStatements(Node* nodeStatements) {

	printf("TypeCheckStatements \n");

	SuperTreeList* list = nodeStatements->getNodesAndLeaves();
	int listSize = list->getSize();

	printf("listsize Statements: %d \n", listSize);

	if (listSize == 3) {
		if (list->getSuperTree(0)->gt == STATEMENT && list->getSuperTree(1)->gt == LEAF && list->getSuperTree(2)->gt == STATEMENTS) {
			typeCheckStatement((Node*)list->getSuperTree(0));
			typeCheckStatements((Node*)list->getSuperTree(2));
			nodeStatements->store(noType);
		}
	}
	if (listSize == 0) {
		nodeStatements->store(noType);
	}
}

void Parser::typeCheckStatement(Node* nodeStatement) {

	printf("TypeCheckStatement \n");

	SuperTreeList* list = nodeStatement->getNodesAndLeaves();
	int listSize = list->getSize();

	printf("listsize Statement: %d \n", listSize);

	if (listSize == 4) {
		if (list->getSuperTree(0)->gt == LEAF && list->getSuperTree(1)->gt == INDEX && list->getSuperTree(2)->gt == LEAF && list->getSuperTree(3)->gt == EXP) {
			printf("#############################richtiges if\n");
			typeCheckExp((Node*)list->getSuperTree(3));
			typeCheckIndex((Node*)list->getSuperTree(1));
			if (((Leaf*)list->getSuperTree(0))->getType() == noType) {
				error("in typeCheckStatement(): identifier not defined \0", list->getSuperTree(0)->getLine(), list->getSuperTree(0)->getColumn()); //identifier not defined
				nodeStatement->store(errorType);
			}
			else if (((Node*)list->getSuperTree(3))->getType() == intType
					&& (( ((Leaf*)list->getSuperTree(0))->getType() == intType && ((Node*)list->getSuperTree(1))->getType() == noType)
							|| (((Leaf*)list->getSuperTree(0))->getType() == intArrayType && ((Node*)list->getSuperTree(1))->getType() == arrayType))) {
				nodeStatement->store(noType);
			}
			else {
				error("in typeCheckStatement(): incompatible types \0", list->getSuperTree(3)->getLine(), list->getSuperTree(3)->getColumn()); //incompatible types
				nodeStatement->store(errorType);
			}
		}
		//write
		else if (list->getSuperTree(0)->gt == LEAF && list->getSuperTree(1)->gt == LEAF && list->getSuperTree(2)->gt == EXP && list->getSuperTree(3)->gt == LEAF) {
			printf("############################################falsches if\n");
			printf("0: %d \n", ((Leaf*)list->getSuperTree(0))->getLine());
			printf("0: %d \n", ((Leaf*)list->getSuperTree(0))->getColumn());
			printf("1: %d \n", ((Leaf*)list->getSuperTree(1))->getLine());
			printf("1: %d \n", ((Leaf*)list->getSuperTree(1))->getColumn());
			printf("2: %d \n", ((Leaf*)list->getSuperTree(2))->getLine());
			printf("2: %d \n", ((Leaf*)list->getSuperTree(2))->getColumn());
			printf("3: %d \n", ((Leaf*)list->getSuperTree(3))->getLine());
			printf("3: %d \n", ((Leaf*)list->getSuperTree(3))->getColumn());
			typeCheckExp((Node*)list->getSuperTree(2));
			nodeStatement->store(noType);
		}
		else {
			printf("##################so ein scheiss fehler\n");
		}
	}

	if (listSize == 5) {
		//read
		if (list->getSuperTree(0)->gt == LEAF && list->getSuperTree(1)->gt == LEAF && list->getSuperTree(2)->gt == LEAF && list->getSuperTree(3)->gt == INDEX &&
				list->getSuperTree(4)->gt == LEAF) {
			typeCheckIndex((Node*)list->getSuperTree(3));
			if (((Leaf*)list->getSuperTree(2))->getType() == noType) {
				error("in typeCheckStatement(): identifier not defined \0", list->getSuperTree(2)->getLine(), list->getSuperTree(2)->getColumn()); //identifier not defined
				nodeStatement->store(errorType);
			}
			else if ((((Leaf*)list->getSuperTree(2))->getType() == intType && ((Node*)list->getSuperTree(3))->getType() == noType)
					|| (((Leaf*)list->getSuperTree(2))->getType() == intArrayType && ((Node*)list->getSuperTree(3))->getType() == arrayType)) {
				nodeStatement->store(noType);
			}
			else {
				error("in typeCheckStatement(): incompatible types \0", list->getSuperTree(2)->getLine(), list->getSuperTree(2)->getColumn()); //incompatible types
				nodeStatement->store(errorType);
			}
		}
		//while
		else if(list->getSuperTree(0)->gt == LEAF && list->getSuperTree(1)->gt == LEAF && list->getSuperTree(2)->gt == EXP &&
						list->getSuperTree(3)->gt == LEAF && list->getSuperTree(4)->gt == STATEMENT){
					typeCheckExp((Node*)list->getSuperTree(2));
					typeCheckStatement((Node*)list->getSuperTree(4));
					if(list->getSuperTree(2)->getType() == errorType){
						nodeStatement->store(errorType);
					}
					else{
						nodeStatement->store(noType);
					}
				}
	}

	// Statements
	if(listSize == 3){
		printf("###################################alles doof\n");
		if(list->getSuperTree(0)->gt == LEAF && list->getSuperTree(1)->gt == STATEMENTS && list->getSuperTree(2)->gt == LEAF){
			printf("################################################geschweifte klammern sind toll\n");
			typeCheckStatements((Node*)list->getSuperTree(1));
			nodeStatement->store(noType);
		}
	}

	// if
	if(listSize == 7){
		if(list->getSuperTree(0)->gt == LEAF && list->getSuperTree(1)->gt == LEAF && list->getSuperTree(2)->gt == EXP && list->getSuperTree(3)->gt == LEAF &&
				list->getSuperTree(4)->gt == STATEMENT && list->getSuperTree(5)->gt == LEAF && list->getSuperTree(6)->gt == STATEMENT){
			typeCheckExp((Node*)list->getSuperTree(2));
			typeCheckStatement((Node*)list->getSuperTree(4));
			typeCheckStatement((Node*)list->getSuperTree(6));
			if(list->getSuperTree(2)->getType() == errorType){
				nodeStatement->store(errorType);
			}
			else{
				nodeStatement->store(noType);
			}
		}
	}


}

void Parser::typeCheckIndex(Node* nodeIndex){

	printf("TypeCheckIndex \n");

	SuperTreeList* list = nodeIndex->getNodesAndLeaves();
	int listSize = list->getSize();

	printf("listsize Index: %d \n", listSize);

	// array
	if(listSize == 3){
		if(list->getSuperTree(0)->gt == LEAF && list->getSuperTree(1)->gt == EXP && list->getSuperTree(2)->gt == LEAF){
			typeCheckExp((Node*)list->getSuperTree(1));
			if(list->getSuperTree(2)->getType() == errorType){
				nodeIndex->store(errorType);
			}
			else{
				nodeIndex->store(arrayType);
			}
		}
	}
	// Epsilon
	if(listSize == 0){
		nodeIndex->store(noType);
	}
}

void Parser::typeCheckExp(Node* nodeExp){

	printf("TypeCheckExp \n");

	SuperTreeList* list = nodeExp->getNodesAndLeaves();
	int listSize = list->getSize();

	printf("listsize Exp: %d \n", listSize);

	if(listSize == 2){
		if(list->getSuperTree(0)->gt == EXP2 && list->getSuperTree(1)->gt == OP_EXP){
			typeCheckExp2((Node*)list->getSuperTree(0));
			typeCheckOp_Exp((Node*)list->getSuperTree(1));
			if(list->getSuperTree(1)->getType() == noType){
				nodeExp->store(list->getSuperTree(0)->getType());
			}
			else if(list->getSuperTree(0)->getType() != list->getSuperTree(1)->getType()){
				nodeExp->store(errorType);
			}
			else{
				nodeExp->store(list->getSuperTree(0)->getType());
			}
		}
	}

}

void Parser::typeCheckExp2(Node* nodeExp2){

	printf("TypeCheckExp2 \n");

	SuperTreeList* list = nodeExp2->getNodesAndLeaves();
	int listSize = list->getSize();

	printf("listsize Exp2: %d \n", listSize);

	if(listSize == 3){
		if(list->getSuperTree(0)->gt == LEAF && list->getSuperTree(1)->gt == EXP && list->getSuperTree(2)->gt == LEAF){
			typeCheckExp((Node*)list->getSuperTree(1));
			nodeExp2->store(list->getSuperTree(1)->getType());
		}
	}

	if(listSize == 2){
		if(list->getSuperTree(0)->gt == LEAF && list->getSuperTree(1)->gt == INDEX){
			typeCheckIndex((Node*)list->getSuperTree(1));
			if(((Leaf*)list->getSuperTree(0))->getType() == noType){
					error("in typeCheckExp2(): identifier not defined \0", list->getSuperTree(0)->getLine(), list->getSuperTree(0)->getColumn()); // identifier not defined
					nodeExp2->store(errorType);
			}
			else if(list->getSuperTree(0)->getType() == intType && list->getSuperTree(1)->getType() == noType){
					nodeExp2->store(list->getSuperTree(0)->getType());
			}
			else if(list->getSuperTree(0)->getType() == intArrayType && list->getSuperTree(1)->getType() == arrayType){
					nodeExp2->store(intType);
			}
			else{
				error("in typeCheckExp2(): no primitive Type \0", list->getSuperTree(0)->getLine(), list->getSuperTree(0)->getColumn()); // no primitive Type
				nodeExp2->store(errorType);
			}
		}
	}

	if(listSize == 1){
		printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< listSize == 1 \n");
		if(list->getSuperTree(0)->gt == LEAF){
			printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< inttype \n");
			nodeExp2->store(intType);
		}
	}

	if(listSize == 2){
		printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< list 2 \n");
		if(list->getSuperTree(0)->gt == LEAF && list->getSuperTree(1)->gt == EXP2){
			printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< leaf exp2 \n");
			//TODO ! richtig speichern
			char* test = ((Leaf*)list->getSuperTree(0))->getInformation()->getName();
			printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< vor typeckeckexp2 mit int \n");
			typeCheckExp2((Node*)list->getSuperTree(1));
			printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< nach typecheckexp2 von supertree(1) \n");
			if(compare(((Leaf*)list->getSuperTree(0))->getInformation()->getName(),"-")){
				nodeExp2->store(list->getSuperTree(1)->getType());
			}
			else if(compare(((Leaf*)list->getSuperTree(0))->getInformation()->getName(),"!")) {
				//nodeExp2->store(list->getSuperTree(1)->getType());
				printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< ! erkannt \n");
				if(list->getSuperTree(1)->getType() != intType){ //TODO !?
					printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< ist kein intType \n");
					nodeExp2->store(errorType);
				}
				else{
					printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< ist inttype \n");
					nodeExp2->store(intType);
				}
			}
		}
	}
}

void Parser::typeCheckOp_Exp(Node* nodeOp_Exp){

	printf("TypeCheckOp_Exp\n");

	SuperTreeList* list = nodeOp_Exp->getNodesAndLeaves();
	int listSize = list->getSize();

	printf("listsize Op_Exp: %d \n", listSize);

	if(listSize == 2){
		if(list->getSuperTree(0)->gt == OP && list->getSuperTree(1)->gt == EXP){
			typeCheckOp((Node*)list->getSuperTree(0));
			typeCheckExp((Node*)list->getSuperTree(1));
			nodeOp_Exp->store(list->getSuperTree(1)->getType());
		}
	}

	if(listSize == 0){
		nodeOp_Exp->store(noType);
	}
}

void Parser::typeCheckOp(Node* nodeOp){

	printf("TypeCheckOp \n");

	SuperTreeList* list = nodeOp->getNodesAndLeaves();
	int listSize = list->getSize();

	printf("listsize Op: %d \n", listSize);

//	printf("getName: %s \n", ((Leaf*)list->getSuperTree(0))->getInformation()->getName());

	if(listSize == 1){
		if(list->getSuperTree(0)->gt == LEAF){

			if(compare(((Leaf*)list->getSuperTree(0))->getInformation()->getName(),"+")){
				nodeOp->store(opPlusType);
				printf("hier \n");
			}
			else if(compare(((Leaf*)list->getSuperTree(0))->getInformation()->getName(),"-")){
				nodeOp->store(opMinusType);

			}
			else if(compare(((Leaf*)list->getSuperTree(0))->getInformation()->getName(),"*")){
				nodeOp->store(opMultType);

			}
			else if(compare(((Leaf*)list->getSuperTree(0))->getInformation()->getName(),"/")){
				nodeOp->store(opDivType);

			}
			else if(compare(((Leaf*)list->getSuperTree(0))->getInformation()->getName(),"<")){
				nodeOp->store(opLessType);

			}
			else if(compare(((Leaf*)list->getSuperTree(0))->getInformation()->getName(),">")){
				nodeOp->store(opGreaterType);
			}
			else if(compare(((Leaf*)list->getSuperTree(0))->getInformation()->getName(),"=")){
				nodeOp->store(opEqualType);
			}
			else if(compare(((Leaf*)list->getSuperTree(0))->getInformation()->getName(),"<:>")){
				nodeOp->store(opUnEqualType);

			}
			else if(compare(((Leaf*)list->getSuperTree(0))->getInformation()->getName(),"&")){
				nodeOp->store(opAndType);

			}

		}

	}


}


void Parser::makeCodeStart(Tree* parseTree) {

	printf("makeCodeStart \n");

	SuperTreeList* list = parseTree->getNodesAndLeaves();
	int listSize = list->getSize();

	printf("listSize Start: %d \n", listSize);


	if(listSize == 2) {
		if(parseTree->gt == PROG && list->getSuperTree(0)->gt == DECLS && list->getSuperTree(1)->gt == STATEMENTS) {
			makeCodeDecls((Node*)list->getSuperTree(0));
			makeCodeStatements((Node*)list->getSuperTree(1));
			print("STP");
		}
	}

}

void Parser::makeCodeDecls(Node* nodeDecls) {
	printf("makeCodeDecls \n");

	SuperTreeList* list = nodeDecls->getNodesAndLeaves();
	int listSize = list->getSize();

	printf("listSize Decls: %d \n", listSize);

	if(listSize == 3) {
		if(list->getSuperTree(0)->gt == DECL && list->getSuperTree(1)->gt == LEAF && list->getSuperTree(2)->gt == DECLS) {
			makeCodeDecl((Node*)list->getSuperTree(0));
			makeCodeDecls((Node*)list->getSuperTree(2));
		}
	}
}

void Parser::makeCodeDecl(Node* nodeDecl) {
	printf("makeCodeDecl \n");

	SuperTreeList* list = nodeDecl->getNodesAndLeaves();
	int listSize = list->getSize();

	printf("listSize Decl: %d \n", listSize);

	if(listSize == 3) {
		if(list->getSuperTree(0)->gt == LEAF && list->getSuperTree(1)->gt == ARRAY && list->getSuperTree(2)->gt == LEAF) {
			print("DS ");
			print("$");
			print(((Leaf*)list->getSuperTree(2))->getInformation()->getName());
			print(" ");
			makeCodeArray((Node*)list->getSuperTree(1));
		}
	}
}

void Parser::makeCodeArray(Node* nodeArray) {
	printf("makeCodeArray \n");

	SuperTreeList* list = nodeArray->getNodesAndLeaves();
	int listSize = list->getSize();

	printf("listSize Array: %d \n", listSize);

	if(listSize == 3) {
		if(list->getSuperTree(0)->gt == LEAF && list->getSuperTree(1)->gt == LEAF && list->getSuperTree(2)->gt == LEAF) {
			print(((Leaf*)list->getSuperTree(1))->getValue());
			print("\n");
		}
	}
	else if(listSize == 0) {
		print("1");
		print("\n");
	}
}

void Parser::makeCodeStatements(Node* nodeStatements) {
	printf("makeCodeStatements \n");

	SuperTreeList* list = nodeStatements->getNodesAndLeaves();
	int listSize = list->getSize();

	printf("listSize Statements: %d \n", listSize);

	if(listSize == 3) {
		if(list->getSuperTree(0)->gt == STATEMENT && list->getSuperTree(1)->gt == LEAF && list->getSuperTree(2)->gt == STATEMENTS) {
			makeCodeStatement((Node*)list->getSuperTree(0));
			makeCodeStatements((Node*)list->getSuperTree(2));
		}
	}
	else if(listSize == 0) {
		print("NOP ");
		print("\n");
	}
}

void Parser::makeCodeStatement(Node* nodeStatement) {
	printf("makeCodeStatement \n");


	SuperTreeList* list = nodeStatement->getNodesAndLeaves();
	int listSize = list->getSize();

	printf("listSize Statement: %d \n", listSize);

	if(listSize == 4) {
		if(list->getSuperTree(0)->gt == LEAF && list->getSuperTree(1)->gt == INDEX && list->getSuperTree(2)->gt == LEAF && list->getSuperTree(3)->gt == EXP) {
			makeCodeExp((Node*)list->getSuperTree(3));
			print("LA ");
			print("$");
			print(((Leaf*)list->getSuperTree(0))->getInformation()->getName());
			print("\n");
			makeCodeIndex((Node*)list->getSuperTree(1));
			print("STR ");
			print("\n");
		}
		if(list->getSuperTree(0)->gt == LEAF && list->getSuperTree(1)->gt == LEAF && list->getSuperTree(2)->gt == EXP && list->getSuperTree(3)->gt == LEAF) {
			makeCodeExp((Node*)list->getSuperTree(2));
			print("PRI ");
			print("\n");
		}
	}
	else if(listSize == 5) {
		if(list->getSuperTree(0)->gt == LEAF && list->getSuperTree(1)->gt == LEAF && list->getSuperTree(2)->gt == LEAF && list->getSuperTree(3)->gt == INDEX && list->getSuperTree(4)->gt == LEAF) {
			print("REA ");
			print("\n");
			print("LA ");
			print("$");
			print(((Leaf*)list->getSuperTree(2))->getInformation()->getName());
			print("\n");
			makeCodeIndex((Node*)list->getSuperTree(3));
			print("STR ");
			print("\n");
		}
		else if(list->getSuperTree(0)->gt == LEAF && list->getSuperTree(1)->gt == LEAF && list->getSuperTree(2)->gt == EXP
				&& list->getSuperTree(3)->gt == LEAF && list->getSuperTree(4)->gt == STATEMENT){

			char currentLabel1pre[10];
			char* currentLabel1 = getNextLabel(currentLabel1pre);
			char currentLabel2pre[10];
			char* currentLabel2 = getNextLabel(currentLabel2pre);


			print("#");
			print(currentLabel1);
			print("\n");
			print("NOP ");
			print("\n");
			makeCodeExp((Node*)list->getSuperTree(2));
			print("JIN ");
			print("#");
			print(currentLabel2);
			print("\n");
			makeCodeStatement((Node*)list->getSuperTree(4));
			print("JMP ");
			print("#");
			print(currentLabel1);
			print("\n");
			print("#");
			print(currentLabel2);
			print("\n");
			print("NOP ");
			print("\n");

		}
	}
	else if(listSize == 3) {
		if(list->getSuperTree(0)->gt == LEAF && list->getSuperTree(1)->gt == STATEMENTS && list->getSuperTree(2)->gt == LEAF) {
			makeCodeStatements((Node*)list->getSuperTree(1));
		}
	}
	else if(listSize == 7) {
		if(list->getSuperTree(0)->gt == LEAF && list->getSuperTree(1)->gt == LEAF && list->getSuperTree(2)->gt == EXP && list->getSuperTree(3)->gt == LEAF && list->getSuperTree(4)->gt == STATEMENT && list->getSuperTree(5)->gt == LEAF && list->getSuperTree(6)->gt == STATEMENT) {

			char currentLabel1pre[10];
			char* currentLabel1 = getNextLabel(currentLabel1pre);
			char currentLabel2pre[10];
			char* currentLabel2 = getNextLabel(currentLabel2pre);



			printf(">>>>>>>>>>>>>>> Die beiden Label sind: %s, %s", currentLabel1, currentLabel2);

			makeCodeExp((Node*)list->getSuperTree(2));
			print("JIN ");
			print("#");
			print(currentLabel1);
			print("\n");
			makeCodeStatement((Node*)list->getSuperTree(4));
			print("JMP ");
			print("#");
			print(currentLabel2);
			print("\n");
			print("#");
			print(currentLabel1);
			print("\n");
			print("NOP ");
			print("\n");
			makeCodeStatement((Node*)list->getSuperTree(6));
			print("#");
			print(currentLabel2);
			print("\n");
			print("NOP ");
			print("\n");
		}
	}

}

void Parser::makeCodeIndex(Node* nodeIndex) {
	printf("makeCodeIndex \n");

	SuperTreeList* list = nodeIndex->getNodesAndLeaves();
	int listSize = list->getSize();

	printf("listSize Index: %d \n", listSize);

	if(listSize == 3) {
		if(list->getSuperTree(0)->gt == LEAF && list->getSuperTree(1)->gt == EXP && list->getSuperTree(2)->gt == LEAF){
			makeCodeExp((Node*)list->getSuperTree(1));
			print("ADD ");
			print("\n");

		}


	}
}

void Parser::makeCodeExp(Node* nodeExp) {
	printf("makeCodeExp \n");

		SuperTreeList* list = nodeExp->getNodesAndLeaves();
		int listSize = list->getSize();

		printf("listSize Exp: %d \n", listSize);

		if(listSize == 2) {
			if(list->getSuperTree(0)->gt == EXP2 && list->getSuperTree(1)->gt == OP_EXP){
				if(list->getSuperTree(1)->getType() == noType ) {
					makeCodeExp2((Node*)list->getSuperTree(0));
				}
				else if(((Node*)list->getSuperTree(1))->getNodesAndLeaves()->getSuperTree(0)->getType() == opGreaterType) {
					makeCodeOp_Exp((Node*)list->getSuperTree(1));
					makeCodeExp2((Node*)list->getSuperTree(0));
					print("LES ");
					print("\n");
				}
				else if(((Node*)list->getSuperTree(1))->getNodesAndLeaves()->getSuperTree(0)->getType() == opUnEqualType) {
					makeCodeExp2((Node*)list->getSuperTree(0));
					makeCodeOp_Exp((Node*)list->getSuperTree(1));
					print("NOT ");
					print("\n");
				}
				else {
					makeCodeExp2((Node*)list->getSuperTree(0));
					makeCodeOp_Exp((Node*)list->getSuperTree(1));
				}
			}
		}
}

void Parser::makeCodeExp2(Node* nodeExp2) {
	printf("makeCodeExp2 \n");

	SuperTreeList* list = nodeExp2->getNodesAndLeaves();
	int listSize = list->getSize();

	printf("listSize Exp2: %d \n", listSize);

	if(listSize == 3) {
		printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<fseiölkjhgjbnmklö \n");
		if(list->getSuperTree(0)->gt == LEAF && list->getSuperTree(1)->gt == EXP && list->getSuperTree(2)->gt == LEAF){
			printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<fseiölkjhgjbnmklö \n");
			//TODO hier hin kommen
			makeCodeExp((Node*)list->getSuperTree(1));
		}
	}
	else if(listSize == 2) {
		if(list->getSuperTree(0)->gt == LEAF && list->getSuperTree(1)->gt == INDEX){
			print("LA ");
			print("$");
			print(((Leaf*)list->getSuperTree(0))->getInformation()->getName());
			print("\n");
			makeCodeIndex((Node*)list->getSuperTree(1));
			print("LV ");
			print("\n");
		}
		else if(list->getSuperTree(0)->gt == LEAF && list->getSuperTree(1)->gt == EXP2){
			if (compare(((Leaf*)list->getSuperTree(0))->getInformation()->getName(),"-")) {
				print("LC ");
				print("0");
				print("\n");
				makeCodeExp2((Node*)list->getSuperTree(1));
				print("SUB ");
				print("\n");
			}
			else {
				makeCodeExp2((Node*)list->getSuperTree(1));
				print("NOT ");
				print("\n");
				printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< !!!!!!!!!!!!!!!!!!! \n");
			}

		}
	}
	else if(listSize == 1) {
		if(list->getSuperTree(0)->gt == LEAF){
			print("LC ");
			print(((Leaf*)list->getSuperTree(0))->getValue());
			print("\n");
		}
	}
}

void Parser::makeCodeOp_Exp(Node* nodeOp_Exp) {
	printf("makeCodeOp_Exp\n");

	SuperTreeList* list = nodeOp_Exp->getNodesAndLeaves();
	int listSize = list->getSize();

	printf("listSize Op_Exp: %d \n", listSize);

	if(listSize == 2) {
		if(list->getSuperTree(0)->gt == OP && list->getSuperTree(1)->gt == EXP) {
			makeCodeExp((Node*)list->getSuperTree(1));
			makeCodeOp((Node*)list->getSuperTree(0));
		}
	}
}

void Parser::makeCodeOp(Node* nodeOp) {
	printf("makeCodeOp\n");

	SuperTreeList* list = nodeOp->getNodesAndLeaves();
	int listSize = list->getSize();

	printf("listSize Op: %d \n", listSize);

	if(listSize == 1) {
		if(list->getSuperTree(0)->gt == LEAF) {
			if(compare(((Leaf*)list->getSuperTree(0))->getInformation()->getName(),"+")){
				print("ADD");
				print("\n");
			}
			else if(compare(((Leaf*)list->getSuperTree(0))->getInformation()->getName(),"-")){
				print("SUB");
				print("\n");
			}
			else if(compare(((Leaf*)list->getSuperTree(0))->getInformation()->getName(),"*")){
				print("MUL");
				print("\n");
			}
			else if(compare(((Leaf*)list->getSuperTree(0))->getInformation()->getName(),"/")){
				print("DIV");
				print("\n");
			}
			else if(compare(((Leaf*)list->getSuperTree(0))->getInformation()->getName(),"<")){
				print("LES");
				print("\n");
			}
			else if(compare(((Leaf*)list->getSuperTree(0))->getInformation()->getName(),">")){

			}
			else if(compare(((Leaf*)list->getSuperTree(0))->getInformation()->getName(),"=")){
				print("EQU");
				print("\n");
			}
			else if(compare(((Leaf*)list->getSuperTree(0))->getInformation()->getName(),"<:>")){
				print("EQU");
				print("\n");
			}
			else if(compare(((Leaf*)list->getSuperTree(0))->getInformation()->getName(),"&")){
				print("AND");
				print("\n");
			}

		}
	}
}




	bool Parser::compare(char* a, char* b){

		bool equal = false;

		int i = 0;
		while(a[i]){
			if (a[i]==b[i])
			{
				equal = true;
			}
			else
			{
				return false;
			}
			i++;
		}

		i = 0;
			while(b[i]){
				if (a[i]==b[i])
				{
					equal = true;
				}
				else
				{
					return false;
				}
				i++;
			}

		return equal;
	}

void Parser::error(char* errorString, int line, int column) {
	print("ERROR: ");
	print(errorString);
	print(", line: ");
	print(line);
	print(", column: ");
	print(column);
	print("\n");
	printf("ERROR: %s, line: %d, column: %d \n", errorString, line, column);
	fclose(fp);
	exit(0);
}


void Parser::print(char* text) {

	fprintf(fp, text);
	printf("                 Code: %s \n", text);
}

void Parser::print(int text) {

	fprintf(fp, "%d", text);
	printf("                 Code: %d \n", text);
}


char* Parser::getNextLabel(char label[10]) {
	printf("Neues Label erstellen: %d \n", labelCount);
	sprintf(label, "label%d ", labelCount);
	labelCount++;
	printf("######################################Neues Label wurde erstellt: %s \n", label);
	return label;
}
