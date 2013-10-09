#ifndef game_defs_h
#define game_defs_h

#include <vector>
#include <string>
#include <iostream>

struct Node;
struct Face;

typedef int NodeID;
typedef int FaceID;
typedef bool PlayerID;
typedef std::string NodeLabel;
typedef std::string FaceLabel;

struct Node{
	NodeID id;
	NodeLabel label;

	std::vector<FaceID> adj_faces;

	int owner;

	Node(NodeID id, NodeLabel const& label, std::vector<FaceID> adj_faces, int owner = 0)
		:id(id), label(label), adj_faces(adj_faces), owner(owner){}
};

struct Face{
	FaceID id;
	FaceLabel label;

	std::vector<NodeID> adj_nodes;
	std::vector<FaceID> adj_faces;

	int owner;
	std::vector<unsigned int> num_adj_nodes_player;

	Face(FaceID id, FaceLabel const& label, std::vector<NodeID> adj_nodes,
		std::vector<FaceID> adj_faces, int owner = 0, int num_adj_nodes_player1 = 0,
		int num_adj_nodes_player2 = 0)
		:id(id), label(label), adj_nodes(adj_nodes), adj_faces(adj_faces),
		owner(owner), num_adj_nodes_player(2, 0){}
};

struct PQFace{
	Face const& face;
	FaceID found_by;
	uint dist;

	PQFace(Face const& face, FaceID found_by, uint dist)
		:face(face), found_by(found_by), dist(dist){}

	bool operator<(PQFace const& other){
		return dist < other.dist;
	}
};

#endif
