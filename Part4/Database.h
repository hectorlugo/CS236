#include "Parser.h"
#include "Relation.h"
#include <algorithm>
#include <queue>

using namespace std;

class Database{
	private:
		Parser parser;
		ofstream outfile;
		map<string, Relation> relations;
		vector<Predicate> Schemes;
		vector<Predicate> Facts;
		vector<Predicate> Queries;
		vector<Rule> Rules;
		int size;
	public:
		Database(string, string);
		void createRelations();
		void parseSchemes();
		void setRelationScheme(Relation&, int);
		void parseFacts();
		void setTupleAttributeValues(Tuple&, int);
		void evalQueries();
		void qToString(int, int);
		void toString();
		void evaluateRules();
		void forEachParameter(vector<Parameter>&, Relation&, int&, map<string, int>&, map<int, string>&);
		int getSize();
};