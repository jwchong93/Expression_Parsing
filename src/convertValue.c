#include "convertValue.h"
#include <malloc.h>
Token* convertIdentifierToNumber (LinkedList *list,Iterator *iterator,Identifier *identifier)
{
	DefineElement *newElement;
	Number *newNumberToken = malloc(sizeof(Number));
	newElement = getElement(list,identifier->name);
	newNumberToken->type = NUMBER;
	newNumberToken->value = newElement->value;
	
	return (Token*)newNumberToken;
}
