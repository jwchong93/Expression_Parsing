#include "unity.h"
#include "Token.h"
#include <malloc.h>
#include <string.h>
#include "CException.h"
#include "mock_Stack.h"
#include "StringObject.h"
#include "Error.h"

void setUp(){}
void tearDown(){}

void test_stringCreate_should_initiate_and_return_a_tokenizer_properly()
{
	//Initiate a new tokenizer which will contain the data of 2+3
	String *testTokenizer = stringCreate("2+3");
	TEST_ASSERT_NOT_NULL(testTokenizer);
	TEST_ASSERT_EQUAL_STRING("2+3", testTokenizer->rawString);
	TEST_ASSERT_EQUAL(0,testTokenizer->startIndex);
	TEST_ASSERT_EQUAL(3,testTokenizer->length);
	free(testTokenizer);
	
	//Try a longer expression
	testTokenizer = stringCreate("2+3*8+8");
	TEST_ASSERT_NOT_NULL(testTokenizer);
	TEST_ASSERT_EQUAL_STRING("2+3*8+8", testTokenizer->rawString);
	TEST_ASSERT_EQUAL(0,testTokenizer->startIndex);
	TEST_ASSERT_EQUAL(7,testTokenizer->length);
	free(testTokenizer);
}

void test_getToken_should_return_the_token_by_sequence()
{
	Number *testNum;
	Operator *testOpe;
	Token *testToken=NULL;
	String *testTokenizer = stringCreate("2+3");
	
	//Get the first token which is 2 and test the length and startIndex of tokenizer.
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(2,testTokenizer->length);
	TEST_ASSERT_EQUAL(1,testTokenizer->startIndex);
	
	//Cast the returned token type address to the respective type and test the data contained.
	TEST_ASSERT_EQUAL(NUMBER,*testToken);
	testNum = (Number *) testToken;
	TEST_ASSERT_EQUAL(NUMBER,testNum->type);
	TEST_ASSERT_EQUAL(2,testNum->value);
	free(testNum);
	
	//Get the second token which is + and test the length and startIndex.
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(1,testTokenizer->length);
	TEST_ASSERT_EQUAL(2,testTokenizer->startIndex);
	
	//Test the token type that accepted and cast it back to it respective type and test.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	testOpe = (Operator *) testToken;
	TEST_ASSERT_EQUAL(OPERATOR,testOpe->type);
	TEST_ASSERT_EQUAL(ADD,testOpe->id);
	free(testOpe);

	//Get the last token which is 3 an1d test the length and startIndex.
	testToken=getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(0,testTokenizer->length);
	TEST_ASSERT_EQUAL(3,testTokenizer->startIndex);
	
	//Test the returned token type.
	TEST_ASSERT_EQUAL(NUMBER, *testToken);
	testNum = (Number*)testToken;
	TEST_ASSERT_EQUAL(NUMBER,testNum->type);
	TEST_ASSERT_EQUAL(3,testNum->value);
	free(testNum);
	
	//Continue getToken even the token all been retrieved
	testToken=getToken(testTokenizer);
	TEST_ASSERT_NULL(testToken);
	TEST_ASSERT_EQUAL(0,testTokenizer->length);
	TEST_ASSERT_EQUAL(3,testTokenizer->startIndex);
	
	free(testTokenizer);
	
}

void test_getToken_should_indentify_the_identifier_consist_in_the_expression()
{
	Identifier *IdenToken;
	Token *testToken=NULL;
	String *testTokenizer = stringCreate("2+MAX5-4");
	
	//Since previous test had tested how to return 2 and + lets skip the test
	free(getToken(testTokenizer));
	free(getToken(testTokenizer));
	
	//This getToken should return an identifier token address.
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(IDENTIFIER,*testToken);
	IdenToken = (Identifier*)testToken;
	TEST_ASSERT_EQUAL_STRING("MAX5",IdenToken->name);
	free(testTokenizer);
	free(IdenToken);

}

