#include "communicationHub.h"

using namespace std;

CommunicationHub::CommunicationHub(GraphicsConf const& graphics_conf, Board const& board)
	: run(true), graphics_conf(graphics_conf), board(board),
	engine_msg_id(0) {}

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
		case GAME_WINNER:
			process(static_pointer_cast<MsgGameWinner>(msg));
			break;
		case PLAYER_QUIT:
			process(static_pointer_cast<MsgPlayerQuit>(msg));
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
			cerr << "ERROR: Unexpected message type: " << toString(msg->type) << endl;
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
	std::shared_ptr<Message> new_engine_msg(
		new MsgEngineCreate(nextEngineMsgID(), glm::vec3(0.0, 0.0, 0.0), glm::quat(), glm::vec3(1.0),
		graphics_conf.board_geometry, graphics_conf.board_material) );
	_engine_channel.send(new_engine_msg);
	_game_channel.send(static_pointer_cast<Message>(msg));
}

void CommunicationHub::process(std::shared_ptr<MsgGameCreateGem> msg)
{
	Node const& node(board.getNode(msg->node_id));
	std::string const* gem_material;

	if (msg->player_id) {
		gem_material = &graphics_conf.gem_material_p2;
	}
	else {
		gem_material = &graphics_conf.gem_material_p1;
	}

	std::shared_ptr<Message> new_msg(
		new MsgEngineCreate(nextEngineMsgID(), node.position, node.orientation,
			glm::vec3(1.0), graphics_conf.gem_geometry, *gem_material));
	// TODO put id into map.

	_engine_channel.send(new_msg);
}

void CommunicationHub::process(std::shared_ptr<MsgGameWinner> msg)
{
	std::shared_ptr<Message> new_msg(new MsgGameQuit());
	_game_channel.send(new_msg);
}

void CommunicationHub::process(std::shared_ptr<MsgGameFinished> msg)
{

}

void CommunicationHub::process(std::shared_ptr<MsgGameCreateMarker> msg)
{
	Face const& face(board.getFace(msg->face_id));
	std::string const* marker_material;

	if (msg->player_id) {
		marker_material = &graphics_conf.marker_material_p2;
	}
	else {
		marker_material = &graphics_conf.marker_material_p1;
	}

	std::shared_ptr<Message> new_msg(
		new MsgEngineCreate(nextEngineMsgID(), face.position, face.orientation,
			glm::vec3(1.0), graphics_conf.marker_geometry, *marker_material));
	// TODO put id into map.

	_engine_channel.send(new_msg);
}

void CommunicationHub::process(std::shared_ptr<MsgGameCreatePlayer> msg)
{
	_player_channel.send(static_pointer_cast<Message>(msg));
}

void CommunicationHub::process(std::shared_ptr<MsgPlayerQuit> msg)
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

int CommunicationHub::nextEngineMsgID()
{
	return engine_msg_id++;
}
