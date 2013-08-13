#ifndef game_players_h
#define game_players_h

#include "defs.h"

#include <string>
#include <iostream>

class Player{
	protected:
		std::string name;
	public:
		Player(std::string const& name);

		virtual void getNextMove(NodeLabel& node_label) = 0;
		std::string getName();
};


class ConsolePlayer : public Player{
	public:
		ConsolePlayer(std::string const& name):Player(name){}

		void getNextMove(NodeLabel& node_label);
		void getMarkerMove(FaceLabel& face_label);
};

#endif
