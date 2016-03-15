#include "Relation.h"
#include <fstream>

using namespace std;

Relation::Relation(string n) : name(n){}

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

void Relation::project(vector<int>& variables)
{
	set<Tuple> newTuples;
	Scheme newScheme;
	Tuple t;

	for (auto& v : variables){
		newScheme.addAttribute(scheme.getAttributes().at(v));
	}

	for (auto& tup : tuples){
		for (auto& v : variables)
		{
			t.addAttValue(tup.at(v));
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

void Relation::rename(vector<string>& variableName)
{
	Scheme newScheme;
	for (auto& v : variableName){
		newScheme.addAttribute(v);
	}
	scheme = newScheme;
	setName("rename");
}

void Relation::join(Relation& r)
{
	vector<string> s1 = getScheme().getAttributes();
	vector<string> s2 = r.getScheme().getAttributes();
	set<Tuple> tups1 = getTuples();
	set<Tuple> tups2 = r.getTuples();
	emptyTuples();
	makeScheme(s1, s2);

	for (Tuple t1 : tups1){
		for (Tuple t2 : tups2){
			if (canJoin(s1, t1, s2, t2)){
				addTuple(makeTuple(s1, t1, s2, t2));
			}
		}
	}
}

void Relation::makeScheme(vector<string>& s1, vector<string>& s2)
{
	for (auto& name : s2){
		if (!count(s1.begin(), s1.end(), name)){
			scheme.addAttribute(name);
		}
	}
}

bool Relation::canJoin(vector<string>& s1, Tuple& t1, vector<string>& s2, Tuple& t2)
{
	for (int i = 0; i < t1.size(); i++){
		for (int j = 0; j < t2.size(); j++){
			if (s1[i] == s2[j] && t1[i] != t2[j]){
				return false;
			}
		}
	}
	return true;
}

Tuple Relation::makeTuple(vector<string>& s1, Tuple& t1, vector<string>& s2, Tuple& t2)
{
	Tuple temp = t1;
	for (int i = 0; i < t2.size(); i++){
		if (!count(s1.begin(), s1.end(), s2[i])){
			temp.addAttValue(t2[i]);
		}
	}
	return temp;
}

void Relation::relationUnion(Relation& r, ofstream& outfile){
	set<Tuple> tups1 = getTuples();
	set<Tuple> tups2 = r.getTuples();

	for (Tuple t2 : tups2){
		if (!tups1.count(t2)){
			addTuple(t2);
			outfile << " ";
			for (int j = 0; j < scheme.getAttributes().size(); j++){
				outfile << " " << scheme.getAttributes().at(j) << "=" << t2.getTupleValue(j);
			}
			outfile << endl;
		}
	}
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