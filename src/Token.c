#include <stdio.h>
#include "Token.h"
#include <malloc.h>
#include <string.h>
#include "CException.h"
#include "Error.h"
#include "convertValue.h"
#include "GetElement.h"
/*
	This function will generate a token
	
	Input: *tokenizer 		which contain the details of the expression
	Output: none
	return: token 			which carry the type of the token and can be cast to the respective token type structure.
	
	Note: Identifier must obey the rule below:
		1)Must start with number ,under_score(_) or a dot (.).
		2)Must not start with number.
		
*/
Token *getToken (String *tokenizer)
{ 
	int tempNum,i=1; //i is for calculate how many char been tokenize
	//Ignore any space or tab and continue get to details.
	while(tokenizer->rawString[tokenizer->startIndex]==' '||tokenizer->rawString[tokenizer->startIndex]=='\t')
	{
		tokenizer->startIndex ++;
	}
	
	if (isalpha(tokenizer->rawString[tokenizer->startIndex])||(tokenizer->rawString[tokenizer->startIndex])=='.')
	{
		char *name = malloc (tokenizer->length);
		Token *newToken;
		int tempIndex,j=0; //j is for calculate how many char that is belong to identifier
		tempIndex = tokenizer->startIndex;
		
		do
		{
			j++;
			tempIndex++;
		}while(isalnum(tokenizer->rawString[tempIndex])||(tokenizer->rawString[tempIndex]=='.'));
		stringCopy(tokenizer->rawString,name,tokenizer->startIndex,j);
		
		//Check that this identifier is named as low, high or upper.
		newToken=checkIdentifier(name);
		if(newToken!=NULL)
		{
			i=j;
			tokenizer->length-=i;
			tokenizer->startIndex+=i;
			free(name);
			return newToken;
		}
		
	}

	//Check if it is a digit type.
	if(isdigit(tokenizer->rawString[tokenizer->startIndex]))
	{
		//This indicate the error type of identifier which start with number.
		if(isalpha(tokenizer->rawString[tokenizer->startIndex+1]))
		{
			errorMessage. rawString = tokenizer -> rawString;
			errorMessage.position = tokenizer->startIndex;
			errorMessage.message = "Invalid identifier ! ";
			Throw(INVALID_IDENTIFIER);
		}
		
		Number *numToken = malloc(sizeof(Number));
		tempNum=tokenizer->startIndex;
		numToken->value=0;
		
		//Collect all of the integers from string.
		do
		{
			numToken->value =(numToken->value*10)+(tokenizer->rawString[tempNum]-'0');
			tempNum++;
			i++;
			
		}
		while(isdigit(tokenizer->rawString[tempNum]));
		
		i--;
		
		
		numToken->type = NUMBER;
		tokenizer->length-=i;
		tokenizer->startIndex+=i;
		return (Token*)numToken;
	}
	else if (tokenizer->rawString[tokenizer->startIndex]==0)
	{
		return NULL;
	}
	else
	{
		Operator *opeToken ;
		opeToken = detectOperator(tokenizer,i);	
		return (Token*)opeToken;
		
	}
}

