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
	run = false;
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
		case GAME_CREATE_GEM:
			process(static_pointer_cast<MsgGameCreateGem>(msg));
			break;
		case GAME_CREATE_MARKER:
			process(static_pointer_cast<MsgGameCreateMarker>(msg));
			break;
		case GAME_FINISHED:
			process(static_pointer_cast<MsgGameFinished>(msg));
			break;
		case GAME_REQUEST_INPUT:
			process(static_pointer_cast<MsgGameRequestInput>(msg));
			break;
		case PLAYER_RETURN_INPUT:
			process(static_pointer_cast<MsgPlayerReturnInput>(msg));
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

void CommunicationHub::process(std::shared_ptr<MsgGameCreateGem> msg)
{

}

void CommunicationHub::process(std::shared_ptr<MsgGameFinished> msg)
{

}

void CommunicationHub::process(std::shared_ptr<MsgGameCreateMarker> msg)
{

}

void CommunicationHub::process(std::shared_ptr<MsgGameRequestInput> msg)
{
	std::shared_ptr<Message> new_msg(new MsgPlayerRequestInput(msg->player_id));
	_player_channel.send(new_msg);
}

void CommunicationHub::process(std::shared_ptr<MsgPlayerReturnInput> msg)
{

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
