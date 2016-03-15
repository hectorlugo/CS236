#include "Rule.h"

using namespace std;

void Rule::addPredicate(Predicate pred)
{
	rulePredicateList.push_back(pred);
}

void Rule::setRulePred(Predicate r)
{
	rulePred = r;
}

void Rule::emptyRule()
{
	rulePredicateList.clear();
}

Predicate Rule::getRulePred()
{
	return rulePred;
}

vector<Predicate> Rule::getRulePredicateList()
{
	return rulePredicateList;
}

string Rule::toString()
{
	stringstream ss;
	ss << rulePred.toString() << " :- ";

	for (int i = 0; i < rulePredicateList.size(); i++){
		ss << rulePredicateList[i].toString();

		if (i < rulePredicateList.size() - 1){
			ss << ",";
		}
	}
	return ss.str();
}