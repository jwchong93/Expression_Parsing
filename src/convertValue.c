#include "convertValue.h"
#include <malloc.h>
#include "Error.h"
#include <string.h>
#include <stdio.h>
/*
	Convert an identifier to number respectively to the value in linked list.
	Input:
	list		the linked list that carry the name and value of the identifier.
	iterator	iterator which points to the respective linked list.
	identifier	the token that carry the name of the identifier.
	
	return:
	Token that carry the value of the identifier. (Can take out by using type cast.)
*/
Token* convertIdentifierToNumber (LinkedList *list,Iterator *iterator,Identifier *identifier)
{
	DefineElement *newElement;
	Number *newNumberToken = malloc(sizeof(Number));
	newElement = getElement(list,identifier->name);
	if(newElement==NULL)
	{
		return NULL;
	}
	
	newNumberToken->type = NUMBER;
	newNumberToken->value = newElement->value;
	
	
	return (Token*)newNumberToken;
}


int convertBasedNumberToInt(char * anyBaseNumber)
{
	
}