/*AARYAN KAPOOR 2016B4A70166P
 SATWADHI DAS 2016B4A70622P
 ISHAN SANJAY JOGLEKAR 2016B3A70534P
 SATYANSH RAI 2016B4A70632P
 PARTH MISRA 2016B5A70560P*/


#include "parser.h"

extern FILE * fp11;
extern int count;
extern int errflag;
extern int countPTNodes; 
extern int PTmem;
//bool first[NT][T+2];
//bool follow[NT][T+2];
bool isEmpty(Node* top){
        if(top==NULL)
            return true;
        else
            return false;
    }

Node* findMatch(Node * temp){
        if(temp==NULL) return NULL;
        if(temp->next==NULL){
		return findMatch(temp->parent);
		}
        return temp->next;
    }
void insertltt(char * str, char * str1){

    int i, sum=0;
    for(i=0; i<strlen(str); i++){
        sum += str[i];
    }
    sum%=hashSize;
    struct ltt * new = (struct ltt *) malloc (sizeof (struct ltt));
    strcpy(new->value, str);
    new->next=NULL;
    strcpy(new->token,str1);
    struct ltt * temp=lexTokenTable[sum].head;
    if(temp==NULL){
        lexTokenTable[sum].head=new;
        return;
    }
    while (temp->next!=NULL) temp=temp->next;
    temp->next=new;
}
void printltt(){
    int i;
    for(i=0;i<hashSize; i++){
    printf("For i:%d\n", i);
    struct ltt * temp= lexTokenTable[i].head;
    while(temp!=NULL){
        printf("%s %s\n", temp->value, temp->token);
        temp=temp->next;
            }
        }
}
void popltt(){
    int i;
    for(i=0;i<hashSize;i++){
        lexTokenTable[i].key=i;
        lexTokenTable[i].head=NULL;
    }

    insertltt("integer","INTEGER");
    insertltt("real","REAL");
    insertltt("boolean","BOOLEAN");
    insertltt("of","OF");
    insertltt("array","ARRAY");
    insertltt("start","START");
    insertltt("end","END");
    insertltt("declare","DECLARE");
    insertltt("module","MODULE");
    insertltt("driver","DRIVER");
    insertltt("program","PROGRAM");
    insertltt("get_value","GET_VALUE");
    insertltt("print","PRINT");
    insertltt("use","USE");
    insertltt("with","WITH");
    insertltt("parameters","PARAMETERS");
    insertltt("true","TRUE");
    insertltt("false","FALSE");
    insertltt("takes","TAKES");
    insertltt("input","INPUT");
    insertltt("returns","RETURNS");
    insertltt("AND","AND");
    insertltt("OR","OR");
    insertltt("for","FOR");
    insertltt("in","IN");
    insertltt("switch","SWITCH");
    insertltt("case","CASE");
    insertltt("break","BREAK");
    insertltt("default","DEFAULT");
    insertltt("while","WHILE");
    insertltt("+","PLUS");
    insertltt("-","MINUS");
    insertltt("*","MUL");
    insertltt("/","DIV");
    insertltt("<","LT");
    insertltt("<=","LE");
    insertltt(">=","GE");
    insertltt(">","GT");
    insertltt("==","EQ");
    insertltt("!=","NE");
    insertltt("<<","DEF");
    insertltt(">>","ENDDEF");
    insertltt("<<<","DRIVERDEF");
    insertltt(">>>","DRIVERENDDEF");
    insertltt(":","COLON");
    insertltt("..","RANGEOP");
    insertltt(";","SEMICOL");
    insertltt(",","COMMA");
    insertltt(":=","ASSIGNOP");
    insertltt("[","SQBO");
    insertltt("]","SQBC");
    insertltt("(","BO");
    insertltt(")","BC");
    insertltt("ID","ID");
    insertltt("NUM","NUM");
    insertltt("RNUM","RNUM");
    insertltt("EPSILON","EPSILON");


    insertltt("INTEGER","integer");
    insertltt("REAL","real");
    insertltt("BOOLEAN","boolean");
    insertltt("OF","of");
    insertltt("ARRAY","array");
    insertltt("START","start");
    insertltt("END","end");
    insertltt("DECLARE","declare");
    insertltt("MODULE","module");
    insertltt("DRIVER","driver");
    insertltt("PROGRAM","program");
    insertltt("GET_VALUE","get_value");
    insertltt("PRINT","print");
    insertltt("USE","use");
    insertltt("WITH","with");
    insertltt("PARAMETERS","parameters");
    insertltt("TRUE","true");
    insertltt("FALSE","false");
    insertltt("TAKES","takes");
    insertltt("INPUT","input");
    insertltt("RETURNS","returns");
    insertltt("FOR","for");
    insertltt("IN","in");
    insertltt("SWITCH","switch");
    insertltt("CASE","case");
    insertltt("BREAK","break");
    insertltt("DEFAULT","default");
    insertltt("WHILE","while");
    insertltt("PLUS","+");
    insertltt("MINUS","-");
    insertltt("MUL","*");
    insertltt("DIV","/");
    insertltt("LT","<");
    insertltt("LE","<=");
    insertltt("GE",">=");
    insertltt("GT",">");
    insertltt("EQ","==");
    insertltt("NE","!=");
    insertltt("DEF","<<");
    insertltt("ENDDEF",">>");
    insertltt("DRIVERDEF","<<<");
    insertltt("DRIVERENDDEF",">>>");
    insertltt("COLON",":");
    insertltt("RANGEOP","..");
    insertltt("SEMICOL",";");
    insertltt("COMMA",",");
    insertltt("ASSIGNOP",":=");
    insertltt("SQBO","[");
    insertltt("SQBC","]");
    insertltt("BO","(");
    insertltt("BC",")");


 //   printltt();
}
char * searchltt(char * str){
    int i=0, sum=0;
    	          char * str1=(char *)malloc (strlen(str)+1);
          trimwhitespace(str1, strlen(str)+1, str);
          strcpy(str,str1);
    for(i=0; i<strlen(str); i++){
        sum+=str[i];
    }
    sum%=hashSize;
    struct ltt * temp = lexTokenTable[sum].head;
    while(temp!=NULL){
        if(strcmp(str,temp->value)==0){
		free(str1);
            return temp->token;
        }
        temp=temp->next;
    }
    printf("Search Ltt Error for %s\n", str);
	free(str1);
    return NULL;
}


