#pragma once
#include "Scanner.h"
#include "Datalog.h"

using namespace std;

class Parser{
	private:
		Datalog datalog;
		Rule rule;
		Predicate predicate;
		Parameter parameter;
		Scanner scan;
		Token token;
		int position;
		void parseSchemeList();
		void parseScheme();
		void parseFactList();
		void parseFact();
		void parseRuleList();
		void parseRule();
		void parseQueryList();
		void parseQuery();
		void parsePredicateList();
		void parsePredicate();
		void parseParameterList();
		void parseParameter();
		void match(TokenType);
		void error(Token);

	public:
		Parser(string, string);
		void advancePosition();
		void parseDatalog();
		Datalog getDatalog();
		Rule getRule();
		Predicate getPredicate();
		Parameter getParameter();
		string errorToString();
		string toString();
};