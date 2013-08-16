#include "messageReceiver.h"

void MessageReceiver::pushCreateMarkerMessage(int id, int player)
{
	glm::vec3 euclid_pos;
	glm::quat orientation;
	glm::vec3 scaling;
	std::string geom_path = "../data/meshes/marker.fbx";
	std::string mat_path = "../data/materials/default.slmtl";
	if(player=0) mat_path = "../data/materials/bright_wood.slmtl";
	if(player=1) mat_path = "../data/materials/dark_wood.slmtl";
	Message newMsg(CREATE,id,euclid_pos,orientation,scaling,geom_path,mat_path);

	message_fifo.push(newMsg);
	message_counter++;
}

void MessageReceiver::pushCreateGemMessage(int id, int player)
{
	glm::vec3 euclid_pos;
	glm::quat orientation;
	glm::vec3 scaling;
	std::string geom_path = "../data/meshes/gem.fbx";
	std::string mat_path = "../data/materials/default.slmtl";
	if(player=0) mat_path = "../data/materials/bright_stone.slmtl";
	if(player=1) mat_path = "../data/materials/dark_stone.slmtl";
	Message newMsg(CREATE,id,euclid_pos,orientation,scaling,geom_path,mat_path);

	message_fifo.push(newMsg);
	message_counter++;
}

void MessageReceiver::pushDeleteMessage(int id)
{
	Message newMsg(DELETE,id);
	message_fifo.push(newMsg);
	message_counter++;
}

void MessageReceiver::pushExitMessage()
{
}

Message MessageReceiver::popMessage()
{
	Message msg = message_fifo.front();
	message_counter--;
	
	return msg;
}
