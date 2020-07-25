/*AARYAN KAPOOR 2016B4A70166P
 SATWADHI DAS 2016B4A70622P
 ISHAN SANJAY JOGLEKAR 2016B3A70534P
 SATYANSH RAI 2016B4A70632P
 PARTH MISRA 2016B5A70560P*/
#include "symbolTable.h"

extern int typecheckingflag;
extern int oset;
extern int oset1;
extern int REAL_SIZE;
extern int INTEGER_SIZE;
extern int BOOLEAN_SIZE;
extern int driverLineNo;
//extern int arrayNumber;
extern FILE * fp10;
void deleteCompleteST(){

    int j=0;

    for(j;j<200;j++){

        func_El * temp = functionTable[j].head;

        while(temp!=NULL){
		//	printf("%s \n", temp->function.name);
            var_l * tem = temp->function.input_list.head;

            var_l * tem1;

            while(tem!=NULL){

                tem1=tem;

                tem=tem->next;

                free(tem1);

            }
			//free(temp->function.input_list.head);
            tem = temp->function.output_list.head;

            while(tem!=NULL){

                tem1=tem;

                tem=tem->next;

                free(tem1);

            }
    
			//free(temp->function.output_list.head);
            func_El * temp1 = temp;

            

            //while(temp!=NULL){

                temp = temp->next;

                deleteST(temp1->function.loc);
				//free(temp1->function.loc->children);
				free(temp1->function.loc);

                free(temp1);

                //temp1=temp;

            //}

        }
            functionTable[j].head = NULL;

    }

    return;

}
//free(functionTable)

void deleteST(varTabTree *curr)

{

    if(curr==NULL){

        return;

    }

    int i=0;
	
    for(i=0;curr->nochil>i;i++){

        deleteST(curr->children[i]);
		free(curr->children[i]);
    }
	//if(curr->nochil>0){
		///for(;i%5!=4;i++) free(curr->children[i]);
//}
	free(curr->children);
	 int j=0;

    for(j;j<200;j++){

         struct varEl * temp = curr->table[j].head;

         struct varEl * temp1 = curr->table[j].head;

        while(temp!=NULL){

            temp=temp->next;

            free(temp1);

            temp1=temp;

        }

        

    }

    

    return;

}

varid * lookup_varid(int lno, char * str, varTabTree *curr){
	if(curr == NULL) return NULL;
    int i=0, sum=0;
    char * str1=(char *)malloc (strlen(str)+1);
    trimwhitespace(str1, strlen(str)+1, str);
    strcpy(str,str1);
    for(i=0; i<strlen(str); i++){
        sum+=str[i];
    }
    sum%=200;
    struct varEl * temp = curr->table[sum].head;
    while(temp!=NULL){
        if(strcmp(str,temp->var.name)==0){
		varid * temp1;
		if(lno<temp->var.lno){ 
			temp1 = lookup_varid(lno, str, curr->parent);
		}
		else{
			temp1 = &(temp->var);
		}
            free(str1);
            return temp1;
        }
        temp=temp->next;
    }
    if(curr->parent==NULL){
       // printf("Search Error for %s\n", str);
        free(str1);
        return NULL;
    }
    varid * a=lookup_varid(lno, str,curr->parent);
	free(str1);
	return a;
}

void insert_varTab(int p,varTabTree *curr,char *str, int ut, int siz, int v_lino, union type vtype)
{

    if(lookup_varid(v_lino, str,curr)!=NULL){
		if(p==1)
			fprintf(fp10,"Error in Line no: %d, cannot redeclare Variable: %s\n",v_lino,str);
        typecheckingflag=1;
        return;
    }

    int i, sum=0;
    for(i=0; i<strlen(str); i++){
        sum += str[i];
    }
    sum%=200;
    varEl* no = (varEl *) malloc (sizeof (struct varEl));
    strcpy(no->var.name, str);
    no->var.size=siz;
	no->var.offset1 = oset1;
	if(ut==1){
		if(vtype.a.range_kind == 1){
			oset1+=siz-5;
			no->var.size1=siz-5;
		}
		else{
			oset1+=1;
			no->var.size1=1;
		}
	}
	else {
		oset1+=siz;
		no->var.size1=siz;
	}
	//no->var.arrayBefore=arrayNumber;
	//if(ut==1) arrayNumber++;
	oset+=siz;    
	no->var.offset=oset;
	
    no->var.vartype=vtype;
    no->var.lno=v_lino;
    no->var.ut=ut;
    no->next=NULL;
     varEl* temp=curr->table[sum].head;

    if(temp==NULL){
        curr->table[sum].head=no;
        return;
    }
    while (temp->next!=NULL)
        temp=temp->next;
    temp->next=no;
    
}

