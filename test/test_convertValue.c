#include "unity.h"
#include "convertValue.h"
#include "Token.h"
#include "StringObject.h"
#include "Error.h"
#include "mock_GetElement.h"
#include <malloc.h>
#include "Error.h"
#include <string.h>

void setUp(){}

void tearDown(){}

void test_updateTheString_should_update_the_string_object_as_defined_by_user()
{
	String *testTokenizer = stringCreate("12+num1");
	String *newTokenizer;
	Token *testToken;
	Number *numToken;
	free(getToken(testTokenizer));
	free(getToken(testTokenizer));
	Identifier *testIdentifier= malloc (sizeof(Identifier));
	testIdentifier->name = malloc (5);
	stringCopy("num1",testIdentifier->name,0,5);
	testIdentifier->type=IDENTIFIER;
	DefineElement element;
	element.ID = "num1";
	element.actualID = "4";
	
	getElement_ExpectAndReturn(DefineList, testIdentifier->name,&element);
	//Now start put the identifier and tokenizer into the function.
	newTokenizer = updateTheString(testTokenizer,testIdentifier->name);
	TEST_ASSERT_EQUAL(1,newTokenizer->length);
	TEST_ASSERT_EQUAL(3,newTokenizer->startIndex);
	//check the string inside the String.
	TEST_ASSERT_EQUAL('1',newTokenizer->rawString[0]);
	TEST_ASSERT_EQUAL('2',newTokenizer->rawString[1]);
	TEST_ASSERT_EQUAL('+',newTokenizer->rawString[2]);
	TEST_ASSERT_EQUAL('4',newTokenizer->rawString[3]);
	TEST_ASSERT_EQUAL_STRING("12+4",newTokenizer->rawString);
	
	//Since the string been recreate try to get token from it until the last of the string.
	testToken = getToken(newTokenizer); //Should be 4.
	TEST_ASSERT_EQUAL(NUMBER,*testToken);
	numToken = (Number*)testToken;
	TEST_ASSERT_EQUAL(NUMBER,numToken->type);
	TEST_ASSERT_EQUAL(4,numToken->value);
	free(numToken);
		
	testToken = getToken(newTokenizer); //Should be NULL.
	TEST_ASSERT_NULL(testToken);
	free(newTokenizer);
	free(testIdentifier);
	free(testTokenizer);
}

void test_updateTheString_should_update_the_string_object_as_defined_by_user_for_longer_expression()
{
	String *testTokenizer = stringCreate("12+num1");
	String *newTokenizer;
	Token *testToken;
	Operator *opeToken;
	Number *numToken;
	free(getToken(testTokenizer));
	free(getToken(testTokenizer));
	Identifier *testIdentifier= malloc (sizeof(Identifier));
	testIdentifier->name = malloc (5);
	stringCopy("num1",testIdentifier->name,0,5);
	testIdentifier->type=IDENTIFIER;
	DefineElement element;
	element.ID = "num1";
	element.actualID = "4+5";
	
	getElement_ExpectAndReturn(DefineList, testIdentifier->name,&element);
	//Now start put the identifier and tokenizer into the function.
	newTokenizer = updateTheString(testTokenizer,testIdentifier->name);
	TEST_ASSERT_EQUAL(3,newTokenizer->length);
	TEST_ASSERT_EQUAL(3,newTokenizer->startIndex);
	//check the string inside the String.
	TEST_ASSERT_EQUAL('1',newTokenizer->rawString[0]);
	TEST_ASSERT_EQUAL('2',newTokenizer->rawString[1]);
	TEST_ASSERT_EQUAL('+',newTokenizer->rawString[2]);
	TEST_ASSERT_EQUAL('4',newTokenizer->rawString[3]);
	TEST_ASSERT_EQUAL('+',newTokenizer->rawString[4]);
	TEST_ASSERT_EQUAL('5',newTokenizer->rawString[5]);
	TEST_ASSERT_EQUAL_STRING("12+4+5",newTokenizer->rawString);
	
	//Since the string been recreate try to get token from it until the last of the string.
	testToken = getToken(newTokenizer); //Should be 4.
	TEST_ASSERT_EQUAL(NUMBER,*testToken);
	numToken = (Number*)testToken;
	TEST_ASSERT_EQUAL(NUMBER,numToken->type);
	TEST_ASSERT_EQUAL(4,numToken->value);
	free(numToken);
	
	testToken = getToken(newTokenizer); //Should be +.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(ADD,opeToken->id);
	free(opeToken);
	
	testToken = getToken(newTokenizer); //Should be 5.
	TEST_ASSERT_EQUAL(NUMBER,*testToken);
	numToken = (Number*)testToken;
	TEST_ASSERT_EQUAL(NUMBER,numToken->type);
	TEST_ASSERT_EQUAL(5,numToken->value);
	free(numToken);
	
	testToken = getToken(newTokenizer); //Should be NULL.
	TEST_ASSERT_NULL(testToken);
	free(newTokenizer);
	free(testIdentifier);
	free(testTokenizer);
}

