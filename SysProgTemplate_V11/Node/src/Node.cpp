/*
 * Node.cpp
 *
 *  Created on: 17.10.2014
 *      Author: rebecca
 */

#include "Node.h"

/**
 * Erstellt einen neuen Node.
 */
Node::Node(grammarType grammartype, int line, int column) : Tree(grammartype, line, column) {

}



Node::~Node() {
}

Type Node::getType(){
	return type;
}

bool Node::hasLeave(){

	if(nodesAndLeaves->getSize() > 0)
	{
		return true;
	}
	else{
		return false;
	}

}
