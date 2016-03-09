/*
 * Node.h
 *
 *  Created on: 17.10.2014
 *      Author: rebecca
 */

#ifndef NODE_H_
#define NODE_H_
#include "../../Tree/src/SuperTree.h"
#include "../../Tree/src/Tree.h"

class Node :public Tree {
public:
	Node(grammarType grammartype, int line, int column);
	virtual ~Node();
	Type getType();
	bool hasLeave();

private:


};

#endif /* NODE_H_ */
