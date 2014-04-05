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
	String testTokenizer;
	String *testTokenizer1;
	testTokenizer.rawString = "d'1 00'";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 6;
	Error exception;
	Try
	{
		testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("d'1 00'",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	
	
	testTokenizer.rawString = "d'1456781 00'";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 13;
	//Make sure this will work for longer expression.
	Try
	{
		testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("d'1456781 00'",errorMessage.rawString);
		TEST_ASSERT_EQUAL(9,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	
	testTokenizer.rawString = "d'1@00'";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 6;
	//Since it is work , c whether work for other symbol
	Try
	{
		testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("d'1@00'",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	
	testTokenizer.rawString = "d'1$00'";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 6;
	Try
	{
		testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("d'1$00'",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	
	testTokenizer.rawString = "d'1=00'";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 6;
	Try
	{
		testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
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
	String testTokenizer;
	String *testTokenizer1;
	testTokenizer.rawString = "h'1 00'";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 6;
	Error exception;
	Try
	{
		testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("h'1 00'",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	
	
	testTokenizer.rawString = "h'1456781 00'";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 13;
	//Make sure this will work for longer expression.
	Try
	{
		testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("h'1456781 00'",errorMessage.rawString);
		TEST_ASSERT_EQUAL(9,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	
	testTokenizer.rawString = "h'1@00'";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 6;
	//Since it is work , c whether work for other symbol
	Try
	{
		testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("h'1@00'",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	
	testTokenizer.rawString = "h'1$00'";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 6;
	Try
	{
		testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("h'1$00'",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	
	testTokenizer.rawString = "h'1=00'";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 6;
	Try
	{
		testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
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
	String testTokenizer;
	String *testTokenizer1;
	testTokenizer.rawString = "o'1 00'";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 7;
	Error exception;
	Try
	{
		testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("o'1 00'",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	
	testTokenizer.rawString = "o'1800'";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 7;
	Try
	{
		testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("o'1800'",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	
	testTokenizer.rawString = "o'1900'";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 7;
	Try
	{
		testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("o'1900'",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	
	testTokenizer.rawString = "o'1a00'";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 7;
	
	Try
	{
		testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
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

void test_convertBasedNumberToBase10Number_will_throw_error_when_a_space_is_or_other_unwanted_simbol_inside_the_hexadecimal_expression_end_with_h()
{
	String testTokenizer;
	String *testTokenizer1;
	testTokenizer.rawString = "c0ffee h";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 8;
	Error exception;
	Try
	{
		testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("c0ffee h",errorMessage.rawString);
		TEST_ASSERT_EQUAL(6,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	
	testTokenizer.rawString = "c0ffeekh";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 8;
	
	Try
	{
		testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("c0ffeekh",errorMessage.rawString);
		TEST_ASSERT_EQUAL(6,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	
	testTokenizer.rawString = "c0ffeek";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 7;
	Try
	{
		testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("c0ffeek",errorMessage.rawString);
		TEST_ASSERT_EQUAL(6,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	
	testTokenizer.rawString = "c0ffeey";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 7;
	Try
	{
		testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
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


void test_convertBasedNumberToBase10Number_will_throw_error_when_an_invalid_symbol_is_inside_the_hexadecimal_expression_star_with_0x()
{
	String testTokenizer;
	String *testTokenizer1;
	testTokenizer.rawString = "0x1 00";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 6;
	Error exception;
	Try
	{
		testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("0x1 00",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
}
void test_convertBasedNumberToBase10Number_will_throw_error_when_a_space_is_inside_the_hexadecimal_expression_star_with_0x()
{
	String testTokenizer;
	String *testTokenizer1;
	Error exception;
	testTokenizer.rawString = "0x1456781 00";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 12;
	
	//Make sure this will work for longer expression.
	Try
	{
		testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("0x1456781 00",errorMessage.rawString);
		TEST_ASSERT_EQUAL(9,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
}
void test_convertBasedNumberToBase10Number_will_throw_error_when_a_symbol_inside_the_hexadecimal_expression_star_with_0x()
{
	String testTokenizer;
	String *testTokenizer1;
	Error exception;
	testTokenizer.rawString = "0x1@00";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 6;
	//Since it is work , c whether work for other symbol
	Try
	{
		testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("0x1@00",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	
	testTokenizer.rawString = "0x1$00";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 6;
	Try
	{
		testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		
		// Check the error message been updated or not . 
		TEST_ASSERT_EQUAL_STRING("0x1$00",errorMessage.rawString);
		TEST_ASSERT_EQUAL(3,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
		
	}
	
	testTokenizer.rawString = "0x1=00";
	testTokenizer.startIndex = 0;
	testTokenizer.length = 6;
	Try
	{
		testTokenizer1 = convertBasedNumberToBase10Number(&testTokenizer);
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




