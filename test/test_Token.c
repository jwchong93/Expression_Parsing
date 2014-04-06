#include "unity.h"
#include "Token.h"
#include <malloc.h>
#include <string.h>
#include "CException.h"
#include "StringObject.h"
#include "Error.h"
#include "convertValue.h"
#include "mock_GetElement.h"

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
	TEST_ASSERT_EQUAL(70,opeToken->precedence);
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
	TEST_ASSERT_EQUAL(70,opeToken->precedence);
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
	TEST_ASSERT_EQUAL(70,opeToken->precedence);
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
	TEST_ASSERT_EQUAL(90,opeToken->precedence);
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
	TEST_ASSERT_EQUAL(90,opeToken->precedence);
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
	TEST_ASSERT_EQUAL(1,opeToken->precedence);
	
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
	TEST_ASSERT_EQUAL(2,opeToken->precedence);
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
	TEST_ASSERT_EQUAL(10,opeToken->precedence);
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
	TEST_ASSERT_EQUAL(80,opeToken->precedence);
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
	TEST_ASSERT_EQUAL(40,opeToken->precedence);
	
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
	TEST_ASSERT_EQUAL(80,opeToken->precedence);
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
	TEST_ASSERT_EQUAL(80,opeToken->precedence);
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
	TEST_ASSERT_EQUAL(80,opeToken->precedence);
	free (opeToken);
	
	testToken = getToken(testTokenizer);

	//This testToken should be not NULL
	TEST_ASSERT_NOT_NULL(testToken);
	//With operator type.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(LEFT_PARENTHESIS,opeToken->id);
	TEST_ASSERT_EQUAL(1,opeToken->precedence);
	free (opeToken);
	
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(NUMBER,*testToken);
	Number *numToken = (Number*)testToken;
	TEST_ASSERT_EQUAL(NUMBER,numToken->type);
	TEST_ASSERT_EQUAL(45012357,numToken->value);
	free (numToken);
	
	
	testToken = getToken(testTokenizer);

	//This testToken should be not NULL
	TEST_ASSERT_NOT_NULL(testToken);
	//With operator type.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(RIGHT_PARENTHESIS,opeToken->id);
	TEST_ASSERT_EQUAL(2,opeToken->precedence);
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
	TEST_ASSERT_EQUAL(80,opeToken->precedence);
	free (opeToken);
		
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(LEFT_PARENTHESIS,opeToken->id);
	TEST_ASSERT_EQUAL(1,opeToken->precedence);
	free (opeToken);
	free(testTokenizer);
	

}

void test_getToken_will_differentiate_greater__greater_or_equal__right_shift_and_right_shift_set_equal()
{
	String * testTokenizer = stringCreate("456>123");
	Token * testToken;
	free(getToken(testTokenizer));

	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(GREATER_THAN,opeToken->id);
	TEST_ASSERT_EQUAL(40,opeToken->precedence);
	free(opeToken);
	
	
	free(testTokenizer);
	
	testTokenizer = stringCreate("3>=3>>=456>>1");
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(GREATER_EQUAL_THAN,opeToken->id);
	TEST_ASSERT_EQUAL(40,opeToken->precedence);
	free(opeToken);
	
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(RIGHT_SHIFT_SET_EQUAL,opeToken->id);
	TEST_ASSERT_EQUAL(10,opeToken->precedence);
	free(opeToken);
	
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(RIGHT_SHIFT,opeToken->id);
	TEST_ASSERT_EQUAL(50,opeToken->precedence);
	free(opeToken);
	free(testTokenizer);
	
}

void test_getToken_will_differentiate_less__less_or_equal__left_shift_and_left_shift_set_equal()
{
	String * testTokenizer = stringCreate("213213<21542143");
	Token * testToken;
	
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(LESS_THAN,opeToken->id);
	TEST_ASSERT_EQUAL(40,opeToken->precedence);
	free(opeToken);
	free(testTokenizer);
	
	testTokenizer = stringCreate("547351123<=21312<<=2131231<<1");
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(LESS_EQUAL_THAN,opeToken->id);
	TEST_ASSERT_EQUAL(40,opeToken->precedence);
	free(opeToken);
	
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(LEFT_SHIFT_SET_EQUAL,opeToken->id);
	TEST_ASSERT_EQUAL(10,opeToken->precedence);
	free(opeToken);
	
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(LEFT_SHIFT,opeToken->id);
	TEST_ASSERT_EQUAL(50,opeToken->precedence);
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
	String * testTokenizer = stringCreate("5=2+3");
	Token *testToken ;
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(EQUAL,opeToken->id);
	TEST_ASSERT_EQUAL(10,opeToken->precedence);
	free(opeToken);
	free(testTokenizer);
	
	testTokenizer = stringCreate("6==5");
	free(getToken(testTokenizer));
	testToken = getToken(testTokenizer); //==
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(EQUAL_TO,opeToken->id);
	TEST_ASSERT_EQUAL(40,opeToken->precedence);
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
	TEST_ASSERT_EQUAL(30,opeToken->precedence);
	free(opeToken);
	
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(LOGICAL_AND,opeToken->id);
	TEST_ASSERT_EQUAL(20,opeToken->precedence);
	free(opeToken);
	free(testTokenizer);
	
	testTokenizer = stringCreate("345&=23423");
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(AND_SET_EQUAL,opeToken->id);
	TEST_ASSERT_EQUAL(10,opeToken->precedence);
	free(opeToken);
	free(testTokenizer);
}