func * lookupFunc(char * str){
    int i=0, sum=0;
    char * str1=(char *)malloc (strlen(str)+1);
   // trimwhitespace(str1, strlen(str)+1, str);
  //  strcpy(str,str1);
 //   printf("The function %s\n",str);
    for(i=0; i<strlen(str); i++){
        sum+=str[i];
    }
    sum%=200;
    struct func_El * temp = functionTable[sum].head;
    while(temp){
        if(strcmp(str,temp->function.name)==0){
            free(str1);
            return &(temp->function);
        }
        temp=temp->next;
    }
   // printf("Function Search Error for %s\n", str);
free(str1);
    return NULL;
}


void insert_function(int p,char *str, func fun)
{

	if(lookupFunc(str)!=NULL){
		if(p==1)		
			fprintf(fp10,"Error in line No: %d, overloading not allowed for function: %s\n", fun.lno, str);
        typecheckingflag=1;
        return;
    }
    int i, sum=0;
    for(i=0; i<strlen(str); i++){
        sum += str[i];
    }
    sum%=200;
    func_El* no = (func_El *) malloc (sizeof (struct func_El));
    no->function=fun;
    no->next=NULL;
     func_El* temp=functionTable[sum].head;

    if(temp==NULL){
        functionTable[sum].head=no;
        return;
    }
    while (temp->next!=NULL) temp=temp->next;
    temp->next=no;

    return;
}

char** getIDlist(int p,AST *itr, int *sz)
{
    int k=5;
    int cnt=0;
    char **lis;
    AST *temp=itr;
    lis=(char**) malloc(k*(sizeof(char*)));
    Node *tree=itr->a.treeNode;
    lis[cnt]=(char*)malloc(30*sizeof(char));
    strcpy(lis[0],tree->name);
    *sz=*sz+1;
    temp=temp->next;
    while(temp)
    {
        tree=temp->a.treeNode;
        if(k==*sz)
        {
            k=k*2;
            lis=(char**)realloc(lis,k*sizeof(char*));
        }

        lis[*sz]=(char*)malloc(30*sizeof(char));
        strcpy(lis[*sz],tree->name);
        *sz=*sz+1;
        temp=temp->next;
    }

    return lis;
}

union type getun(int p,AST *dtype, int *vt, int *of, varTabTree* curr){
union type vtype;
        if(dtype->type==array_datatypeNode)
        {

            struct arr ar;
            AST *range=dtype->a.twoChildNode[0];
			ar.range_kind=4;
            if(range->a.twoChildNode[0]->a.treeNode->value==NUM+100){
            int i=0, sum=0;
			ar.range_kind-=2;
            for(i=0; i<strlen(range->a.twoChildNode[0]->a.treeNode->name); i++){
				sum=sum*10 + (range->a.twoChildNode[0]->a.treeNode->name[i]-48);
			}
            ar.st.num=sum;
            }
            else{
				varid * x = lookup_varid(range->a.twoChildNode[0]->a.treeNode->lineNo, range->a.twoChildNode[0]->a.treeNode->name, curr);
				if(x!=NULL){
					ar.st.name=x;
				}
				else{
					ar.st.name = (varid *) malloc(sizeof(varid));
					strcpy(ar.st.name->name, range->a.twoChildNode[0]->a.treeNode->name);
					ar.st.name->lno = 10000;
					ar.st.name->ut=0;
					ar.st.name->vartype.t.a=INTEGER;
					ar.st.name->size=INTEGER_SIZE;
				}
			}
            if(range->a.twoChildNode[1]->a.treeNode->value==NUM+100){
            int i=0, sum=0;
			 ar.range_kind-=1;
            for(i=0; i<strlen(range->a.twoChildNode[1]->a.treeNode->name); i++){
            sum=sum*10 + (range->a.twoChildNode[1]->a.treeNode->name[i]-48);
            }
            ar.end.num=sum;
            }
			else{
				varid * x = lookup_varid(range->a.twoChildNode[1]->a.treeNode->lineNo, range->a.twoChildNode[1]->a.treeNode->name, curr);
				if(x!=NULL){
					ar.end.name=x;
				}
				else{
					ar.end.name = (varid *) malloc(sizeof(varid));
                    strcpy(ar.end.name->name, range->a.twoChildNode[1]->a.treeNode->name);
                  //  printf("TESTINGGG....END:%s",ar.end.name->name);
					ar.end.name->lno = 10000;
					ar.end.name->ut=0;
					ar.end.name->vartype.t.a=INTEGER;
					ar.end.name->size=INTEGER_SIZE;
				}
			}
            vtype.a=ar;
            
            union type subtype = getun(p,dtype->a.twoChildNode[1],vt,of, curr);
            if(ar.range_kind==1)
				*of=(*of)*(ar.end.num-ar.st.num + 1)+6;
			else *of = 6;
            *vt=1;
            ar.sub = subtype.t;
            vtype.a=ar;
        }
        else
        {
            struct nrnm meh;
            meh.a=dtype->type-100;
            
            *vt=0;
            vtype.t=meh;
            if(meh.a==REAL)
                *of=REAL_SIZE;
            if(meh.a==INTEGER)
                *of=INTEGER_SIZE;
            if(meh.a==BOOLEAN)
                *of=BOOLEAN_SIZE;            
        }
        return vtype;
        }


