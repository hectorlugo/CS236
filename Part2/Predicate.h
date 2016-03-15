#pragma once

#include "Parameter.h"
#include <sstream>
#include <vector>

using namespace std;

class Predicate{
	public:
		string data;
		vector<Parameter> parameterList;

	
		Predicate();
		Predicate(string data_in);

		void addParameter(Parameter);
		void setData(string data);
		vector<Parameter> getParameterList();
		string toString();
};