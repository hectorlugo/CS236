#include "Scheme.h"

using namespace std;

void Scheme::addAttribute(string attribute)
{
	attributes.push_back(attribute);
}

void Scheme::setAttribute(int position, string value)
{
	attributes[position] = value;
}

vector<string> Scheme::getAttributes()
{
	return attributes;
}

void Scheme::emptyAttributes()
{
	attributes.clear();
}