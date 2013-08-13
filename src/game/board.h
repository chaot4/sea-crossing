#ifndef board_h
#define board_h

#include "defs.h"

#include <map>
#include <string>
#include <vector>
#include <cassert>

class Board{
	private:
		std::vector<Node> nodes;
		std::vector<Face> faces;

		std::map<NodeLabel, NodeID> node_map;
		std::map<FaceLabel, FaceID> face_map;

		void init_maps();

	public:
		Board();

		void reset();

		bool placeGem(NodeLabel& label, PlayerID player_id);
		bool placeMarker(FaceLabel& label, PlayerID player_id);
		bool removeGem(NodeLabel& label);
		bool removeMarker(FaceLabel& label);
		bool checkVictoryCondition(PlayerID player_id);
};

#endif
