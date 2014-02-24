#include <stdio.h>
#include "Token.h"
#include <malloc.h>
#include <stdlib.h>
Token Identify (char input)
{
	Token type;
	if(isdigit(input))
		type=NUMBER;
	else if(isalpha(input))
		type=IDENTIFIER;
	else
		type=OPERAND;
	return type;
}