/*
	The job of this function is to detect the operation type and return it. 
	
	input:			*tokenizer 	-> which contain the expression and the details
					i			-> contain a value for update tokenizer purpose.
	
	output: 		none
	
	return:			opeToken	-> If it is a valid operator.
					NULL		-> If it is not a valid operator.
*/	
Operator *detectOperator(String *tokenizer, int i)
{	
	Operator *opeToken = malloc(sizeof(Operator));
	switch(tokenizer->rawString[tokenizer->startIndex])
		{
			case '+':
			{
				if(tokenizer->rawString[tokenizer->startIndex+1]=='=')
				{
					i++;
					opeToken->id=ADD_SET_EQUAL;
					opeToken->precedence=10;
					
				}
				else
				{
					opeToken->id=ADD;
					opeToken->precedence=60;
				}
				break;
			}
			case '-':
			{
				if(tokenizer->rawString[tokenizer->startIndex+1]=='=')
				{
					i++;
					opeToken->id=SUBTRACT_SET_EQUAL;
					opeToken->precedence=10;
					
				}
				else
				{
					opeToken->id=SUBTRACT;
					opeToken->precedence=60;
				}
				break;
			}
			case '*':
			{
				if(tokenizer->rawString[tokenizer->startIndex+1]=='=')
				{
					i++;
					opeToken->id=MULTIPLY_SET_EQUAL;
					opeToken->precedence=10;
					
				}
				else
				{
					opeToken->id=MULTIPLY;
					opeToken->precedence=70;
				}
				break;
			}
			case '/':
			{
				if(tokenizer->rawString[tokenizer->startIndex+1]=='=')
				{
					i++;
					opeToken->id=DIVIDE_SET_EQUAL;
					opeToken->precedence=10;
					
				}
				else
				{
					opeToken->id=DIVIDE;
					opeToken->precedence=70;
				}
				break;
			}
			case '%':
			{
				if(tokenizer->rawString[tokenizer->startIndex+1]=='=')
				{
					i++;
					opeToken->id=MODULUS_SET_EQUAL;
					opeToken->precedence=10;
					
				}
				else
				{
					opeToken->id=MODULUS;
					opeToken->precedence=70;
				}
				break;
			}
			case '$':
			{
				opeToken->id=CURRENT_PROGRAM_COUNTER;
				opeToken->precedence=90;
				break;
			}
			case '(':
			{
				opeToken->id=LEFT_PARENTHESIS;
				opeToken->precedence=1;
				break;
			}
			case ')':
			{
				opeToken->id=RIGHT_PARENTHESIS;
				opeToken->precedence=2;
				break;
			}
			case '=':
			{
				if(tokenizer->rawString[tokenizer->startIndex+1]=='=')
				{
					i++;
					opeToken->id=EQUAL_TO;
					opeToken->precedence=40;
				}
				else
				{
					opeToken->id=EQUAL;
					opeToken->precedence=10;
				}
				break;
			}
			case '!':
			{
				if(tokenizer->rawString[tokenizer->startIndex+1]=='=')
				{
					opeToken->id=NOT_EQUAL;
					opeToken->precedence=40;
					i++;
				}
				else
				{
					opeToken->id=LOGIC_NOT;
					opeToken->precedence=80;
				}
				break;
			}
			case '~':
			{
				opeToken->id=COMPLEMENT;
				opeToken->precedence=80;
				break;
			}
			case '>':
			{
				if(tokenizer->rawString[tokenizer->startIndex+1]=='=')
				{	
					opeToken->id=GREATER_EQUAL_THAN;
					opeToken->precedence=40;
					i++;
				}
				else if(tokenizer->rawString[tokenizer->startIndex+1]=='>')
				{
					i++;
					if(tokenizer->rawString[tokenizer->startIndex+2]=='=')
					{	
						opeToken->id=RIGHT_SHIFT_SET_EQUAL;
						opeToken->precedence=10;
						i++;
					}
					else
					{
						opeToken->id=RIGHT_SHIFT;
						opeToken->precedence=50;
					}
				}	
				else
				{
					opeToken->id=GREATER_THAN;
					opeToken->precedence=40;
				}
				break;
			}
			case '<':
			{
				if(tokenizer->rawString[tokenizer->startIndex+1]=='=')
				{	
					opeToken->id=LESS_EQUAL_THAN;
					opeToken->precedence=40;
					i++;
				}
				else if(tokenizer->rawString[tokenizer->startIndex+1]=='<')
				{
					i++;
					if(tokenizer->rawString[tokenizer->startIndex+2]=='=')
					{	
						opeToken->id=LEFT_SHIFT_SET_EQUAL;
						opeToken->precedence=10;
						i++;
					}
					else
					{
						opeToken->id=LEFT_SHIFT;
						opeToken->precedence=50;
					}
				}	
				else
				{
					opeToken->id=LESS_THAN;
					opeToken->precedence=40;
				}
				break;
			}
			case '&':
			{
				if(tokenizer->rawString[tokenizer->startIndex+1]=='&')
				{
					i++;
					opeToken->id = LOGICAL_AND;
					opeToken->precedence=20;
				}
				else if(tokenizer->rawString[tokenizer->startIndex+1]=='=')
				{
					opeToken->id = AND_SET_EQUAL;
					opeToken->precedence=10;
					i++;
				}
				else
				{
					opeToken->id=BITWISE_AND;
					opeToken->precedence=30;
				}
				break;
			}
			case '^':
			{
				if(tokenizer->rawString[tokenizer->startIndex+1]=='=')
				{
					i++;
					opeToken->id = XOR_SET_EQUAL;
					opeToken->precedence=10;
				}
				else
				{
					opeToken->id=BITWISE_XOR;
					opeToken->precedence=30;
				}
				break;
			}
			case '|':
			{
				if(tokenizer->rawString[tokenizer->startIndex+1]=='=')
				{
					i++;
					opeToken->id = OR_SET_EQUAL;
					opeToken->precedence=10;
				}
				else if(tokenizer->rawString[tokenizer->startIndex+1]=='|')
				{
					i++;
					opeToken->id = LOGICAL_OR;
					opeToken->precedence=20;
				}		
				else
				{
					opeToken->id=BITWISE_OR;
					opeToken->precedence=30;
				}
				break;
			}
			default:
			{
				errorMessage.rawString = tokenizer -> rawString;
				errorMessage.position = tokenizer -> startIndex;
				errorMessage.message = "Unknown operator ! ";
				Throw(UNKNOWN_OPERATOR);
				break;
			}
		}
		opeToken->type = OPERATOR;
		tokenizer->length-=i;
		tokenizer->startIndex+=i;
		return opeToken;
		
}

