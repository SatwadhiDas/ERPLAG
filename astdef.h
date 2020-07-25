/*AARYAN KAPOOR 2016B4A70166P
 SATWADHI DAS 2016B4A70622P
 ISHAN SANJAY JOGLEKAR 2016B3A70534P
 SATYANSH RAI 2016B4A70632P
 PARTH MISRA 2016B5A70560P*/

#ifndef _astDef
#define _astDef 
#include "parser.h"

typedef struct astNode AST;
//typedef struct parsetr Node;


enum typeOfNode{
    programNode,
    moduleDeclarationNode,
    driverModuleNode,
    moduleNode,
    input_plistNode,
    input_plist1Node,
    output_plistNode,
    output_plist1Node,
    array_datatypeNode,
    getValueNode,
    printNode,
    assignStmtNode,
    lvalueArrStmtNode,
    moduleReuseStmtNode,
    declareStmtNode,
    conditionalStmtNode,
    caseStmtNode,
    forstmtNode,
    whileStmtNode,
    rangeNode,
    range1Node,
    multiplyNode,
    divideNode,
    plusNode,
    minusNode,
    relationalOpNode,
    logicalOpNode,
    unaryPlusNode,
    unaryMinusNode,
    unaryExpressionNode,
    expressionNode,
	emptyDefaultNode,
    parsetreeNode
};

union ast{
    AST * oneChildNode[1];
    AST * twoChildNode[2];
    AST * threeChildNode[3];
    AST * fourChildNode[4];
    Node * treeNode;
};

struct astNode{
    union ast a;
    int type;
	int addr;
	int addrType;
    AST * next;
};

#endif
