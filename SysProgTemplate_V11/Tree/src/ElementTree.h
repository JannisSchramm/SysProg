/*
 * ElementTree.h
 *
 *  Created on: Jan 7, 2015
 *      Author: mude1013
 */

#ifndef ElementTree_H_
#define ElementTree_H_
#include "../../Tree/src/SuperTree.h"

class ElementTree{

public:
	ElementTree(SuperTree* superTree);
	virtual ~ElementTree();
	SuperTree* getSuperTree();
	ElementTree* getNextElementTree();
	void setNextElementTree(ElementTree* e);
	bool hasNextElementTree();
private:
	ElementTree* nextElementTree;
	SuperTree* mySuperTree;
};





#endif /* ElementTree_H_ */
