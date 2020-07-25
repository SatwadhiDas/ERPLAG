    /* AARYAN KAPOOR 2016B4A70166P
     SATYANSH RAI 2016B4A70632P
     SATWADHI DAS 2016B4A70622P
     PARTH MISRA 2016B5A70560P
     ISHAN SANJAY JOGLEKAR 2016B3A70534P */

    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include<stdbool.h>
    #include<ctype.h>
   

    #define hashSize 71
	

    typedef struct node val;
    struct node{
        char value[25];
        int token;
        int tnt;	//0 for t 1 for nt;
        val * next;
    };

    typedef struct hash htable;

    struct hash{
            int key;
            val * head;
    };

    htable maptable[hashSize];


    void trimwhitespace(char *out, size_t len, const char *str)
    {
      if(len == 0)
        return;

      const char *end;
      size_t out_size;

      // Trim leading space
      while(isspace((unsigned char)*str)) str++;

      if(*str == 0)  // All spaces?
      {
        *out = 0;
        return;
      }

      // Trim trailing space
      end = str + strlen(str) - 1;
      while(end > str && isspace((unsigned char)*end)) end--;
      end++;

      // Set output size to minimum of trimmed string length and buffer size minus 1
      out_size = (end - str) < len-1 ? (end - str) : len-1;
      // Copy trimmed string and add null terminator
      memcpy(out, str, out_size);
      out[out_size] = 0;

      //return out_size;
    }



    void insert(htable * t, char * str, int en, int tnt){

        int i, sum=0;
        for(i=0; i<strlen(str); i++){
            sum += str[i];
        }
        sum%=hashSize;
        val * new = (val *) malloc (sizeof (val));
        strcpy(new->value, str);
        new->next=NULL;
        new->token=en;
        new->tnt=tnt;
        val * temp=t[sum].head;
            //printf("%s %d\n", str, sum);
        if(temp==NULL){
            t[sum].head=new;
            return;
        }
        while (temp->next!=NULL) temp=temp->next;
        temp->next=new;
    }

    int search(char * str){
        int i=0, sum=0;
        char * str1=(char *)malloc (strlen(str)+1);
        trimwhitespace(str1, strlen(str)+1, str);
     //   printf("New map:%s \n", str1);
        for(i=0; i<strlen(str1); i++){
            sum+=str1[i];
        }
        sum%=hashSize;
        val * temp = maptable[sum].head;
        while(temp!=NULL){
            if(strcmp(str1,temp->value)==0){
		free(str1);
                return temp->token;
            }
            temp=temp->next;
        }
        printf("Search Error:%s\n", str);
        exit (0);
	free(str1);
        return -1;
    }

    bool isTerminal(char * str){
        int i=0, sum=0;
	char * str1=(char *)malloc (strlen(str)+4);
        trimwhitespace(str1, strlen(str)+4, str);
        for(i=0; i<strlen(str); i++){
            sum+=str1[i];
        }
        sum%=hashSize;
        val * temp = maptable[sum].head;
        while(temp!=NULL){
            if(strcmp(str1,temp->value)==0){
		free(str1);
                if(temp->tnt == 1) return false;
                return true;
            }
            temp=temp->next;
        }
        printf("isTerminal Error:%s\n",str);
	free(str1);
	exit(0);
        return false;
    }

