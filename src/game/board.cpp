#include "board.h"

using namespace std;

/* Public members. */

Board::Board():
	nodes{
		Node(0, "eSW", {37}),
		Node(1, "eSE", {33}),
		Node(2, "dS-3", {22, 36, 37}),
		Node(3, "dS-2", {21, 22, 36}),
		Node(4, "dS-1", {21, 35, 36}),
		Node(5, "dS", {20, 21, 35}),
		Node(6, "dS1", {20, 34, 35}),
		Node(7, "dS2", {19, 20, 34}),
		Node(8, "dS3", {19, 33, 34}),
		Node(9, "dW-3", {22, 37, 38}),
		Node(10, "dE-3", {19, 32, 33}),
		Node(11, "cS-2", {11, 21, 22}),
		Node(12, "cS-1", {10, 11, 21}),
		Node(13, "cS", {10, 20, 21}),
		Node(14, "cS1", {9, 10, 20}),
		Node(15, "cS2", {9, 19, 20}),
		Node(16, "dW-2", {22, 23, 38}),
		Node(17, "cW-2", {11, 22, 23}),
		Node(18, "cE-2", {9, 18, 19}),
		Node(19, "dE-2", {18, 19, 32}),
		Node(20, "bS-1", {4, 10, 11}),
		Node(21, "bS", {3, 4, 10}),
		Node(22, "bS1", {3, 9, 10}),
		Node(23, "dW-2", {22, 23, 38}),
		Node(24, "cW-1", {11, 12, 23}),
		Node(25, "bW-1", {4, 11, 12}),
		Node(26, "bE-1", {3, 8, 9}),
		Node(27, "cE-1", {8, 9, 18}),
		Node(28, "dE-1", {18, 31, 32}),
		Node(29, "aS", {0, 3, 4}),
		Node(30, "dW", {23, 24, 39}),
		Node(31, "cW", {12, 23, 24}),
		Node(32, "bW", {1, 4, 12}),
		Node(33, "aW", {0, 1, 4}),
		Node(34, "0", {0}),
		Node(35, "aE", {0, 2, 3}),
		Node(36, "bE", {2, 3, 8}),
		Node(37, "cE", {8, 17, 18}),
		Node(38, "dE", {17, 18, 31}),
		Node(39, "aN", {0, 1, 2}),
		Node(40, "dW1", {24, 39, 40}),
		Node(41, "cW1", {5, 12, 24}),
		Node(42, "bW1", {1, 5, 12}),
		Node(43, "bE1", {2, 7, 8}),
		Node(44, "cE1", {7, 8, 17}),
		Node(45, "dE1", {17, 30, 31}),
		Node(46, "bN-1", {1, 5, 6}),
		Node(47, "bN", {1, 2, 6}),
		Node(48, "bN1", {2, 6, 7}),
		Node(49, "dW2", {13, 24, 40}),
		Node(50, "cW2", {5, 13, 24}),
		Node(51, "cE2", {7, 16, 17}),
		Node(52, "dE2", {16, 17, 30}),
		Node(53, "cN-2", {5, 13, 14}),
		Node(54, "cN-1", {5, 6, 14}),
		Node(55, "cN", {6, 14, 15}),
		Node(56, "cN1", {6, 7, 15}),
		Node(57, "cN2", {7, 15, 16}),
		Node(58, "dW3", {13, 25, 40}),
		Node(59, "dE3", {16, 29, 30}),
		Node(60, "dN-3", {13, 25, 26}),
		Node(61, "dN-2", {13, 14, 26}),
		Node(62, "dN-1", {14, 26, 27}),
		Node(63, "dN", {14, 15, 27}),
		Node(64, "dN1", {15, 27, 28}),
		Node(65, "dN2", {15, 16, 28}),
		Node(66, "dN3", {16, 28, 29}),
		Node(67, "eNW", {25}),
		Node(68, "eNE", {29})
	},
	faces{
                Face(0, "A", {29, 33, 34, 35, 39}, {1, 2, 3, 4}),
                Face(1, "BNW", {32, 33, 39, 42, 46, 47}, {0, 2, 4, 5, 6, 12}),
                Face(2, "BNE", {35, 36, 39, 43, 47, 48}, {0, 1, 3, 6, 7, 8}),
                Face(3, "BSE", {21, 22, 26, 29, 35, 36}, {0, 2, 4, 8, 9, 10}),
                Face(4, "BSW", {20, 21, 25, 29, 32, 33}, {0, 1, 3, 10, 11, 12}),
                Face(5, "CNW", {41, 42, 46, 50, 53, 54}, {1, 6, 12, 13, 14, 24}),
                Face(6, "CN", {46, 47, 48, 54, 55, 56}, {1, 2, 5, 7, 14, 15}),
                Face(7, "CNE", {43, 44, 48, 51, 56, 57}, {2, 6, 8, 15, 16, 17}),
                Face(8, "CE", {26, 27, 36, 37, 43, 44}, {2, 3, 7, 9, 17, 18}),
                Face(9, "CSE", {14, 15, 18, 22, 26, 27}, {3, 8, 10, 18, 19, 20}),
                Face(10, "CS", {12, 13, 14, 20, 21, 22}, {3, 4, 9, 11, 20, 21}),
                Face(11, "CSW", {11, 12, 17, 20, 24, 25}, {4, 10, 12, 21, 22, 23}),
                Face(12, "CW", {24, 25, 31, 32, 41, 42}, {1, 4, 5, 11, 23, 24}),
                Face(13, "DNW", {49, 50, 53, 58, 60, 61}, {5, 14, 24, 25, 26, 40}),
                Face(14, "DN-1", {53, 54, 55, 61, 62, 63}, {5, 6, 13, 15, 26, 27}),
                Face(15, "DN1", {55, 56, 57, 63, 64, 65}, {6, 7, 14, 16, 27, 28}),
                Face(16, "DNE", {51, 52, 57, 59, 65, 66}, {7, 15, 17, 28, 29, 30}),
                Face(17, "DE1", {37, 38, 44, 45, 51, 52}, {7, 8, 16, 18, 30, 31}),
                Face(18, "DE-1", {18, 19, 27, 28, 37, 38}, {8, 9, 17, 19, 31, 32}),
                Face(19, "DSE", {7, 8, 10, 15, 18, 19}, {9, 18, 20, 32, 33, 34}),
                Face(20, "DS1", {5, 6, 7, 13, 14, 15}, {9, 10, 19, 21, 34, 35}),
                Face(21, "DS-1", {3, 4, 5, 11, 12, 13}, {10, 11, 20, 22, 35, 36}),
                Face(22, "DSW", {2, 3, 9, 11, 16, 17, 23}, {11, 21, 23, 36, 37, 38}),
                Face(23, "DW-1", {16, 17, 23, 24, 30, 31}, {11, 12, 22, 24, 38, 39}),
                Face(24, "DW1", {30, 31, 40, 41, 49, 50}, {5, 12, 13, 23, 39, 40}),
                Face(25, "ENW", {58, 60, 67}, {13, 26, 40}),
                Face(26, "EN-1", {60, 61, 62}, {13, 14, 25, 27}),
                Face(27, "EN", {62, 63, 64}, {14, 15, 26, 28}),
                Face(28, "EN1", {64, 65, 66}, {15, 16, 27, 29}),
                Face(29, "ENE", {59, 66, 68}, {16, 28, 30}),
                Face(30, "EE1", {45, 52, 59}, {16, 17, 29, 31}),
                Face(31, "EE", {28, 38, 45}, {17, 18, 30, 32}),
                Face(32, "EE-1", {10, 19, 28}, {18, 19, 31, 33}),
                Face(33, "ESE", {1, 8, 10}, {19, 32, 34}),
                Face(34, "ES1", {6, 7, 8}, {19, 20, 33, 35}),
                Face(35, "ES", {4, 5, 6}, {20, 21, 34, 36}),
                Face(36, "ES-1", {2, 3, 4}, {21, 22, 35, 37}),
                Face(37, "ESW", {0, 2, 9}, {22, 36, 38}),
                Face(38, "EW-1", {9, 16, 23}, {22, 23, 37, 39}),
                Face(39, "EW", {30, 40}, {23, 24, 38, 40}),
                Face(40, "EW1", {40, 49, 58}, {13, 24, 25, 39})
	}
{
	initMaps();
}

