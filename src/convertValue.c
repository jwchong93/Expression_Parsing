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
String *getFromListAndUpdate(String *beforeUpdate, char *name)
{
	int stringLength = strlen(beforeUpdate->rawString);
	int length1,length2;
	String *afterUpdate=malloc(sizeof(String));
	DefineElement *tempElement = getElement(DefineList,name);
	if(tempElement == NULL)
	{
		free(afterUpdate);
		return NULL;
	}
	length1 = strlen(tempElement->ID);
	length2 = strlen(tempElement->actualID);
	afterUpdate->rawString = malloc(stringLength-(length1-length2)+1);
	
	//Get the current index.
	afterUpdate->startIndex=beforeUpdate->startIndex;
	//Since the length of the string might be changed, we must refer to the length of the original identifier and the target char
	afterUpdate->length=beforeUpdate->length-(length1-length2);
	
	
	//Copy the previous string into the new string
	stringCopy(beforeUpdate->rawString,afterUpdate->rawString,0,beforeUpdate->startIndex);
	//Copy the found(from element) into the string.
	stringCopy(tempElement->actualID,&(afterUpdate->rawString[beforeUpdate->startIndex]),0,length2);
	//Copy the remaining string into it.
	stringCopy(beforeUpdate->rawString,
			&(afterUpdate->rawString[beforeUpdate->startIndex+length2]),
			beforeUpdate->startIndex + length1,
			beforeUpdate->length-(beforeUpdate->startIndex + length1));
	
	beforeUpdate->rawString="";
	free(beforeUpdate->rawString);
	free(beforeUpdate);

	return afterUpdate;
	

}

String *convertBasedNumberToBase10Number(String *input)
{
	int i =input->startIndex,j=0,result=0;
	String *afterUpdate = malloc(sizeof(String));
	char *string;
	int tempResult,stringLength,length1,length2;
	if(input->rawString[i] == 100 )//ASCII d = 100
	{
		i++;
		if(input->rawString[i]==39)//ASCII ' = 39
		{
			i++;
			while(isdigit(input->rawString[i]))
			{
				result =(result*10)+(input->rawString[i]-'0');
				i++;
			}
			
		}
		if(input->rawString[i]!=39)
		{
			errorMessage.rawString = input->rawString;
			errorMessage.position = i;
			errorMessage.message = "Invalid expression ! ";
			Throw(INVALID_EXPRESSION);
		}

	}
	else if(input->rawString[i] == 104 )//ASCII h = 104
	{
		i++;
		if(input->rawString[i]==39)//ASCII ' = 39
		{
			i++;
			while(isdigit(input->rawString[i])||(input->rawString[i]>=97&&input->rawString[i]<=102))
			{
				j++;
				i++;
			}
			for(;j>0;j--)
			{
				if(isalpha(input->rawString[i-j]))
				{
					result += (input->rawString[i-j]-87)* (int)(pow(16,j-1));
				}
				else
				{
					result += (input->rawString[i-j]-'0')* (int)(pow(16,j-1));
				}
			}
			
		}
		if(input->rawString[i]!=39)
		{
			errorMessage.rawString = input->rawString;
			errorMessage.position = i;
			errorMessage.message = "Invalid expression ! ";
			Throw(INVALID_EXPRESSION);
		}
	}
	else if(input->rawString[i] == 111 )//ASCII o = 111
	{
		i++;
		if(input->rawString[i]==39)//ASCII ' = 39
		{
			i++;
			while(input->rawString[i]>=48&&input->rawString[i]<=55)
			{
				j++;
				i++;
				
			}
			for(;j>0;j--)
			{
				result += (input->rawString[i-j]-'0')* (int)(pow(8,j-1));
			}
		}
		if(input->rawString[i]!=39)
		{
			errorMessage.rawString = input->rawString;
			errorMessage.position = i;
			errorMessage.message = "Invalid expression ! ";
			Throw(INVALID_EXPRESSION);
		}
	}
	else if(input->rawString[i] == 98 )//ASCII b = 98
	{
		i++;
		if(input->rawString[i]==39)//ASCII ' = 39
		{
			i++;
			while(input->rawString[i]==48||input->rawString[i]==49)
			{
				j++;
				i++;		
			}
			for(;j>0;j--)
			{
				result += (input->rawString[i-j]-'0')* (int)(pow(2,j-1));
			}
		}
		if(input->rawString[i]!=39)
		{
			errorMessage.rawString = input->rawString;
			errorMessage.position = i;
			errorMessage.message = "Invalid expression ! ";
			Throw(INVALID_EXPRESSION);
		}
	}
/*	else if (isdigit(input->rawString[i]))
	{
		while(isdigit(input->rawString[i])||(input->rawString[i]>=97&&input->rawString[i]<=102))
		{
			j++;
			i++;
		}
		if(input->rawString[i]!=104)
		{
			errorMessage.rawString = input->rawString;
			errorMessage.position = i;
			errorMessage.message = "Invalid expression ! ";
			Throw(INVALID_EXPRESSION);
		}
		for(;j>0;j--)
		{
			if(isalpha(input->rawString[i-j]))
			{
				result += (input->rawString[i-j]-87)* (int)(pow(16,j-1));
			}
			else
			{
				result += (input->rawString[i-j]-'0')* (int)(pow(16,j-1));
			}
		}
	}*/
	else if(input->rawString[i] == 48 )//ASCII 0 = 48
	{
		i++;
		if(input->rawString[i]==120)//ASCII x = 120
		{
			i++;
			while(isdigit(input->rawString[i])||(input->rawString[i]>=97&&input->rawString[i]<=102))
			{
				j++;
				i++;
			}
			for(;j>0;j--)
			{
				if(isalpha(input->rawString[i-j]))
				{
					result += (input->rawString[i-j]-87)* (int)(pow(16,j-1));
				}
				else
				{
					result += (input->rawString[i-j]-'0')* (int)(pow(16,j-1));
				}
			}
		}
		else
		{
			result =0;
		}
		if(input->rawString[i]!=0)
		{
			errorMessage.rawString = input->rawString;
			errorMessage.position = i;
			errorMessage.message = "Invalid expression ! ";
			Throw(INVALID_EXPRESSION);
		}
	i--;
	}
	else 
	{
		return NULL;
	}
	if(result!=0)
	{
		tempResult = result;
		j=0;
		while(tempResult!=0)
		{
			j++;
			tempResult=tempResult/10;
		}
		
		string = malloc(j);
		sprintf(string,"%d",result);
		
		length1 = ++i - input->startIndex;
		length2 = strlen(string);
		stringLength = strlen(input->rawString);
		afterUpdate->rawString = malloc(stringLength-(length1-length2)+1);
		

			//Copy the previous string into the new string
			stringCopy(input->rawString,afterUpdate->rawString,0,input->startIndex);
			//Copy the found(from element) into the string.
			stringCopy(string,&(afterUpdate->rawString[input->startIndex]),0,length2);
			//Copy the remaining string into it.
			stringCopy(input->rawString,
						&(afterUpdate->rawString[input->startIndex+length2]),
						input->startIndex + length1,
						input->length-(input->startIndex + length1));
						
		afterUpdate->length = stringLength-(length1-length2);
		afterUpdate->startIndex=input->startIndex;
		
		free(input->rawString);
		free(string);
		free(input);
		
		return afterUpdate;
	}
	else
	{
		return input;
	}
	
}
















