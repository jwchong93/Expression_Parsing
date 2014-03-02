#include "unity.h"
#include "Token.h"
#include <malloc.h>
#include <string.h>
#include "CException.h"
void setUp(){}
void tearDown(){}

void test_initTokenizer_should_initiate_and_return_a_tokenizer_properly()
{
	//Initiate a new tokenizer which will contain the data of 2+3
	Tokenizer *testTokenizer = initTokenizer("2+3");
	TEST_ASSERT_NOT_NULL(testTokenizer);
	TEST_ASSERT_EQUAL_STRING("2+3", testTokenizer->rawString);
	TEST_ASSERT_EQUAL(0,testTokenizer->startIndex);
	TEST_ASSERT_EQUAL(3,testTokenizer->length);
	free(testTokenizer);
	
	//Try a longer expression
	testTokenizer = initTokenizer("2+3*8+8");
	TEST_ASSERT_NOT_NULL(testTokenizer);
	TEST_ASSERT_EQUAL_STRING("2+3*8+8", testTokenizer->rawString);
	TEST_ASSERT_EQUAL(0,testTokenizer->startIndex);
	TEST_ASSERT_EQUAL(7,testTokenizer->length);
	free(testTokenizer);
}

void test_initTokenizer_should_remove_space_and_tab()
{
	Tokenizer *testTokenizer = initTokenizer("2 + 3");
	TEST_ASSERT_NOT_NULL(testTokenizer);
	TEST_ASSERT_EQUAL_STRING("2+3", testTokenizer->rawString);
	TEST_ASSERT_EQUAL(0,testTokenizer->startIndex);
	TEST_ASSERT_EQUAL(3,testTokenizer->length);
}
void test_getToken_should_return_the_token_by_sequence()
{
	Number *testNum;
	Operator *testOpe;
	Token *testToken=NULL;
	Tokenizer *testTokenizer = initTokenizer("2+3");
	
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
	TEST_ASSERT_EQUAL(ADD,testOpe->ope);
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
	Tokenizer *testTokenizer = initTokenizer("2+MAX5-4");
	
	//Since previous test had tested how to return 2 and + lets skip the test
	testToken = getToken(testTokenizer);
	free(testToken);
	testToken = getToken(testTokenizer);
	
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
	Tokenizer *testTokenizer = initTokenizer("5MAX+4");
	Error Exception;
	Try 
	{
	Token *testToken = getToken (testTokenizer);
	//The getToken function will return NULL and throw an enum INVALID_IDENTFIER.
	TEST_ASSERT_NULL(testToken);
	free(testToken);
	}Catch(Exception)
	{
		TEST_ASSERT_EQUAL(INVALID_INDENTIFIER,Exception);
	}
	
	//lets try the function which the invalid identifier being in the last part of thr expression
	testTokenizer = initTokenizer("2+5MAX");
	Try 
	{
	Token *testToken = getToken (testTokenizer);
	free(testToken);
	testToken = getToken (testTokenizer);
	free(testToken);
	testToken = getToken (testTokenizer);
	//The getToken function will return NULL and throw an enum INVALID_IDENTFIER.
	TEST_ASSERT_NULL(testToken);
	free(testToken);
	}Catch(Exception)
	{
		TEST_ASSERT_EQUAL(INVALID_INDENTIFIER,Exception);
	}
	free(testTokenizer);
}

void test_getToken_should_detect_the_valid_identifier_which_have_a_different_pattern()
{
	//Try some valid format like .MAX
	Tokenizer *testTokenizer = initTokenizer("2+.MAX");

	Token *testToken = getToken (testTokenizer);
	free(testToken);
	testToken = getToken (testTokenizer);
	free(testToken);
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
	testTokenizer = initTokenizer("2+..MAX");
	testToken = getToken (testTokenizer);
	free(testToken);
	testToken = getToken (testTokenizer);
	free(testToken);
	testToken = getToken (testTokenizer);
	TEST_ASSERT_NOT_NULL(testToken);
	TEST_ASSERT_EQUAL(IDENTIFIER,*testToken);
	testIden = (Identifier*)testToken;
	TEST_ASSERT_EQUAL_STRING("..MAX",testIden->name);
	free(testTokenizer);
	free(testIden);
	
	//Try the identifier which have many dot in random location.
	testTokenizer = initTokenizer("2+.M.A.X.");
	testToken = getToken (testTokenizer);
	free(testToken);
	testToken = getToken (testTokenizer);
	free(testToken);
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
	Tokenizer *testTokenizer = initTokenizer("25-456");
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
	TEST_ASSERT_EQUAL(SUBTRACT,testOpe->ope);
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
	Tokenizer *testTokenizer = initTokenizer("25*456");
	
	//Since the program already can detect 25.
	Token *testToken = getToken(testTokenizer);
	free(testToken);
	testToken = getToken(testTokenizer);
	
	//This testToken should be not NULL
	TEST_ASSERT_NOT_NULL(testToken);
	//With operator type.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(MULTIPLY,opeToken->ope);
	free(testTokenizer);
	free(opeToken);
	
}

