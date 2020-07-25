/*AARYAN KAPOOR 2016B4A70166P
SATWADHI DAS 2016B4A70622P
ISHAN SANJAY JOGLEKAR 2016B3A70534P
SATYANSH RAI 2016B4A70632P
PARTH MISRA 2016B5A70560P*/

#ifndef _typeCheckerDef
#define _typeCheckerDef 
#include"symbolTable.h"



typedef struct loopvar loopvar;


struct loopvar{
    char str[25];
	int lno;
    struct loopvar * next;
};


extern int forflag;
typedef struct whilevar whilevar;
struct whilevar{
	int flag;
	loopvar * head;
	int lno;
	struct whilevar * next;
};



#endif

