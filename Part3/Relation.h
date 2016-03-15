#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>
#include "Scheme.h"
#include "Tuple.h"

using namespace std;

class Relation {
	private:
		Scheme scheme;
		string name;
		set<Tuple> tuples;
	public:
		Relation(){};
		Relation(string);
		void setName(string);
		void setScheme(Scheme);
		void addSchemeAtt(string);
		void addTuple(Tuple);
		void emptyTuples();
		void clearTupScheme();
		void select(int, string);
		void select(int, int);
		void project(map<int, string>&);
		void rename(map<int, string>&);
		void toString(ofstream&);
		Tuple getTuple(int);
		string getName() const;
		Scheme getScheme();
		set<Tuple> getTuples();
};