#include "TokenType.h"

using namespace std;

//returns a string version of the token. 

string TokenTypeToString(TokenType tokenType){
	string tokenString;
	switch (tokenType){
		case COMMA:			tokenString = "COMMA";			break;
		case PERIOD:		tokenString = "PERIOD";			break;
		case Q_MARK:		tokenString = "Q_MARK";			break;
		case LEFT_PAREN:	tokenString = "LEFT_PAREN";		break;
		case RIGHT_PAREN:	tokenString = "RIGHT_PAREN";	break;
		case COLON:			tokenString = "COLON";			break;
		case COLON_DASH:	tokenString = "COLON_DASH";		break;
		case SCHEMES:		tokenString = "SCHEMES";		break;
		case FACTS:			tokenString = "FACTS";			break;
		case RULES:			tokenString = "RULES";			break;
		case QUERIES:		tokenString = "QUERIES";		break;
		case ID:			tokenString = "ID";				break;
		case STRING:		tokenString = "STRING";			break;
		case eof:			tokenString = "EOF";			break;
		case NEWLINE:		tokenString = "NEWLINE";		break;
		case SPACE:			tokenString = "SPACE";			break;
	}
	return tokenString;
}