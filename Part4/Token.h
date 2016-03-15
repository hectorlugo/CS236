#include "TokenType.h"
#include <iostream>

using namespace std;

class Token
{
	private:
		TokenType tokenType;
		string value;
		int lineNumber;
		
	public:
		Token();
		Token(TokenType, string, int);
		int getLineNumber();
		string getValue();
		TokenType getTokenType();
		
		void setTokenType(TokenType);
		void setValue(string);
		void setLineNumber(int);

		string toString();
};