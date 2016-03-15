#pragma once

#include <iostream>
#include <sstream>

#include "Token.h"

using namespace std;

class Parameter{
	public:
		TokenType tokentype;
		string info;
		
	
		Parameter(TokenType tokentype_in, string info_in);
		string toString();
};