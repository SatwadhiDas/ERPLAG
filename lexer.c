/*AARYAN KAPOOR 2016B4A70166P
 SATWADHI DAS 2016B4A70622P
 ISHAN SANJAY JOGLEKAR 2016B3A70534P
 SATYANSH RAI 2016B4A70632P
 PARTH MISRA 2016B5A70560P*/

#include "lexer.h"

extern char stan[30];

extern int cnt;
extern int somerandom;
extern int lno;
extern char character;
extern int state;
extern int table[60][130];
extern int dret;
extern int sret[50];
extern int fin[50];


extern int cn[50];


extern int lexflag;
extern int buf;


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

char * findGrammarToken(int value){
	switch(value){
	case 0: return "<program>";
	break;
	case 1: return "<moduleDeclarations>";
	break;
	case 2: return "<moduleDeclaration>";
	break;
	case 3: return "<otherModules>";
	break;
	case 4: return "<driverModule>";
	break;
	case 5: return "<module>";
	break;
	case 6: return "<ret>";
	break;
	case 7: return "<input_plist>";
	break;
	case 8: return "<input_plist1>";
	break;
	case 9: return "<output_plist>";
	break;
	case 10: return "<output_plist1>";
	break;
	case 11: return "<dataType>";
	break;
	case 12: return "<type>";
	break;
	case 13: return "<moduleDef>";
	break;
	case 14: return "<statements>";
	break;
	case 15: return "<statement>";
	break;
	case 16: return "<ioStmt>";
	break;
	case 17: return "<var1>";
	break;
	case 18: return "<booleanConst>";
	break;
	case 19: return "<var>";
	break;
	case 20: return "<whichId>";
	break;
	case 21: return "<simpleStmt>";
	break;
	case 22: return "<assignmentStmt>";
	break;
	case 23: return "<whichStmt>";
	break;
	case 24: return "<lvalueIDStmt>";
	break;
	case 25: return "<lvalueARRStmt>";
	break;
	case 26: return "<index>";
	break;
	case 27: return "<moduleReuseStmt>";
	break;
	case 28: return "<optional>";
	break;
	case 29: return "<idList>";
	break;
	case 30: return "<idList1>";
	break;
	case 31: return "<expression>";
	break;
	case 32: return "<U>";
	break;
	case 33: return "<New>";
	break;
	case 34: return "<arithmeticBooleanExpr>";
	break;
	case 35: return "<LOP>";
	break;
	case 36: return "<V>";
	break;
	case 37: return "<ROP>";
	break;
	case 38: return "<arithmeticExpr>";
	break;
	case 39: return "<Factor>";
	break;
	case 40: return "<Term>";
	break;
	case 41: return "<Term2>";
	break;
	case 42: return "<Term1>";
	break;
	case 43: return "<logicalOp>";
	break;
	case 44: return "<relationalOp>";
	break;
	case 45: return "<declareStmt>";
	break;
	case 46: return "<condionalStmt>";
	break;
	case 47: return "<caseStmts>";
	break;
	case 48: return "<caseStmt1>";
	break;
	case 49: return "<caseStmt>";
	break;
	case 50: return "<value>";
	break;
	case 51: return "<default>";
	break;
	case 52: return "<iterativeStmt>";
	break;
	case 53: return "<range>";
	break;
	case 54: return "<range1>";
	break;
	default:
		return "InvalidNonTerminal";
	}
}

