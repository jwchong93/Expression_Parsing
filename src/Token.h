#ifndef __TOKEN_H__
#define __TOKEN_H__

typedef enum {NUMBER,OPERATOR,IDENTIFIER}Token;
//Will be update soon.
typedef enum {CURRENT_PROGRAM_COUNTER,LEFT_PARENTHESIS,RIGHT_PARENTHESIS,LOGIC_NOT,
				NEGATION,NOT_EQUAL,ADD,SUBTRACT,DIVIDE,MULTIPLY,MODULUS,POST_INCREMENT,
				PRE_INCREMENT,POST_DECREMENT,PRE_DECREMENT,EQUAL}Operation;

//Will be update when discuss with bing xuan group.
typedef enum {INVALID_INDENTIFIER,INCOMPLETE_EXPRESSION} Error;

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
	Operation ope;
}Operator;

typedef struct {
	Token type;
	char *name;
}Identifier;

Tokenizer *initTokenizer(char *expression);
Token *getToken (Tokenizer *tokenizer);
void copyString(char *source, char* destination, int startLocation,int length);
Operator *detectOperator(Tokenizer *tokenizer, int i);
#endif //__TOKEN_H__