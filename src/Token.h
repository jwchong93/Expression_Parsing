#ifndef __TOKEN_H__
#define __TOKEN_H__

typedef enum {NUMBER,OPERAND,IDENTIFIER}Token;
//Will be update soon.
typedef enum {ADD,SUBTRACT,DIVIDE,MULTIPLY}Operator;

//This structure store the converted version of string
typedef struct {
	char *rawString;
	int  startIndex;
	int length;
}Tokenizer;

//Three type of token needed.
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

Tokenizer *InitTokenizer(char *expression);
#endif //__TOKEN_H__