#ifndef __TOKEN_H__
#define __TOKEN_H__

enum Token{NUMBER,OPERAND,IDENTIFIER};
//Will be added soon.
enum Operator {ADD,SUBTRACT,DIVIDE,MULTIPLY};

typedef struct {
	enum Token type;
	int value;
}Number;

typedef struct {
	enum Token type;
	enum Operator ope;
}Operand;

typedef struct {
	enum Token type;
	char *name;
}Identifier;

void Tokenize (char input);
#endif //__TOKEN_H__