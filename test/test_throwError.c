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
	Error exception;
	getElement_ExpectAndReturn(DefineList, testIdentifier.name,NULL);
	//Now start put the identifier and tokenizer into the function.
	Try
	{
		newTokenizer = getFromListAndUpdate(&testTokenizer,testIdentifier.name);
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(UNDEFINED_IDENTIFIER,exception);
		TEST_ASSERT_EQUAL_STRING("Undefined Identifier! ",errorMessage.message);
		
	}
	free(testIdentifier.name);
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

void test_stringCreate_will_throw_error_if_the_identifier_is_not_defined_in_the_linked_list()
{
	char *name = "num1";
	Error exception;
	getElement_ExpectAndReturn(DefineList, name,NULL);
	Try
	{
		String * testTokenizer = stringCreate("6num1");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(UNDEFINED_IDENTIFIER,exception);
		TEST_ASSERT_EQUAL_STRING("6num1",errorMessage.rawString);
		TEST_ASSERT_EQUAL(1,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Undefined Identifier! ",errorMessage.message);
	}
}

void test_stringCreate_will_throw_error_if_the_identifier_is_not_defined_in_the_linked_list_for_a_loger_expression()
{
	char *name = "num1";
	Error exception;
	getElement_ExpectAndReturn(DefineList, name,NULL);
	Try
	{
		String * testTokenizer = stringCreate("6+1208345%69-num1");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(UNDEFINED_IDENTIFIER,exception);
		TEST_ASSERT_EQUAL_STRING("6+1208345%69-num1",errorMessage.rawString);
		TEST_ASSERT_EQUAL(13,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Undefined Identifier! ",errorMessage.message);
	}
}

void test_stringCreate_will_throw_error_if_the_based_number_is_not_valid()
{
	Error exception;
	Try
	{
		String * testTokenizer = stringCreate("6*o'243");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		TEST_ASSERT_EQUAL_STRING("6*o'243",errorMessage.rawString);
		TEST_ASSERT_EQUAL(2,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
	}
}

void test_stringCreate_will_throw_error_if_the_based_number_is_not_valid_for_a_complex_expression()
{
	Error exception;
	Try
	{
		String * testTokenizer = stringCreate("6*h'24q'");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		TEST_ASSERT_EQUAL_STRING("6*h'24q'",errorMessage.rawString);
		TEST_ASSERT_EQUAL(2,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
	}
}

void test_stringCreate_will_throw_error_if_the_based_number_is_not_valid_for_0x()
{
	Error exception;
	Try
	{
		String * testTokenizer = stringCreate("6*0x1234p");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		TEST_ASSERT_EQUAL_STRING("6*0x1234p",errorMessage.rawString);
		TEST_ASSERT_EQUAL(2,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
	}
}
void test_stringCreate_will_throw_error_if_the_based_number_is_not_valid_for_number_that__larger_than_the_base()
{
	Error exception;
	Try
	{
		String * testTokenizer = stringCreate("6*o'1234p'");
	}
	Catch(exception)
	{
		TEST_ASSERT_EQUAL(INVALID_EXPRESSION,exception);
		TEST_ASSERT_EQUAL_STRING("6*o'1234p'",errorMessage.rawString);
		TEST_ASSERT_EQUAL(2,errorMessage.position);
		TEST_ASSERT_EQUAL_STRING("Invalid expression ! ",errorMessage.message);
	}
}