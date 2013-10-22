#include "communicationHub.h"

using namespace std;

CommunicationHub::CommunicationHub()
	: run(true) {}

void CommunicationHub::start()
{
	while(run){
		processMessage(_engine_channel);
		sleep(1);
		processMessage(_menu_channel);
		sleep(1);
		processMessage(_game_channel);
		sleep(1);
		processMessage(_player_channel);
		sleep(1);
	}
}

void CommunicationHub::stop()
{
//	sendQuit(_engine_channel);
//	sendQuit(_menu_channel);
//	sendQuit(_game_channel);
//	sendQuit(_player_channel);
}

void CommunicationHub::processMessage(TwoWayChannel& channel)
{
	shared_ptr<Message> msg;
	if (!channel.receive(msg)) {
		return;
	}

	switch (msg->type) {
		case ENGINE_CREATE_FEEDBACK:
			process(static_pointer_cast<MsgEngineCreateFeedback>(msg));
			break;
		case ENGINE_USER_INPUT:
			process(static_pointer_cast<MsgEngineUserInput>(msg));
			break;
		case GAME_CREATE:
			process(static_pointer_cast<MsgGameCreate>(msg));
			break;
		case GAME_CREATE_GEM:
			process(static_pointer_cast<MsgGameCreateGem>(msg));
			break;
		case GAME_CREATE_MARKER:
			process(static_pointer_cast<MsgGameCreateMarker>(msg));
			break;
		case GAME_CREATE_PLAYER:
			process(static_pointer_cast<MsgGameCreatePlayer>(msg));
			break;
		case GAME_FINISHED:
			process(static_pointer_cast<MsgGameFinished>(msg));
			break;
		case GAME_REQUEST_INPUT:
			process(static_pointer_cast<MsgGameRequestInput>(msg));
			break;
		case GAME_RETURN_INPUT:
			process(static_pointer_cast<MsgGameReturnInput>(msg));
			break;
		default:
			cerr << "ERROR: Unexpected message type." << endl;
	}
}

void CommunicationHub::process(std::shared_ptr<MsgEngineCreateFeedback> msg)
{

}

void CommunicationHub::process(std::shared_ptr<MsgEngineUserInput> msg)
{

}

void CommunicationHub::process(std::shared_ptr<MsgGameCreate> msg)
{
	_game_channel.send(static_pointer_cast<Message>(msg));
}

void CommunicationHub::process(std::shared_ptr<MsgGameCreateGem> msg)
{
	std::shared_ptr<Message> new_engine_msg(
	new MsgEngineCreate(42, glm::vec3(0.0, 0.0, 0.0), glm::quat(), glm::vec3(1.0),
	"../resources/meshes/board.fbx","../resources/materials/debugging.slmtl"));
	_engine_channel.send(new_engine_msg);
	// TODO place the right gem
}

void CommunicationHub::process(std::shared_ptr<MsgGameFinished> msg)
{

}

void CommunicationHub::process(std::shared_ptr<MsgGameCreateMarker> msg)
{

}

void CommunicationHub::process(std::shared_ptr<MsgGameCreatePlayer> msg)
{
	_player_channel.send(static_pointer_cast<Message>(msg));
}

void CommunicationHub::process(std::shared_ptr<MsgGameRequestInput> msg)
{
	_player_channel.send(static_pointer_cast<Message>(msg));
}

void CommunicationHub::process(std::shared_ptr<MsgGameReturnInput> msg)
{
	_game_channel.send(static_pointer_cast<Message>(msg));
}

TwoWayChannel& CommunicationHub::getEngineChannel()
{
	return _engine_channel;
}

TwoWayChannel& CommunicationHub::getMenuChannel()
{
	return _menu_channel;
}

TwoWayChannel& CommunicationHub::getGameChannel()
{
	return _game_channel;
}

TwoWayChannel& CommunicationHub::getPlayerChannel()
{
	return _player_channel;
}

void CommunicationHub::sendQuit(TwoWayChannel& channel)
{
	std::shared_ptr<Message> msg(new MsgQuit());
	channel.send(msg);
}
