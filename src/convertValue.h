#ifndef convertValue_H
#define convertValue_H
#include "Token.h"
#include "Iterator.h"
#include "GetElement.h"

typedef enum {CHECKED,UNCHECKED,NEUTRAL}Status;

String* getFromListAndUpdate(String *beforeUpdate, char *name);
String * convertBasedNumberToBase10Number(String *input);

#endif // convertValue_H
