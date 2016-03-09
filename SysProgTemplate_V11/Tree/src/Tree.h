/*
 * Tree.h
 *
 *  Created on: 17.10.2014
 *      Author: rebecca
 */

#ifndef TREE_H_
#define TREE_H_




#include "SuperTree.h"
#include "SuperTreeList.h"





class Tree : public SuperTree{
public:
	Tree(grammarType grammartype, int line, int column);
	void addNode(SuperTree* node);
	void addLeaf(SuperTree* leaf);
	virtual ~Tree();
	void typeCheck();
	SuperTreeList* getNodesAndLeaves();
	SuperTreeList* nodesAndLeaves;



private:
};

#endif /* TREE_H_ */