void deleteFromSS(int p,char *str, varTabTree *curr)
{
    int i=0, sum=0;
    char * str1=(char *)malloc (strlen(str)+1);
    trimwhitespace(str1, strlen(str)+1, str);
    strcpy(str,str1);
    for(i=0; i<strlen(str); i++){
        sum+=str[i];
    }
    sum%=200;
    struct varEl * temp = curr->table[sum].head;
	if(temp && strcmp(str,temp->var.name)==0){		
			if(p==1)
				fprintf(fp10,"Error in Line no: %d, cannot redeclare output Variable: %s\n",temp->var.lno,str);
            typecheckingflag=1;
            varEl *del_node1=temp;
            curr->table[sum].head=temp->next;
            
            free(del_node1);
            
        }
        
    while(temp && temp->next){
        if(strcmp(str,temp->next->var.name)==0){
			if(p==1)
				fprintf(fp10,"Error in Line no: %d, cannot redeclare output Variable: %s\n",temp->next->var.lno,str);
            typecheckingflag=1;
            varEl *del_node=temp->next;
            temp->next=temp->next->next;
            
            free(del_node);
            break;
        }
        temp=temp->next;
    }
    for(i=0;curr->nochil>i;i++)
        deleteFromSS(p,str,curr->children[i]);
    free(str1);
    return;
}

void createSS(int p,varTabTree *curr,AST *itr)
{
	if(curr==NULL){return;}
	//printf("itr : %d\n", itr->type);
	while(itr)
	{
	if(itr->type == 100 + END){
		break;
	}	
    if(itr->type == declareStmtNode)
    {
		int i;
        char **lis;
        int *sz=(int*)malloc(sizeof(int));
        *sz=0;
        union type vtype;
        int *vt=(int*)malloc(sizeof(int));
        int *of=(int*)malloc(sizeof(int));
        int v_lino=itr->a.twoChildNode[0]->a.treeNode->lineNo;
        lis=getIDlist(p,itr->a.twoChildNode[0],sz);
        vtype=getun(p,itr->a.twoChildNode[1],vt,of,curr);
        for(i=0;*sz>i;i++){
            insert_varTab(p,curr,lis[i],*vt,*of,v_lino,vtype);
			free(lis[i]);
		}
		free(of);
		free(vt);
		free(sz);
		free(lis);
		
    }
    if(itr->type==whileStmtNode)
    {
        //printf("q");
        varTabTree *chil=(varTabTree *)malloc(sizeof (varTabTree));
        chil->nochil=0;
		int kill_me;
			for(kill_me=0;200>kill_me;kill_me++)
				chil->table[kill_me].head=NULL;
        createSS(p,chil,itr->a.twoChildNode[1]);
        if(curr->nochil==0)
            curr->children=(varTabTree**)malloc(5*sizeof(varTabTree*));
        if(curr->nochil%5==0 && curr->nochil!=0)
            curr->children=(varTabTree**)realloc(curr->children,(curr->nochil+5)*sizeof(varTabTree*));
        curr->children[curr->nochil]=chil;
        chil->parent=curr;
        AST * x = itr->a.twoChildNode[1];
        while (x->next!=NULL)
            x=x->next;
        chil->endline = x->a.treeNode->lineNo;
        AST * temp6 = itr->a.twoChildNode[0];
        int lineNo1;
        while(true){
             if(temp6->type == expressionNode || temp6->type==unaryExpressionNode || temp6->type==unaryMinusNode || temp6->type==unaryPlusNode){
                 temp6 = temp6->a.oneChildNode[0];
             }
             if(temp6->type == logicalOpNode || temp6->type == relationalOpNode){
                 temp6 = temp6->a.threeChildNode[0];
                 lineNo1=temp6->a.treeNode->lineNo;
                 break;
             }
             if(temp6->type == multiplyNode || temp6->type == divideNode ||temp6->type == minusNode || temp6->type == plusNode){
                 temp6 = temp6->a.twoChildNode[0];
             }
             else if(temp6->type==parsetreeNode){
                 lineNo1=temp6->a.treeNode->lineNo;
                 break;
             }
             else {
                 lineNo1=temp6->a.oneChildNode[0]->a.treeNode->lineNo;
                 break;
             }
         }
        chil->startline = lineNo1;
        (curr->nochil)++;

    }
    if(itr->type==forstmtNode)
    {
       // printf("q");
        varTabTree *chil=(varTabTree *)malloc(sizeof (varTabTree));
        chil->nochil=0;
		int kill_me;
			for(kill_me=0;200>kill_me;kill_me++)
				chil->table[kill_me].head=NULL;
        createSS(p,chil,itr->a.threeChildNode[2]);
        if(curr->nochil==0)
            curr->children=(varTabTree**)malloc(5*sizeof(varTabTree*));
        if(curr->nochil%5==0 && curr->nochil!=0)
            curr->children=(varTabTree**)realloc(curr->children,(curr->nochil+5)*sizeof(varTabTree*));
        curr->children[curr->nochil]=chil;
        chil->parent=curr;
        AST * x = itr->a.threeChildNode[2];
        while (x->next!=NULL)
            x=x->next;
        chil->endline = x->a.treeNode->lineNo;
        chil->startline = itr->a.threeChildNode[0]->a.treeNode->lineNo;
        (curr->nochil)++;

    }
	if(itr->type==conditionalStmtNode){
	varTabTree *chil=(varTabTree *)malloc(sizeof (varTabTree));
        chil->nochil=0;
		int kill_me;
			for(kill_me=0;200>kill_me;kill_me++)
				chil->table[kill_me].head=NULL;
	AST * itr1 = itr->a.threeChildNode[1];
		while(itr1->next){        	
				createSS(p,chil,itr1->a.twoChildNode[1]);
				itr1=itr1->next;
		}
		if(itr->a.threeChildNode[2]!=NULL && itr->a.threeChildNode[2]->type!=emptyDefaultNode)
			createSS(p,chil,itr->a.threeChildNode[2]);
		if(curr->nochil==0)
            curr->children=(varTabTree**)malloc(5*sizeof(varTabTree*));
        if(curr->nochil%5==0 && curr->nochil!=0)
            curr->children=(varTabTree**)realloc(curr->children,(curr->nochil+5)*sizeof(varTabTree*));
        curr->children[curr->nochil]=chil;
        chil->parent=curr;
        AST * x = itr->a.threeChildNode[1];
        while (x->next!=NULL)
            x=x->next;
        chil->endline = x->a.treeNode->lineNo;
        chil->startline = itr->a.threeChildNode[0]->a.treeNode->lineNo;
        (curr->nochil)++;	

	}
        
    if(itr->type== moduleReuseStmtNode){
        func * funky = lookupFunc(itr->a.threeChildNode[1]->a.treeNode->name);
        if(funky!=NULL){
            if(funky->status==0)
                funky->status=1;
        }
    }
                                  
	itr=itr->next;
    }
}

