#include <stdio.h>
#include "Token.h"
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/*
	This function will generate a tokenizer
	
	Input: *expression 		which contain the string(expression)
	Output: none
	return: Tokenizer 		which pass to the getToken to generate token.
*/
Tokenizer *initTokenizer(char *expression)
{
	Tokenizer *newTokenizer = malloc (sizeof(Tokenizer));
	newTokenizer->rawString =expression;
	newTokenizer ->startIndex =0;
	newTokenizer ->length =strlen(expression);
	return newTokenizer;
}


/*
	This function will generate a token
	
	Input: *tokenizer 	which contain the details of the expression
	Output: none
	return: token 		which carry the type of the token and can be cast to the respective token type structure.
*/
Token *getToken (Tokenizer *tokenizer)
{ int tempNum,i=1; //i is for calculate how many char been tokenize

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
		Identifier *idenToken = malloc(sizeof(Identifier));
		int tempIndex,j=0; //j is for calculate how many char that is belong to identifier
		char tempChar;
		tempIndex = tokenizer->startIndex;
		idenToken->type=IDENTIFIER;
		idenToken->name = malloc (sizeof(Identifier)*tokenizer->length);
		while(isalnum(tokenizer->rawString[tempIndex]))
		{
			j++;
			tempIndex++;
		}
		copyString(tokenizer->rawString,idenToken->name,tokenizer->startIndex,j);
		i=j;
		return (Token*)idenToken;
	}
	else
	{
		Operator *opeToken = malloc(sizeof(Operator));
		switch(tokenizer->rawString[tokenizer->startIndex])
		{
			case '+':
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
				break;
			}
			case '-':
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
				break;
			}
			default:
			{
				return NULL;
				break;
			}
		}
		opeToken->type = OPERATOR;;
		tokenizer->length-=i;
		tokenizer->startIndex+=i;			
		return (Token*)opeToken;
		
	}
	
}
/*
	input :
	destination 		must be in array to make this work , complicated issue , no explain.
*/
void copyString(char *source,char*destination,int startLocation, int length)
{
	/*
	destination[0]= source[startLocation-1];
	destination[1]= source[startLocation];
	destination[2]= source[startLocation+1];
	destination[3]= source[startLocation+2];
	destination[4]= source[startLocation+3];
	destination[5]= '\0';
	*/
	int i,j=0;
	for (i=0;i<length;i++,j++)
	{
		destination[j]= source[startLocation+i];
	}
	destination[j]='\0';
	

}	