void Board::reset()
{
	/* Reset the nodes. */
	for(unsigned int i=0; i<nodes.size(); i++)
		nodes[i].owner = 0;

	/* Reset the faces. */
	for(unsigned int i=0; i<faces.size(); i++){
		Face& face(faces[i]);
		face.owner = 0;
		face.num_adj_nodes_player[0] = 0;
		face.num_adj_nodes_player[1] = 0;
	}
}

bool Board::placeGem(NodeLabel& label, PlayerID player_id)
{
	Node& node(nodes[node_map[label]]);

	if(!node.owner){
		node.owner = player_id+1;

		/* Update counts of adjacent faces. */
		for(unsigned int i=0; i<node.adj_faces.size(); i++){
			Face& face(faces[node.adj_faces[i]]);
			face.num_adj_nodes_player[player_id]++;
		}
	}
	else{
		return false;
	}

	return true;
}

bool Board::placeMarker(FaceLabel& label, PlayerID player_id)
{
	Face& face(faces[face_map[label]]);

	if(!face.owner)
		face.owner = player_id+1;
	else
		return false;

	return true;
}

bool Board::removeGem(NodeLabel& label)
{
	Node& node(nodes[node_map[label]]);

	if(node.owner){
		PlayerID old_owner_id = node.owner-1;
		node.owner = 0;

		/* Update counts of adjacent faces. */
		for(unsigned int i=0; i<node.adj_faces.size(); i++){
			Face& face(faces[node.adj_faces[i]]);
			face.num_adj_nodes_player[old_owner_id]--;
			assert(face.num_adj_nodes_player[old_owner_id] >= 0);
		}
	}
	else{
		return false;
	}

	return true;
}

