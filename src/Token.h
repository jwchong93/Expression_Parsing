#ifndef __TOKEN_H__
#define __TOKEN_H__
#include "Stack.h"
#include "StringObject.h"




typedef enum {NUMBER,OPERATOR,IDENTIFIER}Token;
//Updating in progress, please be patient.....
typedef enum {XOR_SET_EQUAL,OR_SET_EQUAL,AND_SET_EQUAL,RIGHT_SHIFT_SET_EQUAL,
				LEFT_SHIFT_SET_EQUAL,MODULUS_SET_EQUAL,DIVIDE_SET_EQUAL,
				MULTIPLY_SET_EQUAL,SUBTRACT_SET_EQUAL,ADD_SET_EQUAL,EQUAL,
				LOGICAL_OR,LOGICAL_AND,BITWISE_OR,BITWISE_XOR,BITWISE_AND,
				NOT_EQUAL,EQUAL_TO,LESS_EQUAL_THAN,LESS_THAN,GREATER_THAN,
				GREATER_EQUAL_THAN,RIGHT_SHIFT,LEFT_SHIFT,SUBTRACT,ADD,MODULUS,
				DIVIDE,MULTIPLY,UPPER,HIGH,LOW,COMPLEMENT,LOGIC_NOT,LEFT_PARENTHESIS,
				RIGHT_PARENTHESIS,CURRENT_PROGRAM_COUNTER}OperatorID;

				
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
	OperatorID id;
}Operator;

typedef struct {
	Token type;
	char *name;
}Identifier;


//Global variable
// errorMessage *errMsg=malloc(sizeof(errorMessage));

//Main functions
String *initTokenizer(char *expression);
Token *getToken (String *tokenizer);
//Sub-function
Operator *detectOperator(String *tokenizer, int i);
Token *checkIdentifier(char *name);
//Utility function that help in evaluating the expression in shunting yard part.
Token *createNumberToken(int number);
int isOperator (Token * unknownToken);
int isNumber (Token * unknownToken);
void tryEvaluateThePush(Token *operators, Stack *numberStack , Stack *operatorStack);
#endif //__TOKEN_H__