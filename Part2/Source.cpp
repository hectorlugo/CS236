#include <iostream>
#include <fstream>
#include <vector>
#include <ctype.h>
#include <string>
#include "Token.h"
#include "Parser.h"


using namespace std;
//checks the token type and outputs the string value, ID and string get passed along
string getToken(TokenType tokenType, string& idToken){
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
//Checks for the four token keywords as well as possible ID tokens
void getString(ifstream& input, char& curr, TokenType& tokenType, string& token){
	token = "";
	token += curr;
	while (isalnum(input.peek())){ //checks if char is alpha numeric. OK since first char test was done before
		curr = input.get();
		token += curr;
	}
	if (token == "Schemes"){
		tokenType = SCHEMES;
	}
	else if (token == "Facts"){
		tokenType = FACTS;
	}
	else if (token == "Rules"){
		tokenType = RULES;
	}
	else if (token == "Queries"){
		tokenType = QUERIES;
	}
	else{	//token is an ID if previous keywords fail to match
		tokenType = ID;
	}

}
//captures the string to be used for the value in a STRING token
void captureStringToken(ifstream& input, char& curr, string& tokenString, bool& fail){
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
void skipLine(ifstream& input){
	while (input.peek() != '\n'){
		if (input.peek() == -1){
			return;
		}
		input.ignore();
	}
}

void pushToken(TokenType tokenType, string token, int lineNumber, string stringToken, vector<Token>& tokens){
	token = getToken(tokenType, stringToken);
	Token newToken = Token(tokenType, token, lineNumber);
	tokens.push_back(newToken);
}

//outputs the collected data to the file specified in the command line
void outFile(string fileName, vector<Token>& tokens, bool fail, int lineNumber){
	ofstream output;
	output.open(fileName);
	
	try{
		Parser parser;
		parser.parse(tokens);
		parser.print(output);
	}
	catch (Token error){
		output << "Failure!" << endl;
		output << "  " << error.toString();
	}

	output.close();
}

void defaultTest(ifstream& input, char& curr, TokenType& tokenType, string& stringToken, bool& fail){
	if(isalpha(curr)){
		getString(input, curr, tokenType, stringToken);
	}
	else if(isdigit(curr)){
		fail = true;
	}
	else if(isspace(curr)){
		tokenType = SPACE;
	}
	else{
		fail = true;
	}
}

void afterTest(TokenType tokenType, string token, int& lineNumber, string stringToken, vector<Token>& tokens, ifstream& input){
	
	if (tokenType == NEWLINE){
		//increments the line number when it reaches a new line
		lineNumber++;
	}
	else if(tokenType == SPACE){
		//DO NOTHING for spaces between tokens
	}
	else if (tokenType == POUND){
			skipLine(input);
	}
	else{	
		pushToken(tokenType, token, lineNumber, stringToken, tokens);
	}
	
}

//opens the file and goes through each character to find the tokens
void loadFile(string fileName, vector<Token>& tokens, bool& fail, int& lineNumber){
	ifstream input;
	string token;
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
			afterTest(tokenType, token, lineNumber, stringToken, tokens, input);
		}
	
	}  //end of while loop
}

int main(int argc, char* argv[]){
	vector<Token> tokens;
	bool fail = false;
	int lineNumber = 1;
	loadFile(argv[1], tokens, fail, lineNumber);
	outFile(argv[2], tokens, fail, lineNumber);
	return 0;
}
