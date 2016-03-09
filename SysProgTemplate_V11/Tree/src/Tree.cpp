/*
 * Tree.cpp
 *
 *  Created on: 17.10.2014
 *      Author: rebecca
 */

#include "Tree.h"

/**
 * Erstellt einen neuen Tree.
 */
Tree::Tree(grammarType grammartype, int line, int column): SuperTree(grammartype, line, column) {
	nodesAndLeaves = new SuperTreeList();

}


Tree::~Tree() {
	delete nodesAndLeaves;
}

void Tree::addNode(SuperTree* node) {
	nodesAndLeaves->addSuperTree(node);
}

void Tree::addLeaf(SuperTree* leaf) {
	nodesAndLeaves->addSuperTree(leaf);
}

SuperTreeList* Tree::getNodesAndLeaves(){
	return nodesAndLeaves;
}






