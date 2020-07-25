/*AARYAN KAPOOR 2016B4A70166P
 SATWADHI DAS 2016B4A70622P
 ISHAN SANJAY JOGLEKAR 2016B3A70534P
 SATYANSH RAI 2016B4A70632P
 PARTH MISRA 2016B5A70560P*/
#include "typeCheckerDef.h"

bool idDeclared (varid * idLoc, AST * Nod);
bool idTypeMatch1(varid * idLoc, var_l * temp, int lineNo);
bool idTypeMatch(varid * idLoc, varid * temp, int lineNo);
bool idTypeMatch2(var_l * idLoc, var_l * temp, int lineNo);
bool arrayInBound(varid * idLoc, AST * Nod, func * presentModule, varTabTree * symbolTable);
bool arrayInBound1(var_l * idLoc, AST * Nod, func * presentModule, varTabTree * symbolTable);
bool funcDeclared(func * funcLoc, AST * Nod);
loopvar * addToWhile(AST * nod, int lno);
int expressionTypeChecker(AST * Node, varTabTree * symbolTable, int lineNo, func * presentModule);
int typeChecker(AST * Node, varTabTree * symbolTable, int childNo, func * presentModule);
void freewhilevar(whilevar * whileVar);
void freeloopvar(loopvar * loopVar);