void test_updateTheString_should_update_the_string_object_if_the_identifier_is_being_in_front_of_the_expression()
{
	String *testTokenizer = stringCreate("num1+12");
	String *newTokenizer;
	Token *testToken;
	Operator *opeToken;
	Number *numToken;
	Identifier *testIdentifier= malloc (sizeof(Identifier));
	testIdentifier->name = malloc (5);
	stringCopy("num1",testIdentifier->name,0,5);
	testIdentifier->type=IDENTIFIER;
	DefineElement element;
	element.ID = "num1";
	element.actualID = "4";
	
	getElement_ExpectAndReturn(DefineList, testIdentifier->name,&element);
	//Now start put the identifier and tokenizer into the function.
	newTokenizer = updateTheString(testTokenizer,testIdentifier->name);
	TEST_ASSERT_EQUAL(4,newTokenizer->length);
	TEST_ASSERT_EQUAL(0,newTokenizer->startIndex);
	//check the string inside the String.
	TEST_ASSERT_EQUAL('4',newTokenizer->rawString[0]);
	TEST_ASSERT_EQUAL('+',newTokenizer->rawString[1]);
	TEST_ASSERT_EQUAL('1',newTokenizer->rawString[2]);
	TEST_ASSERT_EQUAL('2',newTokenizer->rawString[3]);
	TEST_ASSERT_EQUAL_STRING("4+12",newTokenizer->rawString);
	
	//Since the string been recreate try to get token from it until the last of the string.
	testToken = getToken(newTokenizer); //Should be 4.
	TEST_ASSERT_EQUAL(NUMBER,*testToken);
	numToken = (Number*)testToken;
	TEST_ASSERT_EQUAL(NUMBER,numToken->type);
	TEST_ASSERT_EQUAL(4,numToken->value);
	free(numToken);
	
	testToken = getToken(newTokenizer); //Should be +.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(ADD,opeToken->id);
	free(opeToken);
	
	testToken = getToken(newTokenizer); //Should be 12.
	TEST_ASSERT_EQUAL(NUMBER,*testToken);
	numToken = (Number*)testToken;
	TEST_ASSERT_EQUAL(NUMBER,numToken->type);
	TEST_ASSERT_EQUAL(12,numToken->value);
	free(numToken);
		
	testToken = getToken(newTokenizer); //Should be NULL.
	TEST_ASSERT_NULL(testToken);
	free(newTokenizer);
	free(testIdentifier);
	free(testTokenizer);
}

