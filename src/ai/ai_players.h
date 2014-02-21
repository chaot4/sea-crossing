#ifndef ai_ai_players
#define ai_ai_players

#include "../game/defs.h"
#include "../game/player.h"

#include <string>
#include <unordered_set>
#include <random>
#include <algorithm>
#include <iterator>
#include <limits>
#include <cassert>
#include <cmath>


/* RANDOM AI PLAYER */


class RandomAIPlayer : public Player
{
	private:
		std::random_device rand;
	public:
		RandomAIPlayer(PlayerID id, std::string const& name, Board const& board);
		void initGemMove();
};

template <class Cost, class Rating>
class ShortestPathAIPlayer : public Player
{
	private:
		void intersect_paths(std::vector<FaceID>& path1,
				std::vector<FaceID>& path2,
				std::vector<FaceID>& intersection);
		NodeID findBestAdjNode(std::vector<FaceID> const& faces);
	public:
		ShortestPathAIPlayer(PlayerID id, std::string const& name, Board const& board);
		void initGemMove();
};


/* COST */


class Cost
{
	protected:
		Board const& board;
		PlayerID player_id;

	public:
		Cost(Board const& board, PlayerID player_id);

		virtual int get(Face const& face) = 0;
};

class NaiveCost : public Cost
{
	public:
		NaiveCost(Board const& board, PlayerID player_id);

		int get(Face const& face);
};


/* RATING */


class Rating
{
	protected:
		Board const& board;
		PlayerID player_id;

	public:
		Rating(Board const& board, PlayerID player_id);

		virtual double get(NodeID node_id) = 0;
};

class ZeroRating : public Rating
{
	public:
		ZeroRating(Board const& board, PlayerID player_id);

		double get(NodeID node_id);
};

class EqualityRating : public Rating
{
	public:
		EqualityRating(Board const& board, PlayerID player_id);

		double get(NodeID node_id);
};


/* SHORTEST PATH AI PLAYER */


template <class Cost, class Rating>
ShortestPathAIPlayer<Cost, Rating>::ShortestPathAIPlayer(PlayerID id,
		std::string const& name, Board const& board)
	:Player(id, name, board) {}

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
