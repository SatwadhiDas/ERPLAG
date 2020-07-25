/*AARYAN KAPOOR 2016B4A70166P
 SATWADHI DAS 2016B4A70622P
 ISHAN SANJAY JOGLEKAR 2016B3A70534P
 SATYANSH RAI 2016B4A70632P
 PARTH MISRA 2016B5A70560P*/
#include "typeChecker.h"

extern int typecheckingflag;

extern loopvar * loopVar;
extern whilevar * whileVar;
void freewhilevar(whilevar * whileVar){

    whilevar * temp = whileVar;

    whilevar * temp1 = whileVar;

    while(temp!=NULL){

        freeloopvar(temp->head);

        temp = temp->next;

        free(temp1);

        temp1=temp;

    }

    return;

}


void freeloopvar(loopvar * loopVar){

    loopvar * temp  = loopVar;

    loopvar * temp1  = loopVar;

    while(temp!=NULL){

        temp = temp->next;

        free(temp1);

        temp1=temp;

    }

    return;

}


loopvar * addToWhile(AST * Node, int lineNo){
	if(Node==NULL)
        return NULL;
	loopvar * temp;
	loopvar * LHS, * RHS;
    switch (Node->type){
		case expressionNode:
		case unaryExpressionNode:
		case unaryPlusNode:
		case unaryMinusNode:
			return addToWhile(Node->a.oneChildNode[0], lineNo);
        case multiplyNode:
        case divideNode:
        case minusNode:
        case plusNode:
            LHS = addToWhile(Node->a.twoChildNode[0], lineNo);
            RHS = addToWhile(Node->a.twoChildNode[1], lineNo);			
            if(LHS==NULL)
                return RHS;
            temp = LHS;
			while(temp->next!=NULL){
				temp=temp->next;	
			}    		
			temp->next=RHS;
			return LHS;
            break;
        
            
        case relationalOpNode:
            LHS = addToWhile(Node->a.threeChildNode[1], lineNo);
            RHS = addToWhile(Node->a.threeChildNode[2], lineNo);
            if(LHS==NULL)
                return RHS;
            temp = LHS;
			while(temp->next!=NULL){
				temp=temp->next;	
			}    		
			temp->next=RHS;
			return LHS;
            
        break;
        
        case logicalOpNode:					 
            LHS = addToWhile(Node->a.threeChildNode[1], lineNo);
            RHS = addToWhile(Node->a.threeChildNode[2], lineNo);

           	if(LHS==NULL)
                return 	RHS;
            temp = LHS;
			while(temp->next!=NULL){
				temp=temp->next;	
			}    		
			temp->next=RHS;
			return LHS;
    
            break;
        case INTEGER+100:
        case REAL+100:
        case BOOLEAN+100:
        case TRUET+100:
        case FALSET+100:
            return NULL;
            
        case parsetreeNode:
            switch(Node->a.treeNode->value-100){
                case ID:
					temp = (loopvar *)malloc(sizeof(loopvar));
                    strcpy(temp->str, Node->a.treeNode->name);
					temp->lno= lineNo;
					temp->next=NULL;
                	return temp;
				default:
					return NULL;
            }
			default:
					return NULL;	
    }

}
bool funcDeclared(func * funcLoc, AST * Nod){
    if(funcLoc == NULL){
        printf("Error in Line no: %d, Function: %s not defined\n",Nod->a.treeNode->lineNo,Nod->a.treeNode->name);
        typecheckingflag=1;
        return false;
    }
                 
    if(funcLoc->lno > Nod->a.treeNode->lineNo){
        printf("Error in Line no: %d, Function: %s not definded\n",Nod->a.treeNode->lineNo,Nod->a.treeNode->name);
         typecheckingflag=1;
         return false;
    }

    return true;
}
bool idDeclared (varid * idLoc, AST * Nod){
	//printf("%s %s ", Nod->a.treeNode->name, idLoc->name);
    if(idLoc==NULL){
        //printf("Error in Line no: %d, Variable : %s not declared",Nod->a.treeNode->lineNo,Nod->a.treeNode->name);
        //typecheckingflag=1;
        return false;
    }
    if(idLoc->lno>Nod->a.treeNode->lineNo){
       // printf("Error in Line no: %d, Variable : %s not declared",Nod->a.treeNode->lineNo,Nod->a.treeNode->name);
        //typecheckingflag=1;
        return false;
    }
    
    return true;
}
bool idTypeMatch1(varid * idLoc, var_l * temp, int lineNo){ //INCOMPLETE
    if(idLoc->ut != temp->t){
        printf("Error in Line no: %d, Type mismatch: %s\n",lineNo,idLoc->name);
        typecheckingflag=1;
        return false;
    }
    
    if(idLoc->ut==1){
        if(idLoc->vartype.a.sub.a != temp->typ.a.sub.a){
            printf("Error in Line no: %d, Type mismatch: %s\n",lineNo,idLoc->name);
            typecheckingflag=1;
            return false;
        }
        
        if(idLoc->vartype.a.range_kind==1 && temp->typ.a.range_kind==1)/*check*/{
            int start = idLoc->vartype.a.st.num;
            int end = idLoc->vartype.a.end.num;
            int start1 = temp->typ.a.st.num;
            int end1 = temp->typ.a.end.num;
            if(start!=start1 || end!=end1){
                printf("Error in Line no: %d, Array size mismatch: %s\n",lineNo,idLoc->name);
                typecheckingflag=1;
                return false;
            }
        }
    }
    else{
        if(idLoc->vartype.t.a != temp->typ.t.a){
            printf("Error in Line no: %d, Type mismatch: %s\n",lineNo,idLoc->name);
            typecheckingflag=1;
            return false;
        }
    }
    return true;
}



bool idTypeMatch(varid * idLoc, varid * temp, int lineNo){ //INCOMPLETE
     if(idLoc->ut != temp->ut){
          printf("Error in Line no: %d, Type mismatch: %s\n",lineNo,idLoc->name);
          typecheckingflag=1;
          return false;
      }
      
      if(idLoc->ut==1){
          if(idLoc->vartype.a.sub.a != temp->vartype.a.sub.a){
              printf("Error in Line no: %d, Type mismatch: %s\n",lineNo,idLoc->name);
              typecheckingflag=1;
              return false;
          }
          
          if(idLoc->vartype.a.range_kind==1 && temp->vartype.a.range_kind==1)/*check*/{
              int start = idLoc->vartype.a.st.num;
              int end = idLoc->vartype.a.end.num;
              int start1 = temp->vartype.a.st.num;
              int end1 = temp->vartype.a.end.num;
              if(start!=start1 || end!=end1){
                  printf("Error in Line no: %d, Array size mismatch: %s\n",lineNo,idLoc->name);
                  typecheckingflag=1;
                  return false;
              }
          }
      }
      else{
          if(idLoc->vartype.t.a != temp->vartype.t.a){
              printf("Error in Line no: %d, Type mismatch: %s\n",lineNo,idLoc->name);
              typecheckingflag=1;
              return false;
          }
      }
      return true;
}


bool idTypeMatch2(var_l * idLoc, var_l * temp, int lineNo){ //INCOMPLETE
     if(idLoc->t != temp->t){
          printf("Error in Line no: %d, Type mismatch: %s\n",lineNo,temp->name);
          typecheckingflag=1;
          return false;
      }
      
      if(idLoc->t==1){
          if(idLoc->typ.a.sub.a != temp->typ.a.sub.a){
              printf("Error in Line no: %d, Type mismatch: %s\n",lineNo,temp->name);
              typecheckingflag=1;
              return false;
          }
          
          if(idLoc->typ.a.range_kind==1 && temp->typ.a.range_kind==1)/*check*/{
              int start = idLoc->typ.a.st.num;
              int end = idLoc->typ.a.end.num;
              int start1 = temp->typ.a.st.num;
              int end1 = temp->typ.a.end.num;
              if(start!=start1 || end!=end1){
                  printf("Error in Line no: %d, Array size mismatch: %s\n",lineNo,temp->name);
                  typecheckingflag=1;
                  return false;
              }
          }
      }
      else{
          if(idLoc->typ.t.a != temp->typ.t.a){
              printf("Error in Line no: %d, Type mismatch: %s\n",lineNo,temp->name);
              typecheckingflag=1;
              return false;
          }
      }
      return true;
}


