#ifndef __STRING_OBJECT_H__
#define __STRING_OBJECT_H__
#include "Iterator.h"

extern LinkedList *Definelist;
typedef struct {
	char *rawString;
	int startIndex;
	int length;
} String;


String *subString;
extern LinkedList *DefineList;

// Function Prototype
String *stringCreate(char *expression) ;
void stringCopy(char *source, char*destination, int startLocation, int length);

void stringLeftTrim(String* string);
void stringRightTrim(String *string);

String *getWordAndUpdate(String *line, char *delimiter);

#endif // __STRING_OBJECT_H__

 