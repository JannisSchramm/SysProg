/*
 * SuperTree.cpp
 *
 *  Created on: Jan 21, 2015
 *      Author: mude1013
 */


#include "SuperTree.h"

SuperTree :: SuperTree(grammarType grammarType, int myLine, int myColumn){
	gt = grammarType;
	type = noType;
	line = myLine;
	column = myColumn;
}


void SuperTree::store(Type t){
	type = t;
}

Type SuperTree::getType() {
	return type;
}

int SuperTree::getLine() {
	return line;
}

int SuperTree::getColumn() {
	return column;
}


