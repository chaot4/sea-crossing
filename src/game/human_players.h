#ifndef game_human_players_h
#define game_human_players_h

#include "defs.h"
#include "player.h"

#include <string>
#include <iostream>

class ConsolePlayer : public Player
{
	public:
		ConsolePlayer(std::string const& name):Player(name){}

		void initGemMove();
};

class DebugPlayer : public ConsolePlayer
{
	public:
		DebugPlayer(std::string const& name):ConsolePlayer(name){}

		// TODO implement the messaging of the marker move
		void initMarkerMove();
};

#endif