var_l* retList(int p,AST *itr, varTabTree *curr)
{
    
    if(itr==NULL)
        return NULL;
    AST *itr1=itr;
    var_l *ne=(var_l*)malloc(sizeof(var_l));
    Node *tree=itr1->a.twoChildNode[0]->a.treeNode;
    
    strcpy(ne->name,tree->name);
    
    union type vtype;
    int *of=(int*)malloc(sizeof(int));
    int *ut=(int*)malloc(sizeof(int));
    vtype=getun(p,itr1->a.twoChildNode[1],ut,of,NULL);
    
    int v_lino=itr->a.twoChildNode[0]->a.treeNode->lineNo;
    
    ne->typ=vtype;
    ne->t=*ut;
    ne->flag=0;
    ne->next=NULL;

	ne->offset1=oset1;
	if(*ut==1){
		ne->size=6;
		ne->size1=5;
		oset+=6;
		oset1+=5;
	}
	else{
		ne->size=*of;
		ne->size1=*of;
	//ne->arrayBefore=arrayNumber;
	//if(*ut==1) ne->size=8;
	//if(*ut==1) arrayNumber++;
	//if(*ut==1) oset+=5;
		oset+=*of;
        oset1+=*of;
	}
	ne->offset=oset;
  //  printf("TESTINGGGGGG : %s, %d\n", ne->name,ne->offset1);
    free(of);
	free(ut);
    var_l *temp1=ne;
    itr1=itr1->next;
    while(itr1)
    {
        Node *temp=itr1->a.twoChildNode[0]->a.treeNode;
        temp1->next=(var_l*)malloc(sizeof(var_l));
        temp1=temp1->next;
        strcpy(temp1->name,temp->name);
       
        int *of1=(int*)malloc(sizeof(int));
        int *ut1=(int*)malloc(sizeof(int));
        union type vtype1;
        int v_lino1=itr1->a.twoChildNode[0]->a.treeNode->lineNo;
        vtype1=getun(p,itr1->a.twoChildNode[1],ut1,of1,NULL);
        temp1->typ=vtype1;
        temp1->t=*ut1;

		temp1->offset1=oset1;
		if(*ut1==1){
			temp1->size=6;
			temp1->size1=5;
			oset+=6;
			oset1+=5;
		}
		else{
			temp1->size=*of1;
			temp1->size1=*of1;
		//ne->arrayBefore=arrayNumber;
		//if(*ut==1) ne->size=8;
		//if(*ut==1) arrayNumber++;
		//if(*ut==1) oset+=5;
			oset+=*of1;
            oset1+=*of1;
		}
		temp1->offset=oset;
       //   printf("TESTINGGGGGG : %s, %d\n", temp1->name,temp1->offset1);
		free(of1);
		free(ut1);
        temp1->flag=0;
        temp1->next=NULL;
        itr1=itr1->next;
    }
    
    return ne;
}


