stage2: newdriver.o codeGeneration.o typeChecker.o symbolTable.o ast.o parser.o lexer.o
	gcc -g -o stage2 newdriver.o codeGeneration.o typeChecker.o symbolTable.o ast.o parser.o lexer.o
newdriver.o : newdriver.c
	gcc -c newdriver.c
codeGeneration.o : codeGeneration.c
	gcc -c codeGeneration.c
typeChecker.o : typeChecker.c
	gcc -c typeChecker.c
symbolTable.o : symbolTable.c
	gcc -c symbolTable.c
ast.o: ast.c
	gcc -c ast.c
parser.o : parser.c
	gcc -c parser.c
lexer.o : lexer.c
	gcc -c lexer.c
clean: 
	rm newdriver.o
	rm codeGeneration.o 
	rm typeChecker.o 
	rm symbolTable.o 
	rm ast.o 
	rm parser.o 
	rm lexer.o 
	rm stage2
	rm Syntax_Errors.txt
	rm ST_Errors.txt
	rm codegen.asm 
	rm codegen.o
	rm a.out
