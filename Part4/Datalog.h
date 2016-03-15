#include "Rule.h"
#include <set>

using namespace std;

class Datalog{
	private:
		vector<Predicate> Schemes;
		vector<Predicate> Facts;
		vector<Predicate> Queries;
		vector<Rule> Rules;
		set<string> domain;
	public:
		Datalog();
		void addScheme(Predicate);
		void addFact(Predicate);
		void addQuery(Predicate);
		void addRule(Rule);
		void addValue(string);
		vector<Predicate> getSchemes();
		vector<Predicate> getFacts();
		vector<Predicate> getQueries();
		vector<Rule> getRules();
		string toString();
};