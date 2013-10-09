#include "ai_players.h"

using namespace std;


/* RANDOM AI PLAYER */


RandomAIPlayer::RandomAIPlayer(string const& name, Board const& board)
	:Player(name), board(board){}

void RandomAIPlayer::getNextMove(NodeLabel& label)
{
	unordered_set<NodeID> free_nodes(board.getFreeNodes());

	/* Get a random node index. */
	unsigned int random_node_index(rand() % free_nodes.size());

	/* Set an iterator on the random_node_index+1-th free node. */
	unordered_set<NodeID>::iterator it(free_nodes.begin());
	for(unsigned int i(0); i<random_node_index; i++){
		it++;
	}

	label = board.getNode(*it).label;
}


/* SHORTEST PATH AI PLAYER */


template <class Cost>
ShortestPathAIPlayer<Cost>::ShortestPathAIPlayer(std::string const& name, Board const& board)
	:Player(name), board(board) {}

template <class Cost>
void ShortestPathAIPlayer<Cost>::getNextMove(NodeLabel& label)
{
	// Calc both shortest paths
	vector<FaceLabel const*> p1_shortest_path(board.calcShortestPath<Cost>(0));
	vector<FaceLabel const*> p2_shortest_path(board.calcShortestPath<Cost>(1));
	// Get the fields that they have in common TODO
	vector<FaceLabel const&> shared_faces;
	// Determine the best adjacent node TODO
	NodeLabel best_node;
	// Write it into 'label'
	label = best_node;
}
