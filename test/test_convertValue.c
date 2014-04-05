#include "unity.h"
#include "convertValue.h"
#include "Token.h"
#include "StringObject.h"
#include "Error.h"
#include "mock_GetElement.h"
#include <malloc.h>
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
	newTokenizer = getFromListAndUpdate(testTokenizer,testIdentifier->name);
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
	free(testIdentifier->name);
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
	newTokenizer = getFromListAndUpdate(testTokenizer,testIdentifier->name);
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
	free(testIdentifier->name);
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
	newTokenizer = getFromListAndUpdate(testTokenizer,testIdentifier->name);
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
	free(testIdentifier->name);
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
	newTokenizer = getFromListAndUpdate(testTokenizer,testIdentifier->name);
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
	free(testIdentifier->name);
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
	testTokenizer = getFromListAndUpdate(testTokenizer,testIdentifier->name);
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
	
	
	testTokenizer = getFromListAndUpdate(testTokenizer,testIdentifier1->name);
	TEST_ASSERT_EQUAL(2,testTokenizer->length);
	TEST_ASSERT_EQUAL(2,testTokenizer->startIndex);
	//check the string inside the String.
	TEST_ASSERT_EQUAL_STRING("4+12",testTokenizer->rawString);
	
	free(opeToken);
	free(testIdentifier1->name);
	free(testIdentifier->name);
	free(testIdentifier);
	free(testIdentifier1);
	free(testTokenizer);
}

void test_updateTheString_should_return_NULL_when_the_identifier_is_not_defined()
{
	
	String testTokenizer;
	testTokenizer.rawString = "12+num1";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 7;
	String *newTokenizer;
	free(getToken(&testTokenizer));
	free(getToken(&testTokenizer));
	Identifier testIdentifier;
	testIdentifier.name = malloc (5);
	stringCopy("num1",testIdentifier.name,0,5);
	testIdentifier.type=IDENTIFIER;
	
	getElement_ExpectAndReturn(DefineList, testIdentifier.name,NULL);
	//Now start put the identifier and tokenizer into the function.
	newTokenizer = getFromListAndUpdate(&testTokenizer,testIdentifier.name);
	
	TEST_ASSERT_NULL(newTokenizer);
	free(testIdentifier.name);
}

void test_convertBasedNumberToBase10Number_will_convert_decimal_number_starting_with_d()
{
	String testTokenizer;
	String *testTokenizer1;
	testTokenizer.rawString = "d'100'";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 6;
	testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	TEST_ASSERT_NOT_NULL(testTokenizer1);
	TEST_ASSERT_EQUAL_STRING("100",testTokenizer1->rawString);
	TEST_ASSERT_EQUAL(0,testTokenizer1->startIndex);
	TEST_ASSERT_EQUAL(3,testTokenizer1->length);
	free(testTokenizer1);

	testTokenizer.rawString = "d'1814561'";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 10;
	testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	TEST_ASSERT_EQUAL_STRING("1814561",testTokenizer1->rawString);
	TEST_ASSERT_EQUAL(0,testTokenizer1->startIndex);
	TEST_ASSERT_EQUAL(7,testTokenizer1->length);
	free(testTokenizer1);
	//*****Error checking tested in test_throwError.c
}

void test_convertBasedNumberToBase10Number_will_convert_hexadecimal_number_starting_with_h()
{
	String testTokenizer;
	String *testTokenizer1;
	testTokenizer.rawString = "h'100'";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 6;
	testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	TEST_ASSERT_EQUAL_STRING("256",testTokenizer1->rawString);
	TEST_ASSERT_EQUAL(0,testTokenizer1->startIndex);
	TEST_ASSERT_EQUAL(3,testTokenizer1->length);
	free(testTokenizer1);

	//Go with some other longer number.
	testTokenizer.rawString = "h'4875'";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 7;
	testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	TEST_ASSERT_EQUAL_STRING("18549",testTokenizer1->rawString);
	TEST_ASSERT_EQUAL(0,testTokenizer1->startIndex);
	TEST_ASSERT_EQUAL(5,testTokenizer1->length);
	free(testTokenizer1);

	//Try some value with integer that exceed 9 
	testTokenizer.rawString = "h'beef'";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 7;
	testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	TEST_ASSERT_EQUAL_STRING("48879",testTokenizer1->rawString);
	TEST_ASSERT_EQUAL(0,testTokenizer1->startIndex);
	TEST_ASSERT_EQUAL(5,testTokenizer1->length);
	free(testTokenizer1);

	testTokenizer.rawString = "h'abcdef'";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 9;
	testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	TEST_ASSERT_EQUAL_STRING("11259375",testTokenizer1->rawString);
	TEST_ASSERT_EQUAL(0,testTokenizer1->startIndex);
	TEST_ASSERT_EQUAL(8,testTokenizer1->length);
	free(testTokenizer1);
	//*****Error checking tested in test_throwError.c
	
}