void test_getToken_should_detect_divide_sign()
{
	Tokenizer *testTokenizer = initTokenizer("25/456");
	
	//Since the program already can detect 25.
	Token *testToken = getToken(testTokenizer);
	free(testToken);
	testToken = getToken(testTokenizer);
	
	//This testToken should be not NULL
	TEST_ASSERT_NOT_NULL(testToken);
	//With operator type.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(DIVIDE,opeToken->ope);
	free(testTokenizer);
	free(opeToken);
	
}

void test_getToken_should_detect_modulus_sign()
{
	Tokenizer *testTokenizer = initTokenizer("200%10");
	
	//Since the program already can detect 25.
	Token *testToken = getToken(testTokenizer);
	free(testToken);
	testToken = getToken(testTokenizer);
	
	//This testToken should be not NULL
	TEST_ASSERT_NOT_NULL(testToken);
	//With operator type.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(MODULUS,opeToken->ope);
	free(testTokenizer);
	free(opeToken);
	
}

void test_getToken_should_detect_current_program_counter_sign()
{
	Tokenizer *testTokenizer = initTokenizer("2+$");
	
	//Since the program already can detect 2 and +.
	Token *testToken = getToken(testTokenizer);
	free(testToken);
	testToken = getToken(testTokenizer);
	free(testToken);
	testToken = getToken(testTokenizer);
	
	//This testToken should be not NULL
	TEST_ASSERT_NOT_NULL(testToken);
	//With operator type.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(CURRENT_PROGRAM_COUNTER,opeToken->ope);
	free(testTokenizer);
	free(opeToken);
	
	//Try reverse the other of the equation
	testTokenizer = initTokenizer("$+2");
	
	testToken = getToken(testTokenizer);

	//This testToken should be not NULL
	TEST_ASSERT_NOT_NULL(testToken);
	//With operator type.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(CURRENT_PROGRAM_COUNTER,opeToken->ope);
	free(testTokenizer);
	free(opeToken);
	
}

void test_getToken_should_detect_parenthesis_sign()
{
	Tokenizer *testTokenizer = initTokenizer("(2+3)");
	
	Token *testToken = getToken(testTokenizer);
	
	//This testToken should be not NULL
	TEST_ASSERT_NOT_NULL(testToken);
	//With operator type.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(LEFT_PARENTHESIS,opeToken->ope);
	
	//Read out the 2 , + and 3
	testToken = getToken(testTokenizer);
	free(testToken);
	testToken = getToken(testTokenizer);
	free(testToken);
	testToken = getToken(testTokenizer);
	
	testToken = getToken(testTokenizer);
	//This testToken should be not NULL
	TEST_ASSERT_NOT_NULL(testToken);
	//With operator type.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(RIGHT_PARENTHESIS,opeToken->ope);
	free(testTokenizer);
	free(opeToken);
}

void test_getToken_should_detect_equal_sign()
{
	Tokenizer *testTokenizer = initTokenizer("2+3=5");
	
	//Since the program already can detect 2,+ and 3.
	Token *testToken = getToken(testTokenizer);
	testToken = getToken(testTokenizer);
	free(testToken);
	testToken = getToken(testTokenizer);
	free(testToken);
	testToken = getToken(testTokenizer);
	
	//This testToken should be not NULL
	TEST_ASSERT_NOT_NULL(testToken);
	//With operator type.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(EQUAL,opeToken->ope);
	free(testTokenizer);
	free(opeToken);
	
	
}

