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
	char* name;
	DefineElement *element1=malloc(sizeof(DefineElement));
	element1->id ="total";
	element1->value=5;
	Token *newToken;

	Identifier identifier;
	identifier.type = IDENTIFIER;
	identifier.name = name;
	getElement_ExpectAndReturn(Definelist,name,element1);
	
	newToken = convertIdentifierToNumber (Definelist,&identifier);
	TEST_ASSERT_EQUAL(NUMBER,*newToken);
	Number * numToken = (Number*) newToken;
	TEST_ASSERT_EQUAL(NUMBER,numToken->type);
	TEST_ASSERT_EQUAL(5,numToken->value);
	
	free(element1);
	free(numToken);
}


void test_convertIdentifierToNumber_should_retrieved_value_for_a_longer_name_of_identifier()
{
	char* name;
	DefineElement *element1=malloc(sizeof(DefineElement));
	element1->id ="thisIsTheNumberThatGoingToDeterminedUsingIterator";
	element1->value=500;
	Token *newToken;
	

	Identifier identifier;
	identifier.type=IDENTIFIER;
	identifier.name = name;
	getElement_ExpectAndReturn(Definelist,name,element1);
	
	newToken = convertIdentifierToNumber (Definelist,&identifier);
	TEST_ASSERT_EQUAL(NUMBER,*newToken);
	Number * numToken = (Number*) newToken;
	TEST_ASSERT_EQUAL(NUMBER,numToken->type);
	TEST_ASSERT_EQUAL(500,numToken->value);
	
	free(element1);
	free(numToken);
}

void test_convertIdentifierToNumber_will_return_NULL_when_the_identifier_is_not_inside_the_linked_list()
{
	char* name;
	Token *newToken;
	Error exception;
	DefineElement *element1 = NULL;
	
	Identifier identifier;
	identifier.type = IDENTIFIER;
	identifier.name = name;
	getElement_ExpectAndReturn(Definelist,name,element1);
	newToken = convertIdentifierToNumber (Definelist,&identifier);
	
	TEST_ASSERT_NULL(newToken);
}