void test_convertBasedNumberToBase10Number_will_convert_octal_number_starting_with_o()
{
	String testTokenizer;
	String *testTokenizer1;
	testTokenizer.rawString = "o'100'";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 6;
	testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	TEST_ASSERT_EQUAL_STRING("64",testTokenizer1->rawString);
	TEST_ASSERT_EQUAL(0,testTokenizer1->startIndex);
	TEST_ASSERT_EQUAL(2,testTokenizer1->length);
	free(testTokenizer1);

	testTokenizer.rawString = "o'4775'";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 7;
	testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	TEST_ASSERT_EQUAL_STRING("2557",testTokenizer1->rawString);
	TEST_ASSERT_EQUAL(0,testTokenizer1->startIndex);
	TEST_ASSERT_EQUAL(4,testTokenizer1->length);
	free(testTokenizer1);
	//*****Error checking tested in test_throwError.c
}


void test_convertBasedNumberToBase10Number_will_convert_binary_number_starting_with_b()
{
	String testTokenizer;
	String *testTokenizer1;
	testTokenizer.rawString = "b'100'";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 6;
	testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	TEST_ASSERT_EQUAL_STRING("4",testTokenizer1->rawString);
	TEST_ASSERT_EQUAL(0,testTokenizer1->startIndex);
	TEST_ASSERT_EQUAL(1,testTokenizer1->length);
	free(testTokenizer1);

	//Go with some other longer number.
	testTokenizer.rawString = "b'101100101'";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 12;
	testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	TEST_ASSERT_EQUAL_STRING("357",testTokenizer1->rawString);
	TEST_ASSERT_EQUAL(0,testTokenizer1->startIndex);
	TEST_ASSERT_EQUAL(3,testTokenizer1->length);
	free(testTokenizer1);
	//*****Error checking tested in test_throwError.c
}
/*
void test_convertBasedNumberToBase10Number_will_convert_hexadecimal_number_end_with_h()
{
	String *testTokenizer =malloc(sizeof(String));
	String *testTokenizer1;
	testTokenizer->rawString = "100h";
	testTokenizer->startIndex = 0;
	testTokenizer->length = 4;
	testTokenizer1 = convertBasedNumberToBase10Number(testTokenizer);
	TEST_ASSERT_EQUAL_STRING("256",testTokenizer1->rawString);
	TEST_ASSERT_EQUAL(0,testTokenizer1->startIndex);
	TEST_ASSERT_EQUAL(3,testTokenizer1->length);
	free(testTokenizer1);
	free(testTokenizer);
}

void test_convertBasedNumberToBase10Number_will_convert_bigger_hexadecimal_number_end_with_h()
{	
	String *testTokenizer =malloc(sizeof(String));
	String *testTokenizer1;
	testTokenizer->rawString = "0abcdefh";
	testTokenizer->startIndex = 0;
	testTokenizer->length = 4;
	//Go with some other longer number.
	testTokenizer1 = convertBasedNumberToBase10Number(testTokenizer);
	TEST_ASSERT_EQUAL_STRING("11259375",testTokenizer1->rawString);
	TEST_ASSERT_EQUAL(0,testTokenizer1->startIndex);
	TEST_ASSERT_EQUAL(8,testTokenizer1->length);
	free(testTokenizer1);
	free(testTokenizer);
	
	//*****Error checking tested in test_throwError.c
}

*/
void test_convertBasedNumberToBase10Number_will_convert_hexadecimal_number_starting_with_0x()
{
	String testTokenizer;
	String *testTokenizer1;
	testTokenizer.rawString = "0x1234";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 6;
	testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	TEST_ASSERT_EQUAL_STRING("4660",testTokenizer1->rawString);
	TEST_ASSERT_EQUAL(0,testTokenizer1->startIndex);
	TEST_ASSERT_EQUAL(4,testTokenizer1->length);
	free(testTokenizer1);

	testTokenizer.rawString = "0xabcd";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 6;
	testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	TEST_ASSERT_EQUAL_STRING("43981",testTokenizer1->rawString);
	TEST_ASSERT_EQUAL(0,testTokenizer1->startIndex);
	TEST_ASSERT_EQUAL(5,testTokenizer1->length);
	free(testTokenizer1);

	testTokenizer.rawString = "0x1a2c3b";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 8;	
	testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	TEST_ASSERT_EQUAL_STRING("1715259",testTokenizer1->rawString);
	TEST_ASSERT_EQUAL(0,testTokenizer1->startIndex);
	TEST_ASSERT_EQUAL(7,testTokenizer1->length);
	free(testTokenizer1);

	testTokenizer.rawString = "0xaaaa";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 6;
	testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	TEST_ASSERT_EQUAL_STRING("43690",testTokenizer1->rawString);
	TEST_ASSERT_EQUAL(0,testTokenizer1->startIndex);
	TEST_ASSERT_EQUAL(5,testTokenizer1->length);
	free(testTokenizer1);
	//*****Error checking tested in test_throwError.c
}




