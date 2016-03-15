#ifndef TokenType_h
#define TokenType_h

#include <string>
using namespace std;
//declares token types
enum TokenType { COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, eof, NEWLINE, SPACE, POUND };

string TokenTypeToString(TokenType tokenType);
#endif