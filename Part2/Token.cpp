#include "Token.h"
using namespace std;
//Token functions and the toString function that will output the file
Token::Token(TokenType value_in, string token_in, int lineNumber_in)
{
	value = value_in;
	token = token_in;
	lineNumber = lineNumber_in;
}


TokenType Token::getValue()
{
	return value;
}
void Token::setValue(TokenType t)
{
	value = t;
}
string Token::getToken()
{
	return token;
}
void Token::setToken(string s)
{
	token = s;
}
int Token::getLineNumber()
{
	return lineNumber;
}
void Token::setLineNumber(int i)
{
	lineNumber = i;
}
string Token::toString()
{
	stringstream ss;
	ss << "(";
	ss << TokenTypeToString(value);
	ss << ",\"";
	ss << token;
	ss << "\",";
	ss << lineNumber;
	ss << ")";
	return ss.str();
}