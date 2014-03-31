#include "convertValue.h"
#include <malloc.h>
#include "Error.h"
#include <string.h>
#include <stdio.h>
#include "StringObject.h"
#include "GetElement.h"
#include <math.h>
/*
	Convert an identifier to number respectively to the value in linked list.
	Input:
	list		the linked list that carry the name and value of the identifier.
	iterator	iterator which points to the respective linked list.
	identifier	the token that carry the name of the identifier.
	
	return:
	Token that carry the value of the identifier. (Can take out by using type cast.)
*/
String *updateTheString(String *beforeUpdate, char *name)
{
	int counter=0;
	int stringLength = strlen(beforeUpdate->rawString);
	int length1,length2;
	String *afterUpdate=malloc(sizeof(String));
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
	
	
	free(beforeUpdate->rawString);
	free(beforeUpdate);

	return afterUpdate;
	

}

int convertBasedNumberToBase10Number(char *input)
{
	int i =0,j=0,result=0;
	if(input[i] == 100 )//ASCII d = 100
	{
		i++;
		if(input[i]==39)//ASCII ' = 39
		{
			i++;
			while(isdigit(input[i]))
			{
				result =(result*10)+(input[i]-'0');
				i++;
				
			}
			
		}
		if(input[i]!=39)
		{
			errorMessage.rawString = input;
			errorMessage.position = i;
			errorMessage.message = "Invalid expression ! ";
			Throw(INVALID_EXPRESSION);
		}
	}
	else if(input[i] == 104 )//ASCII h = 104
	{
		i++;
		if(input[i]==39)//ASCII ' = 39
		{
			i++;
			while(isdigit(input[i])||(input[i]>=97&&input[i]<=102))
			{
				j++;
				i++;
			}
			for(;j>0;j--)
			{
				if(isalpha(input[i-j]))
				{
					result += (input[i-j]-87)* (int)(pow(16,j-1));
				}
				else
				{
					result += (input[i-j]-'0')* (int)(pow(16,j-1));
				}
			}
			
		}
		if(input[i]!=39)
		{
			errorMessage.rawString = input;
			errorMessage.position = i;
			errorMessage.message = "Invalid expression ! ";
			Throw(INVALID_EXPRESSION);
		}
	}
	else if(input[i] == 111 )//ASCII o = 111
	{
		i++;
		if(input[i]==39)//ASCII ' = 39
		{
			i++;
			while(input[i]>=48&&input[i]<=55)
			{
				j++;
				i++;
				
			}
			for(;j>0;j--)
			{
				result += (input[i-j]-'0')* (int)(pow(8,j-1));
			}
		}
		if(input[i]!=39)
		{
			errorMessage.rawString = input;
			errorMessage.position = i;
			errorMessage.message = "Invalid expression ! ";
			Throw(INVALID_EXPRESSION);
		}
	}
	else if(input[i] == 98 )//ASCII b = 98
	{
		i++;
		if(input[i]==39)//ASCII ' = 39
		{
			i++;
			while(input[i]==48||input[i]==49)
			{
				j++;
				i++;
				
			}
			for(;j>0;j--)
			{
				result += (input[i-j]-'0')* (int)(pow(2,j-1));
			}
		}
		if(input[i]!=39)
		{
			errorMessage.rawString = input;
			errorMessage.position = i;
			errorMessage.message = "Invalid expression ! ";
			Throw(INVALID_EXPRESSION);
		}
	}
	else if(input[i] == 48 )//ASCII 0 = 48
	{
		i++;
		if(input[i]==120)//ASCII ' = 120
		{
			i++;
			while(isdigit(input[i])||(input[i]>=97&&input[i]<=102))
			{
				j++;
				i++;
			}
			for(;j>0;j--)
			{
				if(isalpha(input[i-j]))
				{
					result += (input[i-j]-87)* (int)(pow(16,j-1));
				}
				else
				{
					result += (input[i-j]-'0')* (int)(pow(16,j-1));
				}
			}
		}
		if(input[i]!=0)
		{
			errorMessage.rawString = input;
			errorMessage.position = i;
			errorMessage.message = "Invalid expression ! ";
			Throw(INVALID_EXPRESSION);
		}
	}
	/*
	else if ((input[i]>=97&&input[i]<102)||isdigit(input[i]))
	{
		while(isdigit(input[i])||(input[i]>=97&&input[i]<=102))
		{
			j++;
			i++;
		}
		if(input[i]!=104)
		{
			errorMessage.rawString = input;
			errorMessage.position = i;
			errorMessage.message = "Invalid expression ! ";
			Throw(INVALID_EXPRESSION);
		}
		for(;j>0;j--)
		{
			if(isalpha(input[i-j]))
			{
				result += (input[i-j]-87)* (int)(pow(16,j-1));
			}
			else
			{
				result += (input[i-j]-'0')* (int)(pow(16,j-1));
			}
		}
	}
	*/
	return result;
}
















