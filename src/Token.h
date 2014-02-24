#ifndef __TOKEN_H__
#define __TOKEN_H__

enum {NUMBER,OPERAND,IDENTIFIER}Token;
//Will be added soon.
enum {ADD,SUBTRACT,DIVIDE,MULTIPLY}Operator;

typedef struct {
	Token type;
	int value;
}Number;

typedef struct {
	Token type;
	Operator ope;
}Operand;

typedef struct {
	Token type;
	char *name;
}Identifier;

void Tokenize (char input);
#endif //__TOKEN_H__