void test_getToken_should_stop_return_a_token_while_an_invalid_identifer_is_included_in_the_expression()
{
	String *testTokenizer = stringCreate("5MAX+4");
	Error Exception;
	Try 
	{
	Token *testToken = getToken (testTokenizer);
	//The getToken function will return NULL and throw an enum INVALID_IDENTFIER.
	TEST_ASSERT_NULL(testToken);
	free(testToken);
	}Catch(Exception)
	{
		TEST_ASSERT_EQUAL(INVALID_IDENTIFIER,Exception);
	}
	
	//lets try the function which the invalid identifier being in the last part of thr expression
	testTokenizer = stringCreate("2+5MAX");
	Try 
	{
	Token *testToken;
	free(getToken(testTokenizer));
	free(getToken(testTokenizer));
	testToken = getToken (testTokenizer);
	//The getToken function will return NULL and throw an enum INVALID_IDENTFIER.
	TEST_ASSERT_NULL(testToken);
	free(testToken);
	}Catch(Exception)
	{
		TEST_ASSERT_EQUAL(INVALID_IDENTIFIER,Exception);
	}
	free(testTokenizer);
}

void test_getToken_should_detect_the_valid_identifier_which_have_a_different_pattern()
{
	//Try some valid format like .MAX
	String *testTokenizer = stringCreate("2+.MAX");

	Token *testToken;
	free(getToken(testTokenizer));
	free(getToken(testTokenizer));
	testToken = getToken (testTokenizer);
	//The getToken function will not return NULL and do not throw an enum INVALID_IDENTFIER.
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(IDENTIFIER,*testToken);
	Identifier *testIden = (Identifier*)testToken;
	//Since the previous test already test for the properties of tokenizer 
	TEST_ASSERT_EQUAL_STRING(".MAX",testIden->name);
	free(testIden);
	free(testTokenizer);
	
	//Test for the identifier that consist more dot(.)
	testTokenizer = stringCreate("2+..MAX");
	free(getToken(testTokenizer));
	free(getToken(testTokenizer));
	testToken = getToken (testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(IDENTIFIER,*testToken);
	testIden = (Identifier*)testToken;
	TEST_ASSERT_EQUAL_STRING("..MAX",testIden->name);
	free(testTokenizer);
	free(testIden);
	
	//Try the identifier which have many dot in random location.
	testTokenizer = stringCreate("2+.M.A.X.");
	free(getToken(testTokenizer));
	free(getToken(testTokenizer));
	testToken = getToken (testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(IDENTIFIER,*testToken);
	testIden = (Identifier*)testToken;
	TEST_ASSERT_EQUAL_STRING(".M.A.X.",testIden->name);
	free(testTokenizer);
	free(testIden);
	
}

void test_getToken_should_identify_the_number_that_is_more_than_10()
{
	String *testTokenizer = stringCreate("25-456");
	//Get the first token out from the tokenizer.
	Token *testToken = getToken(testTokenizer);
	//Test the tokenizer will be updated as expected.
	TEST_ASSERT_EQUAL(2,testTokenizer->startIndex);
	TEST_ASSERT_EQUAL(4,testTokenizer->length);
	//Check the type of the token that been returned.
	TEST_ASSERT_EQUAL(NUMBER,*testToken);
	Number *testNum = (Number*) testToken;
	//Test the data inside the Token.
	TEST_ASSERT_EQUAL(25,testNum->value);
	free(testNum);
	
	//Get the next token.
	testToken = getToken(testTokenizer);
	TEST_ASSERT_EQUAL(3,testTokenizer->startIndex);
	TEST_ASSERT_EQUAL(3,testTokenizer->length);
	//It should be operator type
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *testOpe = (Operator*) testToken;
	TEST_ASSERT_EQUAL(SUBTRACT,testOpe->id);
	free(testOpe);
	
	//Continue get the token
	testToken = getToken(testTokenizer);
	TEST_ASSERT_EQUAL(6,testTokenizer->startIndex);
	TEST_ASSERT_EQUAL(0,testTokenizer->length);
	//It should be operator type
	TEST_ASSERT_EQUAL(NUMBER,*testToken);
	testNum = (Number*) testToken;
	TEST_ASSERT_EQUAL(456,testNum->value);
	free(testNum);
	
	//Make sure the getToken will return NULL while there is no more token to be return 
	testToken = getToken(testTokenizer);
	TEST_ASSERT_EQUAL(NULL,testToken);
	free(testTokenizer);
	free(testToken);
}

void test_getToken_should_detect_multiply_sign()
{
	String *testTokenizer = stringCreate("25*456");
	
	//Since the program already can detect 25.
	Token *testToken;
	free(getToken(testTokenizer));
	testToken = getToken(testTokenizer);
	
	//This testToken should be not NULL
	TEST_ASSERT_NOT_NULL(testToken);
	//With operator type.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(MULTIPLY,opeToken->id);
	free(testTokenizer);
	free(opeToken);
	
}

void test_getToken_should_detect_divide_sign()
{
	String *testTokenizer = stringCreate("25/456");
	
	//Since the program already can detect 25.
	Token *testToken;
	free(getToken(testTokenizer));
	testToken = getToken(testTokenizer);
	
	//This testToken should be not NULL
	TEST_ASSERT_NOT_NULL(testToken);
	//With operator type.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(DIVIDE,opeToken->id);
	free(testTokenizer);
	free(opeToken);
	
}

void test_getToken_should_detect_modulus_sign()
{
	String *testTokenizer = stringCreate("200%10");
	
	//Since the program already can detect 25.
	Token *testToken;
	free(getToken(testTokenizer));
	testToken = getToken(testTokenizer);
	
	//This testToken should be not NULL
	TEST_ASSERT_NOT_NULL(testToken);
	//With operator type.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(MODULUS,opeToken->id);
	free(testTokenizer);
	free(opeToken);
	
}

void test_getToken_should_detect_current_program_counter_sign()
{
	String *testTokenizer = stringCreate("2+$");
	
	//Since the program already can detect 2 and +.
	Token *testToken;
	free(getToken(testTokenizer));
	free(getToken(testTokenizer));
	testToken = getToken(testTokenizer);
	
	//This testToken should be not NULL
	TEST_ASSERT_NOT_NULL(testToken);
	//With operator type.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(CURRENT_PROGRAM_COUNTER,opeToken->id);
	free(testTokenizer);
	free(opeToken);
	
	//Try reverse the other of the equation
	testTokenizer = stringCreate("$+2");
	
	testToken = getToken(testTokenizer);

	//This testToken should be not NULL
	TEST_ASSERT_NOT_NULL(testToken);
	//With operator type.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(CURRENT_PROGRAM_COUNTER,opeToken->id);
	free(testTokenizer);
	free(opeToken);
	
}

void test_getToken_should_detect_parenthesis_sign()
{
	String *testTokenizer = stringCreate("(2+3)");
	
	Token *testToken = getToken(testTokenizer);
	
	//This testToken should be not NULL
	TEST_ASSERT_NOT_NULL(testToken);
	//With operator type.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(LEFT_PARENTHESIS,opeToken->id);
	
	//Read out the 2 , + and 3
	free(getToken(testTokenizer));
	free(getToken(testTokenizer));
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);
	//This testToken should be not NULL
	TEST_ASSERT_NOT_NULL(testToken);
	//With operator type.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(RIGHT_PARENTHESIS,opeToken->id);
	free(testTokenizer);
	free(opeToken);
}

void test_getToken_should_detect_equal_sign()
{
	String *testTokenizer = stringCreate("2+3=5");
	
	//Since the program already can detect 2,+ and 3.
	Token *testToken;
	free(getToken(testTokenizer));
	free(getToken(testTokenizer));
	free(getToken(testTokenizer));
	testToken = getToken(testTokenizer);
	
	//This testToken should be not NULL
	TEST_ASSERT_NOT_NULL(testToken);
	//With operator type.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(EQUAL,opeToken->id);
	free(testTokenizer);
	free(opeToken);
	
	
}

void test_getToken_should_detect_not_sign()
{
	String *testTokenizer = stringCreate("2+3+!3");
	
	//Since the program already can detect 2,+ and 3.
	Token *testToken;
	free(getToken(testTokenizer));
	free(getToken(testTokenizer));
	free(getToken(testTokenizer));
	free(getToken(testTokenizer));
	testToken = getToken(testTokenizer);	//+
	
	//This testToken should be not NULL
	TEST_ASSERT_NOT_NULL(testToken);
	//With operator type.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(LOGIC_NOT,opeToken->id);
	free(testTokenizer);
	free(opeToken);
	
	//getToken should diffrentiate NOT and not equal
	testTokenizer = stringCreate("2+3!=5");
	
	//Since the program already can detect 2,+ and 3.
	free(getToken(testTokenizer));
	free(getToken(testTokenizer));
	free(getToken(testTokenizer));
	testToken = getToken(testTokenizer);
	
	//This testToken should be not NULL
	TEST_ASSERT_NOT_NULL(testToken);
	//With operator type.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(NOT_EQUAL,opeToken->id);
	
	//The tokenizer should updated to...
	TEST_ASSERT_EQUAL(5,testTokenizer->startIndex);
	TEST_ASSERT_EQUAL(1,testTokenizer->length);
	
	testToken = getToken(testTokenizer);
	//Try to get the last token and check the status of tokenizer.
	TEST_ASSERT_EQUAL(6,testTokenizer->startIndex);
	TEST_ASSERT_EQUAL(0,testTokenizer->length);
	free(testTokenizer);
	free(opeToken);
}

void test_getToken_should_detect_complement_in_an_expression()
{
	String *testTokenizer = stringCreate("~2+9");
	

	Token *testToken = getToken(testTokenizer);
	
	//This testToken should be not NULL
	TEST_ASSERT_NOT_NULL(testToken);
	//With operator type.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(COMPLEMENT,opeToken->id);
	free (opeToken);
	
	//Lets try to input some equation that the complement is being in middle. 
	testTokenizer = stringCreate("2+~9");
	free(getToken(testTokenizer));
	free(getToken(testTokenizer));
	testToken = getToken(testTokenizer); //~
	
	//This testToken should be not NULL
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(COMPLEMENT,opeToken->id);
	free(opeToken);
	
	free(getToken(testTokenizer));
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NULL(testToken);
	free(testTokenizer);
}

void test_getToken_will_differentiate_low_high_and_upper_as_operator()
{
	String *testTokenizer = stringCreate("low(45012357)");
	
	Token *testToken = getToken(testTokenizer);

	//This testToken should be not NULL
	TEST_ASSERT_NOT_NULL(testToken);
	//With operator type.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(LOW,opeToken->id);
	free (opeToken);
	free(testTokenizer);
	
	//Since the function been tested in below. 
	//Try to make some combinational expression.
	testTokenizer = stringCreate("1*high(45012357)");
	
	free(getToken(testTokenizer));
	free(getToken(testTokenizer));
	testToken = getToken(testTokenizer);
	
	//This testToken should be not NULL
	TEST_ASSERT_NOT_NULL(testToken);
	//With operator type.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(HIGH,opeToken->id);
	free (opeToken);
		
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(LEFT_PARENTHESIS,opeToken->id);
	free (opeToken);
	free(testTokenizer);
	

}

void test_getToken_will_differentiate_greater__greater_or_equal__right_shift_and_right_shift_set_equal()
{
	String * testTokenizer = stringCreate("num1>num2");
	Token * testToken = getToken(testTokenizer);
	
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(IDENTIFIER,*testToken);
	Identifier *idenToken = (Identifier*)testToken;
	TEST_ASSERT_EQUAL(IDENTIFIER,idenToken->type);
	TEST_ASSERT_EQUAL_STRING("num1",idenToken->name);
	free(idenToken);
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(GREATER_THAN,opeToken->id);
	free(opeToken);
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(IDENTIFIER,*testToken);
	idenToken = (Identifier*)testToken;
	TEST_ASSERT_EQUAL(IDENTIFIER,idenToken->type);
	TEST_ASSERT_EQUAL_STRING("num2",idenToken->name);
	free(idenToken);
	free(testTokenizer);
	
	testTokenizer = stringCreate("num1>=num2>>=MAX>>1");
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(GREATER_EQUAL_THAN,opeToken->id);
	free(opeToken);
	
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(RIGHT_SHIFT_SET_EQUAL,opeToken->id);
	free(opeToken);
	
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(RIGHT_SHIFT,opeToken->id);
	free(opeToken);
	free(testTokenizer);
	
}

void test_getToken_will_differentiate_less__less_or_equal__left_shift_and_left_shift_set_equal()
{
	String * testTokenizer = stringCreate("num1<num2");
	Token * testToken = getToken(testTokenizer);
	
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(IDENTIFIER,*testToken);
	Identifier *idenToken = (Identifier*)testToken;
	TEST_ASSERT_EQUAL(IDENTIFIER,idenToken->type);
	TEST_ASSERT_EQUAL_STRING("num1",idenToken->name);
	free(idenToken);
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(LESS_THAN,opeToken->id);
	free(opeToken);
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(IDENTIFIER,*testToken);
	idenToken = (Identifier*)testToken;
	TEST_ASSERT_EQUAL(IDENTIFIER,idenToken->type);
	TEST_ASSERT_EQUAL_STRING("num2",idenToken->name);
	free(idenToken);
	free(testTokenizer);
	
	testTokenizer = stringCreate("num1<=num2<<=MAX<<1");
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(LESS_EQUAL_THAN,opeToken->id);
	free(opeToken);
	
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(LEFT_SHIFT_SET_EQUAL,opeToken->id);
	free(opeToken);
	
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(LEFT_SHIFT,opeToken->id);
	free(opeToken);
	
	//Make sure the tokenizer will be updated to the latest position.
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(NUMBER,*testToken);
	Number *numToken = (Number*)testToken;
	TEST_ASSERT_EQUAL(NUMBER,numToken->type);
	TEST_ASSERT_EQUAL(1,numToken->value);
	free(opeToken);
	free(testTokenizer);
	
}

void test_getToken_will_identify_equal_and_equal_to()
{
	String * testTokenizer = stringCreate("tempNum=2+3");
	Token *testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(IDENTIFIER,*testToken);
	Identifier *idenToken = (Identifier*)testToken;
	TEST_ASSERT_EQUAL(IDENTIFIER,idenToken->type);
	TEST_ASSERT_EQUAL_STRING("tempNum",idenToken->name);
	free(idenToken);
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(EQUAL,opeToken->id);
	free(opeToken);
	free(testTokenizer);
	
	testTokenizer = stringCreate("tempNum==5");
	free(getToken(testTokenizer));
	testToken = getToken(testTokenizer); //==
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(EQUAL_TO,opeToken->id);
	free(opeToken);
	free(testTokenizer);
	
}

void test_getToken_will_detect_BITWISE_LOGICAL_AND_AND_and_AND_SET_EQUAL()
{
	String * testTokenizer = stringCreate("4&5&&1");
	Token *testToken;
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator * opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(BITWISE_AND,opeToken->id);
	free(opeToken);
	
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(LOGICAL_AND,opeToken->id);
	free(opeToken);
	free(testTokenizer);
	
	testTokenizer = stringCreate("bool&=input");
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(AND_SET_EQUAL,opeToken->id);
	free(opeToken);
	free(testTokenizer);
}

void test_getToken_will_detect_ADD_SET_EQUAL()
{
	String * testTokenizer = stringCreate("total+=number");
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

void test_getToken_will_identify_SUBTRACT_SET_EQUAL()
{
	String * testTokenizer = stringCreate("total-=number");
	Token *testToken;
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(SUBTRACT_SET_EQUAL,opeToken->id);
	free(opeToken);
	free(testTokenizer);
}

void test_getToken_will_identify_BITWISE_XOR_and_XOR_SET_EQUAL()
{
	String * testTokenizer = stringCreate("total+1^0^=1" );
	Token *testToken;
	free(getToken(testTokenizer));
	free(getToken(testTokenizer));
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);		//^
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(BITWISE_XOR,opeToken->id);
	free(opeToken);
	
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);		//^=
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(XOR_SET_EQUAL,opeToken->id);
	free(opeToken);
	free(testTokenizer);
}

