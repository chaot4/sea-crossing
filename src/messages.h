#ifndef messages_h
#define messages_h

/*	Include sea-crossing headers */
#include "game/defs.h"

/*	Include external headers */
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

enum MessageType { ENGINE_CREATE, ENGINE_DELETE, ENGINE_UPDATE_ENTITY, ENGINE_CREATE_FEEDBACK,
	ENGINE_QUIT, ENGINE_USER_INPUT, GAME_CREATE, GAME_CREATE_GEM,
	GAME_CREATE_MARKER, GAME_CREATE_PLAYER, GAME_QUIT, GAME_FINISHED,
	GAME_RETURN_INPUT, GAME_REQUEST_INPUT, GAME_WINNER, PLAYER_REQUEST_INPUT,
	PLAYER_RETURN_INPUT, PLAYER_CREATE, PLAYER_QUIT, PLAYER_FINISHED, QUIT};

std::string toString(MessageType type);

struct Message
{
	MessageType type;

	Message(MessageType type)
		: type(type) {}
};

struct MsgEngineCreate : Message
{
	unsigned int msg_id;
	glm::vec3 position;
	glm::quat orientation;
	glm::vec3 scaling;
	std::string geometry_path;
	std::string material_path;

	MsgEngineCreate(unsigned int in_msg_id,glm::vec3 in_position,
		glm::quat in_orientation,glm::vec3 in_scaling,
		std::string in_geometry_path,std::string in_material_path)
		: Message(ENGINE_CREATE), msg_id(in_msg_id), position(in_position),
		orientation(in_orientation), scaling(in_scaling), geometry_path(in_geometry_path),
		material_path(in_material_path) {}
};

struct MsgEngineDelete : Message
{
	unsigned int entity_id;

	MsgEngineDelete(unsigned int in_msg_id, unsigned int in_entity_id)
		: Message(ENGINE_DELETE), entity_id(in_entity_id) {}
};

/*
/	Keep on a lookout for a nicer solution.
/	Always having all attributes in the message (even those that aren't updated, and
/	which therefore will have to be filled with junk values) seems like a waste.
*/
struct MsgEngineUpdateEntity : Message
{
	unsigned int entity_id;
	bool update_position;
	bool update_orientation;
	bool update_scaling;
	bool update_geometry_path;
	bool update_material_path;

	glm::vec3 position;
	glm::quat orientation;
	glm::vec3 scaling;
	std::string geometry_path;
	std::string material_path;

	MsgEngineUpdateEntity(unsigned int in_entity_id,
							bool in_update_position,
							bool in_update_orientation,
							bool in_update_scaling,
							bool in_update_geometry_path,
							bool in_update_material_path,
							glm::vec3 in_position, glm::quat in_orientation, glm::vec3 in_scaling,
							std::string in_geometry_path, std::string in_material_path)
		: Message(ENGINE_UPDATE_ENTITY), entity_id(in_entity_id),
		update_position(in_update_position),
		update_orientation(in_update_orientation),
		update_scaling(in_update_scaling),
		update_geometry_path(in_update_geometry_path),
		update_material_path(in_update_material_path),
		position(in_position), orientation(in_orientation), scaling(in_scaling),
		geometry_path(in_geometry_path), material_path(in_material_path) {}
};

struct MsgEngineCreateFeedback : Message
{
	unsigned int msg_id;
	unsigned int entity_id;

	MsgEngineCreateFeedback(unsigned int in_msg_id, unsigned int in_entity_id)
		: Message(ENGINE_CREATE_FEEDBACK), msg_id(in_msg_id), entity_id(in_entity_id) {}
};

struct MsgEngineQuit : Message
{

};

struct MsgEngineUserInput : Message
{

};

struct MsgGameCreate : Message
{
	GameType game_type;

	MsgGameCreate(GameType game_type)
		: Message(GAME_CREATE), game_type(game_type) {}
};

struct MsgGameCreateGem : Message
{
	PlayerID player_id;
	NodeID node_id;

	MsgGameCreateGem(PlayerID player_id, NodeID node_id)
		: Message(GAME_CREATE_GEM), player_id(player_id), node_id(node_id) {}
};

struct MsgGameCreateMarker : Message
{
	PlayerID player_id;
	FaceID face_id;

	MsgGameCreateMarker(PlayerID player_id, FaceID face_id)
		: Message(GAME_CREATE_MARKER), player_id(player_id), face_id(face_id) {}
};

struct MsgGameCreatePlayer : Message
{
	PlayerID player_id;
	PlayerType player_type;
	std::string player_name;

	MsgGameCreatePlayer(PlayerID player_id, PlayerType player_type,
			std::string const& player_name)
		: Message(GAME_CREATE_PLAYER), player_id(player_id),
		player_type(player_type), player_name(player_name) {}
};

struct MsgGameQuit : Message
{
	MsgGameQuit()
		: Message(GAME_QUIT) {}
};

struct MsgGameFinished : Message 
{
	MsgGameFinished()
		: Message(GAME_FINISHED) {}
};

struct MsgGameReturnInput : Message
{
	NodeID node_id;

	MsgGameReturnInput(NodeID node_id)
		: Message(GAME_RETURN_INPUT), node_id(node_id) {}
};

struct MsgGameRequestInput : Message
{
	PlayerID player_id;

	MsgGameRequestInput(PlayerID player_id)
		: Message(GAME_REQUEST_INPUT), player_id(player_id) {}
};

struct MsgGameWinner : Message 
{
	PlayerID winner;

	MsgGameWinner(PlayerID winner)
		: Message(GAME_WINNER), winner(winner) {}
};

struct MsgPlayerRequestInput : Message
{
	PlayerID player_id;

	MsgPlayerRequestInput(PlayerID player_id)
		: Message(PLAYER_REQUEST_INPUT), player_id(player_id) {}
};

struct MsgPlayerReturnInput : Message
{
	PlayerID player_id;
	NodeID node_id;

	MsgPlayerReturnInput(NodeID node_id, PlayerID player_id)
		: Message(PLAYER_RETURN_INPUT), player_id(player_id), node_id(node_id) {}
};

struct MsgPlayerQuit : Message
{
	PlayerID player_id;

	MsgPlayerQuit(PlayerID player_id)
		: Message(PLAYER_QUIT), player_id(player_id) {}
};

struct MsgPlayerFinished : Message
{
	PlayerID player_id;

	MsgPlayerFinished(PlayerID player_id)
		: Message(PLAYER_FINISHED), player_id(player_id) {}
};

struct MsgQuit : Message
{
	MsgQuit()
		: Message(QUIT) {}
};

#endif
