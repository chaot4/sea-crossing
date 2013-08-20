#ifndef ai_ai_players
#define ai_ai_players

#include "../game/defs.h"
#include "../game/player.h"
#include "../game/board.h"

#include <string>
#include <unordered_set>
#include <cstdlib>
#include <time.h>

class RandomAIPlayer : public Player
{
	private:
		Board const& board;
	public:
		RandomAIPlayer(std::string const& name, Board const& board);
		void getNextMove(NodeLabel& label);
};

#endif
