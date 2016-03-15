#include "Parameter.h"

using namespace std;

Parameter::Parameter(TokenType tokentype_in, string info_in)
{
	tokentype = tokentype_in;
	info = info_in;
}

string Parameter::toString()
{
	stringstream ss;
	
		ss << info;
	
	return ss.str();
}