#ifndef game_board_h
#define game_board_h

#include "defs.h"

#include <map>
#include <string>
#include <vector>
#include <unordered_set>
#include <cassert>

class Board{
	private:
		std::vector<Node> nodes;
		std::vector<Face> faces;

		std::map<NodeLabel, NodeID> node_map;
		std::map<FaceLabel, FaceID> face_map;

		std::unordered_set<NodeID> free_nodes;

		void initMaps();

		bool existsPathBetween(std::vector<FaceID> const& start_faces,
				std::vector<FaceID> const& end_faces, PlayerID player_id) const;
		bool isEndFace(FaceID id, std::vector<FaceID> const& end_faces) const;
	public:
		Board();

		void reset();

		bool placeGem(NodeLabel const& label, PlayerID player_id,
				std::vector<FaceLabel>& new_markers);
		bool placeMarker(FaceLabel const& label, PlayerID player_id);
		bool removeGem(NodeLabel const& label, std::vector<FaceLabel>& removed_markers);
		bool removeMarker(FaceLabel const& label);

		bool isNodeLabel(NodeLabel const& label) const;
		bool isFaceLabel(FaceLabel const& label) const;
		bool nodeHasOwner(NodeLabel const& label) const;
		bool faceHasOwner(FaceLabel const& label) const;
		bool checkVictoryCondition(PlayerID player_id) const;

		template <class Cost>
		std::vector<FaceLabel const&> calcShortestPath(PlayerID);

		Node const& getNode(NodeID node_id) const;
		Face const& getFace(FaceID face_id) const;
		std::unordered_set<NodeID> const& getFreeNodes() const;
};

#endif
