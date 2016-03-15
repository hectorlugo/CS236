#include "Token.h"
#include <vector>
#include <fstream>

using namespace std;

class Scanner{
	private:
		vector<Token> tokens;
		bool fail;
		int lineNumber;

		void loadFile(string, vector<Token>&, bool&, int&);
		void afterTest(TokenType, string, int&, string, vector<Token>&, ifstream&);
		void defaultTest(ifstream&, char&, TokenType&, string&, bool&);
		void outFile(string, vector<Token>&, bool, int);
		void pushToken(TokenType, string, int, string, vector<Token>&);
		void captureStringToken(ifstream&, char&, string&, bool&);
		void skipLine(ifstream&);
		void getString(ifstream&, char&, TokenType&, string&);
		string getTokenSymbol(TokenType, string&);

	public:
		Scanner();
		Scanner(string, string);
		Token getToken(int);
};