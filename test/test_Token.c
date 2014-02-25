#include "unity.h"
#include "Token.h"
#include <malloc.h>

void setUp(){}
void tearDown(){}

void test_initTokenizer_should_initiate_and_return_a_tokenizer_properly()
{
	//Initiate a new tokenizer which will contain the data of 2+3
	Tokenizer *testTokenizer = initTokenizer("2+3");
	TEST_ASSERT_NOT_NULL(testTokenizer);
	TEST_ASSERT_EQUAL_STRING("2+3", testTokenizer->rawString);
	TEST_ASSERT_EQUAL(0,testTokenizer->startIndex);
	TEST_ASSERT_EQUAL(3,testTokenizer->length);
}


/*
This program is use to test the structure behaviour.
For testing purpose.

void test_Playing_with_the_struct()
{
	Tokenizer tokenizer;
	//Try if the string are empty and the program are going to access.
	//printf("The string inside the tokenizer is: %s",tokenizer.rawString);
	//Actually will return an error.

	tokenizer.rawString = "2+3";
	printf("The string inside the tokenizer is: %s\n",tokenizer.rawString);
	//Try to work on the length and also the start index.
	tokenizer.startIndex =0;
	tokenizer.length = 3;
	printf("The startIndex:%d \t The length:%d \n",tokenizer.startIndex,tokenizer.length);
	
	//If the tokenizer is a pointer?
	
	Tokenizer *ptrTokenizer = malloc (sizeof(Tokenizer));
	ptrTokenizer-> rawString ="Hello World ! Nothing here, just want to lengthen this string and observe the effect on the memory";
	ptrTokenizer->startIndex=4567813;
	ptrTokenizer->length = 99999999;
	printf ("String:%s \n Start Index:%d \n Length:%d\n",ptrTokenizer-> rawString,ptrTokenizer->startIndex,ptrTokenizer->length);
	free(ptrTokenizer);
	
}
*/