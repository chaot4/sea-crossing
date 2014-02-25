#include "ai_players.h"

using namespace std;


/* RANDOM AI PLAYER */


RandomAIPlayer::RandomAIPlayer(PlayerID id, string const& name, Board const& board)
	: Player(id, name, board) {}

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

/* COST */


Cost::Cost(Board const& board, PlayerID player_id)
	:board(board), player_id(player_id) {}

NaiveCost::NaiveCost(Board const& board, PlayerID player_id)
	: Cost(board, player_id) {}

int NaiveCost::get(Face const& face)
{
	if(face.owner == player_id+1){
		return 0;
	}
	else if(face.owner){
		return 1000;
	}
	else{
		int diff(face.num_adj_nodes_player[!player_id] + 1
				- face.num_adj_nodes_player[player_id]);
		return std::max(diff, 0);
	}
}


/* RATING */


Rating::Rating(Board const& board, PlayerID player_id)
	:board(board), player_id(player_id) {}

ZeroRating::ZeroRating(Board const& board, PlayerID player_id)
	: Rating(board, player_id) {}

double ZeroRating::get(NodeID node_id)
{
	return 0;
}

EqualityRating::EqualityRating(Board const& board, PlayerID player_id)
	: Rating(board, player_id) {}

double EqualityRating::get(NodeID node_id)
{
	double rating(0);
	Node const& node(board.getNode(node_id));

	for (unsigned int i(0); i<node.adj_faces.size(); i++) {
		Face const& face(board.getFace(node.adj_faces[i]));
		if (!face.owner) {
			int adj_nodes_1(face.num_adj_nodes_player[player_id]);
			int adj_nodes_2(face.num_adj_nodes_player[!player_id]);
			int abs_diff(abs(adj_nodes_1-adj_nodes_2));
			int invert_abs_diff(
				abs(abs_diff - (int)ceil(face.adj_nodes.size()/2.0)));
			assert(abs_diff + 1 <= ceil(face.adj_nodes.size()/2.0));

			rating += invert_abs_diff;
		}
	}

	return rating;
}
