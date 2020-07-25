/*AARYAN KAPOOR 2016B4A70166P
 SATWADHI DAS 2016B4A70622P
 ISHAN SANJAY JOGLEKAR 2016B3A70534P
 SATYANSH RAI 2016B4A70632P
 PARTH MISRA 2016B5A70560P*/


#ifndef _parserDef
#define _parserDef 
#include "lexer.h"

typedef struct parsetr Node;

    struct parsetr{
        int tnt;        //t=0 terminal
        char name[30];    //name of the terminal/non-terminal
        int value;    //integer representation of the name
        Node* parent;
        Node* child;
        Node* next;
        int lineNo;
        int rule;
    };

    bool first[NT][T+2];
    bool follow[NT][T+2];

        Symbol * parseTable[NT][T];

    typedef struct ltt lexToToken;
    struct ltt{
        char value[25];
        char token[25];
        lexToToken * next;
    };

    typedef struct lttt lexToTokenTable;
    struct lttt{
            int key;
            lexToToken * head;
    };

    lexToTokenTable lexTokenTable[hashSize];

#endif
