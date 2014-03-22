#include "StringObject.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

LinkedList *Definelist;

/*
	This function will generate a string
	
	Input: *expression 		which contain the string(expression)
	Output: none
	return: Tokenizer 		which pass to the getToken to generate token.
*/
String *stringCreate(char *expression) {
	int length = strlen(expression);
	String *newString = malloc (sizeof(String));
	char *newRawString = malloc (length+1);
	
	stringCopy(expression, newRawString, 0, length);
	newString->rawString = newRawString;
	newString->startIndex = 0;
	newString->length = strlen(newString->rawString);
	
	return newString;
}

/**
 * Trim out the left space/tab of string
 *
 * Input:
 *	string	word or line of string
 */
void stringLeftTrim(String *string) {
	while(string->rawString[string->startIndex] == ' ' || string->rawString[string->startIndex] == '\t' ) {
		string->startIndex++;
		string->length--;
	}
}

/**
 * Trim out the right space/tab of string
 *
 * Input:
 *	string	word or line of string
 */
void stringRightTrim(String *string) {
	while(string->rawString[string->length - 1] == ' ' || string->rawString[string->length - 1] == '\t') {
		string->length--;
	}
}

/**
 * Get word from a line according to delimiters and update the status of the line (startIndex and length)
 *
 * Input:
 *	line		A line of string
 *	delimiter	Symbol to separate words
 *
 * Return:
 *	word		First word from a line
 */
String *getWordAndUpdate(String *line, char *delimiter) {
	String *word = malloc(sizeof(String));
	int i = 0; // Act as loop counter to avoid access beyond end of string

	stringLeftTrim(line);

	word->rawString = line->rawString;
	word->startIndex = line->startIndex;
	word->length = 0;
	
	i = 0;
	while(i < line->length) {
		if(line->rawString[line->startIndex] != *delimiter) {
			line->startIndex++;
			word->length++;
			i++;
		} else { // line->rawString[line->startIndex] == *delimiter
			if(word->length == 0) {
				line->startIndex++;
				word->startIndex++;
				i++;
			} else {
				break;
			}
		}
	}
	
	line->length = line->length - i;
	
	return word;
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
void stringCopy(char *source, char*destination, int startLocation, int length) {
	int i, j = 0;
	
	for (i = 0; i < length; i++, j++) {
		destination[j]= source[startLocation+i];
	}
	
	destination[j] = '\0';
}