#ifndef conf_h
#define conf_h

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

struct GameConf{
	std::string p1_name;
	std::string p2_name;
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
		bool readFileToString(std::string& file);
		bool writeStringToFile(std::string& file);
	public:
		Conf(std::string const& filename);

		bool readFromFile();
		bool setValue(std::string const& keyword,
				std::vector<std::string> const& parameters);

		GameConf const& getGameConf();
		GraphicsConf const& getGraphicsConf();
};

#endif
