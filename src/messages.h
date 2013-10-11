#ifndef messages_h
#define messages_h

enum MessageType { ENGINE_CREATE, ENGINE_DELETE, ENGINE_CREATE_FEEDBACK,
	ENGINE_QUIT, ENGINE_USER_INPUT, GAME_CREATE_GEM, GAME_CREATE_MARKER,
	GAME_QUIT, GAME_RETURN_INPUT, GAME_REQUEST_INPUT };

struct Message
{
	MessageType type;

	Message() {}
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

};

struct MsgGameCreateMarker : Message
{

};

struct MsgGameQuit : Message
{

};

struct MsgGameReturnInput : Message
{

};

struct MsgGameRequestInput : Message
{

};

#endif