void populateFuncTable(int p,AST *itr){
   int loc_oset=oset;
	oset=0;
	oset1=0;
    AST *itr1=itr;
    while(itr1)
    {

        
        func * obj;
        int fg=0;
        obj=lookupFunc(itr1->a.fourChildNode[0]->a.treeNode->name);
        if(obj==NULL)
        {
            fg=1;
            obj=(func*)malloc(sizeof(func));
            strcpy(obj->name,itr1->a.fourChildNode[0]->a.treeNode->name);
            obj->status=2;
            obj->lno=itr1->a.fourChildNode[0]->a.treeNode->lineNo;
        }
        if((obj->status==2 || obj->status==4) && fg==0){
            obj->status=4;
			if(p==1)
				fprintf(fp10,"Error in Line No:%d, multiple definitions for Function: %s\n",itr1->a.fourChildNode[0]->a.treeNode->lineNo, itr1->a.fourChildNode[0]->a.treeNode->name );
            typecheckingflag=1;
			itr1=itr1->next;
			/*var_l * temp = inp_list.head;
			var_l * temp1;
			while(temp!=NULL){
				temp1=temp;
				temp=temp->next;
				free(temp1);
			}
			temp = out_list.head;
			while(temp!=NULL){
				temp1=temp;
				temp=temp->next;
				free(temp1);
			}			
			deleteST(curr);*/
            continue;
        }			 	
        if(obj->status==1){
		    obj->status=2;
		}
        if(obj->status==0){
            obj->status=3;
            
        }
		varTabTree *curr;
        curr=(varTabTree *)malloc(sizeof (varTabTree));
        curr->nochil=0;
        int kill_me;
        for(kill_me=0;200>kill_me;kill_me++)
            curr->table[kill_me].head=NULL;
        var_list inp_list, out_list;
		inp_list.head=NULL;
		out_list.head=NULL;
		oset=0;
		oset1=0;
		//arrayNumber=0;
        inp_list.head=retList(p,itr1->a.fourChildNode[1],curr);
        out_list.head=retList(p,itr1->a.fourChildNode[2],curr);
		//obj->listLen =oset+3*arrayNumber;
		//arrayNumber=0;
		oset1=0;
        createSS(p,curr,itr1->a.fourChildNode[3]);
        AST * x = itr1->a.fourChildNode[3];
        while (x->next!=NULL)
            x=x->next;
        curr->endline = x->a.treeNode->lineNo;
        curr->startline= itr1->a.fourChildNode[0]->a.treeNode->lineNo;
        var_l * temp = out_list.head;
        
        while(temp){
            deleteFromSS(p,temp->name,curr);
            temp=temp->next;
        }
        obj->input_list=inp_list;
        obj->output_list=out_list;
        
        curr->parent=NULL;
        obj->loc=curr;
        if(fg==1){
       			insert_function(p,obj->name,*obj);
				free(obj);
		}
        //free(obj);
        itr1=itr1->next;
    }
	oset=loc_oset;
    return;

}
void popModuleDec(int p,AST *itr)
{
    AST *itr1=itr;
    while(itr1)
    {
		if(lookupFunc(itr1->a.oneChildNode[0]->a.treeNode->name)!=NULL){
			if(p==1)
				fprintf(fp10,"Error in Line no: %d, cannot redeclare Function: %s\n",itr1->a.oneChildNode[0]->a.treeNode->lineNo,itr1->a.oneChildNode[0]->a.treeNode->name);
		    typecheckingflag=1;
		    itr1=itr1->next;
			continue;
    	}
        func obj;
        strcpy(obj.name,itr1->a.oneChildNode[0]->a.treeNode->name);
        obj.status=0;
        obj.input_list.head=NULL;
        obj.output_list.head=NULL;
        obj.loc=NULL;
        obj.lno = itr->a.oneChildNode[0]->a.treeNode->lineNo;
        insert_function(p,obj.name,obj);
        itr1=itr1->next;
    }
    return;
}


