#include "Relation.h"
#include <fstream>

using namespace std;

Relation::Relation(string n) : name(n){}

string print(vector<string> temp)
{
	stringstream output;
	for (int i = 0; i < temp.size(); i++){
		output << "(" << temp[i] << ")" << " ";
	}
	return output.str();
}

void Relation::setName(string name_in)
{
	name = name_in;
}

void Relation::setScheme(Scheme scheme_in)
{
	scheme = scheme_in;
}

void Relation::addSchemeAtt(string attribute)
{
	scheme.addAttribute(attribute);
}

void Relation::addTuple(Tuple tuple)
{
	tuples.insert(tuple);
}

Tuple Relation::getTuple(int t)
{
	return *next(tuples.begin(), t);
}

void Relation::emptyTuples()
{
	tuples.clear();
}

void Relation::clearTupScheme()
{
	name = "";
	scheme.emptyAttributes();
	tuples.clear();
}

void Relation::select(int position, string value)
{
	set<Tuple> newTuples;
	for (auto& t : tuples){
		if (t.at(position) == value){
			newTuples.insert(t);
		}
	}
	tuples = newTuples;
	setName("select");
}

void Relation::select(int position1, int position2)
{
	set<Tuple> newTuples;
	for (auto& t : tuples){
		if (t.at(position1) == t.at(position2)){
			newTuples.insert(t);
		}
	}
	tuples = newTuples;
	setName("select");
}

void Relation::project(map<int, string>& variables)
{
	set<Tuple> newTuples;
	Scheme newScheme;
	Tuple t;

	for (auto& v : variables){
		newScheme.addAttribute(scheme.getAttributes().at(v.first));
	}

	for (auto& tup : tuples){
		for (auto& v : variables)
		{
			t.addAttValue(tup.at(v.first));
		}
		if (variables.size() > 0){
			newTuples.insert(t);
			t.clear();
		}
	}

	tuples = newTuples;
	scheme = newScheme;
	setName("project");
}

void Relation::rename(map<int, string>& variables)
{
	Scheme newScheme;
	for (auto& v : variables){
		newScheme.addAttribute(v.second);
	}
	scheme = newScheme;
	setName("rename");
}

void Relation::toString(ofstream& outfile)
{
	outfile << name << endl;
	if (tuples.size() == 0){
		return;
	}
	for (int i = 0; i < tuples.size(); i++){
		outfile << " ";
		for (int j = 0; j < scheme.getAttributes().size(); j++){
			outfile << " " << scheme.getAttributes().at(j) << "=" << getTuple(i).getTupleValue(j);
		}
		outfile << endl;
	}
}

string Relation::getName() const
{
	return name;
}

Scheme Relation::getScheme()
{
	return scheme;
}

set<Tuple> Relation::getTuples()
{
	return tuples;
}