void FindFirst (int k, bool arr[][T+2], List* Grammar){
    Symbol* tempptr = Grammar[k].head;
    while(tempptr!=NULL){
        int tokenNo=0;
        while (tokenNo < tempptr->noOfTokens) {
             if (tempptr->ruleToken[tokenNo]>=100){
                 arr[k][tempptr->ruleToken[tokenNo]-100]=true;
                 break;
            }
             else{
                 if(tempptr->ruleToken[tokenNo]==k) break;
                 if(arr[tempptr->ruleToken[tokenNo]][T+1]==false){
                     FindFirst(tempptr->ruleToken[tokenNo],arr,Grammar);
                 }
                for(int n=0;n<T-1;n++){
                         arr[k][n]=arr[k][n] || arr[tempptr->ruleToken[tokenNo]][n];
                 }
                 if(arr[tempptr->ruleToken[tokenNo]][T-1]==true){
                     tokenNo++;
                     if(tokenNo == tempptr->noOfTokens) {
                         arr[k][T-1]=true;
                    }
                 }
                 else break;
             }
        }
        tempptr = tempptr->next;
    }
    arr[k][T+1]=true;
    return;
}

void FindFollow (int m, bool arr1[][T+2], List* Grammar, bool arr[][T+2]){
	for(int x=0;x<NT;x++){
        Symbol* tempptr = Grammar[x].head;
        while(tempptr!=NULL){
            int tokenNo=0;
            while(tokenNo<tempptr->noOfTokens){
                while(tokenNo<tempptr->noOfTokens && m!= tempptr->ruleToken[tokenNo]){
                    tokenNo++;
                }

                if(tokenNo<tempptr->noOfTokens && m == tempptr->ruleToken[tokenNo]){
                    int token1 = tokenNo+1;
                    if(token1>=tempptr->noOfTokens){       //next token doesnt exist
                        if(x==tempptr->ruleToken[tokenNo]){}
                        else{
                            if(arr1[x][T+1]==false){
                                FindFollow(x,arr1,Grammar, arr);
                            }
                            for(int a=0;a<T+1;a++){
                                arr1[m][a]=arr1[x][a] || arr1[m][a];        //copy first set of NT
                            }
                        }
                        tokenNo++;
                    }
                    else{                                                           //next token exists
                        if(tempptr->ruleToken[token1]>=100){
                            arr1[m][tempptr->ruleToken[token1]-100]=true;
                        }
                        else{
                            do{
                                for(int c=0;c<T+1;c++){
                                    arr1[m][c]=arr1[m][c] || arr[tempptr->ruleToken[token1]][c];    //copy first set of NT
                                }
                                token1++;
                            }
                            while(arr[tempptr->ruleToken[token1-1]][T-1]==true && tempptr->ruleToken[token1]<100 && token1<tempptr->noOfTokens);
                            if(token1>=tempptr->noOfTokens){       //next token doesnt exist
		                if(x==tempptr->ruleToken[tokenNo]){}
		                else{
		                    if(arr1[x][T+1]==false){
		                        FindFollow(x,arr1,Grammar, arr);
		                    }
		                    for(int a=0;a<T+1;a++){
		                        arr1[m][a]=arr1[x][a] || arr1[m][a];        //copy first set of NT
		                    }
				 }
				}
                            else if(tempptr->ruleToken[token1]>=100){
                                arr1[m][tempptr->ruleToken[token1]-100]=true;
                            }
                        }
                        tokenNo++;
                	}
            }
            else tokenNo++;
        }
        tempptr = tempptr->next;
        }
    }
    arr1[m][T+1]=true;
    return;
}