void getSymbolTable(int p,AST * head){
    if(head==NULL) {
        return;
    }
    switch(head->type){
    case programNode:
		;
		int pat=0;
			for(pat=0;200>pat;pat++)
			{
			functionTable[pat].head=NULL;
			}
        popModuleDec(p,head->a.fourChildNode[0]);
        populateFuncTable(p,head->a.fourChildNode[1]);
        oset=0;
		oset1=0;
        func obj;
        strcpy(obj.name,"DriverModule");
        
        obj.status=2;
        obj.input_list.head=NULL;
        obj.output_list.head=NULL;
        obj.loc=(varTabTree *)malloc(sizeof(varTabTree));
        obj.loc->nochil=0;
		obj.loc->parent=NULL;
		//obj.listLen=0;
            obj.lno = driverLineNo;

        int kill_me;
        for(kill_me=0;200>kill_me;kill_me++)
        obj.loc->table[kill_me].head=NULL;
        createSS(p,obj.loc,head->a.fourChildNode[2]->a.oneChildNode[0]);

            AST * x = head->a.fourChildNode[2]->a.oneChildNode[0];
            if(x==NULL) exit(0);
                //printf("test\n");
            while(x->next!=NULL)
                x = x->next;
            obj.loc->endline = x->a.treeNode->lineNo;
            obj.loc->startline = driverLineNo;

        insert_function(p,obj.name,obj);
       // lookupFunc(obj.name);

        populateFuncTable(p,head->a.fourChildNode[3]);
		break;
    default:
		break;
    }
}

var_l * lookup_varid1(char * str, struct var_list curr){
    char * str1=(char *)malloc (strlen(str)+1);
    trimwhitespace(str1, strlen(str)+1, str);
    strcpy(str,str1);
	var_l * temp = curr.head;
	while(temp!=NULL){
		if(strcmp(temp->name,str)==0){
				free(str1);
				return temp;
		}
		temp=temp->next;
	}
	free(str1);
	return NULL;
}

void printSymbol(varTabTree *curr, char * currfunc, int nestle)
{
    if(curr==NULL){
        return;
    }
    
    int i=0;
    for(i=0; i<200; i++){
        struct varEl * temp = curr->table[i].head;
        while(temp){
            varid * lst = &temp->var;
            if(lst->ut==1){
                if(lst->vartype.a.range_kind==1)
                    printf("%25s%25s    %d-%d     %d%10s%15s\t\t[%d-%d]%10s        %d    %d\n",lst->name,currfunc,curr->startline,curr->endline ,lst->size1,"YES","STATIC",lst->vartype.a.st.num,lst->vartype.a.end.num,lst->vartype.a.sub.a==INTEGER?"INTEGER":lst->vartype.a.sub.a==BOOLEAN?"BOOLEAN":"REAL",lst->offset1,nestle);
                 else if(lst->vartype.a.range_kind==2)
                                            printf("%25s%25s    %d-%d     %d%10s%15s\t\t[%d-%s]%10s        %d    %d\n",lst->name,currfunc,curr->startline,curr->endline ,lst->size1,"YES","DYNAMIC",lst->vartype.a.st.num,lst->vartype.a.end.name->name,lst->vartype.a.sub.a==INTEGER?"INTEGER":lst->vartype.a.sub.a==BOOLEAN?"BOOLEAN":"REAL",lst->offset1,nestle);
                                       
                                   else if(lst->vartype.a.range_kind==3)
                                            printf("%25s%25s    %d-%d     %d%10s%15s\t\t[%s-%d]%10s        %d    %d\n",lst->name,currfunc,curr->startline,curr->endline ,lst->size1,"YES","DYNAMIC",lst->vartype.a.st.name->name,lst->vartype.a.end.num,lst->vartype.a.sub.a==INTEGER?"INTEGER":lst->vartype.a.sub.a==BOOLEAN?"BOOLEAN":"REAL",lst->offset1,nestle);
                                       
                                   else
                                       printf("%25s%25s    %d-%d     %d%10s%15s\t\t[%s-%s]%10s        %d    %d\n",lst->name,currfunc,curr->startline,curr->endline ,lst->size1,"YES","DYNAMIC",lst->vartype.a.st.name->name,lst->vartype.a.end.name->name,lst->vartype.a.sub.a==INTEGER?"INTEGER":lst->vartype.a.sub.a==BOOLEAN?"BOOLEAN":"REAL",lst->offset1,nestle);
            }
            else{
                   printf("%25s%25s    %d-%d     %d%10s%15s%20s%10s        %d    %d\n",lst->name,currfunc,curr->startline,curr->endline ,lst->size1,"NO","---","---",lst->vartype.a.sub.a==INTEGER?"INTEGER":lst->vartype.a.sub.a==BOOLEAN?"BOOLEAN":"REAL",lst->offset1,nestle);
            }
            temp = temp->next;
        }
    }
        for(i=0;curr->nochil>i;i++){
             printSymbol(curr->children[i],currfunc,nestle+1);
        }
        return;
}


