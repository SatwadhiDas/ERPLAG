/*AARYAN KAPOOR 2016B4A70166P
 SATWADHI DAS 2016B4A70622P
 ISHAN SANJAY JOGLEKAR 2016B3A70534P
 SATYANSH RAI 2016B4A70632P
 PARTH MISRA 2016B5A70560P*/


#include "parserDef.h"

Node* findMatch(Node * temp);

void insertltt(char * str, char * str1);

void printltt();

void popltt();

char * searchltt(char * str);

void FindFirst (int k, bool arr[][T+2], List* Grammar);

void FindFollow (int m, bool arr1[][T+2], List* Grammar, bool arr[][T+2]);

void ComputeFirstandFollow(List* Grammar, bool arr[][T+2], bool arr1[][T+2] );

void createParseTable(List* Grammar,bool arr[][T+2], bool arr1[][T+2], Symbol * table[NT][T]);

Node * errorRecover (FILE * fp, Node * tree, struct token * t);

Node* getParseTree(FILE *fp);

void printParseTree(Node* Tree);
