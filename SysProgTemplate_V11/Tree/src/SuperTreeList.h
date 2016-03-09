/*
 * SuperTreeList.h
 *
 *  Created on: Jan 7, 2015
 *      Author: mude1013
 */

#ifndef SUPERTREELIST_H_
#define SUPERTREELIST_H_
#include "../../Tree/src/ElementTree.h"

#include "SuperTree.h"

class SuperTreeList{

public:
	SuperTreeList();
	virtual ~SuperTreeList();
	void addSuperTree(SuperTree* superTree);
	SuperTree* getFirstSuperTree();
	SuperTree* getSuperTree(int index);
	int getSize();

private:
	int size;
	ElementTree* firstElementTree;

};



#endif /* SUPERTREELIST_H_ */
