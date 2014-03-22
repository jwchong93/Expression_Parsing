#include "unity.h"
#include "convertValue.h"
#include "Token.h"
#include "StringObject.h"
#include "Error.h"
#include "mock_GetElement.h"
#include <malloc.h>
#include "Error.h"

void setUp(){}

void tearDown(){}

void test_convertIdentifierToNumber_should_retrieved_value_from_the_linked_list_through_iterator()
{
	LinkedList *list;
	char* name;
	DefineElement *element1=malloc(sizeof(DefineElement));
	element1->id ="total";
	element1->value=5;
	Token *newToken;
	Iterator *iterator;
	String * testTokenizer = stringCreate("total += number");
	Token *testToken;
	
	testToken = getToken(testTokenizer);
	Identifier *identifier = (Identifier *) testToken;
	identifier->name = name;
	getElement_ExpectAndReturn(list,name,element1);
	
	newToken = convertIdentifierToNumber (list,iterator,identifier);
	TEST_ASSERT_EQUAL(NUMBER,*newToken);
	Number * numToken = (Number*) newToken;
	TEST_ASSERT_EQUAL(NUMBER,numToken->type);
	TEST_ASSERT_EQUAL(5,numToken->value);
	
	free(element1);
	free(numToken);
	free(identifier);
	free(testTokenizer);
}


void test_convertIdentifierToNumber_should_retrieved_value_for_a_longer_name_of_identifier()
{
	LinkedList *list;
	char* name;
	DefineElement *element1=malloc(sizeof(DefineElement));
	element1->id ="thisIsTheNumberThatGoingToDeterminedUsingIterator";
	element1->value=500;
	Token *newToken;
	Iterator *iterator;
	String * testTokenizer = stringCreate("thisIsTheNumberThatGoingToDeterminedUsingIterator+= number");
	Token *testToken;
	
	testToken = getToken(testTokenizer);
	Identifier *identifier = (Identifier *) testToken;
	identifier->name = name;
	getElement_ExpectAndReturn(list,name,element1);
	
	newToken = convertIdentifierToNumber (list,iterator,identifier);
	TEST_ASSERT_EQUAL(NUMBER,*newToken);
	Number * numToken = (Number*) newToken;
	TEST_ASSERT_EQUAL(NUMBER,numToken->type);
	TEST_ASSERT_EQUAL(500,numToken->value);
	
	free(element1);
	free(numToken);
	free(identifier);
	free(testTokenizer);
}

void test_convertIdentifierToNumber_will_return_NULL_when_the_identifier_is_not_inside_the_linked_list()
{
	LinkedList *list;
	char* name;
	Token *newToken;
	Iterator *iterator;
	Error exception;
	String * testTokenizer = stringCreate("MAX5 += number");
	Token *testToken;
	DefineElement *element1 = NULL;
	
	testToken = getToken(testTokenizer);
	Identifier *identifier = (Identifier *) testToken;
	identifier->name = name;
	getElement_ExpectAndReturn(list,name,element1);
	newToken = convertIdentifierToNumber (list,iterator,identifier);
	
	TEST_ASSERT_NULL(newToken);
	free(identifier);
	free(testTokenizer);
}























