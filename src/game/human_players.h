#ifndef game_human_players_h
#define game_human_players_h

#include "defs.h"
#include "player.h"

#include <string>
#include <iostream>

class ConsolePlayer : public Player
{
	public:
		ConsolePlayer(PlayerID id, std::string const& name, Board const& board)
			: Player(id, name, board) {}

		void initGemMove();
};

class DebugPlayer : public ConsolePlayer
{
	private:
		void msgSendMarkerMove(FaceID face_id);

	public:
		DebugPlayer(PlayerID id, std::string const& name, Board const& board)
			: ConsolePlayer(id, name, board) {}

		void initMarkerMove();
};

#endif