void insertlex(char * str, int en){
        int i, sum=0;
        for(i=0; i<strlen(str); i++){
            sum += str[i];
        }
        sum%=hashSize;
        struct lexnode * new = (struct lexnode*) malloc (sizeof (struct lexnode));
        strcpy(new->value, str);
        new->next=NULL;
        new->token=en;
         struct lexnode * temp=lext[sum].head;
        if(temp==NULL){
            lext[sum].head=new;
            return;
        }
        while (temp->next!=NULL) temp=temp->next;
        temp->next=new;
    }

    void printlex(){
        int i;
        for(i=0;i<hashSize; i++){
            printf("For i:%d\n", i);
            struct lexnode * temp= lext[i].head;
            while(temp!=NULL){
                printf("%s %d\n", temp->value, temp->token);
                temp=temp->next;
            }
        }
    }
    void poplext(){
     int i=0;
      for(i=0;i<hashSize;i++){
            lext[i].key=i;
            lext[i].head=NULL;
        }
        i=0;
        insertlex("integer", i++);
        insertlex("real", i++);
        insertlex("boolean", i++);
        insertlex("of", i++);
        insertlex("array", i++);
        insertlex("start", i++);
        insertlex("end", i++);
        insertlex("declare", i++);
        insertlex("module", i++);
        insertlex("driver", i++);
        insertlex("program", i++);
        insertlex("get_value", i++);
        insertlex("print", i++);
        insertlex("use", i++);
        insertlex("with", i++);
        insertlex("parameters", i++);
        insertlex("true", i++);
        insertlex("false", i++);
        insertlex("takes", i++);
        insertlex("input", i++);
        insertlex("returns", i++);
        insertlex("AND", i++);
        insertlex("OR", i++);
        insertlex("for", i++);
        insertlex("in", i++);
        insertlex("switch", i++);
        insertlex("case", i++);
        insertlex("break", i++);
        insertlex("default", i++);
        insertlex("while", i++);
//        printlex();
    }
      int searchLex(char * str){
        int i=0, sum=0;
          char * str1=(char *)malloc (strlen(str)+1);
          trimwhitespace(str1, strlen(str)+1, str);
        for(i=0; i<strlen(str1); i++){
            sum+=str1[i];
        }
        sum%=hashSize;
        struct lexnode * temp = lext[sum].head;
        while(temp!=NULL){
            if(strcmp(str1,temp->value)==0){
		free(str1);
                return temp->token;
            }
            temp=temp->next;
        }
	free(str1);
        return -1;
    }

void populateGrammar(char* fileName, List* l1)
	{
		FILE* fp=fopen(fileName,"r");
		if(fp==NULL)
		{
			printf("ERROR Opening File\n");
			exit(0);
		}
		int r,n,c=0,rule=1,index;
		int parent;
		Symbol * s1;
		while((r=fscanf(fp,"%d ",&n))!=EOF)
		{
			if(n<100)
			{
			l1[c].rep=n;
			parent = n;
			}
			else{
				printf("Error, Wrong File\n");
				exit(0);
			}
			r=fscanf(fp,"%d ",&n);
			if(n==999)
			{
				s1=(Symbol*)malloc(sizeof(Symbol));
				l1[c].head=s1;
				r=fscanf(fp,"%d ",&n);
				s1->rep=parent;
				s1->ruleNo=rule;
				rule++;
				index=0;
				s1->next=NULL;
				while(n!=888)
				{
					s1->ruleToken[index]=n;
					index++;
					r=fscanf(fp,"%d ",&n);
				}
				s1->noOfTokens=index;
		//Processing the RHS of the production
				r=fscanf(fp,"%d ",&n);
			while(n!=777)
			{
				index=0;
				Symbol* s=(Symbol *)malloc(sizeof(Symbol));
				s->rep=parent;
				s->ruleNo=rule;
				rule++;
				while(n!=888)
				{
					s->ruleToken[index]=n;
					index++;
					r=fscanf(fp,"%d ",&n);
				}
					s->noOfTokens=index;
					s->next=NULL;
					s1->next=s;
					s1=s;
					r=fscanf(fp,"%d ",&n);
			}

			}
			else{
				printf("Error, Wrong File\n");
				exit(0);
			}
			c++;
		}
	}