bool arrayInBound(varid * idLoc, AST * Nod, func * presentModule, varTabTree * symbolTable){
	if(Nod->type!= parsetreeNode){
		if(Nod->type==lvalueArrStmtNode){
			if(idLoc->vartype.a.range_kind == 1 &&  Nod->a.twoChildNode[0]->a.treeNode->value-100 == NUM){
			 	int start = idLoc->vartype.a.st.num;
				int end = idLoc->vartype.a.end.num;
				int check = atoi(Nod->a.twoChildNode[0]->a.treeNode->name); //stoi working
				if(check<=end && check>=start)
				    return true;
				else{
				    printf("Error in Line no: %d, Array out of bound: %s\n",Nod->a.twoChildNode[0]->a.treeNode->lineNo, idLoc->name);
				    typecheckingflag=1;
				    return false;
				}
			}
			else if(Nod->a.twoChildNode[0]->a.treeNode->value-100 == ID){
				varid * idLoc = lookup_varid(Nod->a.twoChildNode[0]->a.treeNode->lineNo, Nod->a.twoChildNode[0]->a.treeNode->name, symbolTable);
				if(!idDeclared(idLoc, Nod->a.twoChildNode[0])){
						var_l * iLoc = lookup_varid1(Nod->a.twoChildNode[0]->a.treeNode->name, presentModule->input_list);
						if(iLoc==NULL){
							var_l * oLoc = lookup_varid1(Nod->a.twoChildNode[0]->a.treeNode->name, presentModule->output_list);
							if(oLoc == NULL){
								printf("Error in Line no: %d, Array index: %s not declared\n", Nod->a.twoChildNode[0]->a.treeNode->lineNo,Nod->a.twoChildNode[0]->a.treeNode->name);
								typecheckingflag=1;
								return true;
							}
							else if(oLoc->flag == 0){
								printf("Error in Line no: %d, Array index: %s not assigned value\n", Nod->a.twoChildNode[0]->a.treeNode->lineNo,Nod->a.twoChildNode[0]->a.treeNode->name);
								typecheckingflag=1;
							}
							if(oLoc->typ.a.sub.a!=INTEGER){
								printf("Error in Line no: %d, Array index: %s is not integer\n", Nod->a.twoChildNode[0]->a.treeNode->lineNo,Nod->a.twoChildNode[0]->a.treeNode->name);
								typecheckingflag=1;
							}
							
						}
						else if(iLoc->typ.a.sub.a!=INTEGER){
								printf("Error in Line no: %d, Array index: %s is not integer\n", Nod->a.twoChildNode[0]->a.treeNode->lineNo,Nod->a.twoChildNode[0]->a.treeNode->name);
								typecheckingflag=1;
						}

				}
				else if(idLoc->vartype.a.sub.a!=INTEGER){
					printf("Error in Line no: %d, Array index: %s is not integer\n", Nod->a.twoChildNode[0]->a.treeNode->lineNo,Nod->a.twoChildNode[0]->a.treeNode->name);
					typecheckingflag=1;
				}
			}
			return true;
		}	
		return false;
	}
    if(idLoc->vartype.a.range_kind == 1 &&  Nod->next->a.treeNode->value-100 == NUM){
        int start = idLoc->vartype.a.st.num;
        int end = idLoc->vartype.a.end.num;
        int check = atoi(Nod->next->a.treeNode->name); //stoi working
        if(check<=end && check>=start)
            return true;
        else{
            printf("Error in Line no: %d, Array out of bound: %s\n",Nod->a.treeNode->lineNo, idLoc->name);
            typecheckingflag=1;
            return false;
        }
    }
	else if(Nod->next->a.treeNode->value-100 == ID){
				varid * idLoc = lookup_varid(Nod->next->a.treeNode->lineNo,Nod->next->a.treeNode->name, symbolTable);
                	if(!idDeclared(idLoc, Nod->next)){
						var_l * iLoc = lookup_varid1(Nod->next->a.treeNode->name, presentModule->input_list);
						if(iLoc==NULL){
							var_l * oLoc = lookup_varid1(Nod->next->a.treeNode->name, presentModule->output_list);
							if(oLoc == NULL){
								printf("Error in Line no: %d, Array index: %s not declared\n", Nod->next->a.treeNode->lineNo,Nod->next->a.treeNode->name);
								typecheckingflag=1;
								return true;
							}
							else if(oLoc->flag == 0){
								printf("Error in Line no: %d, Array index: %s not assigned value\n", Nod->next->a.treeNode->lineNo,Nod->next->a.treeNode->name);
								typecheckingflag=1;
							}
							if(oLoc->typ.a.sub.a!=INTEGER){
								printf("Error in Line no: %d, Array index: %s is not integer\n", Nod->next->a.treeNode->lineNo,Nod->next->a.treeNode->name);
								typecheckingflag=1;
							}	
						}
						else if(iLoc->typ.a.sub.a!=INTEGER){
								printf("Error in Line no: %d, Array index: %s is not integer\n", Nod->next->a.treeNode->lineNo,Nod->next->a.treeNode->name);
								typecheckingflag=1;
						}

				}
				else if(idLoc->vartype.a.sub.a!=INTEGER){
								printf("Error in Line no: %d, Array index: %s is not integer\n", Nod->next->a.treeNode->lineNo,Nod->next->a.treeNode->name);
								typecheckingflag=1;
				}
	}
    return true;
}

bool arrayInBound1(var_l * idLoc, AST * Nod, func * presentModule, varTabTree * symbolTable){
	
	if(Nod->type!= parsetreeNode){
		if(Nod->type==lvalueArrStmtNode){
			if(idLoc->typ.a.range_kind == 1 &&  Nod->a.twoChildNode[0]->a.treeNode->value-100 == NUM){
			 	int start = idLoc->typ.a.st.num;
				int end = idLoc->typ.a.end.num;
				int check = atoi(Nod->a.twoChildNode[0]->a.treeNode->name); //stoi working
				if(check<=end && check>=start)
				    return true;
				else{
				    printf("Error in Line no: %d, Array out of bound: %s\n",Nod->a.twoChildNode[0]->a.treeNode->lineNo, idLoc->name);
				    typecheckingflag=1;
				    return false;
				}
			}
			else if(Nod->a.twoChildNode[0]->a.treeNode->value-100 == ID){
				varid * idLoc = lookup_varid(Nod->a.twoChildNode[0]->a.treeNode->lineNo,Nod->a.twoChildNode[0]->a.treeNode->name, symbolTable);
					if(!idDeclared(idLoc, Nod->a.twoChildNode[0])){
						var_l * iLoc = lookup_varid1(Nod->a.twoChildNode[0]->a.treeNode->name, presentModule->input_list);
						if(iLoc==NULL){
							var_l * oLoc = lookup_varid1(Nod->a.twoChildNode[0]->a.treeNode->name, presentModule->output_list);
							if(oLoc == NULL){
								printf("Error in Line no: %d, Array index: %s not declared\n", Nod->a.twoChildNode[0]->a.treeNode->lineNo,Nod->a.twoChildNode[0]->a.treeNode->name);
								typecheckingflag=1;
								return true;
							}
							else if(oLoc->flag == 0){
								printf("Error in Line no: %d, Array index: %s not assigned value\n", Nod->a.twoChildNode[0]->a.treeNode->lineNo,Nod->a.twoChildNode[0]->a.treeNode->name);
								typecheckingflag=1;
							}
							if(oLoc->typ.a.sub.a!=INTEGER){
								printf("Error in Line no: %d, Array index: %s is not integer\n", Nod->a.twoChildNode[0]->a.treeNode->lineNo,Nod->a.twoChildNode[0]->a.treeNode->name);
								typecheckingflag=1;
							}
							
						}
						else if(iLoc->typ.a.sub.a!=INTEGER){
								printf("Error in Line no: %d, Array index: %s is not integer\n", Nod->a.twoChildNode[0]->a.treeNode->lineNo,Nod->a.twoChildNode[0]->a.treeNode->name);
								typecheckingflag=1;
						}

				}
				else if(idLoc->vartype.a.sub.a!=INTEGER){
								printf("Error in Line no: %d, Array index: %s is not integer\n", Nod->a.twoChildNode[0]->a.treeNode->lineNo,Nod->a.twoChildNode[0]->a.treeNode->name);
								typecheckingflag=1;
				}
			}
			return true;
		}	
		return false;
	}
    if(idLoc->typ.a.range_kind == 1 &&  Nod->next->a.treeNode->value-100 == NUM){
        int start = idLoc->typ.a.st.num;
        int end = idLoc->typ.a.end.num;
        int check = atoi(Nod->next->a.treeNode->name); //stoi working
        if(check<=end && check>=start)
            return true;
        else{
            printf("Error in Line no: %d, Array out of bound: %s\n",Nod->a.treeNode->lineNo, idLoc->name);
            typecheckingflag=1;
            return false;
        }
    }
	else if(Nod->next->a.treeNode->value-100 == ID){
				varid * idLoc = lookup_varid(Nod->next->a.treeNode->lineNo, Nod->next->a.treeNode->name, symbolTable);
                	if(!idDeclared(idLoc, Nod->next)){
						var_l * iLoc = lookup_varid1(Nod->next->a.treeNode->name, presentModule->input_list);
						if(iLoc==NULL){
							var_l * oLoc = lookup_varid1(Nod->next->a.treeNode->name, presentModule->output_list);
							if(oLoc == NULL){
								printf("Error in Line no: %d, Array index: %s not declared\n", Nod->next->a.treeNode->lineNo,Nod->next->a.treeNode->name);
								typecheckingflag=1;
								return true;
							}
							else if(oLoc->flag == 0){
								printf("Error in Line no: %d, Array index: %s not assigned value\n", Nod->next->a.treeNode->lineNo,Nod->next->a.treeNode->name);
								typecheckingflag=1;
							}
							if(oLoc->typ.a.sub.a!=INTEGER){
								printf("Error in Line no: %d, Array index: %s is not integer\n", Nod->next->a.treeNode->lineNo,Nod->next->a.treeNode->name);
								typecheckingflag=1;
							}
							
						}
						else if(iLoc->typ.a.sub.a!=INTEGER){
								printf("Error in Line no: %d, Array index: %s is not integer\n", Nod->next->a.treeNode->lineNo,Nod->next->a.treeNode->name);
								typecheckingflag=1;
						}

				}
				else if(idLoc->vartype.a.sub.a!=INTEGER){
								printf("Error in Line no: %d, Array index: %s is not integer\n", Nod->next->a.treeNode->lineNo,Nod->next->a.treeNode->name);
								typecheckingflag=1;
				}
	}
    return true;
}



