/*AARYAN KAPOOR 2016B4A70166P
 SATWADHI DAS 2016B4A70622P
 ISHAN SANJAY JOGLEKAR 2016B3A70534P
 SATYANSH RAI 2016B4A70632P
 PARTH MISRA 2016B5A70560P*/


#ifndef _lexerDef
#define _lexerDef 

#include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include<stdbool.h>
    #include<ctype.h>
    #include<time.h>
    #define T 57
    #define NT 55
    #define hashSize 71
#define bsize 101
#define eom '$'
	

  
typedef struct symbol Symbol;

    struct symbol{
	int rep;
	int ruleNo;
        Symbol* next;
        int noOfTokens;			//length stores the number of tokens in the RHS of rule
        int ruleToken[12];
    };

    typedef struct list List;

    struct list{
        int rep;
        Symbol* head;
    };
typedef enum t terminal;

    enum t{INTEGER, REAL, BOOLEAN, OF, ARRAY, START, END, DECLARE, MODULE, DRIVER, PROGRAM, GET_VALUE, PRINT, USE, WITH, PARAMETERS, TRUET, FALSET, TAKES, INPUT, RETURNS, AND, OR, FOR, IN, SWITCH, CASE, BREAK, DEFAULT, WHILE,
    PLUS, MINUS, MUL, DIV, LT, LE, GE, GT, EQ, NE, DEF, ENDDEF, DRIVERDEF, DRIVERENDDEF, COLON, RANGEOP, SEMICOL, COMMA, ASSIGNOP, SQBO, SQBC, BO, BC, ID, NUM, RNUM, EPSILON
    };

typedef enum nt nonterminal;

    enum nt{PROGRAMNT, MODULEDECLARATIONS, MODULEDECLARATION, OTHERMODULES, DRIVERMODULE, MODULENT, RET, INPUT_PLIST, INPUT_PLIST1, OUTPUT_PLIST, OUTPUT_PLIST1, DATATYPE, TYPE, MODULEDEF, STATEMENTS, STATEMENT, IOSTMT, VAR1, BOOLCONST,
    VAR, WHICHID, SIMPLESTMT, ASSIGNMENTSTMT, WHICHSTMT, LVALUEIDSTMT, LVALUEARRSTMT, INDEX, MODULEREUSESTMT, OPTIONAL, IDLIST, IDLIST1, EXPRESSION, U, NEW, ARITHMETICBOOLEANEXPR, LOP, V, ROP, ARITHMETICEXPR, FACTOR, TERM, TERM2,
    TERM1, LOGICALOP, RELATIONALOP, DECLARESTMT, CONDIONALSTMT, CASESTMTS, CASESTMT1, CASESTMT, VALUE, DEFAULTNT, ITERATIVESTMT, RANGE, RANGE1
    };
	
struct lexnode{
        char value[25];
        int token;
        struct lexnode * next;
    };
typedef struct lex lextable;

struct lex{
        int key;
        struct lexnode * head;
    }lext[hashSize];
	
struct token{
        char name[30];
        int to;
        int ln;
    };
typedef struct node val;
    struct node{
        char value[25];
        int token;
        int tnt;	//0 for t 1 for nt;
        val * next;
    };



#endif
