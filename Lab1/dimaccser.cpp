#include <regex>
#include <string>
#include <iostream>	//
#include <sstream>	// std::stringstream
#include <fstream>	// std::ifstream, std::ofstream
#include <unordered_map>
#include <string.h>
#include <vector>
#include <utility>

using namespace std;





string readfile(const char* filename) {

	ifstream infile(filename, std::ios_base::in);
	infile.seekg(0, infile.beg);

	stringstream ss;
	ss << infile.rdbuf();
	return ss.str();
}

vector<string> tokenize(string str, const char * delim ){

	vector<string> tokens;

	size_t token_start = 0;
	size_t token_end = 0;

	while (token_start != string::npos) {

		token_end = str.find_first_of(delim, token_start);
		//eliminate all sequences of delimiters

		if (token_end > token_start) {
			tokens.push_back(str.substr(token_start, token_end - token_start));
		}

		//move token start up to first non-delimiter character 
		token_start = str.find_first_not_of(delim, token_end);

	}

	return tokens;
}


unordered_map<string, int> parseNodes(string verilog){

	int n = 0;	//number of nodes

	unordered_map<string, int> nodes;
	vector<string> tokens;
	string s = verilog;
	string node_list;	
	regex r("(input|reg|wire|output)(.|\r|\n)*?[^;]*");	//regex to get line from the type declaration to semicolon

	sregex_iterator file_begin = sregex_iterator(s.begin(), s.end(), r);
	sregex_iterator file_end = sregex_iterator();		//the default constructor for regex_iterator is the end of sequency iterator, god knows why
		
	for (sregex_iterator it = file_begin; it != file_end; it++){

		smatch match = *it;
		s = match.str();
		s = s.substr(s.find_first_of(" \t\n")+1);	//cut off the type declaration
		cout << s << endl;
		vector<string> new_tokens = tokenize(s,  " ,\t\n;");
		tokens.insert(tokens.end(), new_tokens.begin(), new_tokens.end());
	}
		
		

		
		//

	for (n = 0; n < tokens.size(); n++){
		nodes.insert(std::pair<string, int>(tokens[n],n));
	}
	
	return nodes;

}


void testTokenize() {
	string input = string("input Rdy1RtHS1,Rdy2RtHS1,Rdy1BmHS1,Rdy2BmHS1,\n\n\tInDoneHS1,RtTSHS1,TpArrayHS1,OutputHS1,WantBmHS1,WantRtHS1,OutAvHS1,FullOHS1,FullIHS1,Prog_2,Prog_1,Prog_0;");
	vector<string> tokens = tokenize(input, " ,\t\n;");
	
	for (int i = 0; i < tokens.size(); i++){
		cout << tokens[i] << endl;
	}
}




int main() {
	/*
	string filename = std::string("ex1.v");
	ifstream infile(filename, std::ios_base::in);
	infile.seekg(64, infile.beg);

	stringstream ss;
	ss << infile.rdbuf();

	string test = ss.str();

	cout << test;

	*/

	string file = readfile("ex1.v");

	unordered_map<string,int> mymap = parseNodes(file);

	string keys[] = {"clock", "A", "Y", "S0", "S1", "X1", "NS0", "NS1"};

	for (int i = 0; i < sizeof(keys); i++) {
		cout << mymap[keys[i]] << endl;
	}

	cout << mymap["clock"] << endl;
}