int expressionTypeChecker(AST * Node, varTabTree * symbolTable, int lineNo, func * presentModule){
    int LHS, RHS;
    if(Node==NULL)
        return -1;
	//printf("id : %d\n", Node->type);
    switch (Node->type){
		case expressionNode:
		case unaryExpressionNode:
		case unaryPlusNode:
		case unaryMinusNode:
			return expressionTypeChecker(Node->a.oneChildNode[0], symbolTable, lineNo, presentModule);
        case multiplyNode:
        case divideNode:
        case minusNode:
        case plusNode:
            LHS = expressionTypeChecker(Node->a.twoChildNode[0], symbolTable, lineNo, presentModule);
            RHS = expressionTypeChecker(Node->a.twoChildNode[1], symbolTable, lineNo, presentModule);
            if(LHS==-1||RHS==-1)
                return -1;
            if(LHS == RHS){
                if(LHS==REAL || LHS==INTEGER){return LHS;}
                else{
                    printf("Error in Line no: %d, Arithmetic Operator can only take real or integer values\n",lineNo);
                    typecheckingflag=1;
                    return -1;
                }
            }
            else{
                printf("Error in Line no: %d, datatype mismatch for Arithmetic Operator\n",lineNo);
                typecheckingflag=1;
                return -1;
            }
    
            break;
        
            
        case relationalOpNode:
            LHS = expressionTypeChecker(Node->a.threeChildNode[1], symbolTable, lineNo, presentModule);
            RHS = expressionTypeChecker(Node->a.threeChildNode[2], symbolTable, lineNo, presentModule);
            if(LHS==-1||RHS==-1)
                return -1;
            if(LHS == RHS){
                if(LHS==REAL || LHS==INTEGER){return BOOLEAN;}
                else{
                    printf("Error in Line no: %d, Relational Operator can only take real or integer values\n",lineNo);
                    typecheckingflag=1;
                    return -1;
                }
            }
                else{
                    printf("Error in Line no: %d, datatype mismatch for Relational Operator\n",lineNo);
                    typecheckingflag=1;
                    return -1;
                }
            
        break;
        
        case logicalOpNode:
            LHS = expressionTypeChecker(Node->a.threeChildNode[1], symbolTable, lineNo, presentModule);
            RHS = expressionTypeChecker(Node->a.threeChildNode[2], symbolTable, lineNo, presentModule);
            if(LHS==-1||RHS==-1)
                return -1;
            if(LHS!=RHS){
                printf("Error in Line no: %d, datatype mismatch for Logical Operator\n",lineNo);
                typecheckingflag=1;
                return -1;
            }
            if(LHS==BOOLEAN){return BOOLEAN;}
            else{
                printf("Error in Line no: %d, Logical Operator can only take boolean values\n",lineNo);
                typecheckingflag=1;
                return -1;
            }
    
            break;
	/*	case NUM+100:
			return INTEGER;
		case RNUM+100:
			return REAL;   */ 
        case INTEGER+100:
        case REAL+100:
        case BOOLEAN+100:
            return Node->type;
        case TRUET+100:
        case FALSET+100:
            return BOOLEAN;
            
        case parsetreeNode:
            switch(Node->a.treeNode->value-100){
                case ID:
                    ;

					varid * idLoc = lookup_varid(Node->a.treeNode->lineNo, Node->a.treeNode->name, symbolTable);					
					if(!idDeclared(idLoc, Node)){
						var_l * iLoc = lookup_varid1(Node->a.treeNode->name, presentModule->input_list);
						if(iLoc==NULL){					
							var_l * oLoc = lookup_varid1(Node->a.treeNode->name, presentModule->output_list);
							if(oLoc == NULL){//printf("her\n");
								//printf("%d\n",idLoc->lno);
								printf("Error in Line no: %d, Variable: %s not declared\n", Node->a.treeNode->lineNo,Node->a.treeNode->name);
								typecheckingflag=1;
								return -1;
							}
							else if(oLoc->flag == 0){
								printf("Error in Line no: %d, Variable: %s not assigned value\n", Node->a.treeNode->lineNo,Node->a.treeNode->name);
								typecheckingflag=1;
							}
							return oLoc->typ.t.a;
						}
						if(iLoc->t ==1){
							if(Node->next==NULL){
								printf("Error in Line no: %d, can't have entire array in expression\n",Node->a.treeNode->lineNo);
								typecheckingflag=1;
								return -1;
							}
							if(!arrayInBound1(iLoc,Node,presentModule,symbolTable)){
								//return -1;
							}
							return iLoc->typ.a.sub.a;
						 
						}
						return iLoc->typ.t.a;
					}

                    	//printf("ut:%d %s\n", idLoc->ut, idLoc->name);
					if(idLoc->ut==0)
						return idLoc->vartype.t.a;
					else{
						if(Node->next==NULL){
							printf("Error in Line no: %d, can't have entire array in expression\n",Node->a.treeNode->lineNo);
							typecheckingflag=1;
							return -1;
						}
			//	printf("%s\n",Node->next->a.treeNode->name);
						if(!arrayInBound(idLoc,Node,presentModule,symbolTable)){
							//return -1;
						}
                       // printf("hereinfi\n");
						return idLoc->vartype.a.sub.a;
                     }
                case NUM:
                    return INTEGER;
                case RNUM:
                    return REAL;
                case TRUET:
                case FALSET:
                    return BOOLEAN;
				default:
					return -1;
            }
			default:
					return -1;	
    }
}


