#include "Parameter.h"
#include <sstream>
#include <vector>

using namespace std;

class Predicate{
	private:
		string data;
		vector<Parameter> parameterList;
	public:
		void addParameter(Parameter);
		void setData(string);
		void emptyPredicate();
		string getData();
		vector<Parameter> getParameterList();
		string toString();
};