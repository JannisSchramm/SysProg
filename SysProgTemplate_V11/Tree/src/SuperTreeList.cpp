/*
 * SuperTreeList.cpp
 *
 *  Created on: 22.11.2014
 *      Author: dennis
 */

#include "SuperTreeList.h"

SuperTreeList::SuperTreeList(){
	size = 0;
	firstElementTree = 0;
}

SuperTreeList::~SuperTreeList(){
	delete firstElementTree;
}

/**
 * Fügt ein neues SuperTree in den SuperTreeList ein und gibt den Index zurück.
 */
void SuperTreeList::addSuperTree(SuperTree* superTree){
	ElementTree* elementTree = new ElementTree(superTree);
	int index = 0;
	if(firstElementTree == 0) {
		firstElementTree = elementTree;
	} else {
		ElementTree* e = firstElementTree;
		index = 1;
		while(e->hasNextElementTree()) {

			index++;
			e = e->getNextElementTree();
		}

		e->setNextElementTree(elementTree);
	}
	size++;
}

SuperTree* SuperTreeList::getFirstSuperTree(){
	return firstElementTree->getSuperTree();
}

/*
 * ist n höher als wir SuperTreee in der Liste haben, wird das erste SuperTree zurückgegeben
 */
SuperTree* SuperTreeList::getSuperTree(int n){
	ElementTree* e = firstElementTree;
	if(n <= size){
	//	SuperTree e = firstSuperTree;
		for(int i=0; i < n; i++){
			e = e->getNextElementTree();
		}
	}

	return e->getSuperTree();
}

int SuperTreeList::getSize(){
	return size;
}





