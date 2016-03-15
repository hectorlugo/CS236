#pragma once

#include <vector>
#include "Predicate.h"

using namespace std;

class Rule {
	public:
		Predicate predicate;
		vector<Predicate> predicateList;

	
		Rule(Predicate);
		void addPredicate(Predicate);
};