void displayGrammar(List* l){
        Symbol* s;
        int c=0;
	int index;
        if(l==NULL)
        {
            printf("Grammar does not exist");
            return;
        }
        while(c<NT)
        {
            printf("\nRule No. %d\n",c+1);
            printf("%s -> ",findGrammarToken(l[c].rep));
            s=l[c].head;
            while(s!=NULL)
            {
		for(index=0; index<s->noOfTokens; index++){
			if(s->ruleToken[index]>=100)
				printf("%d ", s->ruleToken[index]);
			else
				printf("%s ", findGrammarToken(s->ruleToken[index]));
		}
		printf("| ");
                s=s->next;
            }
		printf("\n");
            c++;
        }
        return;
    }



    void reTok(struct token *tok)
    {
        int fl=0;
        if(tok->to==25)
        {
            int ntok=searchLex(tok->name);
            if(ntok!=-1)
            {
                fl=1;
                tok->to=ntok;
            }
        }
        if(fl==0)
            tok->to=cn[tok->to];
        return;
    }
    void retract(struct token *tok)
    {
        strncpy(tok->name,stan,cnt-1);
        (tok->name)[cnt-1]='\0';
        tok->to=state;
        tok->ln=lno;
        stan[0]=stan[cnt-1];

        buf=1;
        return;
    }
    void dretract(struct token *tok)
    {
        strncpy(tok->name,stan,cnt-2);
        (tok->name)[cnt-2]='\0';
        tok->to=37;
        tok->ln=lno;
        buf=2;
        stan[0]=stan[cnt-2];
        stan[1]=stan[cnt-1];
        return;
    }
    int getStream(FILE *fp)
     {
         memset(buff,0,bsize);
         int len=fread(buff,1,bsize-1,fp);
         buff[bsize]='\0';
         if(len!=bsize-1)
         {
             buff[len]=' ';
             buff[len+1]='$';
             buff[len+2]='\0';
         }
         return len;
     }
struct token getToken(FILE *fp)
    {
    int err=-1;
        int len;
        struct token tok;
        cnt=0;

        do
        {
		if(lexflag==0 && bsize-1!=somerandom)
		{
		    memset(stan,0,30);
		    len=getStream(fp);
		    somerandom=0;
		    lexflag=1;
		}
		if(bsize-1==somerandom)
		{
		    len=getStream(fp);
		    somerandom=0;
		}

		if(buf==0)
		{
		stan[cnt]=buff[somerandom];
		somerandom++;
		}
		else
		    buf--;
		character=stan[cnt];

		cnt++;
		if(character=='$')
			break;
		if(character<0 || character>130)
		{
			cnt--;
			continue;
		}

            state=table[state][character];
            if(sret[state]==1)
            {
                retract(&tok);
                break;
            }
            if(dret==state)
            {
                dretract(&tok);
                break;
            }
        if(state==0 || state==40 || state==41 || state==42)
            cnt=0;
        if(character=='\n')
            lno++;
            if(fin[state]==1)
            {
                strncpy(tok.name,stan,cnt);
                tok.name[cnt]='\0';
                tok.to=state;
                tok.ln=lno;
                if(buf>=0)
                    stan[0]=stan[1];
                break;
            }
            if(state==err)
            {
                strncpy(tok.name,stan,cnt);
                tok.name[cnt]='\0';
                tok.ln=lno;
                tok.to=-1;
                buf=1;
                stan[0]=stan[cnt-1];
                break;
            }

        }while(character!=eom);
        if(character=='$')
        tok.to=1000;
        state=0;
        if(tok.to!=-1 && tok.to!=1000)
            reTok(&tok);
	if(tok.to==99)
		return getToken(fp);
        return tok;
    }
	
	void removeComments(char* fileName,char* resultFile){
	FILE* fr=fopen(fileName,"r");
	FILE* fw=fopen(resultFile,"w");
	if(fr==NULL)
	{
		printf("Opening Source Code Failed");
		return;
	}
	char ch=fgetc(fr),ch1;
	int flag=0;
	while(ch!=EOF)
	{
		ch1=ch;
		ch=fgetc(fr);
        if(flag==1)
        {
            flag=0;
            continue;
        }
		if(ch1=='*')
        {
            if(ch=='*')
            {
                flag=1;
                ch=fgetc(fr);
                while(!(ch1=='*' && ch=='*'))
                {
                    if(ch=='\n')
					fputc(ch,fw);
                    ch1=ch;
                    ch=fgetc(fr);
                }
            }
            else
            {

                fputc(ch1,fw);
            }
        }
        else
        {
            fputc(ch1,fw);
        }
	}
	fclose(fw);
	fclose(fr);

}
