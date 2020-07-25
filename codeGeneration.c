/*AARYAN KAPOOR 2016B4A70166P
 SATWADHI DAS 2016B4A70622P
 ISHAN SANJAY JOGLEKAR 2016B3A70534P
 SATYANSH RAI 2016B4A70632P
 PARTH MISRA 2016B5A70560P*/


#include "codeGeneration.h"

extern int label_count;
extern varTabTree *SS;
extern func *presMod;
extern struct var_list globInput;
extern struct var_list globOutput; 
extern int child;
extern int temp;
extern int INTEGER_SIZE;
extern int REAL_SIZE;
extern int BOOLEAN_SIZE;
extern int oset;

 varid* newTemp(varTabTree *curr, int typ)
 {
     varid tempvar;
     char name[30];
     sprintf(name,"temp%d",temp);
     temp++;
     union type vty;
     vty.t.a=typ;
     int of;
     if(typ==REAL)
            of=REAL_SIZE;
     if(typ==INTEGER)
            of=INTEGER_SIZE;
     if(typ==BOOLEAN)
            of=BOOLEAN_SIZE;
     insert_varTab(0,curr,name,0,of,0,vty);
     return lookup_varid(0,name,curr);
 }

void intCode(AST *itr, FILE *fp)
{
	//fprintf(fp,"here %d \n",itr->type);
	switch(itr->type)
	{
		case programNode:
			;
			printActivationTable1();
			child=0;			
			AST* mo=itr->a.fourChildNode[1];			
			while(mo)
			{
			intCode(mo,fp);
			mo=mo->next;
			}
		
			//printf("www\n");
			mo=itr->a.fourChildNode[3];
			while(mo)
			{
			intCode(mo,fp);
			mo=mo->next;
			}
			
			mo=itr->a.fourChildNode[2];
			func *fun=lookupFunc("DriverModule");
			SS=fun->loc;
			child=0;
			fprintf(fp,"main:\n");
			fprintf(fp,"mov rbp, rsp\n");
			fprintf(fp,"sub rsp,1024\n");
			fprintf(fp,"xor RCX,RCX\n");
			fprintf(fp,"mov cx, 512\n");
			fprintf(fp,"push RCX\n");
			fprintf(fp,"push RCX\n");
			while(mo)
			{
			intCode(mo,fp);
			mo=mo->next;
			}
			
			fprintf(fp,"JMP exitn\n");
			fprintf(fp,"exit:\n");
			fprintf(fp,"mov RDI, error1\n");
			fprintf(fp,"push RSI\n");
			fprintf(fp,"call printf \n");
			fprintf(fp,"pop RSI\n");
			fprintf(fp,"JMP exitn\n");

			fprintf(fp,"exit1:\n");
			
			fprintf(fp,"mov RDI, error2\n");
			fprintf(fp,"push RSI\n");
			fprintf(fp,"call printf \n");
			fprintf(fp,"pop RSI\n");
			fprintf(fp,"JMP exitn\n");
			
			fprintf(fp,"exit2:\n");
			
			fprintf(fp,"mov RDI, error3\n");
			fprintf(fp,"push RSI\n");
			fprintf(fp,"call printf \n");
			fprintf(fp,"pop RSI\n");
			fprintf(fp,"JMP exitn\n");
			
			fprintf(fp,"exit3:\n");
			
			fprintf(fp,"mov RDI, error4\n");
			fprintf(fp,"push RSI\n");
			fprintf(fp,"call printf \n");
			fprintf(fp,"pop RSI\n");
			fprintf(fp,"JMP exitn\n");
			
			fprintf(fp,"exitn:\n");
			fprintf(fp,"mov rsp,rbp\n");
			break;
			
		case driverModuleNode:
			;
			
			AST *mo1=itr->a.oneChildNode[0];
			while(mo1)
			{
			intCode(mo1,fp);
			mo1=mo1->next;
			}
			break;
		
		case plusNode:
			;
			intCode(itr->a.twoChildNode[0],fp);
			intCode(itr->a.twoChildNode[1],fp);
			int expType=expressionTypeChecker(itr, SS,0,presMod);
			if(expType==INTEGER)
				{
				varid *id=newTemp(SS,INTEGER);
				itr->addr=id->offset;
				fprintf(fp,"mov AX, [RBP - %d] \n",itr->a.twoChildNode[0]->addr);
				fprintf(fp,"add AX, [RBP - %d] \n",itr->a.twoChildNode[1]->addr);
				fprintf(fp,"mov [RBP - %d], AX \n",itr->addr);
				itr->addrType=INTEGER;
				
				}
			else
				{
				varid *id=newTemp(SS,REAL);
				itr->addr=id->offset;
				fprintf(fp,"finit \n");
				fprintf(fp,"fld dword [RBP - %d] \n", itr->a.twoChildNode[1]->addr);
				fprintf(fp,"fld dword [RBP - %d] \n", itr->a.twoChildNode[0]->addr);
				fprintf(fp,"fadd \n");
				fprintf(fp,"FST dword [RBP - %d] \n", itr->addr);
				itr->addrType=REAL;
				}
			
			
			break;
			
		case minusNode:
			;
		
			intCode(itr->a.twoChildNode[0],fp);
			intCode(itr->a.twoChildNode[1],fp);
			expType=expressionTypeChecker(itr, SS,0,presMod);
			if(expType==INTEGER)
				{
				varid *id=newTemp(SS,INTEGER);
				itr->addr=id->offset;
				fprintf(fp,"mov AX, [RBP - %d] \n",itr->a.twoChildNode[0]->addr);
				fprintf(fp,"sub AX, [RBP - %d] \n",itr->a.twoChildNode[1]->addr);
				fprintf(fp,"mov [RBP - %d], AX \n",itr->addr);
				itr->addrType=INTEGER;
				
				}
			else
				{
				varid *id=newTemp(SS,REAL);
				itr->addr=id->offset;
				fprintf(fp,"finit \n");
				fprintf(fp,"fld dword [RBP - %d] \n", itr->a.twoChildNode[1]->addr);
				fprintf(fp,"fld dword [RBP - %d] \n", itr->a.twoChildNode[0]->addr);
				fprintf(fp,"fsub \n");
				fprintf(fp,"FST dword [RBP - %d] \n", itr->addr);
				itr->addrType=REAL;
				}
			
			
			break;
		case multiplyNode:
			;
			intCode(itr->a.twoChildNode[0],fp);
			intCode(itr->a.twoChildNode[1],fp);
			expType=expressionTypeChecker(itr, SS,0,presMod);
			if(expType==INTEGER)
			{
				varid *id=newTemp(SS,INTEGER);
				itr->addr=id->offset;
				
				fprintf(fp,"mov AX, [RBP - %d] \n",itr->a.twoChildNode[0]->addr);
				fprintf(fp,"mov DX, [RBP - %d] \n",itr->a.twoChildNode[1]->addr);
				fprintf(fp,"IMUL DX \n");
				fprintf(fp,"mov [RBP - %d], AX \n",itr->addr);
				itr->addrType=INTEGER;
			}
			else
			{
				varid *id=newTemp(SS,REAL);
				itr->addr=id->offset;
				fprintf(fp,"finit \n");
				fprintf(fp,"fld dword [RBP - %d] \n", itr->a.twoChildNode[1]->addr);
				fprintf(fp,"fld dword [RBP - %d] \n", itr->a.twoChildNode[0]->addr);
				fprintf(fp,"fmul \n");
				fprintf(fp,"FST dword [RBP - %d] \n", itr->addr);
				itr->addrType=REAL;
			}
			break;
		case divideNode:
			;
			
			intCode(itr->a.twoChildNode[0],fp);
			intCode(itr->a.twoChildNode[1],fp);
			expType=expressionTypeChecker(itr, SS,0,presMod);
			if(expType==INTEGER)
			{
				varid *id=newTemp(SS,INTEGER);
				itr->addr=id->offset;
				fprintf(fp,"mov AX, [RBP - %d] \n",itr->a.twoChildNode[0]->addr);
				fprintf(fp,"cwd \n");
				fprintf(fp,"mov BX, [RBP - %d] \n",itr->a.twoChildNode[1]->addr);
				fprintf(fp,"IDIV BX \n");
				fprintf(fp,"mov [RBP - %d], AX \n",itr->addr);
				itr->addrType=INTEGER;
			}
			else
			{
				varid *id=newTemp(SS,REAL);
				itr->addr=id->offset;
				fprintf(fp,"finit \n");
				fprintf(fp,"fld dword [RBP - %d] \n", itr->a.twoChildNode[1]->addr);
				fprintf(fp,"fld dword [RBP - %d] \n", itr->a.twoChildNode[0]->addr);
				fprintf(fp,"fdiv \n");
				fprintf(fp,"FST dword [RBP - %d] \n", itr->addr);
				itr->addrType=REAL;
			}
			break;
		
		case whileStmtNode:
			;
			
			int fls,bgn;
			bgn=label_count;
			fprintf(fp,"label%d: \n",label_count);
			label_count++;
			intCode(itr->a.twoChildNode[0],fp);
			fprintf(fp,"CMP byte [RBP - %d],1 \n",itr->a.twoChildNode[0]->addr);//MOV command
			fls=label_count;
			fprintf(fp,"JNE label%d \n",label_count);
			label_count++;
			int olChl=child;
			child=0;
			varTabTree *olSS=SS;
			SS=SS->children[olChl];
			mo=itr->a.twoChildNode[1];
			while(mo)
			{
			intCode(mo,fp);
			mo=mo->next;
			}
			SS=olSS;
			child=olChl+1;
			fprintf(fp,"JMP label%d \n",bgn);
			fprintf(fp,"label%d: \n",fls);
			break;
		
		case relationalOpNode:
			;
			varid *id=newTemp(SS,BOOLEAN);
			itr->addr=id->offset;
			itr->addrType=BOOLEAN;
			intCode(itr->a.threeChildNode[1],fp);
			intCode(itr->a.threeChildNode[2],fp);
			if(expressionTypeChecker(itr->a.threeChildNode[1],SS,0,presMod)==INTEGER)
			{
				fprintf(fp,"MOV AX, [RBP- %d] \n",itr->a.threeChildNode[1]->addr);
				fprintf(fp,"MOV BX, [RBP- %d] \n",itr->a.threeChildNode[2]->addr);
				fprintf(fp,"CMP AX, BX \n");
			}
			
			else
			{
				fprintf(fp,"finit \n");
				fprintf(fp,"fld dword [%d] \n", itr->a.threeChildNode[2]->addr);
				fprintf(fp,"fld dword [%d] \n", itr->a.threeChildNode[1]->addr);
				fprintf(fp,"FCOMPP \n");
			}
				switch(itr->a.threeChildNode[0]->a.treeNode->value)
				{
					case GE+100:
					fprintf(fp,"JGE label%d \n",label_count);
					break;
					
					case EQ+100:
					fprintf(fp,"JE label%d \n",label_count);
					break;
					
					case LT+100:
					fprintf(fp,"JL label%d \n",label_count);
					break;
					
					case GT+100:
					fprintf(fp,"JG label%d \n",label_count);
					break;
					
					case LE+100:
					fprintf(fp,"JLE label%d \n",label_count);
					break;
					
					case NE+100:
					fprintf(fp,"JNE label%d \n",label_count);
					break;
				}
				fprintf(fp,"mov byte [RBP - %d], 0 \n",itr->addr);
				fprintf(fp,"JMP label%d \n",label_count+1);
				fprintf(fp,"label%d: \n",label_count);
				label_count++;
				fprintf(fp,"mov byte [RBP - %d], 1 \n",itr->addr);
				fprintf(fp,"label%d: \n",label_count);
				label_count++;
				
				
			
			
			break;
			
		case logicalOpNode:
			;
			int v=itr->a.threeChildNode[0]->a.treeNode->value;
			id=newTemp(SS,BOOLEAN);
			itr->addr=id->offset;
			itr->addrType=BOOLEAN;
			switch(v)
			{
				case AND+100:
					;
					intCode(itr->a.threeChildNode[1],fp);
					fprintf(fp,"mov AL,[RBP - %d] \n",itr->a.threeChildNode[1]->addr);
					fprintf(fp,"cmp AL, 1 \n");
					fprintf(fp,"JE label%d\n",label_count);
					int sec_eval=label_count;
					label_count++;
					int en=label_count;
					label_count++;
					fprintf(fp,"mov AL,0 \n");
					fprintf(fp,"mov [RBP - %d],AL\n",itr->addr);
					fprintf(fp,"JMP label%d\n",en);
					fprintf(fp,"label%d:\n",sec_eval);
					
					
					intCode(itr->a.threeChildNode[2],fp);
					fprintf(fp,"mov AL,[RBP - %d] \n",itr->a.threeChildNode[2]->addr);
					fprintf(fp,"cmp AL, 1 \n");
					fprintf(fp,"JE label%d\n",label_count);
					int fin_eval=label_count;
					label_count++;
					
					fprintf(fp,"mov AL,0 \n");
					fprintf(fp,"mov [RBP-%d],AL\n",itr->addr);
					fprintf(fp,"JMP label%d\n",en);
					
					fprintf(fp,"label%d:\n",fin_eval);
					fprintf(fp,"mov AL,1 \n");
					fprintf(fp,"mov [RBP-%d],AL\n",itr->addr);
					
					fprintf(fp,"label%d:\n",en);
					
					break;
					
				case OR+100:
					;
					intCode(itr->a.threeChildNode[1],fp);
					fprintf(fp,"mov AL,[RBP-%d] \n",itr->a.threeChildNode[1]->addr);
					fprintf(fp,"cmp AL, 0 \n");
					fprintf(fp,"JE label%d\n",label_count);
					sec_eval=label_count;
					label_count++;
					int en7=label_count;
					label_count++;
					fprintf(fp,"mov AL, 1 \n");
					fprintf(fp,"mov [RBP-%d],AL\n",itr->addr);
					fprintf(fp,"JMP label%d\n",en7);
					fprintf(fp,"label%d:\n",sec_eval);
					
					
					intCode(itr->a.threeChildNode[2],fp);
					fprintf(fp,"mov AL,[RBP - %d] \n",itr->a.threeChildNode[2]->addr);
					fprintf(fp,"cmp AL, 1 \n");
					fprintf(fp,"JE label%d\n",label_count);
					fin_eval=label_count;
					label_count++;
					
					fprintf(fp,"mov AL,0 \n");
					fprintf(fp,"mov [RBP-%d],AL\n",itr->addr);
					fprintf(fp,"JMP label%d\n",en7);
					
					fprintf(fp,"label%d:\n",fin_eval);
					fprintf(fp,"mov AL,1 \n");
					fprintf(fp,"mov [RBP-%d],AL\n",itr->addr);
					
					fprintf(fp,"label%d:\n",en7);
					
					break;
			}
			break;
			
			
		case forstmtNode:
			;
			
			int st,end;
			AST *range=itr->a.threeChildNode[1];
			st=atoi(range->a.twoChildNode[0]->a.treeNode->name);
			end=atoi(range->a.twoChildNode[1]->a.treeNode->name);
			intCode(itr->a.threeChildNode[0],fp);
			fprintf(fp,"mov word [RBP - %d], %d \n",itr->a.threeChildNode[0]->addr,st);
			int bgn1=label_count;
			fprintf(fp,"label%d: \n",bgn1);
			label_count++;
			fprintf(fp,"CMP word [RBP- %d], %d \n",itr->a.threeChildNode[0]->addr,end);
			
			int fls2;
			fprintf(fp,"JG label%d\n",label_count);
			fls2=label_count;
			label_count++;
			int olChl1=child;
			child=0;
			varTabTree *olSS1=SS;
			SS=SS->children[olChl1];
			mo=itr->a.threeChildNode[2];
			while(mo)
			{
			intCode(mo,fp);
			mo=mo->next;
			}
			SS=olSS1;
			child=olChl1+1;
			fprintf(fp,"ADD word [RBP - %d], 1 \n",itr->a.threeChildNode[0]->addr);
			fprintf(fp,"JMP label%d\n",bgn1);
			fprintf(fp,"label%d:\n",fls2);
			break;
			
		case printNode:
			intCode(itr->a.oneChildNode[0],fp);
			int print_chk=itr->a.oneChildNode[0]->addrType;
			switch(print_chk)
			{
			case NUM+100:
			case INTEGER:
			case INTEGER+100:
			case NUM:
			
	
			fprintf(fp,"mov RDI, output\n");
			fprintf(fp,"push RSI\n");
			fprintf(fp,"call printf \n");
			fprintf(fp,"pop RSI\n");


			fprintf(fp,"mov RSI, RBP \n");
			fprintf(fp,"sub RSI, %d \n",itr->a.oneChildNode[0]->addr);
			fprintf(fp,"mov RDI, outputInt \n");
			fprintf(fp,"mov RSI, [RSI] \n");
			fprintf(fp,"push RSI\n");
			fprintf(fp,"call printf \n");
			fprintf(fp,"pop RSI\n");

		
			fprintf(fp,"mov RDI, outputNew \n");
			fprintf(fp,"push RSI\n");
			fprintf(fp,"call printf \n");
			fprintf(fp,"pop RSI\n");

	
			break;

			case TRUET+100:
			case FALSET+100:
			case TRUET:
			case FALSET:
			case BOOLEAN+100:
			case BOOLEAN:
				fprintf(fp,"mov RDI, output\n");
				fprintf(fp,"push RSI\n");
				fprintf(fp,"call printf \n");
				fprintf(fp,"pop RSI\n");

				fprintf(fp,"cmp byte [RBP- %d], 1 \n",itr->a.oneChildNode[0]->addr);
				int print_true=label_count;
				label_count++;
				fprintf(fp,"push 0\n");
				fprintf(fp,"JE label%d\n",print_true);
				fprintf(fp,"mov RDI, outputFalse \n");
				int end_print=label_count;
				label_count++;
				fprintf(fp,"JMP label%d\n", end_print);
				fprintf(fp,"label%d:\n",print_true);
				fprintf(fp,"mov RDI, outputTrue \n");
				fprintf(fp,"label%d:\n",end_print);
				fprintf(fp,"call printf \n");
				fprintf(fp,"pop RSI\n");

				fprintf(fp,"mov RDI, outputNew \n");
				fprintf(fp,"push RSI\n");
				fprintf(fp,"call printf \n");
				fprintf(fp,"pop RSI\n");
				break;
			case ARRAY_BOOLEAN:
				fprintf(fp,"mov RDI, output\n");
				fprintf(fp,"push RSI\n");
				fprintf(fp,"call printf \n");
				fprintf(fp,"pop RSI\n");
			
				fprintf(fp,"mov AX, [RBP -%d]\n",itr->a.oneChildNode[0]->addr-2);
				fprintf(fp,"mov DX, [RBP -%d]\n",itr->a.oneChildNode[0]->addr-4);	
				fprintf(fp,"sub DX, AX\n");
				fprintf(fp,"add DX, 1\n");
				fprintf(fp,"mov AX, 0\n");
				
				fprintf(fp,"xor RBX,RBX\n");
				fprintf(fp,"mov BX, [RBP-%d]\n",itr->a.oneChildNode[0]->addr);
				

				
				int bg2=label_count;
				label_count++;
				fprintf(fp,"label%d:\n",bg2);
				fprintf(fp,"push RAX\n");
				fprintf(fp,"push RDX\n");
				fprintf(fp,"push RAX\n");
				fprintf(fp,"mov RAX,RBP\n");
				fprintf(fp,"sub RAX,RBX\n");
				fprintf(fp,"cmp byte [RAX], 1 \n");
				int print_true1=label_count;
				label_count++;
				fprintf(fp,"JE label%d\n",print_true1);
				fprintf(fp,"mov RDI, outputFalse \n");
				int end_print1=label_count;
				label_count++;
				fprintf(fp,"JMP label%d\n", end_print1);
				fprintf(fp,"label%d:\n",print_true1);
				fprintf(fp,"mov RDI, outputTrue \n");
				fprintf(fp,"label%d:\n",end_print1);
				fprintf(fp,"call printf \n");
				fprintf(fp,"pop RSI\n");
				fprintf(fp,"SUB RBX, 1 \n");
				fprintf(fp,"pop RDX\n");
				fprintf(fp,"pop RAX\n");
				fprintf(fp,"ADD AX, 1\n");
				fprintf(fp,"CMP DX, AX\n");
				fprintf(fp,"JNE label%d\n",bg2);
				
				fprintf(fp,"mov RDI, outputNew \n");
				fprintf(fp,"push RSI\n");
				fprintf(fp,"call printf \n");
				fprintf(fp,"pop RSI\n");
				break;
			case ARRAY_INTEGER:
				fprintf(fp,"mov RDI, output\n");
				fprintf(fp,"push RSI\n");
				fprintf(fp,"call printf \n");
				fprintf(fp,"pop RSI\n");
			
				fprintf(fp,"mov AX, [RBP -%d]\n",itr->a.oneChildNode[0]->addr-2);
				fprintf(fp,"mov DX, [RBP -%d]\n",itr->a.oneChildNode[0]->addr-4);	
				fprintf(fp,"sub DX, AX\n");
				fprintf(fp,"add DX, 1\n");
				fprintf(fp,"mov AX, 0\n");
				
				fprintf(fp,"xor RBX,RBX\n");
				fprintf(fp,"mov BX, [RBP-%d]\n",itr->a.oneChildNode[0]->addr);
				

				
				int bg24=label_count;
				label_count++;
				fprintf(fp,"label%d:\n",bg24);
				fprintf(fp,"push RAX\n");
				fprintf(fp,"push RDX\n");
				fprintf(fp,"mov RDI, outputInt \n");
				fprintf(fp,"mov RSI,RBP\n");
				fprintf(fp,"sub RSI,RBX\n");
				fprintf(fp,"mov RSI,[RSI]\n");
				fprintf(fp,"push RSI\n");
				fprintf(fp,"call printf \n");
				fprintf(fp,"pop RSI\n");
				fprintf(fp,"SUB RBX, 2 \n");
				fprintf(fp,"pop RDX\n");
				fprintf(fp,"pop RAX\n");
				fprintf(fp,"ADD AX, 1\n");
				fprintf(fp,"CMP DX, AX\n");
				fprintf(fp,"JNE label%d\n",bg24);
				
				fprintf(fp,"mov RDI, outputNew \n");
				fprintf(fp,"push RSI\n");
				fprintf(fp,"call printf \n");
				fprintf(fp,"pop RSI\n");
				break;
			}
			break;

			
			
		case getValueNode:
			intCode(itr->a.oneChildNode[0],fp);
			int get_chk=itr->a.oneChildNode[0]->addrType;
			switch(get_chk)
			{
			case NUM+100:
			case INTEGER:
			case INTEGER+100:
			case NUM:
			fprintf(fp,"push 0\n");
			fprintf(fp,"mov RDI, intStmt \n");
			fprintf(fp,"call printf \n");
			fprintf(fp,"pop RSI\n");
			fprintf(fp,"mov RSI, RBP \n");
			fprintf(fp,"sub RSI, %d \n",itr->a.oneChildNode[0]->addr);
			fprintf(fp,"mov RDI, inputInt \n");
			fprintf(fp,"push RSI\n");
			fprintf(fp,"call scanf \n");
			fprintf(fp,"pop RSI\n");
			fprintf(fp,"mov RSI,RSP\n");
			fprintf(fp,"add RSI, %d \n",2);
			fprintf(fp,"mov RDI, inputBool \n");
			fprintf(fp,"push RSI\n");
			fprintf(fp,"call scanf \n");
			fprintf(fp,"pop RSI\n");
			break;

			case TRUET+100:
			case FALSET+100:
			case TRUET:
			case FALSET:
			case BOOLEAN+100:
			case BOOLEAN:

				fprintf(fp,"push 0\n");
				fprintf(fp,"mov RDI, boolStmt \n");
				fprintf(fp,"call printf \n");
				fprintf(fp,"pop RSI\n");
				fprintf(fp,"mov RSI,RBP\n");
				fprintf(fp,"sub RSI, %d \n",itr->a.oneChildNode[0]->addr);
				fprintf(fp,"mov RDI, inputBool \n");
				fprintf(fp,"push RSI\n");
				fprintf(fp,"call scanf \n");
				fprintf(fp,"pop RSI\n");
				fprintf(fp,"sub byte [RBP - %d], '0' \n",itr->a.oneChildNode[0]->addr);
				fprintf(fp,"mov RSI,RSP\n");
				fprintf(fp,"add RSI, %d \n",2);
				fprintf(fp,"mov RDI, inputBool \n");
				fprintf(fp,"push RSI\n");
				fprintf(fp,"call scanf \n");
				fprintf(fp,"pop RSI\n");
				break;
			case ARRAY_INTEGER: 
				fprintf(fp,"push 0\n");
				fprintf(fp,"mov RDI, arrStmt1 \n");
				fprintf(fp,"call printf \n");
				fprintf(fp,"pop RSI\n");
				
				fprintf(fp,"xor RBX,RBX\n");
				fprintf(fp,"mov AX, [RBP -%d]\n",itr->a.oneChildNode[0]->addr-2);
				fprintf(fp,"mov BX, [RBP -%d]\n",itr->a.oneChildNode[0]->addr-4);						
				fprintf(fp,"sub BX, AX\n");
				fprintf(fp,"add BX, 1\n");
				fprintf(fp,"mov RSI, RBX\n");;
				fprintf(fp,"mov RDI, inputInt \n");
			//	fprintf(fp,"mov RSI, [RSI] \n");
				fprintf(fp,"push 0\n");
				fprintf(fp,"call printf \n");
				fprintf(fp,"pop RSI\n");

				fprintf(fp,"push 0\n");
				fprintf(fp,"mov RDI, arrIntStmt \n");
				fprintf(fp,"call printf \n");
				fprintf(fp,"pop RSI\n");

				fprintf(fp,"mov RSI, RBP \n");
				fprintf(fp,"sub RSI, %d \n",itr->a.oneChildNode[0]->addr-2);
				fprintf(fp,"mov RDI, inputInt \n");
				fprintf(fp,"mov RSI, [RSI] \n");
				fprintf(fp,"push 0\n");
				fprintf(fp,"call printf \n");
				fprintf(fp,"pop RSI\n");
				
				fprintf(fp,"push 0\n");
				fprintf(fp,"mov RDI, arrStmt3 \n");
				fprintf(fp,"call printf \n");
				fprintf(fp,"pop RSI\n");

				fprintf(fp,"mov RSI, RBP \n");
				fprintf(fp,"sub RSI, %d \n",itr->a.oneChildNode[0]->addr-4);
				fprintf(fp,"mov RDI, inputInt \n");
				fprintf(fp,"mov RSI, [RSI] \n");
				fprintf(fp,"push 0\n");
				fprintf(fp,"call printf \n");
				fprintf(fp,"pop RSI\n");

				fprintf(fp,"push 0\n");
				fprintf(fp,"mov RDI, outputNew\n");
				fprintf(fp,"call printf \n");
				fprintf(fp,"pop RSI\n");

				fprintf(fp,"mov AX, [RBP -%d]\n",itr->a.oneChildNode[0]->addr-2);
				fprintf(fp,"mov DX, [RBP -%d]\n",itr->a.oneChildNode[0]->addr-4);	
				fprintf(fp,"sub DX, AX\n");
				fprintf(fp,"add DX, 1\n");
				fprintf(fp,"mov AX, 0\n");
				
				fprintf(fp,"xor RBX,RBX\n");
				fprintf(fp,"mov BX, [RBP-%d]\n",itr->a.oneChildNode[0]->addr);
				

			
				int bg21=label_count;
				label_count++;
				fprintf(fp,"label%d:\n",bg21);
				fprintf(fp,"push RAX\n");
				fprintf(fp,"push RDX\n");
				fprintf(fp,"mov RDI, inputInt \n");
				fprintf(fp,"mov RSI,RBP\n");
				fprintf(fp,"sub RSI,RBX\n");

				fprintf(fp,"push RSI\n");
				fprintf(fp,"call scanf \n");
				fprintf(fp,"pop RSI\n");
				fprintf(fp,"SUB RBX, 2 \n");
				fprintf(fp,"mov RSI,RSP\n");
				fprintf(fp,"add RSI, %d \n",2);
				fprintf(fp,"mov RDI, inputBool \n");
				fprintf(fp,"push RSI\n");
				fprintf(fp,"call scanf \n");
				fprintf(fp,"pop RSI\n");
				fprintf(fp,"pop RDX\n");
				fprintf(fp,"pop RAX\n");
				fprintf(fp,"ADD AX, 1\n");
				fprintf(fp,"CMP DX, AX\n");
				fprintf(fp,"JNE label%d\n",bg21);
				break;
			case ARRAY_BOOLEAN:
				fprintf(fp,"push 0\n");
				fprintf(fp,"mov RDI, arrStmt1 \n");
				fprintf(fp,"call printf \n");
				fprintf(fp,"pop RSI\n");
				
				fprintf(fp,"xor RBX,RBX\n");
				fprintf(fp,"mov AX, [RBP -%d]\n",itr->a.oneChildNode[0]->addr-2);
				fprintf(fp,"mov BX, [RBP -%d]\n",itr->a.oneChildNode[0]->addr-4);						
				fprintf(fp,"sub BX, AX\n");
				fprintf(fp,"add BX, 1\n");
				fprintf(fp,"mov RSI, RBX\n");;
				fprintf(fp,"mov RDI, inputInt \n");
			//	fprintf(fp,"mov RSI, [RSI] \n");
				fprintf(fp,"push 0\n");
				fprintf(fp,"call printf \n");
				fprintf(fp,"pop RSI\n");

				fprintf(fp,"push 0\n");
				fprintf(fp,"mov RDI, arrBoolStmt \n");
				fprintf(fp,"call printf \n");
				fprintf(fp,"pop RSI\n");

				fprintf(fp,"mov RSI, RBP \n");
				fprintf(fp,"sub RSI, %d \n",itr->a.oneChildNode[0]->addr-2);
				fprintf(fp,"mov RDI, inputInt \n");
				fprintf(fp,"mov RSI, [RSI] \n");
				fprintf(fp,"push 0\n");
				fprintf(fp,"call printf \n");
				fprintf(fp,"pop RSI\n");
				
				fprintf(fp,"push 0\n");
				fprintf(fp,"mov RDI, arrStmt3 \n");
				fprintf(fp,"call printf \n");
				fprintf(fp,"pop RSI\n");

				fprintf(fp,"mov RSI, RBP \n");
				fprintf(fp,"sub RSI, %d \n",itr->a.oneChildNode[0]->addr-4);
				fprintf(fp,"mov RDI, inputInt \n");
				fprintf(fp,"mov RSI, [RSI] \n");
				fprintf(fp,"push 0\n");
				fprintf(fp,"call printf \n");
				fprintf(fp,"pop RSI\n");

				fprintf(fp,"push 0\n");
				fprintf(fp,"mov RDI, outputNew\n");
				fprintf(fp,"call printf \n");
				fprintf(fp,"pop RSI\n");

				fprintf(fp,"mov AX, [RBP -%d]\n",itr->a.oneChildNode[0]->addr-2);
				fprintf(fp,"mov DX, [RBP -%d]\n",itr->a.oneChildNode[0]->addr-4);	
				fprintf(fp,"sub DX, AX\n");
				fprintf(fp,"add DX, 1\n");
				fprintf(fp,"mov AX, 0\n");
				
				fprintf(fp,"xor RBX,RBX\n");
				fprintf(fp,"mov BX, [RBP-%d]\n",itr->a.oneChildNode[0]->addr);
				

				
				int bg22=label_count;
				label_count++;
				fprintf(fp,"label%d:\n",bg22);
				fprintf(fp,"push RAX\n");
				fprintf(fp,"push RDX\n");
				fprintf(fp,"mov RDI, inputBool \n");
				fprintf(fp,"mov RSI,RBP\n");
				fprintf(fp,"sub RSI,RBX\n");
				fprintf(fp,"push RSI\n");
				fprintf(fp,"call scanf \n");
				fprintf(fp,"pop RSI\n");
				fprintf(fp,"push RAX\n");
				fprintf(fp,"mov RAX, RBP\n");
				fprintf(fp,"sub RAX,RBX\n");
				fprintf(fp,"sub byte [RAX], '0' \n");
				fprintf(fp,"pop RAX\n");
				fprintf(fp,"SUB RBX, 1 \n");
				fprintf(fp,"mov RSI,RSP\n");
				fprintf(fp,"add RSI, %d \n",2);
				fprintf(fp,"mov RDI, inputBool \n");
				fprintf(fp,"push RSI\n");
				fprintf(fp,"call scanf \n");
				fprintf(fp,"pop RSI\n");
				fprintf(fp,"pop RDX\n");
				fprintf(fp,"pop RAX\n");
				fprintf(fp,"ADD AX, 1\n");
				fprintf(fp,"CMP DX, AX\n");
				fprintf(fp,"JNE label%d\n",bg22);
				
				break;
			
			}
			break;
			
		case assignStmtNode:
			;
			//intCode(itr->a.twoChildNode[0],fp);
			if(itr->a.twoChildNode[1]->type==lvalueArrStmtNode)
			{
				intCode(itr->a.twoChildNode[0],fp);
				intCode(itr->a.twoChildNode[1]->a.twoChildNode[0],fp);
				intCode(itr->a.twoChildNode[1]->a.twoChildNode[1],fp);
				
				id=lookup_varid(1000,itr->a.twoChildNode[0]->a.treeNode->name,SS);
				if(id==NULL)
				{
					
					var_l *alt=lookup_varid1(itr->a.twoChildNode[0]->a.treeNode->name,globInput);
					itr->addr=alt->offset;
					
						int type=alt->typ.a.sub.a;
						
						if(type==INTEGER)
						itr->addrType=INTEGER;
						else
						itr->addrType=BOOLEAN;
							//intCode(itr->next,fp);
							fprintf(fp,"mov AX, [RBP - %d + 2] \n",itr->addr);
							fprintf(fp,"mov BX, [RBP - %d + 4] \n",itr->addr);
							fprintf(fp,"mov DX, [RBP - %d] \n",itr->a.twoChildNode[1]->a.twoChildNode[0]->addr);
							fprintf(fp,"cmp DX, AX \n");
							fprintf(fp,"JL exit \n");
							fprintf(fp,"cmp BX, DX\n");
							fprintf(fp,"JL exit \n");
							fprintf(fp,"sub DX,AX \n");
							if(itr->addrType==INTEGER)
								fprintf(fp,"mov AX, 2\n");
							else
								fprintf(fp,"mov AX, 1 \n");
							varid *id1=newTemp(SS,INTEGER);
							itr->addr=id1->offset;
							fprintf(fp,"IMUL DX\n");
							fprintf(fp,"ADD [RBP-%d], AX\n",itr->addr);
					

					}
					else{
						itr->addr = id->offset;
							int type=id->vartype.a.sub.a;
							if(type==INTEGER)
								itr->addrType=INTEGER;
							else
								itr->addrType=BOOLEAN;
							//intCode(itr->next,fp);
							fprintf(fp,"mov AX, [RBP - %d + 2] \n",itr->addr);
							fprintf(fp,"mov BX, [RBP - %d + 4] \n",itr->addr);
							fprintf(fp,"mov DX, [RBP - %d] \n",itr->a.twoChildNode[1]->a.twoChildNode[0]->addr);
							fprintf(fp,"cmp DX, AX \n");
							fprintf(fp,"JL exit \n");
							fprintf(fp,"cmp BX, DX\n");
							fprintf(fp,"JL exit \n");
							fprintf(fp,"sub DX,AX \n");
							
							if(itr->addrType==INTEGER)
								fprintf(fp,"mov AX, 2\n");
							else
								fprintf(fp,"mov AX, 1 \n");

							fprintf(fp,"IMUL DX\n");
							fprintf(fp,"mov DX,[RBP-%d]\n",itr->addr);
							varid *id1=newTemp(SS,INTEGER);
							itr->addr=id1->offset;
							fprintf(fp,"sub DX, AX\n");
							fprintf(fp,"mov [RBP-%d],DX\n",itr->addr);

						}
							fprintf(fp,"xor RAX,RAX\n");
							fprintf(fp,"mov RAX, RBP\n");
							fprintf(fp,"xor RBX, RBX\n");
							fprintf(fp,"mov BX, [RBP-%d]\n",itr->addr);	
							fprintf(fp,"sub RAX, RBX\n");
							if(itr->addrType==INTEGER)
							{
								fprintf(fp,"mov BX, [RBP -%d]\n",itr->a.twoChildNode[1]->a.twoChildNode[1]->addr);
								fprintf(fp,"mov [RAX], BX\n");
							}
							else
							{
								fprintf(fp,"mov BL, [RBP -%d]\n",itr->a.twoChildNode[1]->a.twoChildNode[1]->addr);
								fprintf(fp,"mov [RAX], BL\n");
							}	
			}
			else
			{
				intCode(itr->a.twoChildNode[1],fp);
				intCode(itr->a.twoChildNode[0],fp);
				
				if(itr->a.twoChildNode[1]->addrType==INTEGER || itr->a.twoChildNode[1]->addrType== INTEGER + 100)
				{
					fprintf(fp,"mov AX, [RBP - %d] \n",itr->a.twoChildNode[1]->addr);
					fprintf(fp,"mov [RBP - %d], AX \n",itr->a.twoChildNode[0]->addr);
				}
				if(itr->a.twoChildNode[1]->addrType==ARRAY_INTEGER || itr->a.twoChildNode[1]->addrType==ARRAY_BOOLEAN)
				{

					fprintf(fp, "mov AX, [RBP - %d +2]\n", itr->a.twoChildNode[1]->addr);
					fprintf(fp, "mov BX, [RBP - %d +2]\n", itr->a.twoChildNode[1]->addr);
					fprintf(fp, "cmp AX,BX\n");
					fprintf(fp,"JNE exit1 \n");
										

					fprintf(fp, "mov AX, [RBP - %d +4]\n", itr->a.twoChildNode[1]->addr);
					fprintf(fp, "mov BX, [RBP - %d +4]\n", itr->a.twoChildNode[1]->addr);
					fprintf(fp, "cmp AX,BX\n");
					fprintf(fp,"JNE exit1 \n");

					fprintf(fp,"mov AX, [RBP - %d] \n",itr->a.twoChildNode[1]->addr);
					fprintf(fp,"mov [RBP - %d], AX \n",itr->a.twoChildNode[0]->addr);
				}
				if(itr->a.twoChildNode[1]->addrType==BOOLEAN || itr->a.twoChildNode[1]->addrType==BOOLEAN + 100)
				{
					fprintf(fp,"mov AL, [RBP - %d] \n",itr->a.twoChildNode[1]->addr);
					fprintf(fp,"mov [RBP - %d], AL \n",itr->a.twoChildNode[0]->addr);
				}
				
			}
			break;
			
			
		case unaryPlusNode:
			;
			intCode(itr->a.oneChildNode[0],fp);
			itr->addr=itr->a.oneChildNode[0]->addr;
			itr->addrType=itr->a.oneChildNode[0]->addrType;
			break;
		
		case unaryMinusNode:
			;
			intCode(itr->a.oneChildNode[0],fp);
			fprintf(fp," mov DX,-1\n");
			fprintf(fp,"mov AX, [RBP-%d]\n",itr->a.oneChildNode[0]->addr);
			fprintf(fp,"IMUL DX\n");
			fprintf(fp,"mov [RBP - %d], AX \n",itr->a.oneChildNode[0]->addr);
			itr->addr=itr->a.oneChildNode[0]->addr;
			itr->addrType=itr->a.oneChildNode[0]->addrType;
			break;
			
		case unaryExpressionNode:
			;
			intCode(itr->a.oneChildNode[0],fp);
			itr->addr=itr->a.oneChildNode[0]->addr;
			itr->addrType=itr->a.oneChildNode[0]->addrType;
			break;
			
		case expressionNode:
			;
			intCode(itr->a.oneChildNode[0],fp);
			itr->addr=itr->a.oneChildNode[0]->addr;
			itr->addrType=itr->a.oneChildNode[0]->addrType;
			break;
		case 100+TRUET:
		case 100+FALSET:
		case parsetreeNode:
			;
			int chk=itr->a.treeNode->value;
			
			switch(chk)
			{
			case NUM:
			case NUM+100:
				;
				int val=atoi(itr->a.treeNode->name);
				id=newTemp(SS,INTEGER);

					//printf("g %d\n", val);
				itr->addr=id->offset;
				fprintf(fp,"mov AX, %d \n",val);
				fprintf(fp,"mov [RBP - %d], AX \n",itr->addr);
				itr->addrType=INTEGER;
				break;
					
		
			
			case TRUET+100:
				;
				id=newTemp(SS,BOOLEAN);
				itr->addr=id->offset;
				fprintf(fp,"mov AL, 1 \n");
				fprintf(fp,"mov [RBP-%d], AL \n",itr->addr);
				
				itr->addrType=BOOLEAN;
				break;
				
				case FALSET+100:
				;
				id=newTemp(SS,BOOLEAN);
				itr->addr=id->offset;
				fprintf(fp,"mov AL, 0 \n");
				fprintf(fp,"mov [RBP-%d], AL \n",itr->addr);
				
				itr->addrType=BOOLEAN;
				break;
				
			case ID+100:
				;
				id=lookup_varid(1000,itr->a.treeNode->name,SS);
				if(id==NULL)
				{
					
					var_l *alt=lookup_varid1(itr->a.treeNode->name,globInput);//change
					if(alt==NULL)
						alt=lookup_varid1(itr->a.treeNode->name,globOutput);
					itr->addr=alt->offset;
					
					if(alt->t==1 && itr->next)
					{
						int type=alt->typ.a.sub.a;
						
						if(type==INTEGER)
						itr->addrType=INTEGER;
						else
						itr->addrType=BOOLEAN;
							intCode(itr->next,fp);
							fprintf(fp,"mov AX, [RBP - %d + 2] \n",itr->addr);
							fprintf(fp,"mov BX, [RBP - %d + 4] \n",itr->addr);
							fprintf(fp,"mov DX, [RBP - %d] \n",itr->next->addr);
							fprintf(fp,"cmp DX, AX \n");
							fprintf(fp,"JL exit \n");
							fprintf(fp,"cmp BX, DX\n");
							fprintf(fp,"JL exit \n");
							fprintf(fp,"sub DX,AX \n");
							if(itr->addrType==INTEGER)
								fprintf(fp,"mov AX, 2\n");
							else
								fprintf(fp,"mov AX, 1 \n");
							varid *id1=newTemp(SS,INTEGER);
							itr->addr=id1->offset;
							fprintf(fp,"IMUL DX\n");

							fprintf(fp,"mov DX, [RBP-%d]\n",itr->addr);
							fprintf(fp,"sub DX, AX\n");
							varid *id2=newTemp(SS,INTEGER);
							itr->addr=id2->offset;
							fprintf(fp,"mov [RBP - %d], DX\n",itr->addr);
					

							fprintf(fp,"xor RAX,RAX\n");
							fprintf(fp,"mov RAX, RBP\n");
							fprintf(fp,"xor RBX, RBX\n");
							fprintf(fp,"mov BX, [RBP-%d]\n",itr->addr);	
							fprintf(fp,"sub RAX, RBX\n");


							fprintf(fp,"mov BX, [RAX]\n");
							fprintf(fp,"mov [RBP - %d], BX\n", itr->addr);
					}
					else
						{	
							if(alt->t==1){
								if(alt->typ.a.sub.a==INTEGER || alt->typ.a.sub.a==INTEGER+100)
									itr->addrType=ARRAY_INTEGER;
								else 						
									itr->addrType=ARRAY_BOOLEAN;
							}
							else
							itr->addrType=alt->typ.t.a;
							
						}
					}
				else{
						itr->addr = id->offset;
						if(id->ut==1 && itr->next)
							{
							int type=id->vartype.a.sub.a;
							if(type==INTEGER)
								itr->addrType=INTEGER;
							else
								itr->addrType=BOOLEAN;
							intCode(itr->next,fp);
							fprintf(fp,"mov AX, [RBP - %d + 2] \n",itr->addr);
							fprintf(fp,"mov BX, [RBP - %d + 4] \n",itr->addr);
							fprintf(fp,"mov DX, [RBP - %d] \n",itr->next->addr);
							fprintf(fp,"cmp DX, AX \n");
							fprintf(fp,"JL exit \n");
							fprintf(fp,"cmp BX, DX\n");
							fprintf(fp,"JL exit \n");
							fprintf(fp,"sub DX,AX \n");
							
							if(itr->addrType==INTEGER)
								fprintf(fp,"mov AX, 2\n");
							else
								fprintf(fp,"mov AX, 1 \n");

							
							fprintf(fp,"IMUL DX\n");
							fprintf(fp,"mov DX, [RBP-%d]\n",itr->addr);
							fprintf(fp,"sub DX, AX\n");
							varid *id1=newTemp(SS,INTEGER);
							itr->addr=id1->offset;
							fprintf(fp,"mov [RBP - %d], DX\n",itr->addr);
	
							fprintf(fp,"xor RAX,RAX\n");
							fprintf(fp,"mov RAX, RBP\n");
							fprintf(fp,"xor RBX, RBX\n");
							fprintf(fp,"mov BX, [RBP-%d]\n",itr->addr);	
							fprintf(fp,"sub RAX, RBX\n");

							fprintf(fp,"mov BX, [RAX]\n");
							fprintf(fp,"mov [RBP - %d], BX\n", itr->addr);
						
						}
						else
							{	
								if(id->ut==1){
									if(id->vartype.a.sub.a==INTEGER || id->vartype.a.sub.a==INTEGER+100)
										itr->addrType=ARRAY_INTEGER;
									else 						
										itr->addrType=ARRAY_BOOLEAN;
								}
								else
								itr->addrType=id->vartype.t.a;
								
							}
							
						}
				
			
	
			
			break;
			}
		
			break;
			
		case conditionalStmtNode:
			;
			//printf("Conditional\n");
			AST *case_st;
			int end1=label_count;
			label_count++;
			intCode(itr->a.threeChildNode[0],fp);
			if(itr->a.threeChildNode[0]->addrType==INTEGER+100 || itr->a.threeChildNode[0]->addrType==INTEGER)
			{
				id=lookup_varid(1000,itr->a.threeChildNode[0]->a.treeNode->name,SS);
				if(id!=NULL)
					itr->addr=id->offset;
				else{
					var_l * wh = lookup_varid1(itr->a.threeChildNode[0]->a.treeNode->name,globInput);
					if(wh==NULL){
						wh=lookup_varid1(itr->a.threeChildNode[0]->a.treeNode->name,globOutput);
					}
					itr->addr=wh->offset;
				}
				itr->addrType=INTEGER;
				case_st=itr->a.threeChildNode[1];
				int olChl=child;
				child=0;
				varTabTree *olSS=SS;
				SS=SS->children[olChl];
				while(case_st->next)
				{
					//printf("%s\n",case_st->a.twoChildNode[0]->a.treeNode->name);
					int val=atoi(case_st->a.twoChildNode[0]->a.treeNode->name);
					fprintf(fp,"mov AX, [RBP- %d] \n",itr->addr);
					fprintf(fp,"cmp AX, %d \n",val);
					int fls=label_count;
					label_count++;
					fprintf(fp,"JNE label%d\n",fls);
					intCode(case_st,fp);
					fprintf(fp,"JMP label%d\n",end1);

					fprintf(fp,"label%d:\n",fls);
					case_st=case_st->next;
				}
				AST* def=itr->a.threeChildNode[2];
				while(def)
				{
					intCode(def,fp);
					def=def->next;
				}
				SS=olSS;
				child=olChl+1;
				fprintf(fp,"label%d:\n",end1);
			}
			if(itr->a.threeChildNode[0]->addrType==BOOLEAN+100 || itr->a.threeChildNode[0]->addrType==BOOLEAN)
			{
				varid *id=lookup_varid(1000,itr->a.threeChildNode[0]->a.treeNode->name,SS);
				if(id!=NULL)
					itr->addr=id->offset;
				else{
					var_l * wh = lookup_varid1(itr->a.threeChildNode[0]->a.treeNode->name,globInput);
					if(wh==NULL){
						wh=lookup_varid1(itr->a.threeChildNode[0]->a.treeNode->name,globOutput);
					}
					itr->addr=wh->offset;
				}
				itr->addrType=BOOLEAN;
				case_st=itr->a.threeChildNode[1];
				int olChl=child;
				child=0;
				varTabTree *olSS=SS;
				SS=SS->children[olChl];
								
					fprintf(fp,"mov AL, [RBP- %d] \n",itr->addr);
					//printf("%d\n",case_st->a.twoChildNode[0]->type);
					if(case_st->a.twoChildNode[0]->type==TRUET+100){
							fprintf(fp,"cmp AL, 1 \n");
							int fls=label_count;
							label_count++;	
							fprintf(fp,"JNE label%d\n",fls);
							intCode(case_st,fp);
							int fls1=label_count;
							label_count++;
							fprintf(fp,"JMP label%d\n",fls1);
							fprintf(fp,"label%d:\n",fls);
							case_st=case_st->next;	
							intCode(case_st,fp);									
							fprintf(fp,"label%d:\n",fls1);	
							//printf("%d %d\n",fls, fls1);	
					}			
					else{
							fprintf(fp,"cmp AL, 0\n");
							int fls=label_count;
							label_count++;	
							fprintf(fp,"JNE label%d\n",fls);
							intCode(case_st,fp);
							int fls1=label_count;
							label_count++;
							fprintf(fp,"JMP label%d\n",fls1);
							fprintf(fp,"label%d:\n",fls);	
							case_st=case_st->next;
							intCode(case_st,fp);									
							fprintf(fp,"label%d:\n",fls1);	
					}
				
				SS=olSS;
				child=olChl+1;
			}
				break;
		case caseStmtNode:
			;
			AST *stmt=itr->a.twoChildNode[1];
			while(stmt)
			{
				intCode(stmt,fp);
				stmt=stmt->next;
			}
			break;
		
		case moduleNode:
			;
			
			//printf("In Module\n");
			fprintf(fp,"%s:\n",itr->a.fourChildNode[0]->a.treeNode->name);
			fprintf(fp,"push rbp\n");
			
			fprintf(fp,"mov rbp, rsp\n");
			fprintf(fp,"sub rsp, 1024\n");
			fprintf(fp,"XOR RCX, RCX\n");
			fprintf(fp,"push RCX\n");
			fprintf(fp,"push RCX\n");
			func *modFunc=lookupFunc(itr->a.fourChildNode[0]->a.treeNode->name);
			int loc_oset=oset;
			oset=modFunc->func_oset;
			presMod=modFunc;
			varTabTree *modSS=SS;
			var_list modInp=globInput;
			var_list modOut=globOutput;
			globInput=modFunc->input_list;
			globOutput=modFunc->output_list;
			SS=modFunc->loc;
			stmt=itr->a.fourChildNode[3];
			while(stmt)
			{
				intCode(stmt,fp);
				stmt=stmt->next;
			}
			SS=modSS;
			globInput=modInp;
			globOutput=modOut;
			
			fprintf(fp,"pop RCX \n");
			fprintf(fp,"pop RCX \n");
			fprintf(fp,"add rsp,1024\n");
			
			fprintf(fp,"pop rbp\n");
			fprintf(fp,"ret\n");
			oset=loc_oset;	
			break;
			
		
		case moduleReuseStmtNode:
			;
			//fprintf(fp,"mov RSP, RBP\n");
			//fprintf(fp,"sub RSP, 5\n");
			//fprintf(fp,"sub rsp, 504\n");
			fprintf(fp,"xor RCX, RCX \n");
			fprintf(fp,"mov CX,512 \n");
			fun=lookupFunc(itr->a.threeChildNode[1]->a.treeNode->name);
			
			func *re=presMod;
			presMod=fun;

			presMod=re;
			
			AST *id_lis=itr->a.threeChildNode[2];
			var_l *blist=fun->input_list.head;
			int i=0;
			while(id_lis)
			{
				intCode(id_lis,fp);
				if(id_lis->addrType==INTEGER)
				{
				i+=2;
				fprintf(fp,"mov BX , [RBP - %d] \n",id_lis->addr);
				fprintf(fp,"mov  [RBP - 1024 - 16 - 16- %d] , BX\n",i);
				}
				if(id_lis->addrType==BOOLEAN)
				{
				i+=1;
				fprintf(fp,"mov BL , [RBP - %d] \n",id_lis->addr);
				fprintf(fp,"mov [RBP - 1024-16 -16 - %d] , BL\n",i);
				}
				if(id_lis->addrType==ARRAY_INTEGER)
				{
				i+=6;
				int r_type=blist->typ.a.range_kind;
				if(r_type==1 || r_type==2)
				{
				int start_ind=blist->typ.a.st.num;
				fprintf(fp,"CMP word [RBP - %d +2], %d\n",id_lis->addr,start_ind);
				fprintf(fp,"JNE exit\n");
				}
				if(r_type==1 || r_type==3)
				{
				int end_ind=blist->typ.a.end.num;
				fprintf(fp,"CMP word [RBP - %d +4], %d\n",id_lis->addr,end_ind);
				fprintf(fp,"JNE exit\n");
				}
				fprintf(fp,"mov AX, [RBP- %d +2]\n",id_lis->addr);
				fprintf(fp,"mov DX, [RBP- %d +4]\n",id_lis->addr);
				fprintf(fp,"push AX\n");	
				fprintf(fp,"push DX\n");
				
				fprintf(fp,"mov [RBP -1024 -16 - 14 - %d], AX\n",i);	
				fprintf(fp,"mov [RBP -1024 - 16- 12 - %d], DX\n",i);				
				
				fprintf(fp,"mov RSI, RBP\n");
				fprintf(fp,"xor rbx,rbx \n");
				fprintf(fp,"mov bx, [RBP- %d]\n",id_lis->addr);
				fprintf(fp,"sub RSI, RBX\n");
				

				fprintf(fp,"mov RDI, RBP\n");
				fprintf(fp,"xor rbx,rbx\n");
				fprintf(fp,"sub RDI, 1056\n");
//				fprintf(fp, "sub rdi, %d\n",i);

				fprintf(fp,"add CX,DX\n");
				fprintf(fp,"add CX,DX\n");
				fprintf(fp,"sub CX,AX\n");
				fprintf(fp,"sub CX,AX\n");
				fprintf(fp,"add CX,2\n");
				
				fprintf(fp,"mov [rbp - 1056 - %d], CX\n",i);

				fprintf(fp,"SUB RDI, RCX\n");

				
				int label_mod=label_count;
				label_count++;				
				fprintf(fp,"label%d:\n",label_mod);
				fprintf(fp,"mov BX,[RSI] \n");
				fprintf(fp,"mov [RDI],BX \n");
			
				fprintf(fp,"push RCX\n");
				fprintf(fp,"xor rcx,rcx\n");				
				fprintf(fp,"mov cx,2\n");
				fprintf(fp,"add RSI,RCX \n");
				fprintf(fp,"add RDI,RCX \n");
				fprintf(fp,"pop RCX\n");
				fprintf(fp,"pop DX\n");	
				fprintf(fp,"pop AX\n");
				fprintf(fp,"add AX,1 \n");
				fprintf(fp,"CMP AX, DX\n");
				fprintf(fp,"push AX\n");	
				fprintf(fp,"push DX\n");
				fprintf(fp,"JLE label%d\n",label_mod);
				fprintf(fp,"pop DX\n");	
				fprintf(fp,"pop AX\n");

				
				
				}


				if(id_lis->addrType==ARRAY_BOOLEAN)
				{
				i+=6;
				int r_type=blist->typ.a.range_kind;
				if(r_type==1 || r_type==2)
				{
				int start_ind=blist->typ.a.st.num;
				fprintf(fp,"CMP word [RBP - %d +2], %d\n",id_lis->addr,start_ind);
				fprintf(fp,"JNE exit\n");
				}
				if(r_type==1 || r_type==3)
				{
				int end_ind=blist->typ.a.end.num;
				fprintf(fp,"CMP word [RBP - %d +4], %d\n",id_lis->addr,end_ind);
				fprintf(fp,"JNE exit\n");
				}
				fprintf(fp,"mov AX, [RBP- %d +2]\n",id_lis->addr);
				fprintf(fp,"mov DX, [RBP- %d +4]\n",id_lis->addr);
				fprintf(fp,"push AX\n");	
				fprintf(fp,"push DX\n");
				
				fprintf(fp,"mov [RBP -1024 -16 - 14 - %d], AX\n",i);	
				fprintf(fp,"mov [RBP -1024 - 16- 12 - %d], DX\n",i);				
				
				fprintf(fp,"mov RSI, RBP\n");
				fprintf(fp,"xor rbx,rbx \n");
				fprintf(fp,"mov bx, [RBP- %d]\n",id_lis->addr);
				fprintf(fp,"sub RSI, RBX\n");
				

				fprintf(fp,"mov RDI, RBP\n");
				fprintf(fp,"xor rbx,rbx\n");
				fprintf(fp,"sub RDI, 1056\n");
//				fprintf(fp, "sub rdi, %d\n",i);

				fprintf(fp,"add CX,DX\n");
			//	fprintf(fp,"add CX,DX\n");
				fprintf(fp,"sub CX,AX\n");
				//fprintf(fp,"sub CX,AX\n");
				fprintf(fp,"add CX,1\n");
				
				fprintf(fp,"mov [rbp - 1056 - %d], CX\n",i);

				fprintf(fp,"SUB RDI, RCX\n");

				
				int label_mod=label_count;
				label_count++;				
				fprintf(fp,"label%d:\n",label_mod);
				fprintf(fp,"mov BL,[RSI] \n");
				fprintf(fp,"mov [RDI],BL \n");
				fprintf(fp,"push RCX\n");
				fprintf(fp,"xor rcx,rcx\n");				
				fprintf(fp,"mov cx,1\n");
				fprintf(fp,"add RSI,RCX \n");
				fprintf(fp,"add RDI,RCX \n");
				fprintf(fp,"pop RCX\n");
				fprintf(fp,"pop DX\n");	
				fprintf(fp,"pop AX\n");
				fprintf(fp,"add AX,1 \n");
				fprintf(fp,"CMP AX, DX\n");
				fprintf(fp,"push AX\n");	
				fprintf(fp,"push DX\n");
				fprintf(fp,"JLE label%d\n",label_mod);
				fprintf(fp,"pop DX\n");	
				fprintf(fp,"pop AX\n");

				
				
				}
				blist=blist->next;
				id_lis=id_lis->next;
				
			}
			fprintf(fp,"call %s \n",itr->a.threeChildNode[1]->a.treeNode->name);
			var_l *vlist=fun->output_list.head;
			AST *opt=itr->a.threeChildNode[0];
			while(opt)
			{
				intCode(opt,fp);
				if(opt->addrType==INTEGER)
				{
				fprintf(fp,"mov BX, [RBP  - 1024-16- 16- %d] \n",vlist->offset);
				fprintf(fp,"mov [RBP - %d], BX \n",opt->addr);
				}
				
				if(opt->addrType==BOOLEAN)
				{
					fprintf(fp,"mov BL, [RBP  - 1024- 16-16- %d] \n",vlist->offset);
					fprintf(fp,"mov [RBP - %d], BL \n",opt->addr);
				}
				opt=opt->next;
				vlist=vlist->next;
			}
			fprintf(fp,"xor RCX, RCX\n");

			

				
			break;
			
			
			
			

			
case ID+100:
break;
			
			
		case declareStmtNode:
			;
			//printf("Inside \n");
			id_lis=itr->a.twoChildNode[0];
			while(id_lis)
			{
				id=lookup_varid(1000,id_lis->a.treeNode->name,SS);
				if(id->ut==0)
				{
					
					if(id->vartype.t.a==INTEGER)
					{
						//printf("Inside here\n");
						fprintf(fp,"mov BX, 0 \n");
						fprintf(fp,"mov [RBP - %d],BX \n",id->offset);
					}
					
					if(id->vartype.t.a==BOOLEAN)
					{
						fprintf(fp,"mov BL, 0 \n");
						fprintf(fp,"mov [RBP - %d],BL \n",id->offset);
					}
				}
				
				else
				{		AST *range=itr->a.twoChildNode[1];
						intCode(range->a.twoChildNode[0]->a.twoChildNode[0],fp);
						intCode(range->a.twoChildNode[0]->a.twoChildNode[1],fp);
						
							int range_type=id->vartype.a.range_kind;
							int chk=id->vartype.a.sub.a;
							fprintf(fp,"mov AX, [RBP - %d] \n",range->a.twoChildNode[0]->a.twoChildNode[0]->addr);
							fprintf(fp,"push AX\n");
							fprintf(fp,"mov [RBP - %d +2], AX \n",id->offset);
							fprintf(fp,"cmp AX, 0 \n");
							fprintf(fp,"JL exit3 \n");
	
							//printf("%d\n",range->a.twoChildNode[0]->a.twoChildNode[1]->addr);
				
							fprintf(fp,"mov DX, [RBP - %d] \n",range->a.twoChildNode[0]->a.twoChildNode[1]->addr);
							fprintf(fp,"push DX\n");
							fprintf(fp,"mov [RBP - %d +4], DX \n",id->offset);
							fprintf(fp,"cmp DX, 0 \n");
							fprintf(fp,"JL exit3 \n");
							fprintf(fp,"pop DX\n");
							fprintf(fp,"pop AX\n");
							
							printf("range type %d\n",range_type);
							if(range_type!=1){
								fprintf(fp,"cmp DX,AX \n");
								fprintf(fp,"JL exit2 \n");	
								fprintf(fp,"sub DX,AX \n");
								fprintf(fp,"add DX, 1 \n");
								//fprintf(fp,"mov AX, DX \n");	
								if(chk==BOOLEAN)
								{
									fprintf(fp,"pop RCX\n");
									fprintf(fp,"pop RCX\n");
									fprintf(fp,"ADD CX , DX \n");
									fprintf(fp,"mov [RBP - %d],CX\n",id->offset);
									fprintf(fp,"push RCX\n");
									fprintf(fp,"push RCX\n");
								
								}
								else if(chk==INTEGER)
								{
									fprintf(fp,"xor RAX, RAX\n");
									fprintf(fp,"ADD AX, 2 \n");
									fprintf(fp,"IMUL DX\n");
									fprintf(fp,"pop RCX\n");
									fprintf(fp,"pop RCX\n");
									fprintf(fp,"ADD CX , AX \n");
									fprintf(fp,"mov [RBP - %d],CX\n",id->offset);
									fprintf(fp,"push RCX\n");
									fprintf(fp,"push RCX\n");
								}
							}
							else{
								fprintf(fp,"xor AX,AX \n");
								fprintf(fp,"add AX,%d\n",id->offset);
								fprintf(fp,"sub AX, 6\n");
								fprintf(fp,"mov [RBP - %d], AX\n", id->offset);

							}
						
						
				}
				id_lis = id_lis->next;
						
			}
			
			break;
			
		
			
	}	
return;
	}

