#include "Datalog.h"

using namespace std;

Datalog::Datalog(){};

void Datalog::addScheme(Predicate schemePred)
{
	Schemes.push_back(schemePred);
}

void Datalog::addFact(Predicate factPred)
{
	Facts.push_back(factPred);
}

void Datalog::addQuery(Predicate queryPred)
{
	Queries.push_back(queryPred);
}

void Datalog::addRule(Rule rule)
{
	Rules.push_back(rule);
}

void Datalog::addValue(string s)
{
	domain.insert(s);
}

vector<Predicate> Datalog::getSchemes()
{
	return Schemes;
}

vector<Predicate> Datalog::getFacts()
{
	return Facts;
}

vector<Predicate> Datalog::getQueries()
{
	return Queries;
}

vector<Rule> Datalog::getRules()
{
	return Rules;
}

string Datalog::toString()
{
	stringstream ss;
	ss << "Schemes(" << Schemes.size() << "):" << endl;
	for (int i = 0; i < Schemes.size(); i++){
		ss << "  " << Schemes[i].toString() << endl;
	}
	
	ss << "Facts(" << Facts.size() << "):" << endl;

	for (int i = 0; i < Facts.size(); i++){
		ss << "  " << Facts[i].toString() << endl;
	}

	ss << "Rules(" << Rules.size() << "):" << endl;

	for (int i = 0; i < Rules.size(); i++){
		ss << "  " << Rules[i].toString() << endl;
	}

	ss << "Queries(" << Queries.size() << "):" << endl;

	for (int i = 0; i < Queries.size(); i++){
		ss << "  " << Queries[i].toString() << endl;
	}

	ss << "Domain(" << domain.size() << "):" << endl;
	set<string>::iterator it;

	for (it = domain.begin(); it != domain.end(); it++){
		string s = *it;
		ss << "  " << s << endl;
	}

	return ss.str();
}