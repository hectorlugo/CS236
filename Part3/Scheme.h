#include <string>
#include <vector>

using namespace std;

class Scheme {
	private:
		vector<string> attributes;
	public:
		Scheme(){};
		void addAttribute(string);
		void setAttribute(int, string);
		vector<string> getAttributes();
		void emptyAttributes();
};