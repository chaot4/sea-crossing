#ifndef game_player_h
#define game_player_h

#include "defs.h"

#include <string>

class Player{
	protected:
		std::string name;
	public:
		Player(std::string const& name):name(name){}
		Player(Player const& player):name(player.getName()){}

		virtual void getNextMove(NodeLabel& node_label) = 0;
		std::string getName() const;
};

#endif
