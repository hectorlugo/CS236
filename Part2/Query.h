#pragma once

#include "Predicate.h"

using namespace std;

class Query {
	public:
		Predicate myPredicate;
		Query(Predicate);
};