void test_updateTheString_should_update_the_string_object_for_longer_expression_of_user_define_and_a_longer_expression()
{
	String *testTokenizer = stringCreate("num1+12+5+99+89");
	String *newTokenizer;
	Token *testToken;
	Operator *opeToken;
	Number *numToken;
	Identifier *testIdentifier= malloc (sizeof(Identifier));
	testIdentifier->name = malloc (5);
	stringCopy("num1",testIdentifier->name,0,5);
	testIdentifier->type=IDENTIFIER;
	DefineElement element;
	element.ID = "num1";
	element.actualID = "4-99+8-456";
	
	getElement_ExpectAndReturn(DefineList, testIdentifier->name,&element);
	//Now start put the identifier and tokenizer into the function.
	newTokenizer = updateTheString(testTokenizer,testIdentifier->name);
	TEST_ASSERT_EQUAL(21,newTokenizer->length);
	TEST_ASSERT_EQUAL(0,newTokenizer->startIndex);
	//check the string inside the String.
	TEST_ASSERT_EQUAL_STRING("4-99+8-456+12+5+99+89",newTokenizer->rawString);
	
	//Since the string been recreate try to get token from it until the last of the string.
	testToken = getToken(newTokenizer); //Should be 4.
	TEST_ASSERT_EQUAL(NUMBER,*testToken);
	numToken = (Number*)testToken;
	TEST_ASSERT_EQUAL(NUMBER,numToken->type);
	TEST_ASSERT_EQUAL(4,numToken->value);
	free(numToken);
	
	testToken = getToken(newTokenizer); //Should be -.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(SUBTRACT,opeToken->id);
	free(opeToken);
	
	testToken = getToken(newTokenizer); //Should be 99.
	TEST_ASSERT_EQUAL(NUMBER,*testToken);
	numToken = (Number*)testToken;
	TEST_ASSERT_EQUAL(NUMBER,numToken->type);
	TEST_ASSERT_EQUAL(99,numToken->value);
	free(numToken);
	
	testToken = getToken(newTokenizer); //Should be +.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(ADD,opeToken->id);
	free(opeToken);
	
	testToken = getToken(newTokenizer); //Should be 8.
	TEST_ASSERT_EQUAL(NUMBER,*testToken);
	numToken = (Number*)testToken;
	TEST_ASSERT_EQUAL(NUMBER,numToken->type);
	TEST_ASSERT_EQUAL(8,numToken->value);
	free(numToken);
	
	testToken = getToken(newTokenizer); //Should be -.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(SUBTRACT,opeToken->id);
	free(opeToken);
	
	testToken = getToken(newTokenizer); //Should be 456.
	TEST_ASSERT_EQUAL(NUMBER,*testToken);
	numToken = (Number*)testToken;
	TEST_ASSERT_EQUAL(NUMBER,numToken->type);
	TEST_ASSERT_EQUAL(456,numToken->value);
	free(numToken);
	
	testToken = getToken(newTokenizer); //Should be +.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(ADD,opeToken->id);
	free(opeToken);
	
		testToken = getToken(newTokenizer); //Should be 12.
	TEST_ASSERT_EQUAL(NUMBER,*testToken);
	numToken = (Number*)testToken;
	TEST_ASSERT_EQUAL(NUMBER,numToken->type);
	TEST_ASSERT_EQUAL(12,numToken->value);
	free(numToken);
	
	testToken = getToken(newTokenizer); //Should be +.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(ADD,opeToken->id);
	free(opeToken);
	
	testToken = getToken(newTokenizer); //Should be 5.
	TEST_ASSERT_EQUAL(NUMBER,*testToken);
	numToken = (Number*)testToken;
	TEST_ASSERT_EQUAL(NUMBER,numToken->type);
	TEST_ASSERT_EQUAL(5,numToken->value);
	free(numToken);
	
	testToken = getToken(newTokenizer); //Should be +.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(ADD,opeToken->id);
	free(opeToken);
	
	testToken = getToken(newTokenizer); //Should be 99.
	TEST_ASSERT_EQUAL(NUMBER,*testToken);
	numToken = (Number*)testToken;
	TEST_ASSERT_EQUAL(NUMBER,numToken->type);
	TEST_ASSERT_EQUAL(99,numToken->value);
	free(numToken);
	
	testToken = getToken(newTokenizer); //Should be +.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(ADD,opeToken->id);
	free(opeToken);
	
	testToken = getToken(newTokenizer); //Should be 89.
	TEST_ASSERT_EQUAL(NUMBER,*testToken);
	numToken = (Number*)testToken;
	TEST_ASSERT_EQUAL(NUMBER,numToken->type);
	TEST_ASSERT_EQUAL(89,numToken->value);
	free(numToken);
	
	testToken = getToken(newTokenizer); //Should be NULL.
	TEST_ASSERT_NULL(testToken);
	free(newTokenizer);
	free(testIdentifier);
	free(testTokenizer);
}

