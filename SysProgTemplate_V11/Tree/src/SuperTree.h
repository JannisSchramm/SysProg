
#ifndef SUPERTREE_H_
#define SUPERTREE_H_

enum Type {intType, intArrayType, arrayType, noType, errorType, opPlusType, opMinusType, opDivType, opMultType, opLessType, opGreaterType, opEqualType,
	opUnEqualType, opAndType};

enum grammarType {

	PROG, DECLS, DECL, ARRAY, STATEMENTS, STATEMENT, EXP, EXP2, INDEX, OP_EXP, OP, LEAF, START

};

class SuperTree {
public:
SuperTree(grammarType gt, int myLine, int myColumn);
void store(Type t);
Type getType();
Type type;
grammarType gt;
int getLine();
int getColumn();

private:

int line;
int column;


};

#endif /* SUPERTREE_H_ */
