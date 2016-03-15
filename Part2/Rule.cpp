#include "Rule.h"

using namespace std;

Rule::Rule(Predicate predicate_in)
{
	predicate = predicate_in;
}

void Rule::addPredicate(Predicate pred)
{
	predicateList.push_back(pred);
}