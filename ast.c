    /*AARYAN KAPOOR 2016B4A70166P
     SATWADHI DAS 2016B4A70622P
     ISHAN SANJAY JOGLEKAR 2016B3A70534P
     SATYANSH RAI 2016B4A70632P
     PARTH MISRA 2016B5A70560P*/
     

#include "ast.h"
extern int countASTNodes; 
extern int ASTmem;
AST * makeNode(enum typeOfNode type){
    AST * iterator = (AST *)malloc(sizeof(AST));
    iterator->type = type;
    iterator->next = NULL;
    countASTNodes++;
    return iterator;
}
void freeAST(AST * head){

    if(head==NULL) {

        return;

    }

    switch(head->type){

    case programNode:

        freeAST(head->a.fourChildNode[0]);

        freeAST(head->a.fourChildNode[1]);

        freeAST(head->a.fourChildNode[2]);

        freeAST(head->a.fourChildNode[3]);

        free(head);

        break;

    case logicalOpNode:

    case relationalOpNode:

        freeAST(head->a.threeChildNode[0]);

        freeAST(head->a.threeChildNode[1]);

        freeAST(head->a.threeChildNode[2]);

        free(head);

        break;

    case plusNode:

    case minusNode:

    case multiplyNode:

    case divideNode:

    case array_datatypeNode:

    case lvalueArrStmtNode:

    case rangeNode:

    case range1Node:

            freeAST(head->a.twoChildNode[0]);

            freeAST(head->a.twoChildNode[1]);

            free(head);

            break;

  

    

         

   

    case driverModuleNode:

    case unaryExpressionNode:

    case expressionNode:

    case unaryPlusNode:

    case unaryMinusNode:

            freeAST(head->a.oneChildNode[0]);

            free(head);

            break;

    case moduleDeclarationNode:

        

            freeAST(head->a.oneChildNode[0]);

            freeAST(head->next);

            free(head);

        

        break;

    case moduleNode:

      

            freeAST(head->a.fourChildNode[0]);

            freeAST(head->a.fourChildNode[1]);

            freeAST(head->a.fourChildNode[2]);

            freeAST(head->a.fourChildNode[3]);

            freeAST(head->next);

            free(head);

        

        break;

    case input_plistNode:

    case input_plist1Node:

    case output_plistNode:

    case output_plist1Node:

        

            freeAST(head->a.twoChildNode[0]);

            freeAST(head->a.twoChildNode[1]);

            freeAST(head->next);

            free(head);
			break;
        

    case declareStmtNode:

    case caseStmtNode:

    case whileStmtNode:

    case assignStmtNode:

        freeAST(head->a.twoChildNode[0]);

        freeAST(head->a.twoChildNode[1]);

        freeAST(head->next);

        free(head);

        break;

    case getValueNode:

    case printNode:

          freeAST(head->a.oneChildNode[0]);

          freeAST(head->next);

          free(head);

        break;


    case moduleReuseStmtNode:

    case conditionalStmtNode:

    case forstmtNode:

      

        freeAST(head->a.threeChildNode[0]);

        freeAST(head->a.threeChildNode[1]);

        freeAST(head->a.threeChildNode[2]);

        freeAST(head->next);

        free(head);

        break;


    case parsetreeNode:
			freeAST(head->next);

        case REAL+100:

        case BOOLEAN+100:

        case TRUET+100:

        case FALSET+100:

        case AND+100:

        case OR+100:

        case GT+100:

        case LT+100:

        case GE+100:

        case LE+100:

        case EQ+100:

        case NE+100:

        case END+100:

        case INTEGER+100:

            free(head->a.treeNode);

            free(head);

            break;

        

            

    default:

        printf("Node unknown\n");

            return;

    }

    return;

}
AST * makeExpression(Node * nod, AST * inh){
    AST * node1, * node2, * node3;
    if(nod->tnt==1); // do something;
    else{
        switch(nod->rule){
            case 65:
                node1 = makeNode(logicalOpNode);
                node1->a.threeChildNode[0] = makeAST(nod->child);
                node1->a.threeChildNode[1] = inh;
                node1->a.threeChildNode[2] = makeAST(nod->child->next);
                node2 = makeExpression(nod->child->next->next, node1);
                //free(nod->child->next->next);
                //free(nod->child->next);
                //free(nod->child);
                return node2;
                break;
            case 69:
                node1 = makeNode(relationalOpNode);
                node1->a.threeChildNode[0] = makeAST(nod->child);
                node1->a.threeChildNode[1] = inh;
                node1->a.threeChildNode[2] = makeAST(nod->child->next);
                //free(nod->child->next);
                //free(nod->child);
                return node1;
                break;
            case 64:
            case 67:
            case 71:
            case 75:
                node1 = makeAST(nod->child);
                node2 = makeExpression(nod->child->next, node1);
                //free(nod->child->next);
                //free(nod->child);
                return node2;
                break;
            case 72:
                node1 = makeNode(plusNode);
                node1->a.twoChildNode[0] = inh;
                node1->a.twoChildNode[1] = makeAST(nod->child->next);
                node2 = makeExpression(nod->child->next->next, node1);
                //free(nod->child->next->next);
                //free(nod->child->next);
                //free(nod->child);
                return node2;
                break;
            case 73:
                node1 = makeNode(minusNode);
                node1->a.twoChildNode[0] = inh;
                node1->a.twoChildNode[1] = makeAST(nod->child->next);
                node2 = makeExpression(nod->child->next->next, node1);
                //free(nod->child->next->next);
                //free(nod->child->next);
                //free(nod->child);
                return node2;
                break;

            case 76:
                node1 = makeNode(multiplyNode);
                node1->a.twoChildNode[0] = inh;
                node1->a.twoChildNode[1] = makeAST(nod->child->next);
                node2 = makeExpression(nod->child->next->next, node1);
                //free(nod->child->next->next);
                //free(nod->child->next);
                //free(nod->child);
                return node2;
                break;
            case 77:
                node1 = makeNode(divideNode);
                node1->a.twoChildNode[0] = inh;
                node1->a.twoChildNode[1] = makeAST(nod->child->next);
                node2 = makeExpression(nod->child->next->next, node1);
                //free(nod->child->next->next);
                //free(nod->child->next);
                //free(nod->child);
                return node2;
                break;
            case 66:
            case 70:
            case 74:
            case 78:
                //free(nod->child);
                return inh;
                break;

        }

    }
}


