#include "Tuple.h"

using namespace std;

void Tuple::addAttValue(string value)
{
	push_back(value);
}

string const Tuple::getTupleValue(int i)
{
	return at(i);
}