void ComputeFirstandFollow(List* Grammar, bool arr[][T+2], bool arr1[][T+2] ){

    for(int i=0;i<NT;i++){
        for(int j=0;j<=T+1;j++){
            arr[i][j]=false;
            arr1[i][j]=false;
        }
    }

    int k=0;
    for(k=0;k<NT;k++){
        if(arr[k][T+1]==false){
            FindFirst(k,arr,Grammar);
        }
    }
    arr1[0][T]=true;
    for(int m=0;m<NT;m++){
        if(arr1[m][T+1]==false){
            FindFollow(m,arr1, Grammar, arr);
        }
    }
    for(int g=0;g<NT;g++){
        arr1[g][T-1]=false;
    }
    return;

}
void createParseTable(List* Grammar,bool arr[][T+2], bool arr1[][T+2], Symbol * table[NT][T]){
        for(int i=0; i<NT; i++){
            for(int j=0; j<T; j++)
                table[i][j]=NULL;
        }

        for(int x=0;x<NT;x++){                                                      //For every NT
            Symbol* tempptr = Grammar[x].head;
            while(tempptr!=NULL){                                                   //for every rule
                int tokenNo=0;
                if(tempptr->ruleToken[tokenNo]==100+T-1){                             //if rhs of rule is epsilon
                    for(int i=0;i<=T;i++){
                        if(arr1[x][i]==true){                                         //copy rule corresponding to terminals in follows of NT
                            if(i==T-1);
                            else if(i==T) table[x][T-1]=tempptr;
                            else table[x][i]=tempptr;
                        }
                    }
                }
                else{
                    while(tokenNo<tempptr->noOfTokens){                             // if rhs is not epsilon
                        if(tempptr->ruleToken[tokenNo]>=100 && tempptr->ruleToken[tokenNo]!=100+T-1){    //if token on RHS is terminal, mark entry true and break
                            table[x][tempptr->ruleToken[tokenNo]-100]=tempptr;
                            break;
                        }
                        else{                                                       // if token on rhs is NT
                            for(int i=0;i<=T-2;i++){
                                if(arr[tempptr->ruleToken[tokenNo]][i]==true){      //makr true corresponding to every element in first of NT
                                    table[x][i]=tempptr;
                                }
                            }
                            if(arr[tempptr->ruleToken[tokenNo]][T-1]==false)        //if epsilon in first of that NT, continue to next token
                                break;
                            else
                                tokenNo++;
                        }
                    }
                    if(tokenNo==tempptr->noOfTokens){                                //if full rule can go to epsilon
                        for(int i=0;i<=T;i++){                                        // write rule corresponding to every t in follow of nt
                            if(arr1[x][i]==true){
                                if(i==T-1);
                                else if(i==T) table[x][T-1]=tempptr;
                                else table[x][i]=tempptr;
                            }
                        }
                    }
                }
                tempptr=tempptr->next;
            }
        }
    }
