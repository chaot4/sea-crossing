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

struct Conf{
	GameConf game_conf;
	GraphicsConf graphics_conf;

	Conf():game_conf(), graphics_conf(){}
};

bool getConfFromFile(std::string const& filename, Conf& conf);

#endif
