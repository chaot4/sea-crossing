#ifndef game_human_players_h
#define game_human_players_h

#include "defs.h"
#include "player.h"

#include <string>
#include <iostream>

class ConsolePlayer : public Player{
	public:
		ConsolePlayer(std::string const& name):Player(name){}
		ConsolePlayer(ConsolePlayer const& player):Player(player){}

		void getNextMove(NodeLabel& node_label);
		void getMarkerMove(FaceLabel& face_label);
};

#endif
