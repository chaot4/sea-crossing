#ifndef game_defs_h
#define game_defs_h

#include <vector>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

enum GameType { DEBUG_GAME, CONSOLE_GAME, GUI_GAME };
enum PlayerType { CONSOLE_PLAYER, GUI_PLAYER, DEBUG_PLAYER, RANDOM_AI, SHORTEST_PATH_AI };

struct Node;
struct Face;

typedef unsigned int NodeID;
typedef unsigned int FaceID;
typedef bool PlayerID;
typedef std::string NodeLabel;
typedef std::string FaceLabel;

struct Node{
	NodeID id;
	NodeLabel label;

	std::vector<FaceID> adj_faces;

	int owner;

	glm::vec3 position;
	glm::quat orientation;

	Node(NodeID id, NodeLabel const& label, std::vector<FaceID> adj_faces,
			glm::vec3 const& position, glm::quat const& orientation = glm::quat(),
			int owner = 0)
		:id(id), label(label), adj_faces(adj_faces), owner(owner),
		position(position), orientation(orientation) {}
};

struct Face{
	FaceID id;
	FaceLabel label;

	std::vector<NodeID> adj_nodes;
	std::vector<FaceID> adj_faces;

	int owner;
	std::vector<unsigned int> num_adj_nodes_player;

	glm::vec3 position;
	glm::quat orientation;

	Face(FaceID id, FaceLabel const& label, std::vector<NodeID> adj_nodes,
		std::vector<FaceID> adj_faces, glm::vec3 const& position,
		glm::quat const& orientation, int owner = 0, int num_adj_nodes_player1 = 0,
		int num_adj_nodes_player2 = 0)
		:id(id), label(label), adj_nodes(adj_nodes), adj_faces(adj_faces),
		owner(owner), num_adj_nodes_player(2, 0), position(position),
		orientation(orientation) {}
};

struct PQFace{
	Face const* face;
	FaceID found_by;
	unsigned int dist;

	PQFace(Face const* face, FaceID found_by, unsigned int dist)
		:face(face), found_by(found_by), dist(dist){}
	PQFace(PQFace const& other)
		:face(other.face), found_by(other.found_by), dist(other.dist) {}

	bool operator>(PQFace const& other) const{
		return dist > other.dist;
	}
};

#endif
