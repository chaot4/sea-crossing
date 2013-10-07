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

void replaceParameters(size_t keyword_pos, string& file_content,
		string const& parameter_string)
{
	size_t begin_parameters(file_content.find_first_of(" \t\n\r", keyword_pos));
	size_t end_parameters(file_content.find_first_of("\r\n", keyword_pos));
	size_t length(end_parameters-begin_parameters);

	file_content.replace(begin_parameters, length, parameter_string);
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

void errorOpenFile(string const& filename)
{
	cerr << "ERROR: Couldn't open the config file \'" << filename
		<< "\'. Exiting." << endl;
}

void errorParsingLine(string const& line)
{
	cerr << "The error arose while parsing the following line: "
		<< "'" << line << "'." << endl;
}

}

/* MEMBER FUNCTIONS */

Conf::Conf(std::string const& filename)
	:filename(filename), game_conf(), graphics_conf(){}

bool Conf::readFileToString(string& file)
{
	ifstream f(filename.c_str());

	if(f.is_open()){
		f.seekg(0, ios::end);
		file.reserve(f.tellg());
		f.seekg(0, ios::beg);
		file.assign(istreambuf_iterator<char>(f), istreambuf_iterator<char>());
		return true;
	}
	else{
		return false;
	}
}

bool Conf::writeStringToFile(std::string& file)
{
	ofstream f(filename.c_str(), ios_base::trunc);

	if(f.is_open()){
		f.write(file.c_str(), file.size());
		return true;
	}
	else{
		return false;
	}
}

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
	else if(keyword == "p1_name"){
		if(parameters.size() == 1){
			game_conf.p1_name = parameters[0];
		}
		else{
			errorWrongNumberOfParameters(keyword);
			return false;
		}
	}
	else if(keyword == "p2_name"){
		if(parameters.size() == 1){
			game_conf.p2_name = parameters[0];
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
				errorParsingLine(line);
			}
		}
	}
	else{
		errorOpenFile(filename);
		return false;
	}

	return true;
}

bool Conf::setValue(std::string const& keyword, std::vector<std::string> const& parameters)
{
	/* Generate the string we want to place as parameters. */
	string parameter_string;
	for(unsigned int i(0); i<parameters.size(); i++){
		parameter_string += ' ' + parameters[i];
	}

	/* Read the whole file into a string. */
	string file_content;
	if(!readFileToString(file_content)){
		errorOpenFile(filename);
		return false;
	}

	/* Edit the string at the wanted positions. */
	size_t keyword_pos(file_content.find(keyword));
	while(keyword_pos != string::npos){
		size_t last_non_space_pos(file_content.find_last_not_of(" \t", keyword_pos-1));
		if(last_non_space_pos == string::npos
				|| file_content[last_non_space_pos] == '\n'){
			replaceParameters(keyword_pos, file_content, parameter_string);
		}
		keyword_pos = file_content.find(keyword, keyword_pos+1);
	}

	/* Overwrite the old file. */
	if(!writeStringToFile(file_content)){
		errorOpenFile(filename);
		return false;
	}

	return true;
}

GameConf const& Conf::getGameConf()
{
	return game_conf;
}

GraphicsConf const& Conf::getGraphicsConf()
{
	return graphics_conf;
}