extern int driverLineNo;

AST * makeAST(Node * nod){

    AST * node1, * tempchild, * tempchild1;
        if(nod->tnt==1); // do something;
        else{
            switch(nod->rule){
            case 1:
                    node1 = makeNode(programNode);
                    node1->a.fourChildNode[0]=makeAST(nod->child);
                    node1->a.fourChildNode[1]=makeAST(nod->child->next);
                    node1->a.fourChildNode[2]=makeAST(nod->child->next->next);
                    node1->a.fourChildNode[3]=makeAST(nod->child->next->next->next);
                    //free(nod->child->next->next->next);
                    //free(nod->child->next->next);
                    //free(nod->child->next);
                    //free(nod->child);
                    return node1;
                    break;
            case 2:
                    node1 = makeAST(nod->child);
                    node1->next = makeAST(nod->child->next);
                    //free(nod->child->next);
                    //free(nod->child);
                    return node1;
                    break;
            case 3:
                    //free(nod->child);
                    return NULL;
                    break;
            case 4:
                    node1 = makeNode(moduleDeclarationNode);
                    AST * tempchild = makeNode(parsetreeNode);
                    tempchild->a.treeNode= nod->child->next->next;
                    node1->a.oneChildNode[0] = tempchild;
                    //free(nod->child->next->next->next);
                    //free(nod->child->next);
                    //free(nod->child);
                    return node1;
                    break;
            case 5:
                    node1 = makeAST(nod->child);
                    node1->next = makeAST(nod->child->next);
                    //free(nod->child->next);
                    //free(nod->child);
                    return node1;
                    break;
            case 6:
                    //free(nod->child);
                    return NULL;
                    break;
            case 7:
                    node1 = makeNode(driverModuleNode);
                    node1->a.oneChildNode[0]=makeAST(nod->child->next->next->next->next);
                    driverLineNo = nod->child->lineNo;
                    //free(nod->child->next->next->next->next);
                    //free(nod->child->next->next->next);
                    //free(nod->child->next->next);
                    //free(nod->child->next);
                    //free(nod->child);
                    return node1;
                    break;
            case 8:
                    node1 = makeNode (moduleNode);
                    tempchild = makeNode(parsetreeNode);
                    tempchild->a.treeNode= nod->child->next->next;
                    node1->a.fourChildNode[0] = tempchild;
                    node1->a.fourChildNode[1] = makeAST(nod->child->next->next->next->next->next->next->next);
                    node1->a.fourChildNode[2] = makeAST(nod->child->next->next->next->next->next->next->next->next->next->next);
                    node1->a.fourChildNode[3] = makeAST(nod->child->next->next->next->next->next->next->next->next->next->next->next);
                    //free(nod->child->next->next->next->next->next->next->next->next->next->next->next);
                    //free(nod->child->next->next->next->next->next->next->next->next->next->next);
                    //free(nod->child->next->next->next->next->next->next->next->next->next);
                    //free(nod->child->next->next->next->next->next->next->next->next);
                    //free(nod->child->next->next->next->next->next->next->next);
                    //free(nod->child->next->next->next->next->next->next);
                    //free(nod->child->next->next->next->next->next);
                    //free(nod->child->next->next->next->next);
                    //free(nod->child->next->next->next);
                    //free(nod->child->next);
                    //free(nod->child);
                    return node1;
                    break;
            case 9:
                    node1 = makeAST(nod->child->next->next);
                    //free(nod->child->next->next->next->next);
                    //free(nod->child->next->next->next);
                    //free(nod->child->next->next);
                    //free(nod->child->next);
                    //free(nod->child);
                    return node1;
                    break;
            case 10:
                    //free(nod->child);
                    return NULL;
                    break;
            case 11:
                    node1 = makeNode(input_plistNode);
                    tempchild = makeNode(parsetreeNode);
                    tempchild->a.treeNode=nod->child;
                    node1->a.twoChildNode[0] = tempchild;
                    node1->a.twoChildNode[1] = makeAST(nod->child->next->next);
                    node1->next = makeAST(nod->child->next->next->next);
                    //free(nod->child->next->next->next);
                    //free(nod->child->next->next);
                    //free(nod->child->next);
                    return node1;
                    break;
            case 12:
                    node1 = makeNode(input_plist1Node);
                    tempchild = makeNode(parsetreeNode);
                    tempchild->a.treeNode=nod->child->next;
                    node1->a.twoChildNode[0] = tempchild;
                    node1->a.twoChildNode[1] = makeAST(nod->child->next->next->next);
                    node1->next = makeAST(nod->child->next->next->next->next);
                    //free(nod->child->next->next->next->next);
                    //free(nod->child->next->next->next);
                    //free(nod->child->next->next);
                    //free(nod->child);
                    return node1;
                    break;
            case 13:
                    //free(nod->child);
                    return NULL;
                    break;
            case 14:
                    node1 = makeNode(output_plistNode);
                    tempchild = makeNode(parsetreeNode);
                    tempchild->a.treeNode=nod->child;
                    node1->a.twoChildNode[0] = tempchild;
                    node1->a.twoChildNode[1] = makeAST(nod->child->next->next);
                    node1->next = makeAST(nod->child->next->next->next);
                    //free(nod->child->next->next->next);
                    //free(nod->child->next->next);
                    //free(nod->child->next);
                    return node1;
                    break;
            case 15:
                    node1 = makeNode(output_plist1Node);
                    tempchild = makeNode(parsetreeNode);
                    tempchild->a.treeNode=nod->child->next;
                    node1->a.twoChildNode[0] = tempchild;
                    node1->a.twoChildNode[1] = makeAST(nod->child->next->next->next);
                    node1->next = makeAST(nod->child->next->next->next->next);
                    //free(nod->child->next->next->next->next);
                    //free(nod->child->next->next->next);
                    //free(nod->child->next->next);
                    //free(nod->child);
                    return node1;
                    break;
            case 16:
                    //free(nod->child);
                    return NULL;
                    break;
            case 17:
                    tempchild = makeNode(nod->child->value);
                    tempchild->a.treeNode=nod->child;
                    return tempchild;                    //CONFIRM CONFIRM CONFIRM CONFIRM CONFIRM
                    break;
            case 18:
                    tempchild = makeNode(nod->child->value);
                    tempchild->a.treeNode=nod->child;
                    return tempchild;                    //CONFIRM CONFIRM CONFIRM CONFIRM CONFIRM
                    break;
            case 19:
                    tempchild = makeNode(nod->child->value);
                    tempchild->a.treeNode=nod->child;
                    return tempchild;                    //CONFIRM CONFIRM CONFIRM CONFIRM CONFIRM
                    break;
            case 20:
                    node1 = makeNode(array_datatypeNode);
                    node1->a.twoChildNode[0]= makeAST(nod->child->next->next);
                    node1->a.twoChildNode[1]= makeAST(nod->child->next->next->next->next->next);
                    //free(nod->child->next->next->next->next->next);
                    //free(nod->child->next->next->next->next);
                    //free(nod->child->next->next->next);
                    //free(nod->child->next->next);
                    //free(nod->child->next);
                    //free(nod->child);
                    return node1;
                    break;
            case 36:
            case 37:
            case 81:
            case 82:
            case 83:
            case 84:
            case 85:
            case 86:
            case 87:
            case 88:
            case 96:
            case 97:
            case 21:
                    tempchild = makeNode(nod->child->value);
                    tempchild->a.treeNode=nod->child;
                    return tempchild;                    //CONFIRM CONFIRM CONFIRM CONFIRM CONFIRM
                    break;
            case 22:
                    tempchild = makeNode(nod->child->value);
                    tempchild->a.treeNode=nod->child;
                    return tempchild;                    //CONFIRM CONFIRM CONFIRM CONFIRM CONFIRM
                    break;
            case 23:
                    tempchild = makeNode(nod->child->value);
                    tempchild->a.treeNode=nod->child;
                    return tempchild;                    //CONFIRM CONFIRM CONFIRM CONFIRM CONFIRM
                    break;
            case 41:
            case 48:
            case 79:
            case 62:
                    node1 = makeAST(nod->child->next);
                    //free(nod->child->next->next);
                    //free(nod->child->next);
                    //free(nod->child);
                    return node1;
                    break;
            case 24:
                    node1 = makeAST(nod->child->next);
                    tempchild = node1;
                    if(tempchild==NULL){
                        tempchild = makeNode(END+100);
                        tempchild->a.treeNode = nod->child->next->next;
                        node1=tempchild;
                    }
                    else{
                        while(tempchild->next!=NULL)
                            tempchild=tempchild->next;
                        tempchild->next = makeNode(END+100);
                        tempchild->next->a.treeNode = nod->child->next->next;
                    }
                    //free(nod->child->next);
                    //free(nod->child);
                    return node1;
                    break;
            case 91:
            case 92:
            case 25:
                    node1 = makeAST(nod->child);
                    node1->next = makeAST(nod->child->next);
                    //free(nod->child->next);
                    //free(nod->child);
                    return node1;
                    break;
            case 42:
            case 54:
            case 57:
            case 93:
            case 99:
            case 26:
                    //free(nod->child);
                    return NULL;
                    break;
            case 43:
            case 63:
            case 44:                                        //CHECK CHECK CHECK CHECK FREE ASSIGNMENTSTMT NODE FROM PARSE TREE IS OKAY RIGHT?
            case 46:
            case 47:
            case 80:
            case 68:
            case 27:
                    node1 = makeAST(nod->child);
                    //free(nod->child);
                    return node1;
                    break;
            case 28:
                    node1 = makeAST(nod->child);
                    //free(nod->child);
                    return node1;
                    break;
            case 29:
                    node1 = makeAST(nod->child);
                    //free(nod->child);
                    return node1;
                    break;
            case 30:
                    node1 = makeAST(nod->child);
                    //free(nod->child);
                    return node1;
                    break;
            case 31:
                    node1 = makeAST(nod->child);
                    //free(nod->child);
                    return node1;
                    break;
            case 32:
                    node1 = makeNode(getValueNode);
                    tempchild = makeNode(parsetreeNode);
                    tempchild->a.treeNode= nod->child->next->next;
                    node1->a.oneChildNode[0] = tempchild;
                    //free(nod->child->next->next->next->next);
                    //free(nod->child->next->next->next);
                    //free(nod->child->next);
                    //free(nod->child);
                    return node1;
                    break;
            case 33:
                    node1 = makeNode(printNode);
                    node1->a.oneChildNode[0] = makeAST(nod->child->next->next);
                    //free(nod->child->next->next->next->next);
                    //free(nod->child->next->next->next);
                    //free(nod->child->next->next);
                    //free(nod->child->next);
                    //free(nod->child);
                    return node1;
                    break;
            case 34:
                    node1 = makeAST(nod->child);
                    //free(nod->child);
                    return node1;
                    break;
            case 35:
                    node1 = makeAST(nod->child);
                    //free(nod->child);
                    return node1;
                    break;
        
            case 38:
                    tempchild = makeNode(parsetreeNode);
                    tempchild->a.treeNode=nod->child;
                    node1 = tempchild;
                    node1->next = makeAST(nod->child->next);
                    //free(nod->child->next);
                    return node1;
                    break;
			case 50:
			case 95:
            case 39:
                   tempchild = makeNode(parsetreeNode);
                   tempchild->a.treeNode=nod->child;
                   return tempchild;                    //CONFIRM CONFIRM CONFIRM CONFIRM CONFIRM
                   break;
            case 40:
                   tempchild = makeNode(parsetreeNode);
                   tempchild->a.treeNode=nod->child;
                   return tempchild;                    //CONFIRM CONFIRM CONFIRM CONFIRM CONFIRM
                   break;
            case 45:
                    node1 = makeNode(assignStmtNode);
                    tempchild = makeNode(parsetreeNode);
                    tempchild->a.treeNode=nod->child;
                    node1->a.twoChildNode[0] = tempchild;
                    node1->a.twoChildNode[1] = makeAST(nod->child->next);
                    //free(nod->child->next);
                    return node1;
                    break;
            case 49:
                    node1 = makeNode(lvalueArrStmtNode);
                    node1->a.twoChildNode[0] = makeAST(nod->child->next);
                    node1->a.twoChildNode[1] = makeAST(nod->child->next->next->next->next);
                    //free(nod->child->next->next->next->next->next);
                    //free(nod->child->next->next->next->next);
                    //free(nod->child->next->next->next);
                    //free(nod->child->next->next);
					//free(nod->child->next);
                    //free(nod->child);
                    return node1;
                    break;
                case 51:
                    tempchild = makeNode(parsetreeNode);
                    tempchild->a.treeNode = nod->child;
                    return tempchild;
                    break;
            case 52:
                    node1 = makeNode(moduleReuseStmtNode);
                    node1->a.threeChildNode[0] = makeAST(nod->child);
                    tempchild = makeNode(parsetreeNode);
                    tempchild->a.treeNode=nod->child->next->next->next;
                    node1->a.threeChildNode[1] = tempchild;
                    node1->a.threeChildNode[2] = makeAST(nod->child->next->next->next->next->next->next);
                    //free(nod->child->next->next->next->next->next->next->next);
                    //free(nod->child->next->next->next->next->next->next);
                    //free(nod->child->next->next->next->next->next);
                    //free(nod->child->next->next->next->next);
                    //free(nod->child->next->next);
                    //free(nod->child->next);
                    //free(nod->child);
                    return node1;
                    break;
            case 53:
                    node1 = makeAST(nod->child->next);
                    //free(nod->child->next->next->next);
                    //free(nod->child->next->next);
                    //free(nod->child->next);
                    //free(nod->child);
                    return node1;
                    break;
            case 55:
                    tempchild = makeNode(parsetreeNode);
                    tempchild->a.treeNode=nod->child;
                    tempchild->next = makeAST(nod->child->next);
                    //free(nod->child->next);
                    return tempchild;
                    break;
            case 56:
                    tempchild = makeNode(parsetreeNode);
                    tempchild->a.treeNode=nod->child->next;
                    tempchild->next = makeAST(nod->child->next->next);
                    //free(nod->child->next->next);
                    //free(nod->child);
                    return tempchild;
                    break;

            //WRITE 58-75 RULES
            case 58:
                    node1 = makeNode(unaryExpressionNode);
                    node1->a.oneChildNode[0] = makeAST(nod->child);
                    //free(nod->child);
                    return node1;
                    break;
            case 59:
                    node1 = makeNode(expressionNode);
                    node1->a.oneChildNode[0] = makeAST(nod->child);
                    //free(nod->child);
                    return node1;
                    break;
            case 60:
                    node1 = makeNode(unaryPlusNode);
                    node1->a.oneChildNode[0] = makeAST(nod->child->next);
                    //free(nod->child->next);
                    //free(nod->child);
                    return node1;
                    break;
            case 61:
                    node1 = makeNode(unaryMinusNode);
                    node1->a.oneChildNode[0] = makeAST(nod->child->next);
                    //free(nod->child->next);
                    //free(nod->child);
                    return node1;
                    break;
            case 75:
            case 64:
            case 67:
            case 71:
                    node1 = makeExpression(nod, NULL);
                    return node1;
                    break;

            case 89:
                    node1 = makeNode(declareStmtNode);
                    node1->a.twoChildNode[0] = makeAST(nod->child->next);
                    node1->a.twoChildNode[1] = makeAST(nod->child->next->next->next);
                    //free(nod->child->next->next->next->next);
                    //free(nod->child->next->next->next);
                    //free(nod->child->next->next);
					//free(nod->child->next);
                    //free(nod->child);
                    return node1;
                    break;
            case 90:
                    node1 = makeNode(conditionalStmtNode);
                    tempchild = makeNode(parsetreeNode);
                    tempchild->a.treeNode=nod->child->next->next;
                    node1->a.threeChildNode[0] = tempchild;
                    node1->a.threeChildNode[1] = makeAST(nod->child->next->next->next->next->next);
                    tempchild = node1->a.threeChildNode[1];
                    while(tempchild->next!=NULL)
                            tempchild=tempchild->next;
                    tempchild->next = makeNode(END+100);
                    tempchild->next->a.treeNode = nod->child->next->next->next->next->next->next->next;
                    node1->a.threeChildNode[2] = makeAST(nod->child->next->next->next->next->next->next);
                    //free(nod->child->next->next->next->next->next->next);
                    //free(nod->child->next->next->next->next->next);
                    //free(nod->child->next->next->next->next);
                    //free(nod->child->next->next->next);
                    //free(nod->child->next);
                    //free(nod->child);
                    return node1;
                    break;
            case 94:
                    node1 = makeNode(caseStmtNode);
                    node1->a.twoChildNode[0]= makeAST(nod->child->next);
                    node1->a.twoChildNode[1]= makeAST(nod->child->next->next->next);
                    //free(nod->child->next->next->next->next->next);
                    //free(nod->child->next->next->next->next);
					//free(nod->child->next->next->next);
                    //free(nod->child->next->next);
                    //free(nod->child->next);
                    //free(nod->child);
                    return node1;
                    break;
            case 98:
                    node1 = makeAST(nod->child->next->next);
					if(node1 == NULL){
						node1=makeNode(emptyDefaultNode);
					}
                    //free(nod->child->next->next->next->next);
                    //free(nod->child->next->next->next);
					//free(nod->child->next->next);
                    //free(nod->child->next);
                    //free(nod->child);
                    return node1;
                    break;
            case 100:
                    node1 = makeNode(forstmtNode);
                    tempchild = makeNode(parsetreeNode);
                    tempchild->a.treeNode=nod->child->next->next;
                    node1->a.threeChildNode[0] = tempchild;
                    node1->a.threeChildNode[1] = makeAST(nod->child->next->next->next->next);
                    node1->a.threeChildNode[2] = makeAST(nod->child->next->next->next->next->next->next->next);
                    tempchild = node1->a.threeChildNode[2];
                    if(tempchild==NULL){
                        tempchild = makeNode(END+100);
                        tempchild->a.treeNode =nod->child->next->next->next->next->next->next->next->next;
                        node1=tempchild;
                    }
                    else{
                        while(tempchild->next!=NULL)
                        tempchild=tempchild->next;
                        tempchild->next = makeNode(END+100);
                        tempchild->next->a.treeNode =nod->child->next->next->next->next->next->next->next->next;
                    }
            //free(nod->child->next->next->next->next->next->next->next);
            //free(nod->child->next->next->next->next->next->next);
                    //free(nod->child->next->next->next->next->next);
                    //free(nod->child->next->next->next->next);
                    //free(nod->child->next->next->next);
                    //free(nod->child->next);
                    //free(nod->child);
                    return node1;
                    break;
            case 101:
                    node1 = makeNode(whileStmtNode);
                    node1->a.twoChildNode[0] = makeAST(nod->child->next->next);
                    node1->a.twoChildNode[1] = makeAST(nod->child->next->next->next->next->next);
                    tempchild = node1->a.twoChildNode[1];
                    if(tempchild==NULL){
                        tempchild = makeNode(END+100);
                        tempchild->a.treeNode = nod->child->next->next->next->next->next->next;
                        node1=tempchild;
                    }
                    else{
                        while(tempchild->next!=NULL)
                        tempchild=tempchild->next;
                        tempchild->next = makeNode(END+100);
                        tempchild->next->a.treeNode = nod->child->next->next->next->next->next->next;
                    }

                    //free(nod->child->next->next->next->next->next);
                    //free(nod->child->next->next->next->next);
                    //free(nod->child->next->next->next);
                    //free(nod->child->next->next);
                    //free(nod->child->next);
                    //free(nod->child);
                    return node1;
                    break;
            case 102:
                    node1 = makeNode(rangeNode);
                    tempchild = makeNode(parsetreeNode);
                    tempchild->a.treeNode=nod->child;
                    node1->a.twoChildNode[0] = tempchild;
                    tempchild1 = makeNode(parsetreeNode);
                    tempchild1->a.treeNode=nod->child->next->next;
                    node1->a.twoChildNode[1] = tempchild1;
                    //free(nod->child->next);
                    return node1;
                    break;
            case 103:
                    node1 = makeNode(range1Node);
                    node1->a.twoChildNode[0] = makeAST(nod->child);
                    node1->a.twoChildNode[1] = makeAST(nod->child->next->next);
                    //free(nod->child->next->next);
                    //free(nod->child->next);
                    //free(nod->child);
                    return node1;
                    break;
            default:
                    printf("Make AST Error/n");
                    return NULL;
                    break;

        }
    }
}

