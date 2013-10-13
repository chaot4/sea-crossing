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
#include <limits>
#include <cassert>

class RandomAIPlayer : public Player
{
	private:
		Board const& board;
		std::random_device rand;
	public:
		RandomAIPlayer(std::string const& name, Board const& board);
		void initGemMove();
};

template <class Cost, class Rating>
class ShortestPathAIPlayer : public Player
{
	private:
		Board const& board;

		void intersect_paths(std::vector<FaceID>& path1,
				std::vector<FaceID>& path2,
				std::vector<FaceID>& intersection);
		NodeID findBestAdjNode(std::vector<FaceID> const& faces);
	public:
		ShortestPathAIPlayer(std::string const& name, Board const& board);
		void initGemMove();
};

class Cost{
	private:
		Board const& board;
		PlayerID player_id;

	public:
		Cost(Board const& board, PlayerID player_id)
			:board(board), player_id(player_id) {}

		int get(Face const& face){
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
};

class Rating{
	private:
		Board const& board;
		PlayerID player_id;

	public:
		Rating(Board const& board, PlayerID player_id)
			:board(board), player_id(player_id) {}

		double get(NodeID node_id){
			return 0;
		}
};


/* SHORTEST PATH AI PLAYER */


template <class Cost, class Rating>
ShortestPathAIPlayer<Cost, Rating>::ShortestPathAIPlayer(std::string const& name, Board const& board)
	:Player(name), board(board) {}

template <class Cost, class Rating>
void ShortestPathAIPlayer<Cost, Rating>::initGemMove()
{
	std::vector<FaceID> p0_shortest_path(board.calcShortestPath<Cost>(0));
	std::vector<FaceID> p1_shortest_path(board.calcShortestPath<Cost>(1));

	std::vector<FaceID> shared_faces;
	intersect_paths(p0_shortest_path, p1_shortest_path, shared_faces);

	NodeID node_id(findBestAdjNode(shared_faces));
	msgSendGemMove(node_id);
}

template <class Cost, class Rating>
NodeID ShortestPathAIPlayer<Cost, Rating>::findBestAdjNode(std::vector<FaceID> const& faces){

	Rating rating(board, id);
	double best_rating(-std::numeric_limits<double>::max());
	NodeID best_node;

	for(unsigned int i(0); i<faces.size(); i++){
		std::vector<NodeID> const& adj_nodes(board.getFace(faces[i]).adj_nodes);

		for(unsigned int j(0); j<adj_nodes.size(); j++){

			double current_rating(rating.get(adj_nodes[j]));
			if(!board.getNode(adj_nodes[j]).owner
					&& current_rating > best_rating){
				best_rating = current_rating;
				best_node = adj_nodes[j];
			}
		}
	}

	assert(best_rating != -std::numeric_limits<double>::max());
	return best_node;
}

template <class Cost, class Rating>
void ShortestPathAIPlayer<Cost, Rating>::intersect_paths(std::vector<FaceID>& path1,
	std::vector<FaceID>& path2, std::vector<FaceID>& intersection){

	sort(path1.begin(), path1.end());
	sort(path2.begin(), path2.end());

	set_intersection(path1.begin(), path1.end(), path2.begin(), path2.end(),
			std::back_inserter(intersection));
}

#endif
