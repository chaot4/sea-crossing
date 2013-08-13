#ifndef game_game_h
#define game_game_h

#include "../defs.h"
#include "defs.h"
#include "board.h"
#include "players.h"

#include <string>
#include <vector>

class DebugGame{
	private:
		struct DebugGameData{
			Board board;
			std::vector<ConsolePlayer> player;

			DebugGameData(Board const& board, ConsolePlayer const& player1,
					ConsolePlayer const& player2)
				:board(board), player{player1, player2}{}
		};

		bool command_player(DebugGameData& d, PlayerID player_id);
		bool command_marker_player(DebugGameData& d, PlayerID player_id);
		void command_back();
		void command_forward();

	public:
		void start();
};

#endif