void test_getToken_will_detect_ADD_SET_EQUAL()
{
	String * testTokenizer = stringCreate("3+=1");
	Token *testToken;
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(ADD_SET_EQUAL,opeToken->id);
	TEST_ASSERT_EQUAL(10,opeToken->precedence);
	free(opeToken);
	free(testTokenizer);
}

void test_getToken_will_identify_SUBTRACT_SET_EQUAL()
{
	String * testTokenizer = stringCreate("3-=4");
	Token *testToken;
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(SUBTRACT_SET_EQUAL,opeToken->id);
	TEST_ASSERT_EQUAL(10,opeToken->precedence);
	free(opeToken);
	free(testTokenizer);
}

void test_getToken_will_identify_BITWISE_XOR_and_XOR_SET_EQUAL()
{
	String * testTokenizer = stringCreate("2+1^0^=1" );
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
	TEST_ASSERT_EQUAL(30,opeToken->precedence);
	free(opeToken);
	
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);		//^=
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(XOR_SET_EQUAL,opeToken->id);
	TEST_ASSERT_EQUAL(10,opeToken->precedence);
	free(opeToken);
	free(testTokenizer);
}

void test_getToken_will_identify_BITWISE_OR_LOGICAL_OR_and_OR_SET_EQUAL()
{
	String * testTokenizer = stringCreate("0|1||0|=1" );
	Token *testToken;
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);		//|
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(BITWISE_OR,opeToken->id);
	TEST_ASSERT_EQUAL(30,opeToken->precedence);
	free(opeToken);
	
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);		//||
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(LOGICAL_OR,opeToken->id);
	TEST_ASSERT_EQUAL(20,opeToken->precedence);
	free(opeToken);
	
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer);		//|=
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(OR_SET_EQUAL,opeToken->id);
	TEST_ASSERT_EQUAL(10,opeToken->precedence);
	free(opeToken);
	free(testTokenizer);
}

void test_getToken_will_identify_MULTIPLY_DIVIDE_and_MODULUS_SET_EQUAL()
{
	String * testTokenizer = stringCreate("234*=0" );
	Token *testToken;
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer); 		//*=
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(MULTIPLY_SET_EQUAL,opeToken->id);
	TEST_ASSERT_EQUAL(10,opeToken->precedence);
	free(opeToken);
	free(testTokenizer);
	
	testTokenizer = stringCreate("234235%=0" );
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer); 		//%=
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(MODULUS_SET_EQUAL,opeToken->id);
	TEST_ASSERT_EQUAL(10,opeToken->precedence);
	free(opeToken);
	free(testTokenizer);
	
	
	testTokenizer = stringCreate("2342344235/=0" );
	free(getToken(testTokenizer));
	
	testToken = getToken(testTokenizer); 		///=
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(DIVIDE_SET_EQUAL,opeToken->id);
	TEST_ASSERT_EQUAL(10,opeToken->precedence);
	free(opeToken);
	free(testTokenizer);
}

void test_stringCreate_will_update_identifier_to_the_defined_term()
{
	//first,consider that the user will define an identifier name num1 as following.
	//#define		num1		200+
	char *name = "num1";
	DefineElement element;
	element.ID = "num1";
	element.actualID = "200+";
	getElement_ExpectAndReturn(DefineList, name,&element);
	String * testTokenizer = stringCreate("num1 6");
	
	//Make sure the identifier been updated.
	TEST_ASSERT_NOT_NULL(testTokenizer);
	TEST_ASSERT_EQUAL_STRING("200+ 6",testTokenizer->rawString);
	free(testTokenizer);
}

