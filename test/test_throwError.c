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
	String *testTokenizer =malloc(sizeof(String));
	testTokenizer->rawString = "5num + 5";
	testTokenizer->startIndex = 0;
	testTokenizer->length = 7;
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

void test_convertBasedNumberToBase10Number_will_throw_error_when_a_space_is_or_other_unwanted_simbol_inside_the_decimal_expression()
{
	int result;
	Error exception;
	Try
	{
		result = convertBasedNumberToBase10Number("d'1 00'");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("d'1 00'",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	
	
	//Make sure this will work for longer expression.
	Try
	{
		result = convertBasedNumberToBase10Number("d'1456781 00'");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("d'1456781 00'",errorMessage.rawString);
		TEST_ASSERT_EQUAL(9,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	//Since it is work , c whether work for other symbol
	Try
	{
		result = convertBasedNumberToBase10Number("d'1@00'");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("d'1@00'",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	
	Try
	{
		result = convertBasedNumberToBase10Number("d'1$00'");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("d'1$00'",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	
	Try
	{
		result = convertBasedNumberToBase10Number("d'1=00'");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("d'1=00'",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
}

void test_convertBasedNumberToBase10Number_will_throw_error_when_a_space_is_or_other_unwanted_simbol_inside_the_hexadecimal_expression()
{
	int result;
	Error exception;
	Try
	{
		result = convertBasedNumberToBase10Number("h'1 00'");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("h'1 00'",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	
	
	//Make sure this will work for longer expression.
	Try
	{
		result = convertBasedNumberToBase10Number("h'1456781 00'");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("h'1456781 00'",errorMessage.rawString);
		TEST_ASSERT_EQUAL(9,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	//Since it is work , c whether work for other symbol
	Try
	{
		result = convertBasedNumberToBase10Number("h'1@00'");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("h'1@00'",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	
	Try
	{
		result = convertBasedNumberToBase10Number("h'1$00'");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("h'1$00'",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	
	Try
	{
		result = convertBasedNumberToBase10Number("h'1=00'");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("h'1=00'",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
}

void test_convertBasedNumberToBase10Number_will_throw_error_when_a_space_is_or_other_unwanted_simbol_inside_the_octal_expression()
{
	int result;
	Error exception;
	Try
	{
		result = convertBasedNumberToBase10Number("o'1 00'");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("o'1 00'",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	Try
	{
		result = convertBasedNumberToBase10Number("o'1800'");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("o'1800'",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	Try
	{
		result = convertBasedNumberToBase10Number("o'1900'");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("o'1900'",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	Try
	{
		result = convertBasedNumberToBase10Number("o'1a00'");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("o'1a00'",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
}
/*
void test_convertBasedNumberToBase10Number_will_throw_error_when_a_space_is_or_other_unwanted_simbol_inside_the_hexadecimal_expression_end_with_h()
{
	int result;
	Error exception;
	Try
	{
		result = convertBasedNumberToBase10Number("c0ffee h");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("c0ffee h",errorMessage.rawString);
		TEST_ASSERT_EQUAL(6,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	Try
	{
		result = convertBasedNumberToBase10Number("c0ffeekh");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("c0ffeekh",errorMessage.rawString);
		TEST_ASSERT_EQUAL(6,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	
	Try
	{
		result = convertBasedNumberToBase10Number("c0ffeek");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("c0ffeek",errorMessage.rawString);
		TEST_ASSERT_EQUAL(6,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	Try
	{
		result = convertBasedNumberToBase10Number("c0ffeey");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("c0ffeey",errorMessage.rawString);
		TEST_ASSERT_EQUAL(6,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	
}
*/
void test_convertBasedNumberToBase10Number_will_throw_error_when_a_space_is_or_other_unwanted_simbol_inside_the_hexadecimal_expression_star_with_0x()
{
	int result;
	Error exception;
	Try
	{
		result = convertBasedNumberToBase10Number("0x1 00");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("0x1 00",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	
	
	//Make sure this will work for longer expression.
	Try
	{
		result = convertBasedNumberToBase10Number("0x1456781 00");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("0x1456781 00",errorMessage.rawString);
		TEST_ASSERT_EQUAL(9,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	//Since it is work , c whether work for other symbol
	Try
	{
		result = convertBasedNumberToBase10Number("0x1@00");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("0x1@00",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	
	Try
	{
		result = convertBasedNumberToBase10Number("0x1$00");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("0x1$00",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	
	Try
	{
		result = convertBasedNumberToBase10Number("0x1=00");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("0x1=00",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
}




