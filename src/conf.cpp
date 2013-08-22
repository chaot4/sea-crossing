#include "conf.h"

using namespace std;

namespace{

void getParameters(stringstream& ss, vector<string>& options)
{
	string option;

	while(ss >> option){
		options.push_back(option);
	}
}

void errorInvalidParameter(string const& keyword, string const& parameter)
{
	cerr << "ERROR: Invalid parameter '" << parameter << "' passed to keyword '"
		<< keyword << "'." << endl;
}

void errorWrongNumberOfOptions(string const& keyword)
{
	cerr << "ERROR: Wrong number of options passed to keyword '" << keyword
		<< "'." << endl;
}

void errorUnknownKeyword(string const& keyword)
{
	cerr << "ERROR: Unknown keyword '" << keyword << "'." << endl;
}

bool parseLine(stringstream& ss, Conf& conf)
{
	string keyword;
	vector<string> options;

	ss >> keyword;
	getParameters(ss, options);

	/* Ignore empty lines and comments. */
	if(keyword == "" || keyword[0] == '#'){}
	/* use_switch_rule <true|false> */
	else if(keyword == "use_switch_rule"){
		if(options.size() == 1){
			if(options[0] == "true"){
				conf.game_conf.use_switch_rule = true;
			}
			else if(options[0] == "false"){
				conf.game_conf.use_switch_rule = false;
			}
			else{
				errorInvalidParameter(keyword, options[0]);
				return false;
			}
		}
		else{
			errorWrongNumberOfOptions(keyword);
			return false;
		}
	}
	else{
		errorUnknownKeyword(keyword);
		return false;
	}

	return true;
}

}

bool getConfFromFile(std::string const& filename, Conf& conf)
{
	ifstream f(filename.c_str());
	string line;

	if(f.is_open()){
		while(getline(f, line)){
			stringstream ss(line);
			if(!parseLine(ss, conf)){
				cerr << "The error arose while parsing the following line: "
					<< "'" << line << "'." << endl;
			}
		}
	}
	else{
		cerr << "ERROR: Couldn't open the config file \'"
			<< filename << "\'. Exiting." << endl;
		return false;
	}

	return true;
}
