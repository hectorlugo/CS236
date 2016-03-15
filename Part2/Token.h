#ifndef Token_h
#define Token_h
#include <iostream>
#include <string>
#include <sstream>
#include "TokenType.h"

using namespace std;
//creates the token class to later be saved as Token objects
class Token
{
	private:
		TokenType value;
		int lineNumber;
		string token;

	public:
		Token(TokenType value_in, string token_in, int lineNumber_in);
		

		TokenType getValue();
		void setValue(TokenType);
		string getToken();
		void setToken(string);
		int getLineNumber();
		void setLineNumber(int);

		string toString();
};
#endif