/*
	The purpose of this function is to validate the input string is low , high or upper.
	
	input :
	*name			The identifier(string) that need to be check
	
	output:
	none
	
	return:
	NULL			If it is an invalid identifier
	opeToken		If it is low, high or upper.
	
*/
Token *checkIdentifier(char * name)
{
	char *tempName = malloc(strlen(name)+1);
	int i =0;
	Operator *opeToken = malloc(sizeof(Operator));
	strcpy(tempName,name);
	while(tempName[i]!='\0')
	{
		tempName[i]= toupper(tempName[i]);
		i++;
	}
	if(strcmp("LOW",tempName)==0)
	{
		opeToken->id= LOW;
	}
	else if (strcmp("HIGH",tempName)==0)
	{
		opeToken->id= HIGH;
	}
	else if (strcmp("UPPER",tempName)==0)
	{
		opeToken->id= UPPER;
	}
	else 
	{
		free(tempName);
		return NULL;
	}
	
	opeToken->type=OPERATOR;
	opeToken->precedence=80;
	free(tempName);
	
	return (Token*)opeToken;
	
}
	
/*
	This function will generate a Token from a number.
	
	input :
	number				Carry the number that going to store in a Token.
	
	output:
	none
	
	return:
	(Token*)newToken	The token that generated.
*/
Token *createNumberToken(int number)
{
	Number *newToken = malloc (sizeof(Number));
	newToken->type = NUMBER;
	newToken->value=number;
	
	return (Token*)newToken;
}

/*
	This function will determine token is operator or not.
	
	input :
	unknownToken		The token that consists the type.(number, operator)
	
	output:
	none
	
	return:
	0					indicate it is not an operator
	1					indicate it is an operator
*/
int isOperator (Token * unknownToken)
{
	if(*unknownToken==OPERATOR)
		return 1;
		
	return 0;
}

/*
	This function will determine token is number or not.
	
	input :
	unknownToken		The token that consists the type.(number, operator)
	
	output:
	none
	
	return:
	0					indicate it is not a number
	1					indicate it is a number
*/
int isNumber (Token * unknownToken)
{
	if(*unknownToken==NUMBER)
		return 1;
		
	return 0;
}








