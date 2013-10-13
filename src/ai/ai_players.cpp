#include "ai_players.h"

using namespace std;


/* RANDOM AI PLAYER */


RandomAIPlayer::RandomAIPlayer(string const& name, Board const& board)
	:Player(name), board(board){}

void RandomAIPlayer::initGemMove()
{
	unordered_set<NodeID> free_nodes(board.getFreeNodes());

	/* Get a random node index. */
	unsigned int random_node_index(rand() % free_nodes.size());

	/* Set an iterator on the random_node_index+1-th free node. */
	unordered_set<NodeID>::iterator it(free_nodes.begin());
	for(unsigned int i(0); i<random_node_index; i++){
		it++;
	}

	msgSendGemMove(*it);
}
