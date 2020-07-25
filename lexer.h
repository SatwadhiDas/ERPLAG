/*AARYAN KAPOOR 2016B4A70166P
 SATWADHI DAS 2016B4A70622P
 ISHAN SANJAY JOGLEKAR 2016B3A70534P
 SATYANSH RAI 2016B4A70632P
 PARTH MISRA 2016B5A70560P*/

#ifndef _lexer
#define _lexer  

#include"lexerDef.h"



void trimwhitespace(char *out, size_t len, const char *str);

void removeComments(char* fileName,char* resultFile);

void insertlex(char * str, int en);

void printlex();

void poplext();

int searchLex(char * str);

void populateGrammar(char* fileName, List* l1);

void displayGrammar(List* l);

struct token getToken(FILE *fp);

void reTok(struct token *tok);

void retract(struct token *tok);

void dretract(struct token *tok);

int getStream(FILE *fp);

char * findGrammarToken(int value);

static char buff[101];
#endif

