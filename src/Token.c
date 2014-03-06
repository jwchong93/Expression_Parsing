#include <stdio.h>
#include "Token.h"
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "CException.h"

/*
	This function will generate a tokenizer
	
	Input: *expression 		which contain the string(expression)
	Output: none
	return: Tokenizer 		which pass to the getToken to generate token.
*/
Tokenizer *initTokenizer(char *expression)
{
	int i =0, j=0;
	Tokenizer *newTokenizer = malloc (sizeof(Tokenizer));
	char *newString = malloc (strlen(expression)+1);
	copyStringWithoutSpace (expression,newString);
	newTokenizer->rawString=newString;
	newTokenizer ->startIndex =0;
	newTokenizer ->length =strlen(newTokenizer->rawString);
	return newTokenizer;
}


/*
	This function will generate a token
	
	Input: *tokenizer 		which contain the details of the expression
	Output: none
	return: token 			which carry the type of the token and can be cast to the respective token type structure.
	
	Note: Identifier must obey the rule below:
		1)Must start with number ,under_score(_) or a dot (.).
		2)Must not start with number.
		
*/
Token *getToken (Tokenizer *tokenizer)
{ int tempNum,i=1; //i is for calculate how many char been tokenize

	if(isdigit(tokenizer->rawString[tokenizer->startIndex]))
	{
		if(isalpha(tokenizer->rawString[tokenizer->startIndex+1]))
		{
			Throw(INVALID_INDENTIFIER);
			return NULL;
		}
		Number *numToken = malloc(sizeof(Number));
		tempNum=tokenizer->startIndex;
		numToken->value=0;
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
	else if (isalpha(tokenizer->rawString[tokenizer->startIndex])||(tokenizer->rawString[tokenizer->startIndex])=='.')
	{
		Identifier *idenToken = malloc(sizeof(Identifier));
		Token *opeToken;
		int tempIndex,j=0; //j is for calculate how many char that is belong to identifier
		char tempChar;
		tempIndex = tokenizer->startIndex;
		idenToken->type=IDENTIFIER;
		idenToken->name = malloc (sizeof(Identifier)*tokenizer->length);
		do
		{
			j++;
			tempIndex++;
		}while(isalnum(tokenizer->rawString[tempIndex])||(tokenizer->rawString[tempIndex]=='.'));
		copyString(tokenizer->rawString,idenToken->name,tokenizer->startIndex,j);
		i=j;
		tokenizer->length-=i;
		tokenizer->startIndex+=i;
		opeToken=checkIdentifier(idenToken->name);
		if(opeToken!=NULL)
		{
			return opeToken;
		}
		return (Token*)idenToken;
	}
	else
	{
		Operator *opeToken ;
		opeToken = detectOperator(tokenizer,i);			
		return (Token*)opeToken;
		
	}
}
	
	
	
Operator *detectOperator(Tokenizer *tokenizer, int i)
{	
	Operator *opeToken = malloc(sizeof(Operator));
	switch(tokenizer->rawString[tokenizer->startIndex])
		{
			case '+':
			{
				opeToken->ope=ADD;
				break;
			}
			case '-':
			{
				if(isalnum(tokenizer->rawString[tokenizer->startIndex+1])&&
				!(isalnum(tokenizer->rawString[tokenizer->startIndex-1])))
				{
					opeToken->ope=NEGATION;
					break;
				}
				else
				{
					opeToken->ope=SUBTRACT;
					break;
				}
			}
			case '*':
			{
				opeToken->ope=MULTIPLY;
				break;
			}
			case '/':
			{
				opeToken->ope=DIVIDE;
				break;
			}
			case '%':
			{
				opeToken->ope=MODULUS;
				break;
			}
			case '$':
			{
				opeToken->ope=CURRENT_PROGRAM_COUNTER;
				break;
			}
			case '(':
			{
				opeToken->ope=LEFT_PARENTHESIS;
				break;
			}
			case ')':
			{
				opeToken->ope=RIGHT_PARENTHESIS;
				break;
			}
			case '=':
			{
				if(tokenizer->rawString[tokenizer->startIndex+1]=='=')
				{
					i++;
					opeToken->ope=EQUAL_TO;
					break;
				}
				else
				{
					opeToken->ope=EQUAL;
					break;
				}
			}
			case '!':
			{
				if(tokenizer->rawString[tokenizer->startIndex+1]=='=')
				{
					opeToken->ope=NOT_EQUAL;
					i++;
				}
				else
				{
					opeToken->ope=LOGIC_NOT;
				}
				break;
			}
			case '~':
			{
				opeToken->ope=COMPLEMENT;
				break;
			}
			case '>':
			{
				if(tokenizer->rawString[tokenizer->startIndex+1]=='=')
				{	
					opeToken->ope=GREATER_EQUAL_THAN;
					i++;
					break;
				}
				else if(tokenizer->rawString[tokenizer->startIndex+1]=='>')
				{
					i++;
					if(tokenizer->rawString[tokenizer->startIndex+2]=='=')
					{	
						opeToken->ope=RIGHT_SHIFT_SET_EQUAL;
						i++;
						break;
					}
					else
					{
						opeToken->ope=RIGHT_SHIFT;
						break;
					}
				}	
				else
				{
					opeToken->ope=GREATER_THAN;
					break;
				}
			}
			case '<':
			{
				if(tokenizer->rawString[tokenizer->startIndex+1]=='=')
				{	
					opeToken->ope=LESS_EQUAL_THAN;
					i++;
					break;
				}
				else if(tokenizer->rawString[tokenizer->startIndex+1]=='<')
				{
					i++;
					if(tokenizer->rawString[tokenizer->startIndex+2]=='=')
					{	
						opeToken->ope=LEFT_SHIFT_SET_EQUAL;
						i++;
						break;
					}
					else
					{
						opeToken->ope=LEFT_SHIFT;
						break;
					}
				}	
				else
				{
					opeToken->ope=LESS_THAN;
					break;
				}
			}
			default:
			{
				return NULL;
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
	NULL			If it is a valid identifier
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
		opeToken->ope= LOW;
	}
	else if (strcmp("HIGH",tempName)==0)
	{
		opeToken->ope= HIGH;
	}
	else if (strcmp("UPPER",tempName)==0)
	{
		opeToken->ope= UPPER;
	}
	else 
	{
		return NULL;
	}
	
	opeToken->type=OPERATOR;
	
	return (Token*)opeToken;
	
}

/*
	This function is to copy string from the middle of the string for specific length.
	
	input :
	*source				The string that contain the wanted string.
	startLocation		The start location of the wanted string in source
	length 				The length of the wanted string 
	
	output:
	*destination 		The wanted string will be copied to this string.(must be in array to make this work)
	
	return:
	none
*/
void copyString(char *source,char*destination,int startLocation, int length)
{
	int i,j=0;
	for (i=0;i<length;i++,j++)
	{
		destination[j]= source[startLocation+i];
	}
	destination[j]='\0';
	
}	

/*
	This function will copy the string without the space. (Trim space)
	
	input :
	*source				The string that contain the wanted string.
	
	output:
	*destination 		The wanted string will be copied to this string.(must be in array to make this work)
	
	return:
	none
*/
void copyStringWithoutSpace(char *source,char *destination)
{
    int i =0 ,j=0;
	int length = strlen(source);
	for(i=0;i<length;i++)
	{
		if(source[i]!=' '&&source[i]!='\t')
		{		
			destination[j] = source[i];
			j++;
		}
	}
	destination[j]='\0';
	
}

Token *createNumberToken(int number)
{
	Number *newToken = malloc (sizeof(Number));
	newToken->type = NUMBER;
	newToken->value=number;
	
	return (Token*)newToken;
}