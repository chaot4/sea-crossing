#include "messages.h"

std::string toString(MessageType type)
{
	switch (type) {
		case ENGINE_CREATE:
			return "ENGINE_CREATE";
		case ENGINE_DELETE:
			return "ENGINE_DELETE";
		case ENGINE_UPDATE_ENTITY:
			return "ENGINE_UPDATE_ENTITY";
		case ENGINE_CREATE_FEEDBACK:
			return "ENGINE_CREATE_FEEDBACK";
		case ENGINE_QUIT:
			return "ENGINE_QUIT";
		case ENGINE_USER_INPUT:
			return "ENGINE_USER_INPUT";
		case GAME_CREATE:
			return "GAME_CREATE";
		case GAME_CREATE_GEM:
			return "GAME_CREATE_GEM";
		case GAME_CREATE_MARKER:
			return "GAME_CREATE_MARKER";
		case GAME_CREATE_PLAYER:
			return "GAME_CREATE_PLAYER";
		case GAME_QUIT:
			return "GAME_QUIT";
		case GAME_FINISHED:
			return "GAME_FINISHED";
		case GAME_RETURN_INPUT:
			return "GAME_RETURN_INPUT";
		case GAME_REQUEST_INPUT:
			return "GAME_REQUEST_INPUT";
		case GAME_WINNER:
			return "GAME_WINNER";
		case PLAYER_REQUEST_INPUT:
			return "PLAYER_REQUEST_INPUT";
		case PLAYER_RETURN_INPUT:
			return "PLAYER_RETURN_INPUT";
		case PLAYER_CREATE:
			return "PLAYER_CREATE";
		case PLAYER_QUIT:
			return "PLAYER_QUIT";
		case PLAYER_FINISHED:
			return "PLAYER_FINISHED";
		case QUIT:
			return "QUIT";
		default:
			std::cerr << "Error: Conversion from MessageType to std::string failed. Unknown Message Type." << std::endl;
			return "";
	}
}
