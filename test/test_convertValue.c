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
	String *testTokenizer =malloc(sizeof(String));
	testTokenizer->rawString = "12+num1";
	testTokenizer->startIndex = 0;
	testTokenizer->length = 7;
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
	String *testTokenizer =malloc(sizeof(String));
	testTokenizer->rawString = "12+num1";
	testTokenizer->startIndex = 0;
	testTokenizer->length = 7;
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
	
	String *testTokenizer =malloc(sizeof(String));
	testTokenizer->rawString = "num1+12";
	testTokenizer->startIndex = 0;
	testTokenizer->length = 7;
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
	String *testTokenizer =malloc(sizeof(String));
	testTokenizer->rawString = "num1+12+5+99+89";
	testTokenizer->startIndex = 0;
	testTokenizer->length = 15;
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
	String *testTokenizer =malloc(sizeof(String));
	testTokenizer->rawString = "num1+num2";
	testTokenizer->startIndex = 0;
	testTokenizer->length = 9;
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
	stringCopy("num2",testIdentifier1->name,0,5);
	testIdentifier1->type=IDENTIFIER;
	DefineElement element1;
	element1.ID = "num2";
	element1.actualID = "12";
	
	getElement_ExpectAndReturn(DefineList, testIdentifier->name,&element);
	getElement_ExpectAndReturn(DefineList, testIdentifier1->name,&element1);
	//Now start put the identifier and tokenizer into the function.
	testTokenizer = updateTheString(testTokenizer,testIdentifier->name);
	TEST_ASSERT_EQUAL(6,testTokenizer->length);
	TEST_ASSERT_EQUAL(0,testTokenizer->startIndex);
	//check the string inside the String.
	TEST_ASSERT_EQUAL_STRING("4+num2",testTokenizer->rawString);
	
	testToken = getToken(testTokenizer); //Should be 4.
	TEST_ASSERT_EQUAL(NUMBER,*testToken);
	numToken = (Number*)testToken;
	TEST_ASSERT_EQUAL(NUMBER,numToken->type);
	TEST_ASSERT_EQUAL(4,numToken->value);
	free(numToken);
	
	testToken = getToken(testTokenizer); //Should be +.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(ADD,opeToken->id);
	
	
	testTokenizer = updateTheString(testTokenizer,testIdentifier1->name);
	TEST_ASSERT_EQUAL(2,testTokenizer->length);
	TEST_ASSERT_EQUAL(2,testTokenizer->startIndex);
	//check the string inside the String.
	TEST_ASSERT_EQUAL_STRING("4+12",testTokenizer->rawString);
	
	free(opeToken);
	free(testIdentifier);
	free(testTokenizer);
}

void test_updateTheString_should_return_NULL_when_the_identifier_is_not_defined()
{
	
	String *testTokenizer =malloc(sizeof(String));
	testTokenizer->rawString = "12+num1";
	testTokenizer->startIndex = 0;
	testTokenizer->length = 7;
	String *newTokenizer;
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

void test_convertBasedNumberToBase10Number_will_convert_decimal_number_starting_with_d()
{
	int result;
	result = convertBasedNumberToBase10Number("d'100'");
	TEST_ASSERT_EQUAL(100,result);
	//Go with some other longer number.
	result = convertBasedNumberToBase10Number("d'18145613548'");
	TEST_ASSERT_EQUAL(18145613548,result);
	
	//*****Error checking tested in test_throwError.c
}

void test_convertBasedNumberToBase10Number_will_convert_hexadecimal_number_starting_with_h()
{
	int result;
	result = convertBasedNumberToBase10Number("h'100'");
	TEST_ASSERT_EQUAL(256,result);
	//Go with some other longer number.
	result = convertBasedNumberToBase10Number("h'4875'");
	TEST_ASSERT_EQUAL(18549,result);
	
	//Try some value with integer that exceed 9 
	result = convertBasedNumberToBase10Number("h'beef'");
	TEST_ASSERT_EQUAL(48879,result);
	
	result = convertBasedNumberToBase10Number("h'abcdef'");
	TEST_ASSERT_EQUAL(11259375,result);
	//*****Error checking tested in test_throwError.c
}

void test_convertBasedNumberToBase10Number_will_convert_octal_number_starting_with_o()
{
	int result;
	result = convertBasedNumberToBase10Number("o'100'");
	TEST_ASSERT_EQUAL(64,result);
	//Go with some other longer number.
	result = convertBasedNumberToBase10Number("o'4775'");
	TEST_ASSERT_EQUAL(2557,result);
	
	//*****Error checking tested in test_throwError.c
}


void test_convertBasedNumberToBase10Number_will_convert_binary_number_starting_with_o()
{
	int result;
	result = convertBasedNumberToBase10Number("b'100'");
	TEST_ASSERT_EQUAL(4,result);
	//Go with some other longer number.
	result = convertBasedNumberToBase10Number("b'101100101'");
	TEST_ASSERT_EQUAL(357,result);
	
	//*****Error checking tested in test_throwError.c
}
/*
void test_convertBasedNumberToBase10Number_will_convert_hexadecimal_number_end_with_h()
{
	int result;
	result = convertBasedNumberToBase10Number("100h");
	TEST_ASSERT_EQUAL(256,result);
	//Go with some other longer number.
	result = convertBasedNumberToBase10Number("abcdefh");
	TEST_ASSERT_EQUAL(11259375,result);
	
	//*****Error checking tested in test_throwError.c
}
*/

void test_convertBasedNumberToBase10Number_will_convert_hexadecimal_number_starting_with_0x()
{
	int result;
	result = convertBasedNumberToBase10Number("0x1234");
	TEST_ASSERT_EQUAL(4660,result);
	//Go with some other longer number.
	result = convertBasedNumberToBase10Number("0xabcd");
	TEST_ASSERT_EQUAL(43981,result);
	
	//Try some value with integer that exceed 9 
	result = convertBasedNumberToBase10Number("0x1a2c3b");
	TEST_ASSERT_EQUAL(1715259,result);
	
	result = convertBasedNumberToBase10Number("0xaaaa");
	TEST_ASSERT_EQUAL(43690,result);
	//*****Error checking tested in test_throwError.c
}




