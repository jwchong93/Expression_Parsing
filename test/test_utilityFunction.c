#include "unity.h"
#include "Token.h"
#include "CException.h"
#include "mock_Stack.h"
#include "StringObject.h"
#include <malloc.h>
#include <string.h>
#include "Error.h"

void setUp() {}
void tearDown () {}




void test_getToken_ignore_space_and_tab()
{
	String * testTokenizer = stringCreate("   total				+=    number   			");
	Token *testToken;
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(ADD_SET_EQUAL,opeToken->id);
	free(opeToken);
	free(testTokenizer);
}

void test_getToken_will_treat_number_with_space_are_two_different_token_object()
{
	String * testTokenizer = stringCreate("total += 3 + 5 6 /7");
	Token *testToken;
	Number *testNum;
	free(getToken(testTokenizer)); //total 
	
	testToken = getToken(testTokenizer); //+=
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(ADD_SET_EQUAL,opeToken->id);
	free(opeToken);
	
	testToken=getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	//Test the returned token type.
	TEST_ASSERT_EQUAL(NUMBER, *testToken);
	testNum = (Number*)testToken;
	TEST_ASSERT_EQUAL(NUMBER,testNum->type);
	TEST_ASSERT_EQUAL(3,testNum->value);
	free(testNum);
	
	testToken = getToken(testTokenizer); //+
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(ADD,opeToken->id);
	free(opeToken);
	
	testToken=getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	//Test the returned token type.
	TEST_ASSERT_EQUAL(NUMBER, *testToken);
	testNum = (Number*)testToken;
	TEST_ASSERT_EQUAL(NUMBER,testNum->type);
	TEST_ASSERT_EQUAL(5,testNum->value);
	free(testNum);
	
	testToken=getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	//Test the returned token type.
	TEST_ASSERT_EQUAL(NUMBER, *testToken);
	testNum = (Number*)testToken;
	TEST_ASSERT_EQUAL(NUMBER,testNum->type);
	TEST_ASSERT_EQUAL(6,testNum->value);
	free(testNum);
	
	testToken = getToken(testTokenizer); // /
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(DIVIDE,opeToken->id);
	free(opeToken);
	
	testToken=getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	//Test the returned token type.
	TEST_ASSERT_EQUAL(NUMBER, *testToken);
	testNum = (Number*)testToken;
	TEST_ASSERT_EQUAL(NUMBER,testNum->type);
	TEST_ASSERT_EQUAL(7,testNum->value);
	free(testNum);
	
	
	free(testTokenizer);
}

void test_getToken_will_throw_error_if_the_the_expression_contain_invalid_simbol()
{
	String * testTokenizer = stringCreate("3?2");
	Error Exception;
	Token *testToken;
	free(getToken(testTokenizer));		//3
	Try
	{
		testToken = getToken(testTokenizer);//? 
	}
	Catch(Exception)
	{
		TEST_ASSERT_EQUAL(UNKNOWN_OPERATOR,Exception);
	}
}

void test_stringCopy_should_copy_the_string_from_source_to_destination()
{
	char * newString ="Hello World!!!!";
	char * stringGet = malloc (sizeof(char)*(strlen(newString)));
	
	//Start From the location 6 and the size is 5
	stringCopy(newString,stringGet,6,5);
	
	TEST_ASSERT_EQUAL('W',stringGet[0]);
	TEST_ASSERT_EQUAL('o',stringGet[1]);
	TEST_ASSERT_EQUAL('r',stringGet[2]);
	TEST_ASSERT_EQUAL('l',stringGet[3]);
	TEST_ASSERT_EQUAL('d',stringGet[4]);
	TEST_ASSERT_EQUAL_STRING("World",stringGet);

}

void test_checkIdentifer_will_filter_out_low_high_and_upper()
{
	Token *testToken=checkIdentifier("low");
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(LOW,opeToken->id);
	free(opeToken);
	
	testToken=checkIdentifier("high");
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(HIGH,opeToken->id);
	free(opeToken);
	
	testToken=checkIdentifier("upper");
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(UPPER,opeToken->id);
	free(opeToken);
	
	//try to input name that out of low , high and upper.
	testToken=checkIdentifier("HAHAHA");
	TEST_ASSERT_NULL(testToken);   	//Should be null.
	
	//Try work on upper case of the key words.\
	//The program should accept any form of low , high and upper.
	testToken=checkIdentifier("LOW");
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(LOW,opeToken->id);
	free(opeToken);
	
	testToken=checkIdentifier("HiGH");
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(HIGH,opeToken->id);
	free(opeToken);
	
	testToken=checkIdentifier("UPpeR");
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(UPPER,opeToken->id);
	free(opeToken);
	
}

void test_createNumberToken_should_identify_the_input_and_return_a_token()
{
	Token *testToken = createNumberToken(7);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(NUMBER,*testToken);
	Number *numToken = (Number*)testToken;
	TEST_ASSERT_EQUAL(NUMBER,numToken->type);
	TEST_ASSERT_EQUAL(7,numToken->value);
	free(numToken);
	
	//Try to input some bigger number like 456789
	testToken = createNumberToken(456789);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(NUMBER,*testToken);
	numToken = (Number*)testToken;
	TEST_ASSERT_EQUAL(NUMBER,numToken->type);
	TEST_ASSERT_EQUAL(456789,numToken->value);	
	free(numToken);
	
}

void test_isOperator_will_return_1_for_operator_return_0_for_non_operator()
{
	String *testTokenizer = stringCreate("2*3");
	Token *testToken;
	int result=5;
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);
	result = isOperator(testToken);
	TEST_ASSERT_EQUAL(1,result);
	free(testToken);
	
	testToken = getToken(testTokenizer);
	result = isOperator(testToken);
	TEST_ASSERT_EQUAL(0,result);
	free(testToken);
}

void test_isNumber_will_return_1_for_number_return_0_for_non_number()
{
	String *testTokenizer = stringCreate("2*3");
	Token *testToken;
	int result=5;
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);
	result = isNumber(testToken);
	TEST_ASSERT_EQUAL(0,result);
	free(testToken);
	
	testToken = getToken(testTokenizer);
	result = isNumber(testToken);
	TEST_ASSERT_EQUAL(1,result);
	free(testToken);
}

void test_tryEvaluateThePush_will_evaluate_2_plus_3()
{
	Stack numberStack, operatorStack;
	Token *token0 = createNumberToken(2);
	Token token1 = OPERATOR;
	Token *token2 = createNumberToken(3);
	// pop_ExpectAndReturn(&operatorStack,NULL);
	// pop_ExpectAndReturn(&numberStack,token0);
	// pop_ExpectAndReturn(&numberStack,token2);
	
	tryEvaluateThePush(&token1,&numberStack,&operatorStack);

}














