#include "Predicate.h"

using namespace std;

Predicate::Predicate()
{

}

Predicate::Predicate(string data_in)
{
	data = data_in;
}

void Predicate::addParameter(Parameter parameter)
{
	parameterList.push_back(parameter);
}

void Predicate::setData(string s)
{
	data = s;
}

string Predicate::toString()
{
	stringstream ss;
	ss << "  " << data << "(";
	return ss.str();
}