#ifndef ai_ai_players
#define ai_ai_players

#include "../game/defs.h"
#include "../game/player.h"
#include "../game/board.h"

#include <string>
#include <unordered_set>
#include <random>
#include <algorithm>
#include <iterator>

class RandomAIPlayer : public Player
{
	private:
		Board const& board;
		std::random_device rand;
	public:
		RandomAIPlayer(std::string const& name, Board const& board);
		void getNextMove(NodeLabel& label);
};

template <class Cost>
class ShortestPathAIPlayer : public Player
{
	private:
		Board const& board;
	public:
		ShortestPathAIPlayer(std::string const& name, Board const& board);
		void getNextMove(NodeLabel& label);
};

class Cost{
	private:
		PlayerID player_id;

	public:
		Cost(Board const& board, PlayerID player_id)
			:player_id(player_id) {}

		int get(Face const& face){
			if(face.owner == player_id+1){
				return 0;
			}
			else if(face.owner == !player_id+1){
				return 1000;
			}
			else{
				int diff(face.num_adj_nodes_player[!player_id] + 1
						- face.num_adj_nodes_player[player_id]);
				return std::max(diff, 0);
			}
		}
};


/* SHORTEST PATH AI PLAYER */


template <class Cost>
ShortestPathAIPlayer<Cost>::ShortestPathAIPlayer(std::string const& name, Board const& board)
	:Player(name), board(board) {}

template <class Cost>
void ShortestPathAIPlayer<Cost>::getNextMove(NodeLabel& label)
{
	// Calc both shortest paths
	std::vector<FaceID> p1_shortest_path(board.calcShortestPath<Cost>(0));
	std::vector<FaceID> p2_shortest_path(board.calcShortestPath<Cost>(1));

	// Get the fields that they have in common
	sort(p1_shortest_path.begin(), p1_shortest_path.end());
	sort(p2_shortest_path.begin(), p2_shortest_path.end());
	std::vector<FaceID> shared_faces;
	set_intersection(p1_shortest_path.begin(), p1_shortest_path.end(),
			p2_shortest_path.begin(), p2_shortest_path.end(),
			std::back_inserter(shared_faces));

	// Determine the best adjacent node TODO improve!
	NodeID best_node(0); // FIX
	for(uint i(0); i<shared_faces.size(); i++){
		std::vector<NodeID> const& adj_nodes(board.getFace(shared_faces[i]).adj_nodes);

		for(uint j(0); j<adj_nodes.size(); j++){
			if(!board.getNode(adj_nodes[j]).owner){
				best_node = adj_nodes[j];
				break;
			}
		}
	}

	// Write it into 'label'
	label = board.getNode(best_node).label;
}

#endif