char * gettype (int type){
    switch(type){
    case programNode:
        return "Program Node";
    case logicalOpNode:
        return "Logical Op Node";
    case relationalOpNode:
        return "Relational Op Node";
    case plusNode:
          return "Plus Node";
    case minusNode:
        return "Minus Node";
    case multiplyNode:
        return "Multiply Node";
    case divideNode:
        return "Divide Node";
    case array_datatypeNode:
        return "Array Datatype Node";
    case lvalueArrStmtNode:
        return "Lvalue Arr Stmt Node";
    case rangeNode:
        return "Range Node";
    case range1Node:
        return "Range1 Node";
    case driverModuleNode:
        return "Driver Module Node";
    case unaryExpressionNode:
        return "Unary Expression Node";
    case expressionNode:
        return "Expression Node";
    case unaryPlusNode:
        return "Unary Plus Node";
    case unaryMinusNode:
        return "Unary Minus Node";
    case moduleDeclarationNode:
        return "Module Declaration Node";
    case moduleNode:
           return "Module Node";
    case input_plistNode:
    case input_plist1Node:
        return "Input list Node";
    case output_plistNode:
    case output_plist1Node:
        return "Output list Node";
    case declareStmtNode:
        return "Declare Stmt Node";
    case caseStmtNode:
        return "Case Stmt Node";
    case whileStmtNode:
        return "While Stmt Node";
    case assignStmtNode:
        return "Assign Stmt Node";
    case getValueNode:
        return "GetValue Stmt Node";
    case printNode:
        return "Print Stmt Node";
    case moduleReuseStmtNode:
        return "Module Reuse Stmt Node";
    case conditionalStmtNode:
        return "Conditional Stmt Node";
    case forstmtNode:
        return "For Stmt Node";
    case ID+100:
    case parsetreeNode:
                return "ID";
    case RNUM+100:

                return "RNUM";
    case NUM+100:
                return "NUM";
        
        case REAL+100:
        return "REAL";
        case BOOLEAN+100:
        return "BOOLEAN";
        case TRUET+100:
        return "TRUE";
        case FALSET+100:
        return "FALSE";
        case AND+100:
        return "AND";
        case OR+100:
        return "OR";
        case GT+100:
        return "GT";
        case LT+100:
        return "LT";
        case GE+100:
        return "GE";
        case LE+100:
        return "LE";
        case EQ+100:
        return "EQ";
        case NE+100:
        return "NE";
    case INTEGER+100:
        return "INTEGER";
            case END+100:
                 return "END";
    default:
        return "UNKWOWN";
    }
}
void printAST(AST * head, AST * parent){
    if(head==NULL) {
        return;
    }
  //  printf("Node type: %d\n",head->type);
    switch(head->type){
    case programNode:
        printf("%25s%15s%25s%25s\n",gettype(head->type),"4","N/A","N/A");
        printAST(head->a.fourChildNode[0],head);
        printAST(head->a.fourChildNode[1],head);
        printAST(head->a.fourChildNode[2],head);
        printAST(head->a.fourChildNode[3],head);
        break;
    case logicalOpNode:
    case relationalOpNode:
        printf("%25s%15s%25s%25s\n",gettype(head->type),"3","N/A",gettype(parent->type));
        printAST(head->a.threeChildNode[0],head);
        printAST(head->a.threeChildNode[1],head);
        printAST(head->a.threeChildNode[2],head);
        break;
    case plusNode:
  printf("%25s%15s%25s%25s\n",gettype(head->type),"2","N/A",gettype(parent->type));
                  printAST(head->a.twoChildNode[0],head);
                  printAST(head->a.twoChildNode[1],head);
                  break;
    case minusNode:
                printf("%25s%15s%25s%25s\n",gettype(head->type),"2","N/A",gettype(parent->type));
                  printAST(head->a.twoChildNode[0],head);
                  printAST(head->a.twoChildNode[1],head);
                  break;
    case multiplyNode:
                printf("%25s%15s%25s%25s\n",gettype(head->type),"2","N/A",gettype(parent->type));
                  printAST(head->a.twoChildNode[0],head);
                  printAST(head->a.twoChildNode[1],head);
                  break;
    case divideNode:
             printf("%25s%15s%25s%25s\n",gettype(head->type),"2","N/A",gettype(parent->type));
                  printAST(head->a.twoChildNode[0],head);
                  printAST(head->a.twoChildNode[1],head);
                  break;
    case array_datatypeNode:
            printf("%25s%15s%25s%25s\n",gettype(head->type),"2","N/A",gettype(parent->type));
                  printAST(head->a.twoChildNode[0],head);
                  printAST(head->a.twoChildNode[1],head);
                  break;
    case lvalueArrStmtNode:
           printf("%25s%15s%25s%25s\n",gettype(head->type),"2","N/A",gettype(parent->type));
                  printAST(head->a.twoChildNode[0],head);
                  printAST(head->a.twoChildNode[1],head);
                  break;
    case rangeNode:
           printf("%25s%15s%25s%25s\n",gettype(head->type),"2","N/A",gettype(parent->type));
                  printAST(head->a.twoChildNode[0],head);
                  printAST(head->a.twoChildNode[1],head);
                  break;
    case range1Node:
        printf("%25s%15s%25s%25s\n",gettype(head->type),"2","N/A",gettype(parent->type));
        printAST(head->a.twoChildNode[0],head);
        printAST(head->a.twoChildNode[1],head);
        break;
    case driverModuleNode:
    case unaryExpressionNode:
    case expressionNode:
    case unaryPlusNode:
    case unaryMinusNode:
        printf("%25s%15s%25s%25s\n",gettype(head->type),"1","N/A",gettype(parent->type));
        printAST(head->a.oneChildNode[0],head);
        break;
    case moduleDeclarationNode:
            if(head->next==NULL)
                printf("%25s%15s%25s%25s\n",gettype(head->type),"1","N/A",gettype(parent->type));
            else printf("%25s%15s%25s%25s\n",gettype(head->type),"1",gettype(head->next->type),gettype(parent->type));
        printAST(head->a.oneChildNode[0],head);
        printAST(head->next,head);
        break;
    case moduleNode:
       if(head->next==NULL)
            printf("%25s%15s%25s%25s\n",gettype(head->type),"4","N/A",gettype(parent->type));
        else printf("%25s%15s%25s%25s\n",gettype(head->type),"4",gettype(head->next->type),gettype(parent->type));
        printAST(head->a.fourChildNode[0],head);
        printAST(head->a.fourChildNode[1],head);
        printAST(head->a.fourChildNode[2],head);
        printAST(head->a.fourChildNode[3],head);
        printAST(head->next,head);
        break;
    case input_plistNode:
    case input_plist1Node:
    case output_plistNode:
    case output_plist1Node:
    case declareStmtNode:
    case caseStmtNode:
    case whileStmtNode:
    case assignStmtNode:
        if(head->next==NULL)
            printf("%25s%15s%25s%25s\n",gettype(head->type),"2","N/A",gettype(parent->type));
        else printf("%25s%15s%25s%25s\n",gettype(head->type),"2",gettype(head->next->type),gettype(parent->type));
        printAST(head->a.twoChildNode[0],head);
        printAST(head->a.twoChildNode[1],head);
        printAST(head->next,head);
        break;
    case getValueNode:
    case printNode:
        if(head->next==NULL)
            printf("%25s%15s%25s%25s\n",gettype(head->type),"1","N/A",gettype(parent->type));
        else printf("%25s%15s%25s%25s\n",gettype(head->type),"1",gettype(head->next->type),gettype(parent->type));
        printAST(head->a.oneChildNode[0],head);
        printAST(head->next,head);
        break;

    case moduleReuseStmtNode:
    case conditionalStmtNode:
    case forstmtNode:
        if(head->next==NULL)
            printf("%25s%15s%25s%25s\n",gettype(head->type),"3","N/A",gettype(parent->type));
        else printf("%25s%15s%25s%25s\n",gettype(head->type),"3",gettype(head->next->type),gettype(parent->type));
        printAST(head->a.threeChildNode[0],head);
        printAST(head->a.threeChildNode[1],head);
        printAST(head->a.threeChildNode[2],head);
        printAST(head->next,head);
        break;

    case parsetreeNode:
	     if(head->a.treeNode->tnt == 1 && (head->a.treeNode->value==ID+100 || head->a.treeNode->value==ID)){
		if(head->next==NULL)
                printf("%25s%15s%25s%25s\n",head->a.treeNode->name,"0","N/A",gettype(parent->type));
		else
		printf("%25s%15s%25s%25s\n",head->a.treeNode->name,"0",gettype(head->next->a.treeNode->value),gettype(parent->type));
		}
		else{
            if(head->next==NULL)
                printf("%25s%15s%25s%25s\n",gettype(head->a.treeNode->value),"0","N/A",gettype(parent->type));
            else printf("%25s%15s%25s%25s\n",gettype(head->a.treeNode->value),"0",gettype(head->next->a.treeNode->value),gettype(parent->type));
            }
       // if(head->a.treeNode->tnt == 1 && head->a.treeNode->value==ID){
                printAST(head->next,head);

       // }
        break;


    
        case REAL+100:
        case BOOLEAN+100:
        case TRUET+100:
        case FALSET+100:
        case AND+100:
        case OR+100:
        case GT+100:
        case LT+100:
        case GE+100:
        case LE+100:
        case EQ+100:
        case NE+100:
            case END+100:
    case INTEGER+100:
            printf("%25s%15s%25s%25s\n",gettype(head->type),"0","N/A",gettype(parent->type));
            break;
        
            
    default:
        printf("Node unknown\n");

    }
}