void test_updateTheString_will_update_the_identifier_when_meet_it()
{
	String *testTokenizer = stringCreate("num1+num2");
	String *newTokenizer;
	Token *testToken;
	Number *numToken;
	Operator *opeToken;
	Identifier *testIdentifier= malloc (sizeof(Identifier));
	testIdentifier->name = malloc (5);
	stringCopy("num1",testIdentifier->name,0,5);
	testIdentifier->type=IDENTIFIER;
	DefineElement element;
	element.ID = "num1";
	element.actualID = "4";
	
	Identifier *testIdentifier1= malloc (sizeof(Identifier));
	testIdentifier1->name = malloc (5);
	stringCopy("num1",testIdentifier1->name,0,5);
	testIdentifier1->type=IDENTIFIER;
	DefineElement element1;
	element1.ID = "num1";
	element1.actualID = "12";
	
	getElement_ExpectAndReturn(DefineList, testIdentifier->name,&element);
	getElement_ExpectAndReturn(DefineList, testIdentifier1->name,&element1);
	//Now start put the identifier and tokenizer into the function.
	newTokenizer = updateTheString(testTokenizer,testIdentifier->name);
	TEST_ASSERT_EQUAL(6,newTokenizer->length);
	TEST_ASSERT_EQUAL(0,newTokenizer->startIndex);
	//check the string inside the String.
	TEST_ASSERT_EQUAL_STRING("4+num2",newTokenizer->rawString);
	
	testToken = getToken(newTokenizer); //Should be 4.
	TEST_ASSERT_EQUAL(NUMBER,*testToken);
	numToken = (Number*)testToken;
	TEST_ASSERT_EQUAL(NUMBER,numToken->type);
	TEST_ASSERT_EQUAL(4,numToken->value);
	free(numToken);
	
	testToken = getToken(newTokenizer); //Should be +.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(ADD,opeToken->id);
	
	
	newTokenizer = updateTheString(newTokenizer,testIdentifier1->name);
	TEST_ASSERT_EQUAL(2,newTokenizer->length);
	TEST_ASSERT_EQUAL(2,newTokenizer->startIndex);
	//check the string inside the String.
	TEST_ASSERT_EQUAL_STRING("4+12",newTokenizer->rawString);
	
	free(opeToken);
	free(newTokenizer);
	free(testIdentifier);
	free(testTokenizer);
}

void test_updateTheString_should_return_NULL_when_the_identifier_is_not_defined()
{
	String *testTokenizer = stringCreate("12+num1");
	String *newTokenizer;
	Token *testToken;
	Number *numToken;
	free(getToken(testTokenizer));
	free(getToken(testTokenizer));
	Identifier *testIdentifier= malloc (sizeof(Identifier));
	testIdentifier->name = malloc (5);
	stringCopy("num1",testIdentifier->name,0,5);
	testIdentifier->type=IDENTIFIER;
	
	getElement_ExpectAndReturn(DefineList, testIdentifier->name,NULL);
	//Now start put the identifier and tokenizer into the function.
	newTokenizer = updateTheString(testTokenizer,testIdentifier->name);
	
	TEST_ASSERT_NULL(newTokenizer);
	free(testIdentifier);
	free(testTokenizer);
}

