bool Board::removeMarker(FaceLabel& label)
{
	Face& face(faces[face_map[label]]);

	if(face.owner)
		face.owner = 0;
	else
		return false;

	return true;
}

bool Board::checkVictoryCondition(PlayerID player_id)
{
	vector<FaceID> start_faces;
	vector<FaceID> end_faces;

	if(player_id){
		start_faces = {25, 37, 38, 39, 40};
		end_faces = {29, 30, 31, 32, 33};
	}
	else{
		start_faces = {33, 34, 35, 36, 37};
		end_faces = {25, 26, 27, 28, 29};
	}

	return existsPathBetween(start_faces, end_faces, player_id);
}

/* Private members. */

void Board::initMaps()
{
	/* Init node_map. */
	for(unsigned int i=0; i<nodes.size(); i++){
		Node const& node(nodes[i]);
		node_map.insert(pair<NodeLabel, NodeID>(node.label, node.id));
	}

	/* Init face_map. */
	for(unsigned int i=0; i<faces.size(); i++){
		Face const& face(faces[i]);
		face_map.insert(pair<FaceLabel, FaceID>(face.label, face.id));
	}
}

bool Board::existsPathBetween(vector<FaceID> const& start_faces,
				vector<FaceID> const& end_faces, PlayerID player_id)
{
	vector<FaceID> stack;
	vector<bool> visited(faces.size(), false);

	for(unsigned int i=0; i<start_faces.size(); i++){

		FaceID face(start_faces[i]);
		if(faces[face].owner == player_id + 1){
			stack.push_back(face);
			visited[face] = true;
		}
	}

	while(!stack.empty()){
		
		Face const& face(faces[stack.back()]);
		stack.pop_back();

		/* Add yet unvisited neighbours to the stack. */
		vector<FaceID> const& adj_faces(face.adj_faces);
		for(unsigned int i=0; i<adj_faces.size(); i++){

			Face const& adj_face(faces[adj_faces[i]]);
			if(adj_face.owner == player_id + 1 && !visited[adj_face.id]){
				stack.push_back(adj_face.id);
				visited[adj_face.id] = true;
			}

			if(isEndFace(adj_face.id, end_faces))
				return true;
		}
	}

	return false;
}

bool Board::isEndFace(FaceID id, vector<FaceID> const& end_faces)
{
	for(unsigned int i=0; i<end_faces.size(); i++)
		if(end_faces[i] == id)
			return true;

	return false;
}
