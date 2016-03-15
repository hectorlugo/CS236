#include <string>
#include <vector>

using namespace std;

class Tuple : public vector<string>{
	public:
		void addAttValue(string);
		string const getTupleValue(int);
};