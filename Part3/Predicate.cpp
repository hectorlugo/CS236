#include "Predicate.h"

using namespace std;

void Predicate::addParameter(Parameter parameter)
{
	parameterList.push_back(parameter);
}

void Predicate::setData(string d)
{
	data = d;
}

void Predicate::emptyPredicate()
{
	parameterList.clear();
}

string Predicate::getData()
{
	return data;
}

vector<Parameter> Predicate::getParameterList()
{
	return parameterList;
}

string Predicate::toString()
{
	stringstream ss;
	ss << data << "(";
	for (int i = 0; i < parameterList.size(); i++){
		ss << parameterList[i].getValue();

		if (i < parameterList.size() - 1){
			ss << ",";
		}
	}
	ss << ")";
	return ss.str();
}