void test_stringCreate_will_update_identifier_to_the_defined_term_if_the_term_is_behind()
{
	char *name = "num1";
	DefineElement element;
	element.ID = "num1";
	element.actualID = "*200";
	getElement_ExpectAndReturn(DefineList, name,&element);
	String * testTokenizer = stringCreate("6num1");
	
	//Make sure the identifier been updated.
	TEST_ASSERT_NOT_NULL(testTokenizer);
	TEST_ASSERT_EQUAL_STRING("6*200",testTokenizer->rawString);
	free(testTokenizer);
}

void test_stringCreate_will_update_identifier_to_the_defined_term_if_the_term_is_middle()
{
	//make it middle.
	char *name = "num1";
	DefineElement element;
	element.ID = "num1";
	element.actualID = "200";
	getElement_ExpectAndReturn(DefineList, name,&element);
	String * testTokenizer = stringCreate("6+num1+100");
	
	//Make sure the identifier been updated.
	TEST_ASSERT_NOT_NULL(testTokenizer);
	TEST_ASSERT_EQUAL_STRING("6+200+100",testTokenizer->rawString);
	free(testTokenizer);
}

void test_stringCreate_will_update_identifier_to_the_defined_term_if_there_are_two_identifier()
{
	//make it middle.
	char *name = "num1";
	char *name1 = "num2";
	DefineElement element;
	element.ID = "num1";
	element.actualID = "200";
	DefineElement element1;
	element1.ID = "num2";
	element1.actualID = "500";
	getElement_ExpectAndReturn(DefineList, name,&element);
	getElement_ExpectAndReturn(DefineList, name1,&element1);
	getElement_ExpectAndReturn(DefineList, name,&element);
	getElement_ExpectAndReturn(DefineList, name,&element);
	String * testTokenizer = stringCreate("num1+num2-num1+num1");
	
	//Make sure the identifier been updated.
	TEST_ASSERT_NOT_NULL(testTokenizer);
	TEST_ASSERT_EQUAL_STRING("200+500-200+200",testTokenizer->rawString);
	free(testTokenizer);
}

void test_stringCreate_will_update_based_number_to_base_10_number()
{
	String * testTokenizer = stringCreate("0x1234");
	TEST_ASSERT_NOT_NULL(testTokenizer);
	TEST_ASSERT_EQUAL_STRING("4660",testTokenizer->rawString);
	TEST_ASSERT_EQUAL(4,testTokenizer->length);
	TEST_ASSERT_EQUAL(0,testTokenizer->startIndex);
	free(testTokenizer);
}

void test_stringCreate_will_update_based_number_to_base_10_number_if_there_is_some_expression_before_it()
{
	char *name = "o";
	String * testTokenizer = stringCreate("3+o'1234'");
	TEST_ASSERT_NOT_NULL(testTokenizer);
	TEST_ASSERT_EQUAL_STRING("3+668",testTokenizer->rawString);
	TEST_ASSERT_EQUAL(5,testTokenizer->length);
	TEST_ASSERT_EQUAL(0,testTokenizer->startIndex);
	free(testTokenizer);
}

void test_stringCreate_will_update_based_number_to_base_10_number_if_the_based_number_is_being_in_middle()
{
	char *name = "o";
	String * testTokenizer = stringCreate("3+h'abcd'/100");
	TEST_ASSERT_NOT_NULL(testTokenizer);
	TEST_ASSERT_EQUAL_STRING("3+43981/100",testTokenizer->rawString);
	TEST_ASSERT_EQUAL(11,testTokenizer->length);
	TEST_ASSERT_EQUAL(0,testTokenizer->startIndex);
	free(testTokenizer);
}

void test_stringCreate_will_update_both_based_number_and_identifier()
{
	char *name = "num1";
	char *name1 = "num2";
	DefineElement element;
	element.ID = "num1";
	element.actualID = "200";
	DefineElement element1;
	element1.ID = "num2";
	element1.actualID = "500";
	getElement_ExpectAndReturn(DefineList, name,&element);
	getElement_ExpectAndReturn(DefineList, name1,&element1);
	String * testTokenizer = stringCreate("0x1234-num1+num2%b'101100'");
	TEST_ASSERT_NOT_NULL(testTokenizer);
	TEST_ASSERT_EQUAL_STRING("4660-200+500%44",testTokenizer->rawString);
	TEST_ASSERT_EQUAL(15,testTokenizer->length);
	TEST_ASSERT_EQUAL(0,testTokenizer->startIndex);
	free(testTokenizer);
}









