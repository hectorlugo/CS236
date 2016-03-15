#include "Token.h"
#include <sstream>
//Token functions and the toString function that will output the file
using namespace std;

Token::Token(){}
Token::Token(TokenType tokenType_in, string value_in, int lineNumber_in)
{
	tokenType = tokenType_in;
	value = value_in;
	lineNumber = lineNumber_in;
}

int Token::getLineNumber()
{
	return lineNumber;
}

string Token::getValue()
{
	return value;
}

TokenType Token::getTokenType()
{
	return tokenType;
}

void Token::setTokenType(TokenType t)
{
	tokenType = t;
}

void Token::setValue(string v)
{
	value = v;
}

void Token::setLineNumber(int i)
{
	lineNumber = i;
}

string Token::toString()
{
	stringstream ss;
	ss << "(";
	ss << TokenTypeToString(tokenType);
	ss << ",\"";
	ss << value;
	ss << "\",";
	ss << lineNumber;
	ss << ")";
	return ss.str();
}
