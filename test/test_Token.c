#include "unity.h"
#include "Token.h"


void setUp(){}
void tearDown(){}

void test_identify_should_return_the_type_of_the_input()
{
	char testChar = '8';
	Token testType;
	testType = Identify(testChar);
	TEST_ASSERT_EQUAL(NUMBER,testType);
	
	testChar = '+';
	testType = Identify(testChar);
	TEST_ASSERT_EQUAL(OPERAND,testType);
	
	testChar= 'A';
	testType = Identify(testChar);
	TEST_ASSERT_EQUAL(IDENTIFIER,testType);
	
	
}