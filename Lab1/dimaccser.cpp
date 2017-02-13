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

struct and_t {
    string out;
    string in1;
    string in2;
};

struct not_t {
    string out;
    string in;
};



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

void testTokenize() {
	string input = string("input Rdy1RtHS1,Rdy2RtHS1,Rdy1BmHS1,Rdy2BmHS1,\n\n\tInDoneHS1,RtTSHS1,TpArrayHS1,OutputHS1,WantBmHS1,WantRtHS1,OutAvHS1,FullOHS1,FullIHS1,Prog_2,Prog_1,Prog_0;");
	vector<string> tokens = tokenize(input, " ,\t\n;");
	
	for (int i = 0; i < tokens.size(); i++){
		cout << tokens[i] << endl;
	}
}


unordered_map<string, int> parseNodes(string file){

	int n = 1;	//number of nodes

	unordered_map<string, int> nodes;
	vector<string> tokens = vector<string>();


	regex r("(input|reg|wire|output)(.|\r|\n)*?[^;]*");	//regex to get line from the type declaration to semicolon

	sregex_iterator file_begin = sregex_iterator(file.begin(), file.end(), r);
	sregex_iterator file_end = sregex_iterator();		//the default constructor for regex_iterator is the end of sequence iterator, god knows why
		

	for (sregex_iterator it = file_begin; it != file_end; it++){

		smatch match = *it;
		string result = match.str();
		result = result.substr(result.find_first_of(" \t\n")+1);	//cut off the type declaration
		cout << result << endl;
		tokens = tokenize(result,  " ,\t\n");
		
		
		for (vector<string>::iterator token = tokens.begin(); token != tokens.end(); token++){
			nodes.insert(std::pair<string, int>(*token, n++));
		}

	}
	
	return nodes;

}

vector<and_t> parseAndGates(string verilog) {
    vector<and_t> result;
    
    regex r("and .*\\((.*),(.*),(.*)\\);");
    sregex_iterator file_begin = sregex_iterator(verilog.begin(), verilog.end(), r);
    sregex_iterator file_end = sregex_iterator();
    
    for (sregex_iterator it = file_begin; it != file_end; it++) {
        smatch match = *it;
        and_t gate;
        gate.out = match[1].str();
        gate.in1 = match[2].str();
        gate.in2 = match[3].str();
        result.push_back(gate);
    }
    
    return result;
}

vector<not_t> parseNotGates(string verilog) {
    vector<not_t> result;
    
    regex r("not .*\\((.*),(.*)\\);");
    sregex_iterator file_begin = sregex_iterator(verilog.begin(), verilog.end(), r);
    sregex_iterator file_end = sregex_iterator();
    
    for (sregex_iterator it = file_begin; it != file_end; it++) {
        smatch match = *it;
        not_t gate;
        gate.out = match[0].str();
        gate.in = match[1].str();
        result.push_back(gate);
    }
    
    return result;
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

	for (int i = 0; i < 8; i++) {
		cout << mymap[keys[i]] << endl;
	}


}

