#include "Parameter.h"

using namespace std;

Parameter::Parameter(){}

void Parameter::setValue(string v)
{
	value = v;
}

string Parameter::getValue()
{
	return value;
}