void test_getToken_will_identify_BITWISE_OR_LOGICAL_OR_and_OR_SET_EQUAL()
{
	String * testTokenizer = stringCreate("total|1||0|=1" );
	Token *testToken;
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);		//|
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(BITWISE_OR,opeToken->id);
	free(opeToken);
	
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);		//||
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(LOGICAL_OR,opeToken->id);
	free(opeToken);
	
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);		//|=
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(OR_SET_EQUAL,opeToken->id);
	free(opeToken);
	free(testTokenizer);
}

void test_getToken_will_identify_MULTIPLY_DIVIDE_and_MODULUS_SET_EQUAL()
{
	String * testTokenizer = stringCreate("total*=0" );
	Token *testToken;
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer); 		//*=
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(MULTIPLY_SET_EQUAL,opeToken->id);
	free(opeToken);
	free(testTokenizer);
	
	testTokenizer = stringCreate("total%=0" );
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer); 		//%=
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(MODULUS_SET_EQUAL,opeToken->id);
	free(opeToken);
	free(testTokenizer);
	
	
	testTokenizer = stringCreate("total/=0" );
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer); 		///=
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(DIVIDE_SET_EQUAL,opeToken->id);
	free(opeToken);
	free(testTokenizer);
}

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

//Stop this and find dr poh to fix this
void xtest_operatorEvaluate_will_evaluate_2_plus_3()
{
	Stack *numberStack, *operatorStack;
	Token *token0 = createNumberToken(2);
	Token token1 = OPERATOR;
	Token *token2 = createNumberToken(3);
	pop_ExpectAndReturn(numberStack,token0);

	operatorEvaluate(numberStack,operatorStack);

}














