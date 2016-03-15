#include "Parser.h"

using namespace std;

//uses scanner
Parser::Parser(string fileName_in, string fileName_out) : scan(fileName_in, fileName_out)
{
	position = 0;
	token = scan.getToken(position);
	ofstream output;
	output.open(fileName_out);
	
	try{
		parseDatalog();
		output << toString();
	}
	catch (Token token){

		output << errorToString();
	}
	output.close();
}

void Parser::advancePosition()
{
	position++;
}

void Parser::parseDatalog()
{
	match(SCHEMES);
	match(COLON);
	if (token.getTokenType() == FACTS){ error(token); }
	parseSchemeList();
	match(FACTS);
	match(COLON);
	if (token.getTokenType() == ID){ parseFactList(); }
	match(RULES);
	match(COLON);
	if (token.getTokenType() == ID){ parseRuleList(); }
	match(QUERIES);
	match(COLON);
	parseQueryList();
}

void Parser::parseSchemeList()
{
	predicate.emptyPredicate();
	parseScheme();
	datalog.addScheme(predicate);
	if (token.getTokenType() == FACTS){
		return;
	}
	else if (token.getTokenType() == ID){
		parseSchemeList();
	}
	else{
		error(token);
	}
}

void Parser::parseScheme()
{
	parsePredicate();
}

void Parser::parseFactList()
{
	predicate.emptyPredicate();
	parseFact();
	datalog.addFact(predicate);
	if (token.getTokenType() == RULES){
		return;
	}
	else if (token.getTokenType() == ID){
		parseFactList();
	}
	else{
		error(token);
	}
}

void Parser::parseFact()
{
	parsePredicate();
	match(PERIOD);
}

void Parser::parseRuleList()
{
	rule.emptyRule();
	parseRule();
	datalog.addRule(rule);
	if (token.getTokenType() == QUERIES){
		return;
	}
	else if (token.getTokenType() == ID){
		parseRuleList();
	}
	else{
		error(token);
	}
}

void Parser::parseRule()
{
	predicate.emptyPredicate();
	parsePredicate();
	rule.setRulePred(predicate);
	match(COLON_DASH);
	parsePredicateList();
	match(PERIOD);
}

void Parser::parseQueryList()
{
	predicate.emptyPredicate();
	parseQuery();
	datalog.addQuery(predicate);
	match(Q_MARK);
	if (token.getTokenType() == eof){
		return;
	}
	else if (token.getTokenType() == ID){
		parseQueryList();
	}
	else{
		error(token);
	}
}

void Parser::parseQuery()
{
	parsePredicate();
}

void Parser::parsePredicateList()
{
	predicate.emptyPredicate();
	parsePredicate();
	rule.addPredicate(predicate);
	if (token.getTokenType() == COMMA){
		match(COMMA);
		parsePredicateList();
	}
}

void Parser::parsePredicate()
{
	predicate.setData(token.getValue());
	match(ID);
	match(LEFT_PAREN);
	parseParameterList();
	match(RIGHT_PAREN);
}

void Parser::parseParameterList(){
	parseParameter();
	predicate.addParameter(parameter);
	if (token.getTokenType() == COMMA){
		match(COMMA);
		parseParameterList();
	}
}

void Parser::parseParameter()
{
	if (token.getTokenType() == STRING){
		parameter.setValue(token.getValue());
		datalog.addValue(token.getValue());
		match(STRING);
	}
	else if (token.getTokenType() == ID){
		parameter.setValue(token.getValue());
		match(ID);
	}
	else{
		error(token);
	}
}

Datalog Parser::getDatalog()
{
	return datalog;
}

void Parser::match(TokenType tokentype)
{
	if (token.getTokenType() == tokentype){
		advancePosition();
		token = scan.getToken(position);
	}
	else{
		error(token);
	}
}

void Parser::error(Token e)
{
	throw e;
}

string Parser::errorToString()
{
	stringstream ss;
	ss << "Failure!" << endl;
	ss << "  " << token.toString();
	return ss.str();
}

string Parser::toString()
{
	stringstream ss;
	ss << "Success!" << endl;
	ss << datalog.toString();
	return ss.str();
}