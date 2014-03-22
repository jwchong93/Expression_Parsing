#ifndef convertValue_H
#define convertValue_H
#include "Token.h"
#include "Iterator.h"
#include "GetElement.h"

Token* convertIdentifierToNumber (LinkedList *list,Identifier *identifier);
int convertBasedNumberToInt(char * anyBaseNumber);

#endif // convertValue_H