void popMap(htable *t){
    int i;
    for(i=0;i<hashSize;i++){
        t[i].key=i;
        t[i].head=NULL;
    }
    i=0;
    insert(t, "<program>", i++, 1);
    insert(t, "<moduleDeclarations>", i++, 1);
    insert(t, "<moduleDeclaration>", i++, 1);
    insert(t, "<otherModules>", i++, 1);
    insert(t, "<driverModule>", i++, 1);
    insert(t, "<module>", i++, 1);
    insert(t, "<ret>", i++, 1);
    insert(t, "<input_plist>", i++, 1);
    insert(t, "<input_plist1>", i++, 1);
    insert(t, "<output_plist>", i++, 1);
    insert(t, "<output_plist1>", i++, 1);
    insert(t, "<dataType>", i++, 1);
    insert(t, "<type>", i++, 1);
    insert(t, "<moduleDef>", i++, 1);
    insert(t, "<statements>", i++, 1);
    insert(t, "<statement>", i++, 1);
    insert(t, "<ioStmt>", i++, 1);
    insert(t, "<var1>", i++, 1);
    insert(t, "<booleanConst>", i++, 1);
    insert(t, "<var>", i++, 1);
    insert(t, "<whichId>", i++, 1);
    insert(t, "<simpleStmt>", i++, 1);
    insert(t, "<assignmentStmt>", i++, 1);
    insert(t, "<whichStmt>", i++, 1);
    insert(t, "<lvalueIDStmt>", i++, 1);
    insert(t, "<lvalueARRStmt>", i++, 1);
    insert(t, "<index>", i++, 1);
    insert(t, "<moduleReuseStmt>", i++, 1);
    insert(t, "<optional>", i++, 1);
    insert(t, "<idList>", i++, 1);
    insert(t, "<idList1>", i++, 1);
    insert(t, "<expression>", i++, 1);
    insert(t, "<U>", i++, 1);
    insert(t, "<New>", i++, 1);
    insert(t, "<arithmeticBooleanExpr>", i++, 1);
    insert(t, "<LOP>", i++, 1);
    insert(t, "<V>", i++, 1);
    insert(t, "<ROP>", i++, 1);
    insert(t, "<arithmeticExpr>", i++, 1);
    insert(t, "<Factor>", i++, 1);
    insert(t, "<Term>", i++, 1);
    insert(t, "<Term2>", i++, 1);
    insert(t, "<Term1>", i++, 1);
    insert(t, "<logicalOp>", i++, 1);
    insert(t, "<relationalOp>", i++, 1);
    insert(t, "<declareStmt>", i++, 1);
    insert(t, "<condionalStmt>", i++, 1);
    insert(t, "<caseStmts>", i++, 1);
    insert(t, "<caseStmt1>", i++, 1);
    insert(t, "<caseStmt>", i++, 1);
    insert(t, "<value>", i++, 1);
    insert(t, "<default>", i++, 1);
    insert(t, "<iterativeStmt>", i++, 1);
    insert(t, "<range>", i++, 1);
    insert(t, "<range1>", i++, 1);

    //Terminals below
    i=0;
    insert(t, "INTEGER", i++, 0);
    insert(t, "REAL", i++, 0);
    insert(t, "BOOLEAN", i++, 0);
    insert(t, "OF", i++, 0);
    insert(t, "ARRAY", i++, 0);
    insert(t, "START", i++, 0);
    insert(t, "END", i++, 0);
    insert(t, "DECLARE", i++, 0);
    insert(t, "MODULE", i++, 0);
    insert(t, "DRIVER", i++, 0);
    insert(t, "PROGRAM", i++, 0);
    insert(t, "GET_VALUE", i++, 0);
    insert(t, "PRINT", i++, 0);
    insert(t, "USE", i++, 0);
    insert(t, "WITH", i++, 0);
    insert(t, "PARAMETERS", i++, 0);
    insert(t, "TRUE", i++, 0);
    insert(t, "FALSE", i++, 0);
    insert(t, "TAKES", i++, 0);
    insert(t, "INPUT", i++, 0);
    insert(t, "RETURNS", i++, 0);
    insert(t, "AND", i++, 0);
    insert(t, "OR", i++, 0);
    insert(t, "FOR", i++, 0);
    insert(t, "IN", i++, 0);
    insert(t, "SWITCH", i++, 0);
    insert(t, "CASE", i++, 0);
    insert(t, "BREAK", i++, 0);
    insert(t, "DEFAULT", i++, 0);
    insert(t, "WHILE", i++, 0);
    insert(t, "PLUS", i++, 0);
    insert(t, "MINUS", i++, 0);
    insert(t, "MUL", i++, 0);
    insert(t, "DIV", i++, 0);
    insert(t, "LT", i++, 0);
    insert(t, "LE", i++, 0);
    insert(t, "GE", i++, 0);
    insert(t, "GT", i++, 0);
    insert(t, "EQ", i++, 0);
    insert(t, "NE", i++, 0);
    insert(t, "DEF", i++, 0);
    insert(t, "ENDDEF", i++, 0);
    insert(t, "DRIVERDEF", i++, 0);
    insert(t, "DRIVERENDDEF", i++, 0);
    insert(t, "COLON", i++, 0);
    insert(t, "RANGEOP", i++, 0);
    insert(t, "SEMICOL", i++, 0);
    insert(t, "COMMA", i++, 0);
    insert(t, "ASSIGNOP", i++, 0);
    insert(t, "SQBO", i++, 0);
    insert(t, "SQBC", i++, 0);
    insert(t, "BO", i++, 0);
    insert(t, "BC", i++, 0);
    insert(t, "ID", i++, 0);
    insert(t, "NUM", i++, 0);
    insert(t, "RNUM", i++, 0);
    insert(t, "EPSILON", i++, 0);
}

	void createNumberOnly()
	{
		FILE* fr=fopen("Grammar.txt","r");
		if(fr==NULL)
		{
		printf("ERROR Opening File\n");
		return;
		}
		FILE* fw=fopen("NewGrammar.txt","w");
		char* buf, * token;
		    int maxLen=150,num,r;
		    buf=(char *)malloc(sizeof(char)*maxLen);
		    while((r=fscanf(fr,"%[^\n]\n",buf)) != EOF)
		    {
		    token=strtok(buf,"---");
		    num=search(token);
		    fprintf(fw,"%d 999 ",num); //999 represents --- here which separates LHS and RHS of the production
		    token=strtok(NULL,"---");
		    char* rest=token;
		    token=strtok_r(rest,"|",&rest);
		    while(token!=NULL)
		    {
		    char* tk=strtok(token," ");
		    while(tk!=NULL)
		    {
		//printf("Current token= %s\n",tk);
		    if(isTerminal(tk))
		    num=search(tk)+100;
		    else
		    num=search(tk);
		//printf("Number representation= %d\n",num);
		    fprintf(fw,"%d ",num);
		    tk=strtok(NULL," ");
		    }
		    fprintf(fw,"888 "); //888 represents | symbol here which separates different rules
		    token=strtok_r(rest,"|",&rest);
		    }
		    fprintf(fw,"777 \n");
		    }
		fclose(fw);
		fclose(fr);
	}

    int main(int argc,char* argv[])
    {
  
        popMap(maptable);
        createNumberOnly();
        return 0;
    }