void printFunctionTable(){
    int i=0;
    var_l * lst;
    for(i=0; i<200; i++){
        func_El * temp = functionTable[i].head;
        while(temp){
            lst = temp->function.input_list.head;
            while(lst){
                if(lst->t==1){
                    if(lst->typ.a.range_kind==1)
                        printf("%25s%25s    %d-%d     %d%10s%15s\t\t[%d-%d]%10s        %d    %d\n",lst->name,temp->function.name,temp->function.loc->startline,temp->function.loc->endline ,lst->size1,"YES","STATIC",lst->typ.a.st.num,lst->typ.a.end.num,lst->typ.a.sub.a==INTEGER?"INTEGER":lst->typ.a.sub.a==BOOLEAN?"BOOLEAN":"REAL",lst->offset1,0);
                    else if(lst->typ.a.range_kind==2)
                             printf("%25s%25s    %d-%d     %d%10s%15s\t\t[%d-%s]%10s        %d    %d\n",lst->name,temp->function.name,temp->function.loc->startline,temp->function.loc->endline ,lst->size1,"YES","DYNAMIC",lst->typ.a.st.num,lst->typ.a.end.name->name,lst->typ.a.sub.a==INTEGER?"INTEGER":lst->typ.a.sub.a==BOOLEAN?"BOOLEAN":"REAL",lst->offset1,0);
                        
                    else if(lst->typ.a.range_kind==3)
                             printf("%25s%25s    %d-%d     %d%10s%15s\t\t[%s-%d]%10s        %d    %d\n",lst->name,temp->function.name,temp->function.loc->startline,temp->function.loc->endline ,lst->size1,"YES","DYNAMIC",lst->typ.a.st.name->name,lst->typ.a.end.num,lst->typ.a.sub.a==INTEGER?"INTEGER":lst->typ.a.sub.a==BOOLEAN?"BOOLEAN":"REAL",lst->offset1,0);
                        
                    else
                        printf("%25s%25s    %d-%d     %d%10s%15s\t\t[%s-%s]%10s        %d    %d\n",lst->name,temp->function.name,temp->function.loc->startline,temp->function.loc->endline ,lst->size1,"YES","DYNAMIC",lst->typ.a.st.name->name,lst->typ.a.end.name->name,lst->typ.a.sub.a==INTEGER?"INTEGER":lst->typ.a.sub.a==BOOLEAN?"BOOLEAN":"REAL",lst->offset1,0);
                }
                else{
                     printf("%25s%25s    %d-%d     %d%10s%15s%20s%10s        %d    %d\n",lst->name,temp->function.name,temp->function.loc->startline,temp->function.loc->endline ,lst->size1,"NO","---","---",lst->typ.t.a==INTEGER?"INTEGER":lst->typ.t.a==BOOLEAN?"BOOLEAN":"REAL",lst->offset1,0);
                }
                lst=lst->next;
            }
            lst = temp->function.output_list.head;
			while(lst){     
				printf("%25s%25s    %d-%d     %d%10s%15s%20s%10s        %d    %d\n",lst->name,temp->function.name,temp->function.loc->startline,temp->function.loc->endline ,lst->size1,"NO","---","---",lst->typ.t.a==INTEGER?"INTEGER":lst->typ.t.a==BOOLEAN?"BOOLEAN":"REAL",lst->offset1,0);
				lst=lst->next;
            }

            printSymbol(temp->function.loc,temp->function.name,1);
            temp=temp->next;
        }
    }
}
void printSymbol1(varTabTree *curr, char * currfunc, int nestle)
{
    if(curr==NULL){
        return;
    }
    
    int i=0;
    for(i=0; i<200; i++){
        struct varEl * temp = curr->table[i].head;
        while(temp){
            varid * lst = &temp->var;
            if(lst->ut==1){
                if(lst->vartype.a.range_kind==1)
                    printf("%25s    %d-%d%25s%15s\t\t[%d-%d]%10s\n",currfunc,curr->startline,curr->endline ,lst->name,"STATIC ARRAY",lst->vartype.a.st.num,lst->vartype.a.end.num,lst->vartype.a.sub.a==INTEGER?"INTEGER":lst->vartype.a.sub.a==BOOLEAN?"BOOLEAN":"REAL");
                 else if(lst->vartype.a.range_kind==2)
                                       printf("%25s    %d-%d%25s%15s\t\t[%d-%s]%10s\n",currfunc,curr->startline,curr->endline ,lst->name,"DYNAMIC ARRAY",lst->vartype.a.st.num,lst->vartype.a.end.name->name,lst->vartype.a.sub.a==INTEGER?"INTEGER":lst->vartype.a.sub.a==BOOLEAN?"BOOLEAN":"REAL");
                                   else if(lst->vartype.a.range_kind==3)
                                       printf("%25s    %d-%d%25s%15s\t\t[%s-%d]%10s\n",currfunc,curr->startline,curr->endline ,lst->name,"DYNAMIC ARRAY",lst->vartype.a.st.name->name,lst->vartype.a.end.num,lst->vartype.a.sub.a==INTEGER?"INTEGER":lst->vartype.a.sub.a==BOOLEAN?"BOOLEAN":"REAL");
                                   else
                                       printf("%25s    %d-%d%25s%15s\t\t[%s-%s]%10s\n",currfunc,curr->startline,curr->endline ,lst->name,"DYNAMIC ARRAY",lst->vartype.a.st.name->name,lst->vartype.a.end.name->name,lst->vartype.a.sub.a==INTEGER?"INTEGER":lst->vartype.a.sub.a==BOOLEAN?"BOOLEAN":"REAL");
            }
            temp = temp->next;
        }
    }
        for(i=0;curr->nochil>i;i++){
             printSymbol1(curr->children[i],currfunc,nestle+1);
        }
        return;
}


