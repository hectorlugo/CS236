#include "Parser.h"
#include "Relation.h"
#include <algorithm>

using namespace std;

class Database{
	private:
		Parser parser;
		ofstream outfile;
		map<string, Relation> relations;
		vector<Predicate> Schemes;
		vector<Predicate> Facts;
		vector<Predicate> Queries;
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
};