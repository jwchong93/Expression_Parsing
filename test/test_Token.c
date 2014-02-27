#include "unity.h"
#include "Token.h"
#include <malloc.h>
#include <string.h>
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
	
	//Try a longer expression
	testTokenizer = initTokenizer("2+3*8+8");
	TEST_ASSERT_NOT_NULL(testTokenizer);
	TEST_ASSERT_EQUAL_STRING("2+3*8+8", testTokenizer->rawString);
	TEST_ASSERT_EQUAL(0,testTokenizer->startIndex);
	TEST_ASSERT_EQUAL(7,testTokenizer->length);
}

void test_getToken_should_return_the_token_by_sequence()
{
	Number *testNum;
	Operator *testOpe;
	Token *testToken=NULL;
	Tokenizer *testTokenizer = initTokenizer("2+3");
	
	//Get the first token which is 2 and test the length and startIndex of tokenizer.
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(2,testTokenizer->length);
	TEST_ASSERT_EQUAL(1,testTokenizer->startIndex);
	
	//Cast the returned token type address to the respective type and test the data contained.
	TEST_ASSERT_EQUAL(NUMBER,*testToken);
	testNum = (Number *) testToken;
	TEST_ASSERT_EQUAL(NUMBER,testNum->type);
	TEST_ASSERT_EQUAL(2,testNum->value);
	
	//Get the second token which is + and test the length and startIndex.
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(1,testTokenizer->length);
	TEST_ASSERT_EQUAL(2,testTokenizer->startIndex);
	
	//Test the token type that accepted and cast it back to it respective type and test.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	testOpe = (Operator *) testToken;
	TEST_ASSERT_EQUAL(OPERATOR,testOpe->type);
	TEST_ASSERT_EQUAL(ADD,testOpe->ope);
	
	//Get the last token which is 3 an1d test the length and startIndex.
	testToken=getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(0,testTokenizer->length);
	TEST_ASSERT_EQUAL(3,testTokenizer->startIndex);
	
	//Test the returned token type.
	TEST_ASSERT_EQUAL(NUMBER, *testToken);
	testNum = (Number*)testToken;
	TEST_ASSERT_EQUAL(NUMBER,testNum->type);
	TEST_ASSERT_EQUAL(3,testNum->value);
	
	//Continue getToken even the token all been retrived
	testToken=getToken(testTokenizer);
	TEST_ASSERT_NULL(testToken);
	TEST_ASSERT_EQUAL(0,testTokenizer->length);
	TEST_ASSERT_EQUAL(3,testTokenizer->startIndex);
}

void test_getToken_should_indentify_the_identifier_consist_in_the_expression()
{
	Identifier *IdenToken;
	Token *testToken=NULL;
	Tokenizer *testTokenizer = initTokenizer("2+MAX5-4");
	
	//Since previous test had tested how to return 2 and + lets skip the test
	testToken = getToken(testTokenizer);
	testToken = getToken(testTokenizer);
	
	//This getToken should return an identifier token address.
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(IDENTIFIER,*testToken);
	IdenToken = (Identifier*)testToken;
	TEST_ASSERT_EQUAL_STRING("MAX5",IdenToken->name);

	
}


void test_getToken_should_identifier_the_number_that_is_more_than_10()
{
	Tokenizer *testTokenizer = initTokenizer("25-456");
	//Get the first token out from the tokenizer.
	Token *testToken = getToken(testTokenizer);
	//Test the tokenizer will be updated as expected.
	TEST_ASSERT_EQUAL(2,testTokenizer->startIndex);
	TEST_ASSERT_EQUAL(4,testTokenizer->length);
	//Check the type of the token that been returned.
	TEST_ASSERT_EQUAL(NUMBER,*testToken);
	Number *testNum = (Number*) testToken;
	//Test the data inside the Token.
	TEST_ASSERT_EQUAL(25,testNum->value);
	//Get the next token.
	testToken = getToken(testTokenizer);
	TEST_ASSERT_EQUAL(3,testTokenizer->startIndex);
	TEST_ASSERT_EQUAL(3,testTokenizer->length);
	//It should be operator type
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *testOpe = (Operator*) testToken;
	TEST_ASSERT_EQUAL(SUBTRACT,testOpe->ope);
	//Continue get the token
	testToken = getToken(testTokenizer);
	TEST_ASSERT_EQUAL(6,testTokenizer->startIndex);
	TEST_ASSERT_EQUAL(0,testTokenizer->length);
	//It should be operator type
	TEST_ASSERT_EQUAL(NUMBER,*testToken);
	testNum = (Number*) testToken;
	TEST_ASSERT_EQUAL(456,testNum->value);
	//Make sure the getToken will return NULL while there is no more token to be return 
	testToken = getToken(testTokenizer);
	TEST_ASSERT_EQUAL(NULL,testToken);
}
void test_copyString_should_copy_the_string_from_source_to_destination()
{
	char * newString ="Hello World!!!!";
	char * stringGet = malloc (sizeof(char)*(strlen(newString)));
	
	//Start From the location 6 and the size is 5
	copyString (newString,stringGet,6,5);
	
	TEST_ASSERT_EQUAL('W',stringGet[0]);
	TEST_ASSERT_EQUAL('o',stringGet[1]);
	TEST_ASSERT_EQUAL('r',stringGet[2]);
	TEST_ASSERT_EQUAL('l',stringGet[3]);
	TEST_ASSERT_EQUAL('d',stringGet[4]);
	TEST_ASSERT_EQUAL_STRING("World",stringGet);


}

/*
This is the testing program for the casting.
After we get the address after a casting , we need to cast it back to his original type
so that we can access to the member inside this structure.

void test_something_about_type_casting()
{
	Token *newToken;
	Number *newNumber=malloc(sizeof(Number));
	newNumber->type = NUMBER;
	newNumber->value = 8;
	newToken = (Token *)newNumber;
	newNumber= (Number *)newToken;
	printf("Type:%d,Value:%d\n",newNumber->type,newNumber->value);
	printf("The type of the token: %d\n",*newToken);
	
}


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