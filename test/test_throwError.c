#include "unity.h"
#include "Token.h"
#include "CException.h"
#include "StringObject.h"
#include "Stack.h"
#include <malloc.h>
#include "Error.h"
#include "convertValue.h"
#include "mock_GetElement.h"

void setUp () {}
void tearDown () {} 

void test_getToken_will_update_the_error_message_when_it_meet_unknown_operator()
{
	String *testTokenizer = stringCreate ("2@3");
	Token *testToken;
	Error exception;
	free(getToken(testTokenizer)); //2
	Try
	{
	testToken = getToken (testTokenizer);
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(UNKNOWN_OPERATOR,exception);
		
		//Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("2@3",errorMessage.rawString);
		TEST_ASSERT_EQUAL(1,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Unknown operator ! ",errorMessage.message);
		
	}
	free(testTokenizer);
	
}

void test_getToken_will_update_the_error_message_when_it_meet_invalid_identifier()
{
	String *testTokenizer = stringCreate ("5num + 5");
	Token *testToken;
	Error exception;
	Try
	{
		testToken = getToken (testTokenizer);
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_IDENTIFIER,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("5num + 5",errorMessage.rawString);
		TEST_ASSERT_EQUAL(0,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid identifier ! ",errorMessage.message);
		
	}
	free(testTokenizer);
}

void test_getToken_will_update_the_error_message_when_it_meet_unknown_operator_in_different_location()
{
	String *testTokenizer = stringCreate ("5+2,3");
	Token *testToken;
	Error exception;
	free(getToken(testTokenizer));//5
	free(getToken(testTokenizer));//+
	free(getToken(testTokenizer));//2
	Try
	{
		testToken = getToken (testTokenizer);
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(UNKNOWN_OPERATOR,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("5+2,3",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Unknown operator ! ",errorMessage.message);
		
	}
	free(testTokenizer);
}

void test_getToken_throw_an_error_while_the_identifier_is_not_defined()
{
	String *testTokenizer = stringCreate ("pptr+12");
	Token *testToken;
	Error exception;
	char *name = "pptr";
	getElement_ExpectAndReturn(DefineList, name,NULL);
	
	Try
	{
		testToken = getToken (testTokenizer);
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(UNDEFINED_IDENTIFIER,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("pptr+12",errorMessage.rawString);
		TEST_ASSERT_EQUAL(0,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Undefined Identifier ! ",errorMessage.message);
		
	}
	free(testTokenizer);
}

void test_getToken_throw_an_error_while_the_undefined_identifier_is_behind_the_expression()
{
	String *testTokenizer = stringCreate ("12+4*2-45/pptr");
	Token *testToken;
	Error exception;
	char *name = "pptr";
	getElement_ExpectAndReturn(DefineList, name,NULL);
	free(getToken(testTokenizer));//12
	free(getToken(testTokenizer));//+
	free(getToken(testTokenizer));//4
	free(getToken(testTokenizer));//*
	free(getToken(testTokenizer));//2
	free(getToken(testTokenizer));//-
	free(getToken(testTokenizer));//45
	free(getToken(testTokenizer));// /
	
	
	Try
	{
		testToken = getToken (testTokenizer);
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(UNDEFINED_IDENTIFIER,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("12+4*2-45/pptr",errorMessage.rawString);
		TEST_ASSERT_EQUAL(10,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Undefined Identifier ! ",errorMessage.message);
		
	}
	free(testTokenizer);
}
















