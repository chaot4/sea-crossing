#ifndef messages_h
#define messages_h

#include "game/defs.h"

enum MessageType { ENGINE_CREATE, ENGINE_DELETE, ENGINE_CREATE_FEEDBACK,
	ENGINE_QUIT, ENGINE_USER_INPUT, GAME_CREATE_GEM, GAME_CREATE_MARKER, GAME_CREATE_PLAYER,
	GAME_QUIT, GAME_FINISHED, GAME_RETURN_INPUT, GAME_REQUEST_INPUT, GAME_SEND_WINNER,
	PLAYER_REQUEST_INPUT, PLAYER_RETURN_INPUT, PLAYER_CREATE, PLAYER_QUIT,
	PLAYER_FINISHED };

struct Message
{
	MessageType type;

	Message(MessageType type)
		: type(type) {}
};

struct MsgEngineCreate : Message
{

};

struct MsgEngineDelete : Message
{

};

struct MsgEngineCreateFeedback : Message
{

};

struct MsgEngineQuit : Message
{

};

struct MsgEngineUserInput : Message
{

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

	MsgGameCreatePlayer(PlayerID player_id, PlayerType player_type)
		: Message(GAME_CREATE_PLAYER), player_id(player_id),
		player_type(player_type) {}
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
		: Message(PLAYER_RETURN_INPUT), node_id(node_id) {}
};

struct MsgGameRequestInput : Message
{
	PlayerID player_id;

	MsgGameRequestInput(PlayerID player_id)
		: Message(GAME_REQUEST_INPUT), player_id(player_id) {}
};

struct MsgGameSendWinner : Message 
{
	PlayerID winner;

	MsgGameSendWinner(PlayerID winner)
		: Message(GAME_SEND_WINNER), winner(winner) {}
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

struct MsgPlayerCreate : Message
{
	PlayerType player_type;
	std::string name;

	MsgPlayerCreate(PlayerType player_type, std::string name)
		: Message(PLAYER_CREATE), player_type(player_type), name(name) {}
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

#endif
