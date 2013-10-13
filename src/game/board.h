#ifndef game_board_h
#define game_board_h

#include "defs.h"

#include <map>
#include <string>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <limits>
#include <queue>

class Board{
	private:
		std::vector<Node> nodes;
		std::vector<Face> faces;

		std::vector<std::vector<FaceID> > start_faces;
		std::vector<std::vector<FaceID> > end_faces;

		std::map<NodeLabel, NodeID> node_map;
		std::map<FaceLabel, FaceID> face_map;

		std::unordered_set<NodeID> free_nodes;

		void initMaps();

		bool isEndFace(FaceID id, PlayerID player_id) const;
	public:
		Board();

		void reset();

		bool placeGem(NodeID node_id, PlayerID player_id,
				std::vector<FaceID>& new_markers);
		bool placeMarker(FaceID face_id, PlayerID player_id);
		bool removeGem(NodeLabel const& label, std::vector<FaceLabel>& removed_markers);
		bool removeMarker(FaceLabel const& label);

		bool isNodeLabel(NodeLabel const& label) const;
		bool isFaceLabel(FaceLabel const& label) const;
		bool isNodeID(NodeID node_id) const;
		bool isFaceID(FaceID face_id) const;
		bool nodeHasOwner(NodeID node_id) const;
		bool faceHasOwner(FaceID face_id) const;
		bool checkVictoryCondition(PlayerID player_id) const;

		template <class Cost>
		std::vector<FaceID> calcShortestPath(PlayerID player_id) const;

		Node const& getNode(NodeID node_id) const;
		Face const& getFace(FaceID face_id) const;
		std::unordered_set<NodeID> const& getFreeNodes() const;
};

template <class Cost>
std::vector<FaceID> Board::calcShortestPath(PlayerID player_id) const
{
	std::vector<unsigned int> dists(faces.size(), std::numeric_limits<unsigned int>::max());
	std::vector<FaceID> found_by(faces.size());
	std::priority_queue<PQFace, std::vector<PQFace>, std::greater<PQFace> > pq;
	Cost cost(*this, player_id);

	for(unsigned int i(0); i<start_faces[player_id].size(); i++){

		FaceID face_id(start_faces[player_id][i]);
		Face const& face(faces[face_id]);

		unsigned int dist(cost.get(face));
		pq.push(PQFace(&face, std::numeric_limits<FaceID>::max(), dist));
//		dists[face.id] = dist; TODO how to minimize the number of elements in pq?
	}

	while(!isEndFace(pq.top().face->id, player_id)){

		Face const* face(pq.top().face);
		unsigned int dist(pq.top().dist);

		if(dist < dists[face->id]){

			dists[face->id] = dist;
			found_by[face->id] = pq.top().found_by;

			for(unsigned int i(0); i<face->adj_faces.size(); i++){
				Face const& adj_face(faces[face->adj_faces[i]]);

				unsigned int adj_dist(dist + cost.get(adj_face));
				if(adj_dist < dists[adj_face.id]){
					pq.push(PQFace(&adj_face, face->id, adj_dist));
//					dists[adj_face.id] = adj_dist; TODO
				}
			}
		}

		pq.pop();
	}

	std::vector<FaceID> path;
	FaceID face_id(pq.top().face->id);
	found_by[face_id] = pq.top().found_by;

	while(face_id != std::numeric_limits<FaceID>::max()){
		path.push_back(face_id);
		face_id = found_by[face_id];
	}
	
	return path;
}

#endif
