#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <set>

#include "Parser.h"
#include "Predicate.h"
#include "Query.h"
#include "Rule.h"


using namespace std;

Token tempToken = Token(COMMA, "", 0);
vector<Predicate> Schemes;
vector<Predicate> Facts;
vector<Rule> Rules;
vector<Predicate> Queries;
set <string> domain;
set <string>::iterator sort;

Parser::Parser()
{
	position = 0;
}

void Parser::parse(vector<Token>& tokens)
{
	getTokenParts(tokens);
	match(SCHEMES);
	getTokenParts(tokens);
	match(COLON);
	parseSchemeList(tokens);
	match(FACTS);
	getTokenParts(tokens);
	match(COLON);
	getTokenParts(tokens);
	parseFactList(tokens);
	match(RULES);
	getTokenParts(tokens);
	match(COLON);
	getTokenParts(tokens);
	parseRuleList(tokens);
	match(QUERIES);
	getTokenParts(tokens);
	match(COLON);
	parseQueryList(tokens);
}

void Parser::getTokenParts(vector<Token>& tokens)
{
	if (position < tokens.size()){
		//tempToken.value = tokens[position].getValue;
		tempToken.setValue(tokens[position].getValue());
		//tempToken.token = tokens[position].getToken();
		tempToken.setToken(tokens[position].getToken());
		//tempToken.lineNumber = tokens[position].getLineNumber();
		tempToken.setLineNumber(tokens[position].getLineNumber());
	}
	else{
		throw(tempToken);
	}
}

void Parser::match(TokenType tokenType)
{
	if (tokenType == tempToken.getValue()){
		advancePosition();
	}
	else{
		throw(tempToken);
	}
}

void Parser::advancePosition()
{
	position++;
}

void Parser::parseSchemeList(vector<Token>& tokens)
{
	while (tempToken.getValue() != FACTS){
		getTokenParts(tokens);
		match(ID);
		Predicate predicate(tempToken.getToken());
		getTokenParts(tokens);
		match(LEFT_PAREN);
		parseParamList(tokens, predicate);
		match(RIGHT_PAREN);
		Schemes.push_back(predicate);
		getTokenParts(tokens);
	}
}

void Parser::parseFactList(vector<Token>& tokens)
{
	while (tempToken.getValue() != RULES){
		match(ID);
		Predicate predicate(tempToken.getToken());
		getTokenParts(tokens);
		match(LEFT_PAREN);
		parseParamList(tokens, predicate);
		match(RIGHT_PAREN);
		getTokenParts(tokens);
		match(PERIOD);
		Facts.push_back(predicate);
		getTokenParts(tokens);
	}
}

void Parser::parseRuleList(vector<Token>& tokens)
{
	while (tempToken.getValue() != QUERIES){
		match(ID);
		Predicate predicate(tempToken.getToken());
		getTokenParts(tokens);
		match(LEFT_PAREN);
		parseParamList(tokens, predicate);
		match(RIGHT_PAREN);
		Rule rule(predicate);
		getTokenParts(tokens);
		match(COLON_DASH);
		parsePredicateList(tokens, rule);
		match(PERIOD);
		Rules.push_back(rule);
		getTokenParts(tokens);
	}
}

void Parser::parseQueryList(vector<Token>& tokens)
{
	while (position < tokens.size()){
		getTokenParts(tokens);
		match(ID);
		Predicate predicate(tempToken.getToken());
		getTokenParts(tokens);
		match(LEFT_PAREN);
		parseParamList(tokens, predicate);
		match(RIGHT_PAREN);
		Queries.push_back(predicate);
		getTokenParts(tokens);
		match(Q_MARK);
		if (position < tokens.size()){
			getTokenParts(tokens);
			if (tempToken.getValue() == eof){
				match(eof);
			}
		}
	}
}