Node * errorRecover (FILE * fp, Node * tree, struct token * t){
   // printf("Here\n");
	errflag=1;
	Node * treecnst;
	treecnst= tree->parent;

	treecnst=treecnst->child;
        while (treecnst->next!=tree) {
                    treecnst=treecnst->next;
        }
	if(tree->tnt==0){
		while(follow[tree->value][(*t).to]==0){
			(*t)=getToken(fp);
		}
		tree->child=NULL;
		return findMatch(tree);
	}
	else{
		treecnst->next=tree->next;
		Node* temp=tree;
		tree=tree->next;
		return findMatch(treecnst);
	}
}

    Node* getParseTree(FILE *fp){
        Node *Tree=(Node*)malloc(sizeof(Node));
        countPTNodes=1;
        Tree->tnt=0;
        strcpy(Tree->name,"<program>");
        Tree->value=0;
        Tree->parent=NULL;
        Tree->next=NULL;
        Tree->child=NULL;
	Tree->rule=1;
        Node * treeptr=Tree;
        struct token t=getToken(fp);
        while(t.to!=1000)
        {
            if(t.to==-1){
		errflag=1;
                printf("Lexical Error in line %d for %s\n", t.ln, t.name);
                t=getToken(fp);
                continue;
            }
            if(treeptr->value>=100 && treeptr->value-100==t.to)
            {
		if(treeptr->value-100==EPSILON) strcpy(treeptr->name, "EPSILON");
                else strcpy(treeptr->name,t.name);
		treeptr->lineNo=t.ln;
                treeptr=findMatch(treeptr);
                t=getToken(fp);
        }
            else if(treeptr->value<100)
            {
                Symbol* s=parseTable[treeptr->value][t.to];

                if(s==NULL)
                {
			errflag=1;
                	fprintf(fp11,"Syntax Error in line %d for %s\n", t.ln, t.name);
			treeptr->child=NULL;
	               	treeptr=errorRecover (fp, treeptr, &t);
			continue;
                }
                char split[s->noOfTokens][30];
                countPTNodes+=s->noOfTokens;
                Node* new2=(Node*)malloc(sizeof(Node));
                new2->value=s->ruleToken[0];
                    new2->tnt=s->ruleToken[0]>=100?1:0;
		if(new2->tnt==0)
                	strcpy(new2->name,findGrammarToken(new2->value));
                new2->parent=treeptr;
		treeptr->rule=s->ruleNo;
		treeptr->child = new2;
		Node * treeptr1 = new2;
                for(int i=s->noOfTokens-2;i>=0;i--)
                {

                    new2=(Node*)malloc(sizeof(Node));
                    new2->value=s->ruleToken[s->noOfTokens-i-1];
                    new2->tnt=s->ruleToken[s->noOfTokens-i-1]>=100?1:0;
		if(new2->tnt==0)
                    	strcpy(new2->name,findGrammarToken(new2->value));
                    new2->parent=treeptr;
					new2->next = NULL;
                    treeptr1->next = new2;
                    treeptr1=new2;
                }
                treeptr = treeptr->child;
                if(treeptr->tnt==1 && treeptr->value-100==T-1) {
					treeptr->lineNo=t.ln;
					treeptr->next=NULL;
					treeptr=findMatch(treeptr->parent);

                }
            }
            else{
		errflag=1;
                fprintf(fp11,"Syntax Error in line %d for %s\n ", t.ln, t.name);
	            treeptr=errorRecover (fp, treeptr, &t);
            }
        }
        if(!(isEmpty(treeptr)) && treeptr->value==OTHERMODULES){
            countPTNodes++;
		Node* new2=(Node*)malloc(sizeof(Node));
		new2->value=T-1;
                new2->tnt=1;
                strcpy(new2->name,"EPSILON");
                new2->parent=treeptr;
		treeptr->rule=6;
                treeptr->child=new2;
                return Tree;
        }
        if(t.to==1000 && !(isEmpty(treeptr)))
        {
		errflag=1;
            printf("Parsing Error. Input File read completely but stack is not empty\n");
           return NULL;
        }
        return Tree;
    }

	
	
void printParseTree(Node* Tree){
        if(Tree==NULL) return;
       //  printf("CHECKING NODE: %S\n", Tree->name);
        printParseTree(Tree->child);
        if(Tree->tnt == 1){
            if(Tree->value-100==NUM) printf("%25s\t\t%15s\t\t\t%d\t\t\t%30s\t\t%15s\t\t",Tree->name,"Current Node",Tree->lineNo, "NUM",Tree->name);
            else if(Tree->value-100==RNUM) printf("%25s\t\t%15s\t\t\t%d\t\t\t%30s\t\t%15s\t\t",Tree->name,"Current Node",Tree->lineNo, "RNUM",Tree->name);
            else if(Tree->value-100==ID) printf("%25s\t\t%15s\t\t\t%d\t\t\t%30s\t\t%15s\t\t",Tree->name,"Current Node",Tree->lineNo, "ID","N/A");
            else if(Tree->value-100==EPSILON) printf("%25s\t\t%15s\t\t\t%d\t\t\t%30s\t\t%15s\t\t","EPSILON","Current Node",Tree->lineNo, "EPSILON","N/A");
            else printf("%25s\t\t%15s\t\t\t%d\t\t\t%30s\t\t%15s\t\t",Tree->name,"Current Node",Tree->lineNo, searchltt(Tree->name),"N/A");
            if(Tree->parent!=NULL){printf("%30s\t\t", Tree->parent->name);}
            else{printf("%30s\t","N/A");}
            printf("%10s\t\t%30s\n","YES", "N/A");
            return;
        }
        printf("%25s\t\t%15s\t\t%10s\t\t\t%30s\t\t%15s\t\t", "---","Current Node","N/A","N/A","N/A");
        if(Tree->parent!=NULL){printf("%30s\t\t", Tree->parent->name);}
        else{printf("%35s\t", "N/A");}
        printf("%10s\t\t%30s\n","NO",Tree->name);

    Node * temp =Tree->child->next;
    while(temp!=NULL){
    printParseTree(temp);
    temp=temp->next;
    }
    }
