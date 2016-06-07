/*
 * Parser.h
 *
 *  Created on: 17.10.2014
 *      Author: rebecca
 */



#ifndef PARSER_H_
#define PARSER_H_
#include <fstream>
#include "../../Scanner/src/Scanner.h"
#include "../../Symboltable/src/Symboltable.h"
#include "../../Tree/src/Tree.h"
#include "../../Tree/src/SuperTree.h"
#include "../../Node/src/Node.h"
#include "../../Leaf/src/Leaf.h"

class Parser {
public:
	Parser();
	virtual ~Parser();
	void typeCheck();
	bool compare(char* a, char* b);
private:
	FILE* fp;
	Token* currentToken;
	Symboltable* symTab;
	Scanner* scanner;
	Tree* parseTree;
	int labelCount;

	Tree* parse();
	Tree* prog();
	Node* decls();
	Node* decl();
	Node* array();
	Node* statements();
	Node* statement();
	Node* exp();
	Node* exp2();
	Node* index();
	Node* op_exp();
	Node* op();

	void typeCheckStart(Tree* parseTree);
	void typeCheckDecls(Node* nodeDecls);
	void typeCheckDecl(Node* nodeDecl);
	void typeCheckArray(Node* nodeArray);
	void typeCheckStatements(Node* nodeStatements);
	void typeCheckStatement(Node* nodeStatement);
	void typeCheckIndex(Node* nodeIndex);
	void typeCheckExp(Node* nodeExp);
	void typeCheckExp2(Node* nodeExp2);
	void typeCheckOp_Exp(Node* nodeOp_Exp);
	void typeCheckOp(Node* nodeOp);

	void makeCodeStart(Tree* parseTree);
	void makeCodeDecls(Node* nodeDecls);
	void makeCodeDecl(Node* nodeDecl);
	void makeCodeArray(Node* nodeArray);
	void makeCodeStatements(Node* nodeStatements);
	void makeCodeStatement(Node* nodeStatement);
	void makeCodeIndex(Node* nodeIndex);
	void makeCodeExp(Node* nodeExp);
	void makeCodeExp2(Node* nodeExp2);
	void makeCodeOp_Exp(Node* nodeOp_Exp);
	void makeCodeOp(Node* nodeOp);

	void error(char* errorString, int line, int column);
	void print(char* text);
	void print(int text);
	char* getNextLabel(char label[10]);
};

#endif /* PARSER_H_ */
