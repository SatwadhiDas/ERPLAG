/*AARYAN KAPOOR 2016B4A70166P
 SATWADHI DAS 2016B4A70622P
 ISHAN SANJAY JOGLEKAR 2016B3A70534P
 SATYANSH RAI 2016B4A70632P
 PARTH MISRA 2016B5A70560P*/

#ifndef _symbolTableDef
#define _symbolTableDef 
#include "ast.h"

struct nrnm{
    int a;
};
typedef struct varid varid;
union range_type{
int num;
varid * name;
};
struct arr{
    struct nrnm sub;
    union range_type st, end;
    int range_kind;
};

union type{
    struct nrnm t;
    struct arr a;
    };


struct varid{
 char name[25];
 int size;
int size1;
 int offset;
int offset1;
 int ut;
 int lno;
 ///int arrayBefore;
 union type vartype;
};



typedef struct var_l var_l;
struct var_l{
    char name[25];
    union type typ;
    int t;
	int size;
	int size1;
	int offset;
	int offset1;
	int flag;
	//int arrayBefore;
    struct var_l *next;
    };
typedef struct var_list var_list;
struct var_list{
struct var_l *head;};

typedef struct varEl varEl;
struct varEl{
    struct varid var;
    varEl *next;
    };

typedef struct varTab varTab;
struct varTab{
varEl *head;

};


typedef struct varTabTree varTabTree;
struct varTabTree{
    varTab table[200];
    int nochil;
    int ins;
    varTabTree **children;
    varTabTree *parent;
    int startline;
    int endline;
};

typedef struct func func;
struct func{
char name[25];
int status;
var_list input_list;
var_list output_list;
//int listLen;
int func_oset;
int lno;
varTabTree *loc;
};

typedef struct func_El func_El;
struct func_El{
    func function;
    func_El *next;};


typedef struct func_obj func_obj;
struct func_obj{
    func_El *head;
}functionTable[200];



#endif
