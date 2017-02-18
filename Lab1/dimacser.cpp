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

/* Returns a map, whose keys are the string names of a particular node, and the values are the dimaccs variable number
 *
 * \param file - a std::string containing the entire contents of the verilog file
 * \param &n - A reference to an integer that tracks the number of variables in
 *
 */ 
map<string, int> parseNodes(string file, int &n) {

	n = 0;

	map<string, int> nodes;
	vector<string> tokens;

	regex r("(input|reg|wire|output)(.|\r|\n)*?[^;]*");	//regex to get line from the type declaration to semicolon

	sregex_iterator file_begin = sregex_iterator(file.begin(), file.end(), r);
	sregex_iterator file_end = sregex_iterator();		//the default constructor for regex_iterator is the end of sequence iterator, god knows why

	for (sregex_iterator it = file_begin; it != file_end; it++){
		smatch match = *it;
		string result = match.str();
		result = result.substr(result.find_first_of(" \t\r\n")+1);	//cut off the type declaration
		tokens = tokenize(result,  " ,\t\r\n");
		
		for (vector<string>::iterator token = tokens.begin(); token != tokens.end(); token++){
			nodes.insert(std::pair<string, int>(*token, ++n));
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
    if (argc != 5) {
        cout << "usage: ./a.out input.v output.dimacs num_unrollings end_state" << endl;
		return -1;
	}

	string file = readfile(argv[1]);
    string outfile_name = argv[2];
    int num_unrollings = stoi(argv[3]);
    int end_state = stoi(argv[4]);

	ofstream outfile(outfile_name, fstream::out);

	//num_variables will be updated with the number of variables needed o
	//represent file in CNF expression
	int num_variables = 0;
	map<string,int> nodes = parseNodes(file, num_variables);

    vector<and_t> and_gates = parseAndGates(file);
    vector<not_t> not_gates = parseNotGates(file);
	vector<buffer_t> buffs = parseBuffers(file);

	int num_clauses = (and_gates.size()*3 + not_gates.size()*2)*(num_unrollings) + buffs.size() * 2 *(num_unrollings - 1) + buffs.size() * 2;
	outfile << "p cnf " << num_variables*num_unrollings << " " << num_clauses << endl;


	outfile << "c Initial Conditions" << endl;
	for (vector<buffer_t>::iterator itr = buffs.begin(); itr != buffs.end(); itr++)
	{
		outfile << "-" << nodes.find(itr->out)->second << " 0" << endl;
	}

    for (int ii = 0; ii < num_unrollings; ii++)
    {

    	outfile << "c " << "Unrolling " << ii + 1 << endl;
    	outfile << "c " << "And Gates" << endl; 
    	int jj;
    	for (jj = 0; jj < and_gates.size(); jj++)
    	{
    		outfile << andToCNF(and_gates[jj], nodes);
    	}

    	outfile << "c Not Gates" << endl;
    	//Add all not gates
    	for (jj = 0; jj < not_gates.size(); jj++)
    	{
    		outfile << notToCNF(not_gates[jj], nodes);
    	}



    	//For all but the last unrolling, assign new numbers to all nodes 
    	if ( ii < num_unrollings - 1){
	    	map<string, int> next_nodes = map<string, int>(nodes);
			for (map<string,int>::iterator itr=next_nodes.begin(); itr!=next_nodes.end(); ++itr) {
				itr->second += num_variables;
			}

			outfile << "c Buffers" << endl;
	    	for (jj = 0; jj < buffs.size(); jj++){
	    		outfile << buffToCNF(buffs[jj], nodes, next_nodes);	
	    	}

    		nodes = next_nodes;
    	}
    }

    outfile << "c Final state" << endl;

    //The final state will be at input to the buffer
	for (vector<buffer_t>::reverse_iterator itr = buffs.rbegin(); itr != buffs.rend(); itr++)
	{
		if (!(end_state & 0x01)){
			outfile << "-";
		}
		end_state = end_state >> 1;
		// For the final unrolling, we want the values of the next state. Therefore, we want the input to the buffer struct
		outfile << nodes.find(itr->in)->second << " 0" << endl;
	}

    outfile.close();

}
