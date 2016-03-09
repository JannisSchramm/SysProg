/*
 * ElementTree.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: mude1013
 */

#include "ElementTree.h"


ElementTree::ElementTree(SuperTree* superTree) {
	mySuperTree = superTree;
	nextElementTree = 0;
}

ElementTree::~ElementTree(){
	delete mySuperTree;
	delete nextElementTree;
}

SuperTree* ElementTree::getSuperTree() {
	return mySuperTree;
}

ElementTree* ElementTree::getNextElementTree() {
	return nextElementTree;
}

void ElementTree::setNextElementTree(ElementTree* e) {
	nextElementTree = e;
}

bool ElementTree::hasNextElementTree() {
	if (nextElementTree == 0) {
		return false;
	} else {
		return true;
	}
}