void test_getToken_should_detect_not_sign()
{
	Tokenizer *testTokenizer = initTokenizer("2+3+!3");
	
	//Since the program already can detect 2,+ and 3.
	Token *testToken = getToken(testTokenizer);
	testToken = getToken(testTokenizer);	//2
	free(testToken);
	testToken = getToken(testTokenizer);	//+
	free(testToken);
	testToken = getToken(testTokenizer);	//3
	free(testToken);
	testToken = getToken(testTokenizer);	//+
	
	//This testToken should be not NULL
	TEST_ASSERT_NOT_NULL(testToken);
	//With operator type.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(LOGIC_NOT,opeToken->ope);
	free(testTokenizer);
	free(opeToken);
	
	//getToken should diffrentiate NOT and not equal
	testTokenizer = initTokenizer("2+3!=5");
	
	//Since the program already can detect 2,+ and 3.
	testToken = getToken(testTokenizer);
	free(testToken);
	testToken = getToken(testTokenizer);
	free(testToken);
	testToken = getToken(testTokenizer);
	free(testToken);
	testToken = getToken(testTokenizer);
	
	//This testToken should be not NULL
	TEST_ASSERT_NOT_NULL(testToken);
	//With operator type.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(NOT_EQUAL,opeToken->ope);
	
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

void test_getToken_should_indentify_negation_symbol()
{
	Tokenizer *testTokenizer = initTokenizer("-2+6");
	Token *testToken = getToken(testTokenizer);
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator * opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(NEGATION,opeToken->ope);
	free(testTokenizer);
	free(opeToken);
	
	
	//Try do on some different equation 
	
	testTokenizer = initTokenizer("2+-6");
	testToken = getToken(testTokenizer); //2
	free(testToken);
	testToken = getToken(testTokenizer); //+
	free(testToken);
	testToken = getToken(testTokenizer); //-
	
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(NEGATION,opeToken->ope);
	free(testTokenizer);
	free(opeToken);
	
	//What if there is a double '-' sign ?
	
	testTokenizer = initTokenizer("2--6");
	testToken = getToken(testTokenizer); //2
	free(testToken);
	testToken = getToken(testTokenizer); //-
	
	//Should get as subtract for the first '-'
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(SUBTRACT,opeToken->ope);
	
	//Should get as negation for the second '-'
	testToken = getToken(testTokenizer); //-
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(NEGATION,opeToken->ope);
	free(testTokenizer);
	free(opeToken);
	
	
}

void test_getToken_should_detect_complement_in_an_expression()
{
	Tokenizer *testTokenizer = initTokenizer("~2+9");
	

	Token *testToken = getToken(testTokenizer);
	
	//This testToken should be not NULL
	TEST_ASSERT_NOT_NULL(testToken);
	//With operator type.
	TEST_ASSERT_EQUAL(OPERATOR,*testToken);
	Operator *opeToken = (Operator*)testToken;
	TEST_ASSERT_EQUAL(OPERATOR,opeToken->type);
	TEST_ASSERT_EQUAL(COMPLEMENT,opeToken->ope);
	
}

void test_copyString_should_copy_the_string_from_source_to_destination()
{
	char * newString ="Hello World!!!!";
	char * stringGet = malloc (sizeof(char)*(strlen(newString)));
	
	//Start From the location 6 and the size is 5
	copyString (newString,stringGet,6,5);
	
	TEST_ASSERT_EQUAL('W',stringGet[0]);
	TEST_ASSERT_EQUAL('o',stringGet[1]);
	TEST_ASSERT_EQUAL('r',stringGet[2]);
	TEST_ASSERT_EQUAL('l',stringGet[3]);
	TEST_ASSERT_EQUAL('d',stringGet[4]);
	TEST_ASSERT_EQUAL_STRING("World",stringGet);

}

void test_copyStringWithoutSpace_should_copy_the_string_without_space_and_tab()
{


	char * newString ="Hello World!";
	char * stringGet ;
	

	copyStringWithoutSpace (newString,stringGet);
	
	TEST_ASSERT_EQUAL('H',stringGet[0]);
	TEST_ASSERT_EQUAL('e',stringGet[1]);
	TEST_ASSERT_EQUAL('l',stringGet[2]);
	TEST_ASSERT_EQUAL('l',stringGet[3]);
	TEST_ASSERT_EQUAL('o',stringGet[4]);
	TEST_ASSERT_EQUAL_STRING("HelloWorld!",stringGet);
	
	
	newString ="Hello 		World!			  ";
	
	copyStringWithoutSpace (newString,stringGet);
	TEST_ASSERT_EQUAL_STRING("HelloWorld!",stringGet);
	
	//Make sure it do nothing on normal string.
	newString ="Hello";
	copyStringWithoutSpace (newString,stringGet);
	TEST_ASSERT_EQUAL_STRING("Hello",stringGet);
	

	
}

/*
This is the testing program for the casting.
After we get the address after a casting , we need to cast it back to his original type
so that we can access to the member inside this structure.

void test_something_about_type_casting()
{
	Token *newToken;
	Number *newNumber=malloc(sizeof(Number));
	newNumber->type = NUMBER;
	newNumber->value = 8;
	newToken = (Token *)newNumber;
	newNumber= (Number *)newToken;
	printf("Type:%d,Value:%d\n",newNumber->type,newNumber->value);
	printf("The type of the token: %d\n",*newToken);
	
}


This program is use to test the structure behaviour.
For testing purpose.

void test_Playing_with_the_struct()
{
	Tokenizer tokenizer;
	//Try if the string are empty and the program are going to access.
	//printf("The string inside the tokenizer is: %s",tokenizer.rawString);
	//Actually will return an error.

	tokenizer.rawString = "2+3";
	printf("The string inside the tokenizer is: %s\n",tokenizer.rawString);
	//Try to work on the length and also the start index.
	tokenizer.startIndex =0;
	tokenizer.length = 3;
	printf("The startIndex:%d \t The length:%d \n",tokenizer.startIndex,tokenizer.length);
	
	//If the tokenizer is a pointer?
	
	Tokenizer *ptrTokenizer = malloc (sizeof(Tokenizer));
	ptrTokenizer-> rawString ="Hello World ! Nothing here, just want to lengthen this string and observe the effect on the memory";
	ptrTokenizer->startIndex=4567813;
	ptrTokenizer->length = 99999999;
	printf ("String:%s \n Start Index:%d \n Length:%d\n",ptrTokenizer-> rawString,ptrTokenizer->startIndex,ptrTokenizer->length);
	free(ptrTokenizer);
	
}
*/