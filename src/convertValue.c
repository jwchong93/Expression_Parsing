#include "convertValue.h"
#include <malloc.h>
#include "Error.h"
#include <string.h>
#include <stdio.h>
#include "StringObject.h"
#include "GetElement.h"
/*
	Convert an identifier to number respectively to the value in linked list.
	Input:
	list		the linked list that carry the name and value of the identifier.
	iterator	iterator which points to the respective linked list.
	identifier	the token that carry the name of the identifier.
	
	return:
	Token that carry the value of the identifier. (Can take out by using type cast.)
*/
String* updateTheString(String *beforeUpdate, char *name)
{
	int counter=0;
	int stringLength = strlen(beforeUpdate->rawString);
	int length1,length2;
	String *afterUpdate = malloc(sizeof(String));
	DefineElement *tempElement = getElement(DefineList,name);
	if(tempElement == NULL)
	{
		return NULL;
	}
	length1 = strlen(tempElement->ID);
	length2 = strlen(tempElement->actualID);
	afterUpdate->rawString = malloc(stringLength-(length1-length2));
	
	//Get the current index.
	afterUpdate->startIndex=beforeUpdate->startIndex;
	//Since the length of the string might be changed, we must refer to the length of the original identifier and the target char
	afterUpdate->length=beforeUpdate->length-(length1-length2);
	
	
	//Copy the previous string into the new string
	stringCopy(beforeUpdate->rawString,afterUpdate->rawString,0,beforeUpdate->startIndex);
	//Copy the found(from element) into the string.
	stringCopy(tempElement->actualID,&(afterUpdate->rawString[beforeUpdate->startIndex]),0,length2);
	//Copy the remaining string into it.
	stringCopy(beforeUpdate->rawString,&(afterUpdate->rawString[beforeUpdate->startIndex+length2]),beforeUpdate->startIndex + length1,afterUpdate->length-length2);
	
	
	free(beforeUpdate);
	return afterUpdate;
	

}