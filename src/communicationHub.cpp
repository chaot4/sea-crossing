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
		case ENG_COMM_SEND_OBJ_ID:
			process(static_pointer_cast<MsgEngComm_SendObjId>(msg));
			break;
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
		case PLAYER_REQUEST_INPUT:
			process(static_pointer_cast<MsgPlayerRequestInput>(msg));
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

void CommunicationHub::process(std::shared_ptr<MsgEngComm_SendObjId>(msg))
{
	std::cout<<"The engine tells me, that you clicked at the object with the id "<<msg->entity_id<<std::endl;

	auto node_it = entity_to_node.find(msg->entity_id);
	auto face_it = entity_to_face.find(msg->entity_id);
	assert((node_it == entity_to_node.end()) || (face_it == entity_to_face.end()));

	if (node_it != entity_to_node.end())
	{
		std::cout<<"Furthermore I can tell you, that it corresponds to node "<<node_it->second<<std::endl;
	}
	else if (face_it != entity_to_face.end())
	{
		std::cout<<"Furthermore I can tell you, that it corresponds to face "<<face_it->second<<std::endl;
	}
}

void CommunicationHub::process(std::shared_ptr<MsgEngineCreateFeedback> msg)
{
	auto node_it = msg_to_node.find(msg->msg_id);
	auto face_it = msg_to_face.find(msg->msg_id);
	//assert((node_it == msg_to_node.end()) != (face_it == msg_to_face.end()));
	assert((node_it == msg_to_node.end()) || (face_it == msg_to_face.end()));

	MsgID entity_id(msg->entity_id);
	if (node_it != msg_to_node.end()) {
		NodeID node_id(node_it->second);
		node_to_entity.insert(
			std::pair<NodeID, unsigned int>(node_id, entity_id));
		entity_to_node.insert(
			std::pair<unsigned int, NodeID>(entity_id, node_id));

		msg_to_node.erase(node_it);
	}
	else if (face_it != msg_to_face.end()) {
		FaceID face_id(face_it->second);
		face_to_entity.insert(
			std::pair<FaceID, unsigned int>(face_id, entity_id));
		entity_to_face.insert(
			std::pair<unsigned int, FaceID>(entity_id, face_id));

		msg_to_face.erase(face_it);
	}
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

	MsgID msg_id(nextEngineMsgID());
	std::shared_ptr<Message> new_msg(
		new MsgEngineCreate(msg_id, node.position, node.orientation,
			glm::vec3(1.0), graphics_conf.gem_geometry, *gem_material));
	msg_to_node.insert(std::pair<MsgID, NodeID>(msg_id, msg->node_id));

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

	MsgID msg_id(nextEngineMsgID());
	std::shared_ptr<Message> new_msg(
		new MsgEngineCreate(msg_id, face.position, face.orientation,
			glm::vec3(1.0), graphics_conf.marker_geometry, *marker_material));
	msg_to_face.insert(std::pair<MsgID, FaceID>(msg_id, msg->face_id));

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

void CommunicationHub::process(std::shared_ptr<MsgPlayerRequestInput> msg)
{
	_engine_channel.send(static_pointer_cast<Message>(msg));
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
