#ifndef conf_h
#define conf_h

#include "game/defs.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

struct GameConf{
	PlayerType p1_type;
	PlayerType p2_type;
	std::string p1_name;
	std::string p2_name;

	GameType game_type;
	bool use_switch_rule;

	GameConf()
		: p1_type(CONSOLE_PLAYER), p2_type(SHORTEST_PATH_AI), p1_name("Spongebob"),
		p2_name("Patrick"), game_type(GUI_GAME), use_switch_rule(true) {}
};

struct GraphicsConf{
	std::string board_geometry;
	std::string gem_geometry;
	std::string marker_geometry;
	std::string board_material;
	std::string gem_material_p1;
	std::string gem_material_p2;
	std::string marker_material_p1;
	std::string marker_material_p2;

	GraphicsConf()
		: board_geometry("../resources/meshes/board.fbx"),
		gem_geometry("../resources/meshes/gem.fbx"),
		marker_geometry("../resources/meshes/marker.fbx"),
		board_material("../resources/materials/debugging.slmtl"),
		gem_material_p1("../resources/materials/templates/silver.slmtl"),
		gem_material_p2("../resources/materials/templates/gold.slmtl"),
		marker_material_p1("../resources/materials/templates/silver.slmtl"),
		marker_material_p2("../resources/materials/templates/gold.slmtl") {}
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
