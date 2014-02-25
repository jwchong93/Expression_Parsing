#include <stdio.h>
#include "Token.h"
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

Tokenizer *initTokenizer(char *expression)
{
	Tokenizer *newTokenizer = malloc (sizeof(Tokenizer));
	newTokenizer->rawString =expression;
	newTokenizer ->startIndex =0;
	newTokenizer ->length =strlen(expression);
	return newTokenizer;
}

Token *getToken (Tokenizer *tokenizer)
{ int tempNum,i=1;

	if(isdigit(tokenizer->rawString[tokenizer->startIndex]))
	{
		Number *numToken = malloc(sizeof(Number));
		numToken->value =atoi (&tokenizer->rawString[tokenizer->startIndex]);
		numToken->type = NUMBER;
		tempNum = numToken->value;
		
		while(tempNum/10!=0)
		{
			tempNum /=10;
			i++;
		}
		tokenizer->length-=i;
		tokenizer->startIndex+=i;
		
		return (Token*)numToken;
	}
	else if (isalpha(tokenizer->rawString[tokenizer->startIndex]))
	{
	}
	else
	{
		Operator *opeToken = malloc(sizeof(Operator));
		if(tokenizer->rawString[tokenizer->startIndex]=='+')
		{
			if(tokenizer->rawString[tokenizer->startIndex+1]=='+'&&tokenizer->length!=0)
			{
				opeToken->ope = POST_INCREMENT;
				i++;
			}
			else if(tokenizer->rawString[tokenizer->startIndex+1]=='+'&&tokenizer->length==0)
			{
				opeToken->ope = PRE_INCREMENT;
				i++;
			}
			else
			{
				opeToken->ope=ADD;
			}
		}
		else if(tokenizer->rawString[tokenizer->startIndex]=='-')
		{
			if(tokenizer->rawString[tokenizer->startIndex+1]=='-'&&tokenizer->length!=0)
			{
				opeToken->ope = POST_DECREMENT;
				i++;
			}
			else if(tokenizer->rawString[tokenizer->startIndex+1]=='-'&&tokenizer->length==0)
			{
				opeToken->ope = PRE_DECREMENT;
				i++;
			}
			else
			{
				opeToken->ope=SUBTRACT;
			}
		}
		opeToken->type = OPERATOR;;
		tokenizer->length-=i;
		tokenizer->startIndex+=i;
		
		return (Token*)opeToken;
	}
	
}
	