void printFunctionTable1(){
    int i=0;
    var_l * lst;
    for(i=0; i<200; i++){
        func_El * temp = functionTable[i].head;
        while(temp){
            lst = temp->function.input_list.head;
            while(lst){
                if(lst->t==1){
                    if(lst->typ.a.range_kind==1)
                        printf("%25s    %d-%d%25s%15s\t\t[%d-%d]%10s\n",temp->function.name,temp->function.loc->startline,temp->function.loc->endline ,lst->name,"STATIC ARRAY",lst->typ.a.st.num,lst->typ.a.end.num,lst->typ.a.sub.a==INTEGER?"INTEGER":lst->typ.a.sub.a==BOOLEAN?"BOOLEAN":"REAL");
                    else if(lst->typ.a.range_kind==2)
                        printf("%25s    %d-%d%25s%15s\t\t[%d-%s]%10s\n",temp->function.name,temp->function.loc->startline,temp->function.loc->endline ,lst->name,"DYNAMIC ARRAY",lst->typ.a.st.num,lst->typ.a.end.name->name,lst->typ.a.sub.a==INTEGER?"INTEGER":lst->typ.a.sub.a==BOOLEAN?"BOOLEAN":"REAL");
                    else if(lst->typ.a.range_kind==3)
                        printf("%25s    %d-%d%25s%15s\t\t[%s-%d]%10s\n",temp->function.name,temp->function.loc->startline,temp->function.loc->endline ,lst->name,"DYNAMIC ARRAY",lst->typ.a.st.name->name,lst->typ.a.end.num,lst->typ.a.sub.a==INTEGER?"INTEGER":lst->typ.a.sub.a==BOOLEAN?"BOOLEAN":"REAL");
                    else
                        printf("%25s    %d-%d%25s%15s\t\t[%s-%s]%10s\n",temp->function.name,temp->function.loc->startline,temp->function.loc->endline ,lst->name,"DYNAMIC ARRAY",lst->typ.a.st.name->name,lst->typ.a.end.name->name,lst->typ.a.sub.a==INTEGER?"INTEGER":lst->typ.a.sub.a==BOOLEAN?"BOOLEAN":"REAL");
                }
                lst=lst->next;
            }
            printSymbol1(temp->function.loc,temp->function.name,1);
            temp=temp->next;
        }
    }
}

int symbolTableSize(varTabTree *curr)
{
    if(curr==NULL){
        return 0;
    }
    
    int i=0;
	int ret=0;
    for(i=0; i<200; i++){
        struct varEl * temp = curr->table[i].head;
        while(temp){
            varid * lst = &temp->var;
            ret+=lst->size1;
            temp = temp->next;
        }
    }
        for(i=0;curr->nochil>i;i++){
           ret+=symbolTableSize(curr->children[i]);
        }
        return ret;
}

void printActivationTable(){
	int i=0;
    var_l * lst;
	int act_size=0;
	printf("%25s%20s\n","Function Name", "Activation Size");
    for(i=0; i<200; i++){
        func_El * temp = functionTable[i].head;
        while(temp){
			act_size=0;
            lst = temp->function.input_list.head;
            while(lst){
				act_size+=lst->size1;
                lst=lst->next;
            }
            lst = temp->function.output_list.head;
            while(lst){
                act_size+=lst->size1;
                lst=lst->next;
            }
			act_size+=symbolTableSize(temp->function.loc);
			printf("%25s\t%d\n",temp->function.name, act_size);
            temp=temp->next;
        }
    }


}

int symbolTableSize1(varTabTree *curr)
{
    if(curr==NULL){
        return 0;
    }
    
    int i=0;
	int ret=0;
    for(i=0; i<200; i++){
        struct varEl * temp = curr->table[i].head;
        while(temp){
            varid * lst = &temp->var;
            ret+=lst->size;
            temp = temp->next;
        }
    }
        for(i=0;curr->nochil>i;i++){
           ret+=symbolTableSize1(curr->children[i]);
        }
        return ret;
}

void printActivationTable1(){
	int i=0;
    var_l * lst;
	int act_size=0;
	//printf("%25s%20s\n","Function Name", "Activation Size");
    for(i=0; i<200; i++){
        func_El * temp = functionTable[i].head;
        while(temp){
			act_size=0;
            lst = temp->function.input_list.head;
            while(lst){
                act_size+=lst->size;
                lst=lst->next;
            }
            lst = temp->function.output_list.head;
            while(lst){
                act_size+=lst->size;
                lst=lst->next;
            }
			act_size+=symbolTableSize1(temp->function.loc);
			temp->function.func_oset=act_size;
            temp=temp->next;
        }
    }


}
