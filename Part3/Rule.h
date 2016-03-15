#pragma once
#include <vector>
#include "Predicate.h"

using namespace std;

class Rule{
private:
	Predicate rulePred;
	vector<Predicate> rulePredicateList;
public:
	void addPredicate(Predicate);
	void setRulePred(Predicate);
	void emptyRule();
	Predicate getRulePred();
	vector<Predicate> getRulePredicateList();
	string toString();
};