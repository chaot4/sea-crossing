#include "conf.h"

using namespace std;

/* ANONYMOUS NAMESPACE */

namespace{

void getParameters(stringstream& ss, vector<string>& parameters)
{
	string parameter;

	while(ss >> parameter){
		parameters.push_back(parameter);
	}
}

void errorInvalidParameter(string const& keyword, string const& parameter)
{
	cerr << "ERROR: Invalid parameter '" << parameter << "' passed to keyword '"
		<< keyword << "'." << endl;
}

void errorWrongNumberOfParameters(string const& keyword)
{
	cerr << "ERROR: Wrong number of parameters passed to keyword '" << keyword
		<< "'." << endl;
}

void errorUnknownKeyword(string const& keyword)
{
	cerr << "ERROR: Unknown keyword '" << keyword << "'." << endl;
}

}

/* MEMBER FUNCTIONS */

Conf::Conf(std::string const& filename)
	:filename(filename), game_conf(), graphics_conf(){}

bool Conf::parseLine(stringstream& ss)
{
	string keyword;
	vector<string> parameters;

	ss >> keyword;
	getParameters(ss, parameters);

	/* Ignore empty lines and comments. */
	if(keyword == "" || keyword[0] == '#'){}
	/* use_switch_rule <true|false> */
	else if(keyword == "use_switch_rule"){
		if(parameters.size() == 1){
			if(parameters[0] == "true"){
				game_conf.use_switch_rule = true;
			}
			else if(parameters[0] == "false"){
				game_conf.use_switch_rule = false;
			}
			else{
				errorInvalidParameter(keyword, parameters[0]);
				return false;
			}
		}
		else{
			errorWrongNumberOfParameters(keyword);
			return false;
		}
	}
	else{
		errorUnknownKeyword(keyword);
		return false;
	}

	return true;
}

bool Conf::readFromFile()
{
	ifstream f(filename.c_str());
	string line;

	if(f.is_open()){
		while(getline(f, line)){
			stringstream ss(line);
			if(!parseLine(ss)){
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
