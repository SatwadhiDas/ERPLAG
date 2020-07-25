/*AARYAN KAPOOR 2016B4A70166P
 SATWADHI DAS 2016B4A70622P
 ISHAN SANJAY JOGLEKAR 2016B3A70534P
 SATYANSH RAI 2016B4A70632P
 PARTH MISRA 2016B5A70560P*/



#include "astdef.h"

void freeAST(AST * head);
AST * makeNode(enum typeOfNode type);
AST * makeExpression(Node * nod, AST * inh);
AST * makeAST(Node * nod);
char * gettype (int type);
void printAST(AST * head, AST * parent);
