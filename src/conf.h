#ifndef conf_h
#define conf_h

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

struct GameConf{
	bool use_switch_rule;

	GameConf()
		:use_switch_rule(true){}
};

struct GraphicsConf{
	std::string board_filename;

	GraphicsConf()
		:board_filename("Invor_please_insert_std_value"){}
};

class Conf{
	private:
		std::string filename;

		GameConf game_conf;
		GraphicsConf graphics_conf;

		bool parseLine(std::stringstream& ss);
	public:
		Conf(std::string const& filename);

		bool readFromFile();
};

#endif
