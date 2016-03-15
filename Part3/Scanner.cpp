#include "Scanner.h"
#include <iostream>


using namespace std;
Scanner::Scanner(){}
Scanner::Scanner(string fileName_in, string fileName_out)
{
	fail = false;
	lineNumber = 1;
	loadFile(fileName_in, tokens, fail, lineNumber);
	//outFile(fileName_out, tokens, fail, lineNumber);
	
}

void Scanner::loadFile(string fileName, vector<Token>& tokens, bool& fail, int& lineNumber)
{
	ifstream input;
	string value;
	string stringToken;
	input.open(fileName);

	while (input.good() && !input.eof()){
		char curr = input.get();
		TokenType tokenType;

		switch (curr){
		case ',':	tokenType = COMMA;			break;
		case '.':	tokenType = PERIOD;			break;
		case '?':	tokenType = Q_MARK;			break;
		case '(':	tokenType = LEFT_PAREN;		break;
		case ')':	tokenType = RIGHT_PAREN;	break;
		case ':':
			if (input.peek() == '-'){
				tokenType = COLON_DASH;
				input.ignore();
				break;
			}
			else{
				tokenType = COLON;			break;
			}
		case '\'':{
					  captureStringToken(input, curr, stringToken, fail);
					  tokenType = STRING;
					  break;
		}
		case '\n':	tokenType = NEWLINE;		break;
		case '#':	tokenType = POUND;			break;
		case EOF:	tokenType = eof;			break;
		default: {
					 defaultTest(input, curr, tokenType, stringToken, fail);
		}
		}

		if (fail){
			return;
		}
		else{
			afterTest(tokenType, value, lineNumber, stringToken, tokens, input);
		}

	}  //end of while loop

}

void Scanner::afterTest(TokenType tokenType, string value, int& lineNumber, string stringToken, vector<Token>& tokens, ifstream& input){

	if (tokenType == NEWLINE){
		//increments the line number when it reaches a new line
		lineNumber++;
	}
	else if (tokenType == SPACE){
		//DO NOTHING for spaces between tokens
	}
	else if (tokenType == POUND){
		skipLine(input);
	}
	else{
		pushToken(tokenType, value, lineNumber, stringToken, tokens);
	}

}

void Scanner::defaultTest(ifstream& input, char& curr, TokenType& tokenType, string& stringToken, bool& fail){
	if (isalpha(curr)){
		getString(input, curr, tokenType, stringToken);
	}
	else if (isdigit(curr)){
		fail = true;
	}
	else if (isspace(curr)){
		tokenType = SPACE;
	}
	else{
		fail = true;
	}
}

void Scanner::outFile(string fileName, vector<Token>& tokens, bool fail, int lineNumber){
	ofstream output;
	output.open(fileName);

	for (int i = 0; i < tokens.size(); i++){
		output << tokens[i].toString() << endl;
	}
	if (fail){
		output << "Input ERROR on line " << lineNumber;
	}
	else{
		output << "Total Tokens = " << tokens.size();
	}

	/*try{
		Parser parser;
		parser.parse(tokens);
		parser.print(output);
	}
	catch (Token error){
		output << "Failure!" << endl;
		output << "  " << error.toString();
	}*/

	output.close();
}

void Scanner::pushToken(TokenType tokenType, string value, int lineNumber, string stringToken, vector<Token>& tokens){
	value = getTokenSymbol(tokenType, stringToken);
	Token newToken = Token(tokenType, value, lineNumber);
	tokens.push_back(newToken);
}

void Scanner::captureStringToken(ifstream& input, char& curr, string& tokenString, bool& fail){
	tokenString = "";
	tokenString += curr;
	while (input.peek() != '\'' && input.peek() != '\n'){
		curr = input.get();
		tokenString += curr;
	}
	if (input.peek() == '\''){
		curr = input.get();
		tokenString += curr;
	}
	else{
		fail = true;
	}
}
//function to ignore comments
void Scanner::skipLine(ifstream& input){
	while (input.peek() != '\n'){
		if (input.peek() == -1){
			return;
		}
		input.ignore();
	}
}
//Checks for the four token keywords as well as possible ID tokens
void  Scanner::getString(ifstream& input, char& curr, TokenType& tokenType, string& value){
	value = "";
	value += curr;
	while (isalnum(input.peek())){ //checks if char is alpha numeric. OK since first char test was done before
		curr = input.get();
		value += curr;
	}
	if (value == "Schemes"){
		tokenType = SCHEMES;
	}
	else if (value == "Facts"){
		tokenType = FACTS;
	}
	else if (value == "Rules"){
		tokenType = RULES;
	}
	else if (value == "Queries"){
		tokenType = QUERIES;
	}
	else{	//token is an ID if previous keywords fail to match
		tokenType = ID;
	}

}
//checks the token type and outputs the string value, ID and string get passed along
string Scanner::getTokenSymbol(TokenType tokenType, string& idToken){
	string token;

	switch (tokenType){
	case COMMA:			token = ",";		break;
	case PERIOD:		token = ".";		break;
	case Q_MARK:		token = "?";		break;
	case LEFT_PAREN:	token = "(";		break;
	case RIGHT_PAREN:	token = ")";		break;
	case COLON:			token = ":";		break;
	case COLON_DASH:	token = ":-";		break;
	case SCHEMES:		token = "Schemes";	break;
	case FACTS:			token = "Facts";	break;
	case RULES:			token = "Rules";	break;
	case QUERIES:		token = "Queries";	break;
	case ID:			token = idToken;			break;
	case STRING:		token = idToken;			break;
	case eof:			token = "";			break;
	}
	return token;
}

Token Scanner::getToken(int i)
{
	return tokens[i];
}