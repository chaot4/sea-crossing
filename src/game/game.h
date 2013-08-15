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

		struct Move{
			std::string label;
			bool owner_id;
			bool is_gem;

			Move(std::string const& label, PlayerID owner_id, bool is_gem)
				:label(label), owner_id(owner_id), is_gem(is_gem){}
		};

		std::vector<Move> moves;
		std::vector<Move> reverted_moves;

		bool command_player(DebugGameData& d, PlayerID player_id);
		bool command_marker_player(DebugGameData& d, PlayerID player_id);
		void command_back(DebugGameData& d);
		void command_forward(DebugGameData& d);

		void placeGem(DebugGameData& d, PlayerID player_id, NodeLabel label);
		void placeMarker(DebugGameData& d, PlayerID player_id, FaceLabel label);
		void removeGem(DebugGameData& d, Move const& move);
		void removeMarker(DebugGameData& d, Move const& move);

	public:
		void start();
};

#endif
