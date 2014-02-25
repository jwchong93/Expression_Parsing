#include <stdio.h>
#include "Token.h"
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

Tokenizer *initTokenizer(char *expression)
{
	Tokenizer *newTokenizer = malloc (sizeof(Tokenizer));
	newTokenizer->rawString =expression;
	newTokenizer ->startIndex =0;
	newTokenizer ->length =strlen(expression);
	return newTokenizer;
}