void Parser::parseParamList(vector<Token>& tokens, Predicate& predicate)
{
	getTokenParts(tokens);
	if (tempToken.getValue() == STRING){
		match(STRING);
		Parameter parameter(tempToken.getValue(), tempToken.getToken());
		predicate.addParameter(parameter);
		domain.insert(tempToken.getToken());
	}
	else{
		match(ID);
		Parameter parameter(tempToken.getValue(), tempToken.getToken());
		predicate.addParameter(parameter);
	}
	getTokenParts(tokens);
	if (tempToken.getValue() == COMMA){
		advancePosition();
		parseParamList(tokens, predicate);
	}
	else{
		//do nothing, epsilon
	}
}

void Parser::parsePredicateList(vector<Token>& tokens, Rule& rule)
{
	getTokenParts(tokens);
	match(ID);
	Predicate predicate(tempToken.getToken());
	getTokenParts(tokens);
	match(LEFT_PAREN);
	parseParamList(tokens, predicate);
	rule.addPredicate(predicate);
	getTokenParts(tokens);
	match(RIGHT_PAREN);
	getTokenParts(tokens);
	if (tempToken.getValue() == COMMA){		//recursive
		advancePosition();
		parsePredicateList(tokens, rule);
	}
	else{
		//do nothing, epsilon option
	}
}

void Parser::print(ofstream& output)
{
	output << "Success!" << endl;
	printSchemes(output);
	printFacts(output);
	printRules(output);
	printQueries(output);
	printDomain(output);
}

void Parser::printSchemes(ofstream& output)
{
	output << "Schemes(" << Schemes.size() << "):" << endl;
	for (int i = 0; i < Schemes.size(); i++){
		output << Schemes[i].toString();
		for (int j = 0; j < Schemes[i].parameterList.size(); j++){
			output << Schemes[i].parameterList[j].toString();
			if (j < (Schemes[i].parameterList.size() - 1)){
				output << ",";
			}
		}
		output << ")" << endl;
	}
}

void Parser::printFacts(ofstream& output)
{
	output << "Facts(" << Facts.size() << "):" << endl;
	for (int i = 0; i < Facts.size(); i++){
		output << Facts[i].toString();
		for (int j = 0; j < Facts[i].parameterList.size(); j++){
			output << Facts[i].parameterList[j].toString();
			if (j < (Facts[i].parameterList.size() - 1)){
				output << ",";
			}
		}
		output << ")" << endl;
	}
}

void Parser::printRules(ofstream& output)
{
	output << "Rules(" << Rules.size() << "):" << endl;
	for (int i = 0; i < Rules.size(); i++){
		output << "  " << Rules[i].predicate.data << "(";

		for (int j = 0; j < Rules[i].predicate.parameterList.size(); j++){
			output << Rules[i].predicate.parameterList[j].toString();
			if (j < (Rules[i].predicate.parameterList.size() - 1)){
				output << ",";
			}
		}
		output << ") :- ";

		for (int c = 0; c < Rules[i].predicateList.size(); c++){
			output << Rules.at(i).predicateList[c].data << "(";

			for (int d = 0; d < Rules[i].predicateList[c].parameterList.size(); d++){
				output << Rules[i].predicateList[c].parameterList[d].toString();
				if (d < (Rules[i].predicateList[c].parameterList.size() - 1)){
					output << ",";
				}
			}
			if (c < (Rules[i].predicateList.size() - 1)){
				output << "),";
			}
			else{
				output << ")" << endl;
			}
		}
	}
}

void Parser::printQueries(ofstream& output)
{
	output << "Queries(" << Queries.size() << "):" << endl;
	for (int i = 0; i < Queries.size(); i++){
		output << Queries[i].toString();
		for (int j = 0; j < Queries[i].parameterList.size(); j++){
			output << Queries[i].parameterList[j].toString();
			if (j < (Queries[i].parameterList.size() - 1)){
				output << ",";
			}
		}
		output << ")" << endl;
	}
}

void Parser::printDomain(ofstream& output)
{
	output << "Domain(" << domain.size() << "):" << endl;
	for (sort = domain.begin(); sort != domain.end(); sort++){
		output << "  " << *sort << endl;
	}
}