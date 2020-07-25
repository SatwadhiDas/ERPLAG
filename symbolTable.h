/*AARYAN KAPOOR 2016B4A70166P
 SATWADHI DAS 2016B4A70622P
 ISHAN SANJAY JOGLEKAR 2016B3A70534P
 SATYANSH RAI 2016B4A70632P
 PARTH MISRA 2016B5A70560P*/

#include "symbolTableDef.h"

varid * lookup_varid(int lno, char * str, varTabTree *curr);
void insert_varTab(int p,varTabTree *curr,char *str, int ut, int siz, int v_lino, union type vtype);
func * lookupFunc(char * str);
void insert_function(int p,char *str, func fun);
char** getIDlist(int p,AST *itr, int *sz);
union type getun(int p,AST *dtype, int *vt, int *of, varTabTree * curr);
void deleteFromSS(int p,char *str, varTabTree *curr);
void createSS(int p,varTabTree *curr,AST *itr);
var_l* retList(int p,AST *itr, varTabTree *curr);
void populateFuncTable(int p,AST *itr);
void popModuleDec(int p,AST *itr);
void getSymbolTable(int p,AST * head);
var_l * lookup_varid1(char * str, struct var_list curr);
void printSymbol(varTabTree *curr, char * currfunc, int nestle);
void printFunctionTable();
int symbolTableSize(varTabTree *curr);
void printActivationTable();
int symbolTableSize1(varTabTree *curr);
void printActivationTable1();
void printSymbol1(varTabTree *curr, char * currfunc, int nestle);
void printFunctionTable1();
void deleteCompleteST();
void deleteST(varTabTree *curr);
