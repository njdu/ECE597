#include <regex>
#include <string>
#include <iostream>	//
#include <sstream>	// std::stringstream
#include <fstream>	// std::ifstream, std::ofstream
#include <map>
#include <string.h>
#include <vector>
#include <utility>

using namespace std;

struct and_t {
    and_t(string output, string input1, string input2) {
		out = output;
		in1 = input1;
        in2 = input2;
	}
    
    string out;
    string in1;
    string in2;
};

struct not_t {
    not_t(string output, string input) {
		out = output;
		in = input;
	}
    
    string out;
    string in;
};

struct buffer_t {
	buffer_t(string output, string input) {
		out = output;
		in = input;
	}
    
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

map<string, int> parseNodes(string file) {
	int n = 1;	//number of nodes

	map<string, int> nodes;
	vector<string> tokens;

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

vector<buffer_t> parseBuffers(string file){
	regex r (".*<=.*[^;]*?");

	vector<buffer_t> buffs = vector<buffer_t>();
	sregex_iterator file_begin = sregex_iterator(file.begin(), file.end(), r);
	sregex_iterator file_end = sregex_iterator();

	for (sregex_iterator it = file_begin; it != file_end; it++)	{
		smatch match = *it;
		vector<string> tokens = tokenize(match.str(), " \t<=;");
		buffs.push_back(buffer_t(tokens[0], tokens[1]));
	}

	return buffs;
}

vector<and_t> parseAndGates(string file) {
    vector<and_t> result;
    
    regex r("and .*\\((.*),(.*),(.*)\\);");
    sregex_iterator file_begin = sregex_iterator(file.begin(), file.end(), r);
    sregex_iterator file_end = sregex_iterator();
    
    for (sregex_iterator it = file_begin; it != file_end; it++) {
        smatch match = *it;
        result.push_back(and_t(match[1].str(), match[2].str(), match[3].str()));
    }
    
    return result;
}

vector<not_t> parseNotGates(string file) {
    vector<not_t> result;
    
    regex r("not .*\\((.*),(.*)\\);");
    sregex_iterator file_begin = sregex_iterator(file.begin(), file.end(), r);
    sregex_iterator file_end = sregex_iterator();
    
    for (sregex_iterator it = file_begin; it != file_end; it++) {
        smatch match = *it;
        result.push_back(not_t(match[1].str(), match[2].str()));
    }
    
    return result;
}

string andToCNF(and_t gate, map<string,int> nodes) {
    int a = nodes.find(gate.in1)->second;
    int b = nodes.find(gate.in2)->second;
    int x = nodes.find(gate.out)->second;
    stringstream result;
    result << a << " -" << x << " 0" << endl;
    result << b << " -" << x << " 0" << endl;
    result << "-" << a << " -" << b << " " << x << " 0" << endl;
    return result.str();
}

string notToCNF(not_t gate, map<string,int> nodes) {
    int a = nodes.find(gate.in)->second;
    int x = nodes.find(gate.out)->second;
    stringstream result;
    result << "-" << a << " -" << x << " 0" << endl;
    result << a << " " << x << " 0" << endl;
    return result.str();
}

string buffToCNF(buffer_t buff, map<string,int> prevNodes, map<string,int> nextNodes) {
    int a = prevNodes.find(buff.in)->second;
    int x = nextNodes.find(buff.out)->second;
    stringstream result;
    result << "-" << a << " " << x << " 0" << endl;
    result << a << " -" << x << " 0" << endl;
    return result.str();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "usage: ./a.out input.v num_unrollings" << endl;
		return -1;
	}
	string file = readfile(argv[1]);
    int num_unrollings = stoi(argv[2]);

	map<string,int> mymap = parseNodes(file);
    vector<and_t> and_gates = parseAndGates(file);
    vector<not_t> not_gates = parseNotGates(file);
	vector<buffer_t> buffs = parseBuffers(file);

    cout << "Map:" << endl;
    for (map<string,int>::iterator ii=mymap.begin(); ii!=mymap.end(); ++ii) {
		cout << ii->first << ":" << ii->second << endl;
	}
    cout << endl;
    
    cout << "And gates:" << endl;
    for (vector<and_t>::iterator ii=and_gates.begin(); ii!=and_gates.end(); ++ii) {
		cout << ii->out << ", " << ii->in1 << ", " << ii->in2 << endl;
	}
    cout << endl;
    
    cout << "Not gates:" << endl;
    for (vector<not_t>::iterator ii=not_gates.begin(); ii!=not_gates.end(); ++ii) {
		cout << ii->out << ", " << ii->in << endl;
	}
	cout << endl;

	cout << "Buffers:" << endl;
    for (vector<buffer_t>::iterator ii=buffs.begin(); ii!=buffs.end(); ++ii) {
		cout << ii->out << ", " << ii->in << endl;
	}
    cout << endl;
    
    
}