int typeChecker(AST * Node, varTabTree * symbolTable, int childNo, func * presentModule){
    //printf("Here\n");
        if(forflag==0){
            loopVar = (loopvar *)malloc(sizeof(loopvar));
			loopVar->lno=0;
            strcpy(loopVar->str,"rhkbcdqwlcknfb3hijcn");
            loopVar->next = NULL;
			/*loopVar1 = (loopvar1 *)malloc(sizeof(loopvar1));
            strcpy(loopVar1->str,"rhkbcdqwlcknfb3hijcn");
			loopVar1->lno=0;
            loopVar1->next = NULL;*/
			whileVar = (whilevar *)malloc(sizeof(whilevar));
			whileVar->flag = 1;
			whileVar->lno=0;
			whileVar->head = NULL;
			whileVar->next = NULL;
			forflag=1;
        }
    
        varid * idLoc;
        func * funcLoc;
		var_l * iLoc;
		var_l * oLoc;
		int ret;
        if(Node==NULL) {
            //printf("NULL\n");
            return childNo;
        }
    	//printf("called for: %s ", Node->a.treeNode->name);
        switch(Node->type){
                
        case programNode:
                ;
            ret = typeChecker(Node->a.fourChildNode[1],symbolTable,childNo,presentModule);
                
            funcLoc = lookupFunc("DriverModule");
                
                if(funcLoc == NULL){printf("Driver module not found\n");exit(0);}
                
            ret = typeChecker(Node->a.fourChildNode[2],funcLoc->loc,childNo,funcLoc);
            ret = typeChecker(Node->a.fourChildNode[3],symbolTable,childNo,presentModule);
            return childNo;
            break;
                
        case driverModuleNode:
                ;
                AST * itr = Node->a.oneChildNode[0];
                while(itr->next!=NULL){
                    childNo = typeChecker(itr,symbolTable,childNo,presentModule);
                    itr = itr->next;
                }
                return childNo;
                break;
        
                
        case moduleNode:
             funcLoc = lookupFunc(Node->a.fourChildNode[0]->a.treeNode->name);
             AST * itr1 = Node->a.fourChildNode[3];
            while(itr1->next!=NULL){
                 childNo = typeChecker(itr1,funcLoc->loc,childNo,funcLoc);
                 itr1 = itr1->next;
            }
			var_l * temp1=funcLoc->input_list.head; 
				while(temp1!=NULL){
                    if(temp1->t==1 && temp1->typ.a.range_kind==1){
							int start  = temp1->typ.a.st.num;
							int end  = temp1->typ.a.end.num;
							if(start>end){
                            printf("Error in line no: %d, array definition is not correct- Start index should be less than end index in input list of: %s\n",Node->a.fourChildNode[0]->a.treeNode->lineNo, Node->a.fourChildNode[0]->a.treeNode->name);
                            typecheckingflag=1;
                    }
                        
					}
					temp1=temp1->next;
				}
			
			
				temp1 = funcLoc->output_list.head;
                while(temp1!=NULL){
                   if(temp1->flag!=1){
                       printf("Error in Line No: %d, all output variables not assigned value for Function: %s\n", Node->a.fourChildNode[0]->a.treeNode->lineNo, Node->a.fourChildNode[0]->a.treeNode->name);
                       break;
                    }
					temp1 = temp1->next;
				}
                if(Node->next!=NULL){
                    funcLoc = lookupFunc(Node->next->a.fourChildNode[0]->a.treeNode->name);
                    ret = typeChecker(Node->next,funcLoc->loc,0,funcLoc);
                }
           
            return childNo;
            break;
                
        case array_datatypeNode:
            
                if(Node->a.twoChildNode[0]->a.twoChildNode[0]->a.treeNode->value -100 == ID){
                    idLoc = lookup_varid(Node->a.twoChildNode[0]->a.twoChildNode[0]->a.treeNode->lineNo, Node->a.twoChildNode[0]->a.twoChildNode[0]->a.treeNode->name,symbolTable);
                    if(idDeclared(idLoc,Node->a.twoChildNode[0]->a.twoChildNode[0])){
                        if(idLoc->ut==1){
                            printf("Error in line no: %d, can't have array as range index\n",Node->a.twoChildNode[0]->a.twoChildNode[0]->a.treeNode->lineNo);
                            typecheckingflag=1;
                        }
                        else{
                            if(idLoc->vartype.t.a!=INTEGER){
                                printf("Error in line no: %d, must have integer as range index\n",Node->a.twoChildNode[0]->a.twoChildNode[0]->a.treeNode->lineNo);
                                typecheckingflag=1;
                            }
                        }
						//return childNo;
					}
					else{
						iLoc = lookup_varid1(Node->a.twoChildNode[0]->a.twoChildNode[0]->a.treeNode->name, presentModule->input_list);
						if(iLoc==NULL){
							oLoc = lookup_varid1(Node->a.twoChildNode[0]->a.twoChildNode[0]->a.treeNode->name, presentModule->output_list);
							if(oLoc == NULL){
								printf("Error in Line no: %d, Variable: %s not declared\n", Node->a.twoChildNode[0]->a.twoChildNode[1]->a.treeNode->lineNo,Node->a.twoChildNode[0]->a.twoChildNode[0]->a.treeNode->name);
								typecheckingflag=1;
							}
							else if(oLoc->flag == 0){
								printf("Error in Line no: %d, Variable: %s not assigned value\n", Node->a.twoChildNode[0]->a.twoChildNode[1]->a.treeNode->lineNo,Node->a.twoChildNode[0]->a.twoChildNode[0]->a.treeNode->name);
								typecheckingflag=1;
							}
							else{
								if(oLoc->t==1){
									printf("Error in line no: %d, can't have array as range index\n",Node->a.twoChildNode[0]->a.twoChildNode[0]->a.treeNode->lineNo);
									typecheckingflag=1;
								}
								else{
									if(oLoc->typ.t.a!=INTEGER){
										printf("Error in line no: %d, must have integer as range index\n",Node->a.twoChildNode[0]->a.twoChildNode[0]->a.treeNode->lineNo);
										typecheckingflag=1;
									}
								}
								
							}
							
						}
						else{
							if(iLoc->t==1){
									printf("Error in line no: %d, can't have array as range index\n",Node->a.twoChildNode[0]->a.twoChildNode[0]->a.treeNode->lineNo);
									typecheckingflag=1;
								}
							else{
									if(iLoc->typ.t.a!=INTEGER){
									printf("Error in line no: %d, must have integer as range index\n",Node->a.twoChildNode[0]->a.twoChildNode[0]->a.treeNode->lineNo);
									typecheckingflag=1;
								}
							}
						}
					}
				}
				
				if(Node->a.twoChildNode[0]->a.twoChildNode[1]->a.treeNode->value -100 == ID){
                        idLoc = lookup_varid(Node->a.twoChildNode[0]->a.twoChildNode[1]->a.treeNode->lineNo, Node->a.twoChildNode[0]->a.twoChildNode[1]->a.treeNode->name,symbolTable);
                        if(idDeclared(idLoc,Node->a.twoChildNode[0]->a.twoChildNode[1])){
                            if(idLoc->ut==1){
                                printf("Error in line no: %d, can't have array as range index\n",Node->a.twoChildNode[0]->a.twoChildNode[1]->a.treeNode->lineNo);
                                typecheckingflag=1;
                            }
                            else{
                                if(idLoc->vartype.t.a!=INTEGER){
                                    printf("Error in line no: %d, must have integer as range index\n",Node->a.twoChildNode[0]->a.twoChildNode[1]->a.treeNode->lineNo);
                                    typecheckingflag=1;
                                }

                            }
						}
						else{
							iLoc = lookup_varid1(Node->a.twoChildNode[0]->a.twoChildNode[1]->a.treeNode->name, presentModule->input_list);
							if(iLoc==NULL){
								oLoc = lookup_varid1(Node->a.twoChildNode[0]->a.twoChildNode[1]->a.treeNode->name, presentModule->output_list);
								if(oLoc == NULL){
									printf("Error in Line no: %d, Variable: %s not declared\n",Node->a.twoChildNode[0]->a.twoChildNode[1]->a.treeNode->lineNo,Node->a.twoChildNode[0]->a.twoChildNode[1]->a.treeNode->name);
									typecheckingflag=1;
								}
								else if(oLoc->flag == 0){
									printf("Error in Line no: %d, Variable: %s not assigned value\n", Node->a.twoChildNode[0]->a.twoChildNode[1]->a.treeNode->lineNo,Node->a.twoChildNode[0]->a.twoChildNode[1]->a.treeNode->name);
									typecheckingflag=1;
								}
								else{
									if(oLoc->t==1){
										printf("Error in line no: %d, can't have array as range index\n",Node->a.twoChildNode[0]->a.twoChildNode[1]->a.treeNode->lineNo);
										typecheckingflag=1;
									}
									else{
										if(oLoc->typ.t.a!=INTEGER){
											printf("Error in line no: %d, must have integer as range index\n",Node->a.twoChildNode[0]->a.twoChildNode[1]->a.treeNode->lineNo);
											typecheckingflag=1;
										}
									}
									
								}
								
							}
							else{
								if(iLoc->t==1){
										printf("Error in line no: %d, can't have array as range index\n",Node->a.twoChildNode[0]->a.twoChildNode[0]->a.treeNode->lineNo);
										typecheckingflag=1;
									}
								else{
										if(iLoc->typ.t.a!=INTEGER){
										printf("Error in line no: %d, must have integer as range index\n",Node->a.twoChildNode[0]->a.twoChildNode[0]->a.treeNode->lineNo);
										typecheckingflag=1;
									}
								}
							}
						}
                    }
                
                else if(Node->a.twoChildNode[0]->a.twoChildNode[0]->a.treeNode->value -100 == NUM && Node->a.twoChildNode[0]->a.twoChildNode[0]->a.treeNode->value -100 == NUM){
                    int start  = atoi(Node->a.twoChildNode[0]->a.twoChildNode[0]->a.treeNode->name);
                    int end  = atoi(Node->a.twoChildNode[0]->a.twoChildNode[1]->a.treeNode->name);
                    if(start>end){
                            printf("Error in line no: %d, array definition is not correct- Start index should be less than end index\n",Node->a.twoChildNode[0]->a.twoChildNode[0]->a.treeNode->lineNo);
                            typecheckingflag=1;
                    }

                }
                        return childNo;
                        break;


                
                
        case getValueNode: //to update for i
                ;
                loopvar * x = loopVar;
                while(x!=NULL){
                    if(strcmp(x->str,Node->a.oneChildNode[0]->a.treeNode->name)==0){
						/*loopvar1 * y = loopVar1;
							while(y!=NULL){
								if(strcmp(y->str,x->str)==0 && y->lno>=x->lno) break;
								y=y->next;										
							}
							if(y==NULL){
								printf("Error in Line no: %d, for iterator variable cannot be assigned a value\n",Node->a.oneChildNode[0]->a.treeNode->lineNo);
								typecheckingflag=1;
								return childNo;
							}
							break;*/
						varid * a = lookup_varid(Node->a.oneChildNode[0]->a.treeNode->lineNo, Node->a.oneChildNode[0]->a.treeNode->name, symbolTable);
						if(a==NULL){
							printf("Error in Line no: %d, for iterator variable cannot be assigned a value\n",Node->a.oneChildNode[0]->a.treeNode->lineNo);		
							typecheckingflag=1;
							//break;
							return childNo;
						}
						else if(a->lno<=x->lno){
							printf("Error in Line no: %d, for iterator variable cannot be assigned a value\n",Node->a.oneChildNode[0]->a.treeNode->lineNo);		
							typecheckingflag=1;
							//break;
							return childNo;
						}
						break;
                    }
                    x=x->next;
                }
				whilevar * w3 = whileVar->next;
				while(w3){
					if(w3->flag==0){
						loopvar * x1= w3->head;
						while(x1){
							if(strcmp(x1->str,Node->a.twoChildNode[0]->a.treeNode->name)==0){
								varid * a = lookup_varid(Node->a.twoChildNode[0]->a.treeNode->lineNo, Node->a.twoChildNode[0]->a.treeNode->name, symbolTable);
								if(a==NULL){
									w3->flag=1;
								}
								else if(a->lno<w3->lno){
									w3->flag=1;
								}
								break;
							}
							x1=x1->next;
						}
					}
					w3=w3->next;
				}
                idLoc = lookup_varid(Node->a.oneChildNode[0]->a.treeNode->lineNo, Node->a.oneChildNode[0]->a.treeNode->name, symbolTable);
                if(!idDeclared(idLoc,Node->a.oneChildNode[0])){
                    oLoc = lookup_varid1(Node->a.oneChildNode[0]->a.treeNode->name, presentModule->output_list);
                    if(oLoc!=NULL){
                        oLoc->flag = 1;
                    }
                    else{
                        iLoc = lookup_varid1(Node->a.oneChildNode[0]->a.treeNode->name, presentModule->input_list);
							if(iLoc==NULL){
								printf("Error in Line no: %d, Variable: %s not declared\n",Node->a.oneChildNode[0]->a.treeNode->lineNo,Node->a.oneChildNode[0]->a.treeNode->name );
								typecheckingflag=1;
							}
					}
                }
                return childNo;
                break;
                
                
        case printNode:
                if(Node->a.oneChildNode[0]->a.treeNode->value-100 == NUM || Node->a.oneChildNode[0]->a.treeNode->value-100 == RNUM || Node->a.oneChildNode[0]->a.treeNode->value-100 == TRUET || Node->a.oneChildNode[0]->a.treeNode->value-100 == FALSET)
                    return childNo;
        
                idLoc = lookup_varid(Node->a.oneChildNode[0]->a.treeNode->lineNo, Node->a.oneChildNode[0]->a.treeNode->name, symbolTable);
                if(!idDeclared(idLoc,Node->a.oneChildNode[0])){
                    iLoc = lookup_varid1(Node->a.oneChildNode[0]->a.treeNode->name, presentModule->input_list);
                    if(iLoc==NULL){
						oLoc = lookup_varid1(Node->a.oneChildNode[0]->a.treeNode->name, presentModule->output_list);
						if(oLoc == NULL){
							printf("Error in Line no: %d, Variable: %s not declared\n", Node->a.oneChildNode[0]->a.treeNode->lineNo,Node->a.oneChildNode[0]->a.treeNode->name);
							typecheckingflag=1;
						}
						else if(oLoc->flag == 0){
							printf("Error in Line no: %d, Variable: %s not assigned value\n", Node->a.oneChildNode[0]->a.treeNode->lineNo, Node->a.oneChildNode[0]->a.treeNode->name);
							typecheckingflag=1;
						} 
                    }
                    else{
                        if(iLoc->t==1){
                            if(Node->a.oneChildNode[0]->next!=NULL){
                                if(!arrayInBound1(iLoc,Node->a.oneChildNode[0],presentModule,symbolTable)){
                                    return childNo;
								}
                            }
                        }
                    }
                }
                else{             
                    if(idLoc->ut == 1){
                        if(Node->a.oneChildNode[0]->next!=NULL){
                            if(!arrayInBound(idLoc,Node->a.oneChildNode[0],presentModule,symbolTable))
                                return childNo;
                        }
                    }
                }
                return childNo;
                break;
                
        case assignStmtNode:  //to update for i
                ;
                loopvar * x1 = loopVar;
                while(x1!=NULL){
                    if(strcmp(x1->str,Node->a.twoChildNode[0]->a.treeNode->name)==0){
						/*loopvar1 * y = loopVar1;
							while(y!=NULL){
								if(strcmp(y->str,x1->str)==0 && y->lno>=x1->lno) break;
								y=y->next;										
							}
							if(y==NULL){
								printf("Error in Line no: %d, for iterator variable cannot be assigned a value\n",Node->a.twoChildNode[0]->a.treeNode->lineNo);
								typecheckingflag=1;
								return childNo;t
							}
							break;*/
						varid * a = lookup_varid(Node->a.twoChildNode[0]->a.treeNode->lineNo, Node->a.twoChildNode[0]->a.treeNode->name, symbolTable);
						if(a==NULL){
							printf("Error in Line no: %d, for iterator variable cannot be assigned a value\n",Node->a.twoChildNode[0]->a.treeNode->lineNo);		
							typecheckingflag=1;
							//break;
						}
						else if(a->lno<=x1->lno){
							printf("Error in Line no: %d, for iterator variable cannot be assigned a value\n",Node->a.twoChildNode[0]->a.treeNode->lineNo);		
							typecheckingflag=1;
							//break;
						}
						break;
                    }
                    x1=x1->next;
                }

				whilevar * w2 = whileVar->next;
				while(w2){
					if(w2->flag==0){
						loopvar * x1= w2->head;
						while(x1){
							if(strcmp(x1->str,Node->a.twoChildNode[0]->a.treeNode->name)==0){
								varid * a = lookup_varid(Node->a.twoChildNode[0]->a.treeNode->lineNo, Node->a.twoChildNode[0]->a.treeNode->name, symbolTable);
								if(a==NULL){
									w2->flag=1;
								}
								else if(a->lno<w2->lno){
									w2->flag=1;
								}
								break;
							}
							x1=x1->next;
						}
					}
					w2=w2->next;
				}
                   idLoc = lookup_varid(Node->a.twoChildNode[0]->a.treeNode->lineNo, Node->a.twoChildNode[0]->a.treeNode->name, symbolTable);
                   if(!idDeclared(idLoc,Node->a.twoChildNode[0])){
                       oLoc = lookup_varid1(Node->a.oneChildNode[0]->a.treeNode->name, presentModule->output_list);
                       if(oLoc!=NULL){

							int rhs=expressionTypeChecker(Node->a.twoChildNode[1],symbolTable, Node->a.twoChildNode[0]->a.treeNode->lineNo,presentModule);
                           oLoc->flag = 1;
                            if(rhs==-1) return childNo;
                            if(rhs!= oLoc->typ.t.a){
								printf("Error in Line no: %d, assigned value doesn't match type\n",Node->a.twoChildNode[0]->a.treeNode->lineNo);
								typecheckingflag=1;
								return childNo;
								}
                
                       }
						else{
							iLoc = lookup_varid1(Node->a.twoChildNode[0]->a.treeNode->name, presentModule->input_list);
							if(iLoc==NULL){
								printf("Error in Line no: %d, Variable: %s not declared\n",Node->a.twoChildNode[0]->a.treeNode->lineNo,Node->a.twoChildNode[0]->a.treeNode->name );
								typecheckingflag=1;
							}
							else{
								if(iLoc->t==1){
									if(Node->a.twoChildNode[1]->type == lvalueArrStmtNode){
										if(!arrayInBound1(iLoc,Node->a.twoChildNode[1],presentModule,symbolTable))
											return childNo;
										int rhs=expressionTypeChecker(Node->a.twoChildNode[1]->a.twoChildNode[1],symbolTable, Node->a.twoChildNode[0]->a.treeNode->lineNo, presentModule);
										if(rhs==-1) return childNo;
										if(rhs!= iLoc->typ.a.sub.a){
											printf("Error in Line no: %d, assigned value doesn't match type\n",Node->a.twoChildNode[0]->a.treeNode->lineNo);
											typecheckingflag=1;
											return childNo;
										}
									}
									else{
										if(Node->a.twoChildNode[1]->type == expressionNode){
											
											if(Node->a.twoChildNode[1]->a.oneChildNode[0]->type == parsetreeNode){
												if(Node->a.twoChildNode[1]->a.oneChildNode[0]->a.treeNode->value-100 !=ID){
													printf("Error in Line no: %d, cannot assign value to array using expression\n",Node->a.twoChildNode[0]->a.treeNode->lineNo);
													typecheckingflag=1;
													return childNo;
												}
												if(Node->a.twoChildNode[1]->a.oneChildNode[0]->next!=NULL){
													printf("Error in Line no: %d, cannot assign value to array using expression\n",Node->a.twoChildNode[0]->a.treeNode->lineNo);
													typecheckingflag=1;
													return childNo;
												}
												varid * idLoc1 = lookup_varid(Node->a.twoChildNode[1]->a.oneChildNode[0]->a.treeNode->lineNo, Node->a.twoChildNode[1]->a.oneChildNode[0]->a.treeNode->name, symbolTable);
												if(!idDeclared(idLoc1,Node->a.twoChildNode[1]->a.oneChildNode[0])){
													var_l * iLoc1 = lookup_varid1(Node->a.twoChildNode[1]->a.oneChildNode[0]->a.treeNode->name, presentModule->input_list);
													if(iLoc1==NULL){
														oLoc = lookup_varid1(Node->a.twoChildNode[1]->a.oneChildNode[0]->a.treeNode->name, presentModule->output_list);
														if(oLoc == NULL){
															printf("Error in Line no: %d, Variable: %s not declared\n", Node->a.twoChildNode[1]->a.oneChildNode[0]->a.treeNode->lineNo,Node->a.twoChildNode[1]->a.oneChildNode[0]->a.treeNode->name);
															typecheckingflag=1;
														}
														else{
															printf("Error in Line no: %d, Variable: %s cannot assign value to array using expression\n", Node->a.twoChildNode[1]->a.oneChildNode[0]->a.treeNode->lineNo,Node->a.twoChildNode[1]->a.oneChildNode[0]->a.treeNode->name);
															typecheckingflag=1;
														} 																						
													}
													else idTypeMatch1(idLoc, iLoc1,Node->a.twoChildNode[1]->a.oneChildNode[0]->a.treeNode->lineNo);

													return childNo;
												}
												else if (!idTypeMatch(idLoc, idLoc1,Node->a.twoChildNode[1]->a.oneChildNode[0]->a.treeNode->lineNo)){
													return childNo;
												}
											}
											else{
												printf("Error in Line no: %d, cannot assign value to array using expression\n",Node->a.twoChildNode[0]->a.treeNode->lineNo);
												typecheckingflag=1;
											}
										}
										else{
											printf("Error in Line no: %d, cannot assign value to array using expression\n",Node->a.twoChildNode[0]->a.treeNode->lineNo);
											typecheckingflag=1;
											return childNo;
										}
									
										
									}
								}
								else{
									int rhs=expressionTypeChecker(Node->a.twoChildNode[1],symbolTable, Node->a.twoChildNode[0]->a.treeNode->lineNo, presentModule);
									if(rhs==-1) return childNo;
									if(rhs!= iLoc->typ.t.a){
										 printf("Error in Line no: %d, assigned value doesn't match type\n",Node->a.twoChildNode[0]->a.treeNode->lineNo);
										 typecheckingflag=1;
										 return childNo;
									}
								}
								
							}
						}
					   return childNo;
                    }
                    if(idLoc->ut==1){
                        if(Node->a.twoChildNode[1]->type == lvalueArrStmtNode){
							if(!arrayInBound(idLoc,Node->a.twoChildNode[1],presentModule,symbolTable))
								return childNo;
							int rhs=expressionTypeChecker(Node->a.twoChildNode[1]->a.twoChildNode[1],symbolTable, Node->a.twoChildNode[0]->a.treeNode->lineNo, presentModule);
							if(rhs==-1) return childNo;
                            if(rhs!= idLoc->vartype.a.sub.a){
                                printf("Error in Line no: %d, assigned value doesn't match type\n",Node->a.twoChildNode[0]->a.treeNode->lineNo);
                                typecheckingflag=1;
                                return childNo;
                            }
                        }
                        else{
                            if(Node->a.twoChildNode[1]->type == expressionNode){
                                
                                if(Node->a.twoChildNode[1]->a.oneChildNode[0]->type == parsetreeNode){
                                    if(Node->a.twoChildNode[1]->a.oneChildNode[0]->a.treeNode->value-100 !=ID){
										printf("Error in Line no: %d, cannot assign value to array using expression\n",Node->a.twoChildNode[0]->a.treeNode->lineNo);
										typecheckingflag=1;
										return childNo;
									}
									if(Node->a.twoChildNode[1]->a.oneChildNode[0]->next!=NULL){
										printf("Error in Line no: %d, cannot assign value to array using expression\n",Node->a.twoChildNode[0]->a.treeNode->lineNo);
										typecheckingflag=1;
										return childNo;
									}
                                    varid * idLoc1 = lookup_varid(Node->a.twoChildNode[1]->a.oneChildNode[0]->a.treeNode->lineNo, Node->a.twoChildNode[1]->a.oneChildNode[0]->a.treeNode->name, symbolTable);
                                    if(!idDeclared(idLoc1,Node->a.twoChildNode[1]->a.oneChildNode[0])){
										iLoc = lookup_varid1(Node->a.twoChildNode[1]->a.oneChildNode[0]->a.treeNode->name, presentModule->input_list);
										if(iLoc==NULL){
											oLoc = lookup_varid1(Node->a.twoChildNode[1]->a.oneChildNode[0]->a.treeNode->name, presentModule->output_list);
											if(oLoc == NULL){
												printf("Error in Line no: %d, Variable: %s not declared\n", Node->a.twoChildNode[1]->a.oneChildNode[0]->a.treeNode->lineNo,Node->a.twoChildNode[1]->a.oneChildNode[0]->a.treeNode->name);
												typecheckingflag=1;
											}
											else{
												printf("Error in Line no: %d, Variable: %s cannot assign value to array using expression\n", Node->a.twoChildNode[1]->a.oneChildNode[0]->a.treeNode->lineNo,Node->a.twoChildNode[1]->a.oneChildNode[0]->a.treeNode->name);
												typecheckingflag=1;
											} 																						
										}
										else idTypeMatch1(idLoc, iLoc,Node->a.twoChildNode[1]->a.oneChildNode[0]->a.treeNode->lineNo);

                                        return childNo;
                                    }
                                    else if (!idTypeMatch(idLoc, idLoc1,Node->a.twoChildNode[1]->a.oneChildNode[0]->a.treeNode->lineNo)){
                                        return childNo;
                                    }
                                }
								else{
									printf("Error in Line no: %d, cannot assign value to array using expression\n",Node->a.twoChildNode[0]->a.treeNode->lineNo);
									typecheckingflag=1;
								}
                            }
							else{
								printf("Error in Line no: %d, cannot assign value to array using expression\n",Node->a.twoChildNode[0]->a.treeNode->lineNo);
								typecheckingflag=1;
								return childNo;
							}
                        
                            
                        }
                    }
					else{
						int rhs=expressionTypeChecker(Node->a.twoChildNode[1],symbolTable, Node->a.twoChildNode[0]->a.treeNode->lineNo, presentModule);
						if(rhs==-1) return childNo;
                        if(rhs!= idLoc->vartype.t.a){
                             printf("Error in Line no: %d, assigned value doesn't match type\n",Node->a.twoChildNode[0]->a.treeNode->lineNo);
                             typecheckingflag=1;
                             return childNo;
                        }
                    }
					return childNo;
                   break;
                
                
                
        case moduleReuseStmtNode: //toUpdate for i and o
                ;
            AST * temp15 = Node->a.threeChildNode[0];
            while(temp15!=NULL){
                    loopvar * x2 = loopVar;
                    while(x2!=NULL){
                        if(strcmp(x2->str,temp15->a.treeNode->name)==0){
						/*loopvar1 * y = loopVar1;
							while(y!=NULL){
								if(strcmp(y->str,temp15->a.treeNode->name)==0&& y->lno>=x2->lno) break;
								y=y->next;										
							}
							if(y==NULL){
								printf("Error in Line no: %d, for iterator variable cannot be assigned a value\n",temp15->a.treeNode->lineNo);
								typecheckingflag=1;
								//return childNo;
							}
							break;*/
							varid * a = lookup_varid(temp15->a.treeNode->lineNo, temp15->a.treeNode->name, symbolTable);
							if(a==NULL){
								printf("Error in Line no: %d, for iterator variable cannot be assigned a value\n",temp15->a.treeNode->lineNo);		
								typecheckingflag=1;
								//break;
								//return childNo;
							}
							else if(a->lno<=x->lno){
								printf("Error in Line no: %d, for iterator variable cannot be assigned a value\n",temp15->a.treeNode->lineNo);		
								typecheckingflag=1;
								//break;
								//return childNo;
							}
							break;
                        }
                        x2=x2->next;
                    }
					whilevar * w2 = whileVar->next;
					while(w2){
						if(w2->flag==0){
							loopvar * x1= w2->head;
							while(x1){
								if(strcmp(x1->str,temp15->a.treeNode->name)==0){
									varid * a = lookup_varid(temp15->a.treeNode->lineNo, temp15->a.treeNode->name, symbolTable);
									if(a==NULL){
										w2->flag=1;
									}
									else if(a->lno<w2->lno){
										w2->flag=1;
									}
									break;
								}
								x1=x1->next;
							}
						}
						w2=w2->next;
					}
                temp15=temp15->next;
            }
                
                funcLoc = lookupFunc(Node->a.threeChildNode[1]->a.treeNode->name);
                if(!funcDeclared(funcLoc,Node->a.threeChildNode[1])){return childNo;}
				 if(funcLoc->status==1){
                     printf("Error in Line no: %d, Function declared but not defined\n",Node->a.threeChildNode[1]->a.treeNode->lineNo);
                     typecheckingflag=1;
                     return childNo;
                }
                if(strcmp(funcLoc->name,presentModule->name)==0){
                    printf("Error in Line no: %d, direct recursion not permitted\n",Node->a.threeChildNode[1]->a.treeNode->lineNo);
                    typecheckingflag=1;
                    return childNo;
                }
                       
                if(funcLoc->status==3)//check
				{
                        printf("Error in Line No: %d, redundant declaration for Function: %s\n", Node->a.threeChildNode[1]->a.treeNode->lineNo, funcLoc->name);
                        typecheckingflag=1;
                        return childNo;
                }
                AST * temp = Node->a.threeChildNode[2];
                var_l * temp4 = funcLoc->input_list.head;
                while(temp!=NULL && temp4!=NULL){
                    idLoc = lookup_varid(temp->a.treeNode->lineNo, temp->a.treeNode->name,symbolTable);
                    if(idDeclared(idLoc, temp)){
                        //return;
						idTypeMatch1(idLoc,temp4,temp->a.treeNode->lineNo);
						//return;
					}
					else{
						oLoc = lookup_varid1(temp->a.treeNode->name, presentModule->output_list);
						if(oLoc==NULL){
							iLoc = lookup_varid1(temp->a.treeNode->name, presentModule->input_list);
							if(iLoc==NULL){
								printf("Error in Line no: %d, Variable: %s not declared\n",temp->a.treeNode->lineNo,temp->a.treeNode->name );
								typecheckingflag=1;
							}
							else{
								idTypeMatch2(temp4, iLoc, temp->a.treeNode->lineNo);
								}
						}
						else if(oLoc->flag==0){
                                printf("Error in Line no: %d, Variable: %s not assigned value\n", temp->a.treeNode->lineNo,temp->a.treeNode->name);
                                typecheckingflag=1;
                       	}
						else{
							//oLoc->flag=1;
							idTypeMatch2(temp4, oLoc,temp->a.treeNode->lineNo);

						}
					}
                    temp = temp->next;
                    temp4 = temp4->next;
                }
                
                if(temp!=NULL || temp4!=NULL){
                    printf("Error in Line no: %d, No. of input parameters mismatch\n",Node->a.threeChildNode[1]->a.treeNode->lineNo);
                    typecheckingflag=1;
                    //return;
                }
                
                temp = Node->a.threeChildNode[0];
                temp4 = funcLoc->output_list.head;
                while(temp!=NULL && temp4!=NULL){
                    idLoc = lookup_varid(temp->a.treeNode->lineNo, temp->a.treeNode->name,symbolTable);
                    if(idDeclared(idLoc, temp)){
                        //return;
						idTypeMatch1(idLoc,temp4,temp->a.treeNode->lineNo);
						//return;
					}
					else{
						oLoc = lookup_varid1(temp->a.treeNode->name, presentModule->output_list);
						if(oLoc==NULL){
							iLoc = lookup_varid1(temp->a.treeNode->name, presentModule->input_list);
                            if(iLoc==NULL){
                                printf("Error in Line no: %d, Variable: %s not declared\n", temp->a.treeNode->lineNo,temp->a.treeNode->name);
                                typecheckingflag=1;
                            }
                      
                            else{

                                idTypeMatch2(temp4, iLoc,temp->a.treeNode->lineNo);
                            }
						}
						else{								
							oLoc->flag=1;
							idTypeMatch2(temp4, oLoc,temp->a.treeNode->lineNo);

						}
					}
                    temp = temp->next;
                    temp4 = temp4->next;
                }
                            
                if(temp!=NULL || temp4!=NULL){
                    printf("Error in Line no: %d, No. of output parameters mismatch\n",Node->a.threeChildNode[1]->a.treeNode->lineNo);
                    typecheckingflag=1;
                   //return;
                }
				return childNo;
            break;
                
                
        case declareStmtNode:
                    if(Node->a.twoChildNode[1]->type == array_datatypeNode){
                        ret = typeChecker(Node->a.twoChildNode[1],symbolTable,childNo,presentModule);
                    }
                    /*AST * temp5 = Node->a.twoChildNode[0];
                    while(temp5!=NULL){
                        loopvar * x = loopVar;
                        while(x!=NULL){
                            if(strcmp(x->str,temp5->a.treeNode->name)==0){
								loopvar1 * y = loopVar1->next;
								loopvar1 * new = (loopvar1 *)malloc(sizeof(loopvar1));
								strcpy(new->str,x->str);
								new->lno=temp5->a.treeNode->lineNo;
								new->next=y;
								loopVar1->next=new;
								break;
                            }
                            x=x->next;
                        }
                        temp5 = temp5->next;
                    }*/
                    
                    return childNo;
                    break;
                       

       case conditionalStmtNode:
			idLoc = lookup_varid(Node->a.threeChildNode[0]->a.treeNode->lineNo, Node->a.threeChildNode[0]->a.treeNode->name, symbolTable);
			if(!idDeclared(idLoc, Node->a.threeChildNode[0])){
				iLoc = lookup_varid1(Node->a.threeChildNode[0]->a.treeNode->name, presentModule->input_list);
				if(iLoc==NULL){
					oLoc = lookup_varid1(Node->a.threeChildNode[0]->a.treeNode->name, presentModule->output_list);
					if(oLoc == NULL){
						printf("Error in Line no: %d, Variable: %s not declared\n", Node->a.threeChildNode[0]->a.treeNode->lineNo,Node->a.threeChildNode[0]->a.treeNode->name);
						typecheckingflag=1;
						return childNo+1;
					}
					else if(oLoc->flag == 0){
						printf("Error in Line no: %d, Variable: %s not assigned value\n", Node->a.threeChildNode[0]->a.treeNode->lineNo, Node->a.threeChildNode[0]->a.treeNode->name);
						typecheckingflag=1;
					}
					if(oLoc->t!=0 || !(oLoc->typ.t.a==INTEGER || oLoc->typ.t.a==BOOLEAN) /*for integer*/){
						printf("Error in Line no: %d, switch statement Variable: %s must be an integer or boolean\n",Node->a.threeChildNode[0]->a.treeNode->lineNo,Node->a.threeChildNode[0]->a.treeNode->name);			
						typecheckingflag=1;
						return childNo+1;
					}
					AST * temp9 = Node->a.threeChildNode[1];
					ret=0;
					while(temp9->next!=NULL){
						if(!((oLoc->typ.t.a == INTEGER && temp9->a.twoChildNode[0]->a.treeNode->value-100 == NUM) || (oLoc->typ.t.a == BOOLEAN && temp9->a.twoChildNode[0]->a.treeNode->value-100 == TRUET) || (oLoc->typ.t.a == BOOLEAN && temp9->a.twoChildNode[0]->a.treeNode->value-100 == FALSET))){
							printf("Error in Line no: %d, case statement value: %s type doesn't match switch variable type\n",temp9->a.twoChildNode[0]->a.treeNode->lineNo,temp9->a.twoChildNode[0]->a.treeNode->name);
							typecheckingflag=1;
						}
						AST * iter = temp9->a.twoChildNode[1];
						while(iter!=NULL){
							ret=typeChecker(iter, symbolTable->children[childNo],ret, presentModule);
							iter=iter->next;
						}
						temp9=temp9->next;
					}
		   
					if(oLoc->typ.t.a==INTEGER){
						if(Node->a.threeChildNode[2]==NULL){
							printf("Error in Line no: %d, default statement mandatory for switch statement on integer variable\n",Node->a.threeChildNode[0]->a.treeNode->lineNo);
							typecheckingflag=1;
						}
						else if(Node->a.threeChildNode[2]->type!=emptyDefaultNode) {
							AST * iter = Node->a.threeChildNode[2];
							//ret=0;
							while(iter!=NULL){
								ret=typeChecker(iter, symbolTable->children[childNo],ret, presentModule);
								iter=iter->next;
							}
						}
						//ret=typeChecker(Node->a.threeChildNode[2], symbolTable->children[childNo],0, presentModule,loopVar);
					}	
					else if(oLoc->typ.t.a==BOOLEAN){ //write code
						if(Node->a.threeChildNode[2]!=NULL){
							printf("Error in Line no: %d, default statement cannot be present for switch statement on boolean Variable\n",Node->a.threeChildNode[0]->a.treeNode->lineNo);
							typecheckingflag=1;
						}
						if(Node->a.threeChildNode[1]->a.twoChildNode[0]->a.treeNode->value-100==TRUET && Node->a.threeChildNode[1]->next!=NULL && Node->a.threeChildNode[1]->next->a.twoChildNode[0]->a.treeNode->value-100==FALSET && Node->a.threeChildNode[1]->next->next!=NULL && Node->a.threeChildNode[1]->next->next->type==END+100 ){
											;
						}
						else if(Node->a.threeChildNode[1]->a.twoChildNode[0]->a.treeNode->value-100==FALSET && Node->a.threeChildNode[1]->next!=NULL && Node->a.threeChildNode[1]->next->a.twoChildNode[0]->a.treeNode->value-100==TRUET && Node->a.threeChildNode[1]->next->next!=NULL && Node->a.threeChildNode[1]->next->next->type==END+100){
										;
						}
						else{
							printf("Error in Line no: %d, switch statement on boolean must have 2 cases - TRUE and FALSE\n",Node->a.threeChildNode[0]->a.treeNode->lineNo);
							typecheckingflag=1;
						}
					}
					return childNo+1;
				}
				else if(iLoc->t!=0 || !(iLoc->typ.t.a==INTEGER || iLoc->typ.t.a==BOOLEAN) /*for integer*/){
					printf("Error in Line no: %d, switch statement Variable: %s must be an integer or boolean\n",Node->a.threeChildNode[0]->a.treeNode->lineNo,Node->a.threeChildNode[0]->a.treeNode->name);
					typecheckingflag=1;
					return childNo+1;
				}
              
				AST * temp8 = Node->a.threeChildNode[1];
				ret=0;
				while(temp8->next!=NULL){
					if(!((iLoc->typ.t.a == INTEGER && temp8->a.twoChildNode[0]->a.treeNode->value-100 == NUM) || (iLoc->typ.t.a == BOOLEAN && temp8->a.twoChildNode[0]->a.treeNode->value-100 == TRUET) || (iLoc->typ.t.a == BOOLEAN && temp8->a.twoChildNode[0]->a.treeNode->value-100 == FALSET))){
						printf("Error in Line no: %d, case statement value: %s type doesn't match switch variable type\n",temp8->a.twoChildNode[0]->a.treeNode->lineNo,temp8->a.twoChildNode[0]->a.treeNode->name);
						typecheckingflag=1;
					}
					AST * iter = temp8->a.twoChildNode[1];
					while(iter!=NULL){
						ret=typeChecker(iter, symbolTable->children[childNo],ret, presentModule);
						iter=iter->next;
					}
					temp8=temp8->next;
				}
       
				if(iLoc->typ.t.a==INTEGER){
					if(Node->a.threeChildNode[2]==NULL){
						printf("Error in Line no: %d, default statement mandatory for switch statement on integer variable\n",Node->a.threeChildNode[0]->a.treeNode->lineNo);
						typecheckingflag=1;
					}
					else if(Node->a.threeChildNode[2]->type!=emptyDefaultNode){
						AST * iter = Node->a.threeChildNode[2];
						//ret=0;
						while(iter!=NULL){
						ret=typeChecker(iter, symbolTable->children[childNo],ret, presentModule);
						iter=iter->next;
						}
					}
				}	
				else if(iLoc->typ.t.a==BOOLEAN){ //write code
					if(Node->a.threeChildNode[2]!=NULL){
						printf("Error in Line no: %d, default statement cannot be present for switch statement on boolean variable\n",Node->a.threeChildNode[0]->a.treeNode->lineNo);
						typecheckingflag=1;
					}
	                if(Node->a.threeChildNode[1]->a.twoChildNode[0]->a.treeNode->value-100==TRUET && Node->a.threeChildNode[1]->next!=NULL && Node->a.threeChildNode[1]->next->a.twoChildNode[0]->a.treeNode->value-100==FALSET && Node->a.threeChildNode[1]->next->next!=NULL && Node->a.threeChildNode[1]->next->next->type==END+100){
		                                ;
					}
					else if(Node->a.threeChildNode[1]->a.twoChildNode[0]->a.treeNode->value-100==FALSET && Node->a.threeChildNode[1]->next!=NULL && Node->a.threeChildNode[1]->next->a.twoChildNode[0]->a.treeNode->value-100==TRUET && Node->a.threeChildNode[1]->next->next!=NULL && Node->a.threeChildNode[1]->next->next->type==END+100){
		                            ;
					}
					else{
						printf("Error in Line no: %d, switch statement on boolean must have 2 cases - TRUE and FALSE\n",Node->a.threeChildNode[0]->a.treeNode->lineNo);
						typecheckingflag=1;
					}
				}
	
				return childNo+1;
			}
			else if(idLoc->ut!=0 || !(idLoc->vartype.t.a==INTEGER || idLoc->vartype.t.a==BOOLEAN) /*for integer*/){
				printf("Error in Line no: %d, switch statement Variable: %s must be an integer or boolean\n",Node->a.oneChildNode[0]->a.treeNode->lineNo,Node->a.oneChildNode[0]->a.treeNode->name);
				typecheckingflag=1;
				return childNo+1;
			}
			AST * temp7 = Node->a.threeChildNode[1];
			ret=0;
			while(temp7->next!=NULL){
				if(!((idLoc->vartype.t.a == INTEGER && temp7->a.twoChildNode[0]->a.treeNode->value-100 == NUM) || (idLoc->vartype.t.a == BOOLEAN && temp7->a.twoChildNode[0]->a.treeNode->value-100 == TRUET) || (idLoc->vartype.t.a == BOOLEAN && temp7->a.twoChildNode[0]->a.treeNode->value-100 == FALSET))){
					printf("Error in Line no: %d, case statement value: %s type doesn't match switch variable type\n",temp7->a.twoChildNode[0]->a.treeNode->lineNo,temp7->a.twoChildNode[0]->a.treeNode->name);
					typecheckingflag=1;
				}
				AST * iter = temp7->a.twoChildNode[1];
				while(iter!=NULL){
					ret=typeChecker(iter, symbolTable->children[childNo],ret, presentModule);
					iter=iter->next;
				}
				temp7=temp7->next;
			}

          
			if(idLoc->vartype.t.a==INTEGER){

				if(Node->a.threeChildNode[2]==NULL){
					printf("Error in Line no: %d, default statement mandatory for switch statement on integer variable\n",Node->a.threeChildNode[0]->a.treeNode->lineNo);
					typecheckingflag=1;
				}
				else if(Node->a.threeChildNode[2]->type!=emptyDefaultNode) {
					AST * iter = Node->a.threeChildNode[2];
					//ret=0;
					while(iter!=NULL){
						ret=typeChecker(iter, symbolTable->children[childNo],ret, presentModule);
						iter=iter->next;
					}
				}
				else{
											//printf("here");	
				}
		//ret=typeChecker(Node->a.threeChildNode[2], symbolTable->children[childNo],0, presentModule,loopVar);
			}
			else if(idLoc->vartype.t.a==BOOLEAN){
				if(Node->a.threeChildNode[2]!=NULL){
					printf("Error in Line no: %d, default statement cannot be present for switch statement on boolean variable\n",Node->a.threeChildNode[0]->a.treeNode->lineNo);
					typecheckingflag=1;
				}
				if(Node->a.threeChildNode[1]->a.twoChildNode[0]->a.treeNode->value-100==TRUET && Node->a.threeChildNode[1]->next!=NULL && Node->a.threeChildNode[1]->next->a.twoChildNode[0]->a.treeNode->value-100==FALSET && Node->a.threeChildNode[1]->next->next!=NULL && Node->a.threeChildNode[1]->next->next->type==END+100){
											;
				}
				else if(Node->a.threeChildNode[1]->a.twoChildNode[0]->a.treeNode->value-100==FALSET && Node->a.threeChildNode[1]->next!=NULL && Node->a.threeChildNode[1]->next->a.twoChildNode[0]->a.treeNode->value-100==TRUET && Node->a.threeChildNode[1]->next->next!=NULL && Node->a.threeChildNode[1]->next->next->type==END+100){
		                            ;
				}
				else{
					printf("Error in Line no: %d, switch statement on boolean must have 2 cases - TRUE and FALSE\n",Node->a.threeChildNode[0]->a.treeNode->lineNo);
					typecheckingflag=1;
				}
            }
			
		childNo++;
       	return childNo;
   	break;
                 
                              
        case caseStmtNode:
                   ;
                AST * itr2 = Node->a.twoChildNode[1];
				ret =childNo;
                while(itr2!=NULL){
                    ret = typeChecker(itr2,symbolTable,ret,presentModule);
                    itr2 = itr2->next;
                }
                return childNo;
                break;
                
                
                
                
        case forstmtNode: //add same itr?
                ;
                loopvar * forlist = loopVar;
		/*while(forlist!=NULL){
			if(strcmp(forlist->str,Node->a.threeChildNode[0]->a.treeNode->name)==0){
						
						varid * a = lookup_varid(Node->a.threeChildNode[0]->a.treeNode->lineNo, Node->a.threeChildNode[0]->a.treeNode->name, symbolTable);
						if(a==NULL){
							printf("Error in Line no: %d, for iterator variable cannot be reused in internal for loop\n",Node->a.threeChildNode[0]->a.treeNode->lineNo);		
							typecheckingflag=1;
							//break;
						}
						else if(a->lno<=forlist->lno){
							printf("Error in Line no: %d, for iterator variable cannot be reused in internal for loop\n",Node->a.threeChildNode[0]->a.treeNode->lineNo);		
							typecheckingflag=1;
							//break;
						}
						break; 
			}
			forlist=forlist->next;			
		}*/	
		
            
                idLoc = lookup_varid(Node->a.threeChildNode[0]->a.treeNode->lineNo, Node->a.threeChildNode[0]->a.treeNode->name, symbolTable);
                if(!idDeclared(idLoc, Node->a.threeChildNode[0])){
					iLoc = lookup_varid1(Node->a.threeChildNode[0]->a.treeNode->name, presentModule->input_list);
					if(iLoc==NULL){
						oLoc = lookup_varid1(Node->a.threeChildNode[0]->a.treeNode->name, presentModule->output_list);
						if(oLoc == NULL){
							printf("Error in Line no: %d, Variable: %s not declared\n", Node->a.threeChildNode[0]->a.treeNode->lineNo,Node->a.threeChildNode[0]->a.treeNode->name);
							typecheckingflag=1;
							return childNo + 1;
						}
						else if(oLoc->flag == 0){
							printf("Error in Line no: %d, Variable: %s not assigned value\n", Node->a.threeChildNode[0]->a.treeNode->lineNo,Node->a.threeChildNode[0]->a.treeNode->name);
							typecheckingflag=1;
						} 
						if(oLoc->t!=0 || oLoc->typ.t.a!=INTEGER /*for integer*/){
							printf("Error in Line no: %d, for statement Variable: %s must be an integer\n",Node->a.threeChildNode[0]->a.treeNode->lineNo,Node->a.threeChildNode[0]->a.treeNode->name);
							typecheckingflag=1;
						}
					}
					else if(iLoc->t!=0 || iLoc->typ.t.a!=INTEGER /*for integer*/){
							printf("Error in Line no: %d, for statement Variable: %s must be an integer\n",Node->a.threeChildNode[0]->a.treeNode->lineNo,Node->a.threeChildNode[0]->a.treeNode->name);
							typecheckingflag=1;
					}
					
					
				}
                else if(idLoc->ut!=0 || idLoc->vartype.t.a!=INTEGER /*for integer*/){
                    printf("Error in Line no: %d, for statement Variable: %s must be an integer\n",Node->a.threeChildNode[0]->a.treeNode->lineNo,Node->a.threeChildNode[0]->a.treeNode->name);
                    typecheckingflag=1;
                    //return childNo+1;
                }
				
				int start = atoi(Node->a.threeChildNode[1]->a.twoChildNode[0]->a.treeNode->name);
				int end = atoi(Node->a.threeChildNode[1]->a.twoChildNode[1]->a.treeNode->name);
				if(end < start){
					printf("Error in Line no: %d, Ending index cannot be less than starting index in for loop\n",Node->a.threeChildNode[0]->a.treeNode->lineNo);
					typecheckingflag=1;
				}
                //loopvar1 * endMarker = loopVar1->next;
				
				forlist=loopVar->next;                
                loopvar * forlist1 = (loopvar *)malloc(sizeof(loopvar));
                strcpy(forlist1->str,Node->a.threeChildNode[0]->a.treeNode->name);
                forlist1->next=NULL;
                forlist1->next= forlist;
				forlist1->lno= Node->a.threeChildNode[0]->a.treeNode->lineNo;
				loopVar->next=forlist1;
              
				

                AST * temp100 = Node->a.threeChildNode[2];
                ret=0;
                while(temp100->next!=NULL){
                    ret=typeChecker(temp100, symbolTable->children[childNo],ret,presentModule);
                    temp100 = temp100->next;
                }
				/*loopvar1 * endMarker1 = loopVar1->next;
				loopvar1 * temp123 =endMarker1;
				while(endMarker1!=endMarker){
					endMarker1=endMarker1->next;
					loopVar1->next=endMarker1;
					free(temp123);
					temp123=endMarker1;
				}*/
				
	
                forlist = loopVar->next;
                forlist1 = loopVar->next->next;
				loopVar->next = forlist1;
                free(forlist);
               
                childNo++;
                return childNo;
            break;
                
                
                
                
                
        case whileStmtNode:
                   ;
                  AST * temp6 = Node->a.twoChildNode[0];
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
                   
                   int check = expressionTypeChecker(Node->a.twoChildNode[0], symbolTable, lineNo1, presentModule);
                   if(check!=-1 && check!=BOOLEAN){
                        printf("Error in Line no: %d, While condition must be a boolean expression\n",lineNo1);
                        typecheckingflag=1;
                        //return;
                    }
                   //int ret = typeChecker(Node->a.twoChildNode[1],symbolTable->children[childNo],0);
					whilevar * wv = (whilevar *)malloc(sizeof(whilevar)); 
					wv->head = addToWhile(Node->a.twoChildNode[0], lineNo1);		
					if(wv->head==NULL){
						//printf("Error in Line no: %d, While condition must have atleast one variable\n",lineNo1);
                        //typecheckingflag=1;
						wv->flag=1;				
						//free(wv);
						//return childNo+1;
					}	
					else wv->flag=0;
					wv->lno=lineNo1;
					wv->next=whileVar->next;
					whileVar->next = wv;					
					AST * itr6 = Node->a.twoChildNode[1];
					while(itr6->next!=NULL){
                        ret = typeChecker(itr6,symbolTable->children[childNo],0, presentModule);
                        itr6 = itr6->next;
					}
					
					whilevar * wv1 = whileVar->next;
					if(wv1->flag==0){
						printf("Error in Line no: %d, No while condition's variable's value is being updated\n",lineNo1);
                        typecheckingflag=1;
					}
					
					whileVar->next = wv1->next;	
					loopvar *l1, * l2; 
					l2=wv1->head;
					while(l2){
						l1=l2;
						l2=l2->next;
						free(l1);
					}
					free(wv1);
				   childNo++;
                   return childNo;
                break;
      
           
        default:
             return childNo;

    }
    

    
}


