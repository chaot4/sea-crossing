#ifndef game_players_h
#define game_players_h

#include "defs.h"

#include <string>
#include <iostream>

class Player{
	protected:
		std::string name;
	public:
		Player(std::string const& name):name(name){}
		Player(Player const& player):name(player.getName()){}

		virtual void getNextMove(NodeLabel& node_label) = 0;
		std::string getName() const;
};


class ConsolePlayer : public Player{
	public:
		ConsolePlayer(std::string const& name):Player(name){}
		ConsolePlayer(ConsolePlayer const& player):Player(player){}

		void getNextMove(NodeLabel& node_label);
		void getMarkerMove(FaceLabel& face_label);
};

#endif
