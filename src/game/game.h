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
		struct Move{
			std::string label;
			bool owner_id;
			bool is_gem;

			Move(std::string const& label, PlayerID owner_id, bool is_gem)
				:label(label), owner_id(owner_id), is_gem(is_gem){}
		};

		std::vector<ConsolePlayer> player;
		Board board;

		std::vector<Move> moves;
		std::vector<Move> reverted_moves;

		bool command_player(PlayerID player_id);
		bool command_marker_player(PlayerID player_id);
		void command_back();
		void command_forward();

		void placeGem(PlayerID player_id, NodeLabel label);
		void placeMarker(PlayerID player_id, FaceLabel label);
		void removeGem(Move const& move);
		void removeMarker(Move const& move);

	public:
		DebugGame(ConsolePlayer const& player1, ConsolePlayer const& player2);
		void start();
};

class ConsoleGame{
	private:
		std::vector<ConsolePlayer> player;
		Board board;

		bool makeMove(PlayerID player_id);
		void placeGem(PlayerID player_id, NodeLabel label);

	public:
		ConsoleGame(ConsolePlayer const& player1, ConsolePlayer const& player2);
		void start();
};

#endif
