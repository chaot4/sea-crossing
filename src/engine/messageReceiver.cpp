#include "messageReceiver.h"

MessageReceiver::MessageReceiver():message_counter(0)
{
	entity_info_map.insert(std::pair<std::string, EntityInfo>("A",
		EntityInfo(0, glm::vec3(0, 0.125, 0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("BNW",
		EntityInfo(1, glm::vec3(-2.5, 0.125, 2.5), glm::quat(glm::rotate(glm::quat(), -45.0, glm::vec3(0, 1, 0))))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("BNE",
		EntityInfo(2, glm::vec3(2.5, 0.125, 2.5), glm::quat(glm::rotate(glm::quat(), 45.0, glm::vec3(0, 1, 0))))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("BSE",
		EntityInfo(3, glm::vec3(2.5, 0.125, -2.5), glm::rotate(glm::quat(), -45.0, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("BSW",
		EntityInfo(4, glm::vec3(-2.5, 0.125, -2.5), glm::quat(glm::rotate(glm::quat(), 45.0, glm::vec3(0, 1, 0))))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("CNW",
		EntityInfo(5, glm::vec3(-5, 0.125, 5), glm::quat(glm::rotate(glm::quat(), -45.0, glm::vec3(0, 1, 0))))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("CN",
		EntityInfo(6, glm::vec3(0, 0.125, 6.25), glm::quat(glm::rotate(glm::quat(), 0, glm::vec3(0, 1, 0))))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("CNE",
		EntityInfo(7, glm::vec3(5, 0.125, 5), glm::quat(glm::rotate(glm::quat(), 45, glm::vec3(0, 1, 0))))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("CE",
		EntityInfo(8, glm::vec3(6.25, 0.125, 0), glm::quat(glm::rotate(glm::quat(), 90, glm::vec3(0, 1, 0))))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("CSE",
		EntityInfo(9, glm::vec3(5, 0.125, -5), glm::quat(glm::rotate(glm::quat(), -45, glm::vec3(0, 1, 0))))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("CS",
		EntityInfo(10, glm::vec3(0, 0.125, -6.25), glm::quat(glm::rotate(glm::quat(), 0, glm::vec3(0, 1, 0))))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("CSW",
		EntityInfo(11, glm::vec3(-5, 0.125, -5), glm::quat(glm::rotate(glm::quat(), -45, glm::vec3(0, 1, 0))))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("CW",
		EntityInfo(12, glm::vec3(-6.25, 0.125, 0), glm::quat(glm::rotate(glm::quat(), 90, glm::vec3(0, 1, 0))))));
}

void MessageReceiver::pushLoadSceneMessages()
{
	Message newMsg(CREATE,100,glm::vec3(0.0,0.0,0.0),glm::quat(),glm::vec3(1.0),
		"../resources/meshes/board.fbx",
		"../resources/materials/default.slmtl");

	message_fifo.push(newMsg);
	message_counter++;
}

void MessageReceiver::pushCreateMarkerMessage(std::string label, int player)
{
	EntityInfo const& entity_info(entity_info_map.at(label));
	int id(entity_info.id);
	glm::vec3 euclid_pos(entity_info.coords);
	glm::quat orientation(entity_info.orientation);
	glm::vec3 scaling(1, 1, 1);
	std::string geom_path = "../resources/meshes/marker.fbx";
	std::string mat_path = "../resources/materials/default.slmtl";
	//if(player == 0) mat_path = "../data/materials/bright_wood.slmtl";
	//if(player == 1) mat_path = "../data/materials/dark_wood.slmtl";
	mat_path = "../resources/materials/default.slmtl";
	Message newMsg(CREATE,id,euclid_pos,orientation,scaling,geom_path,mat_path);

	message_fifo.push(newMsg);
	message_counter++;
}

void MessageReceiver::pushCreateGemMessage(std::string label, int player)
{
	EntityInfo const& entity_info(entity_info_map.at(label));
	int id(entity_info.id);
	glm::vec3 euclid_pos(entity_info.coords);
	glm::quat orientation(entity_info.orientation);
	glm::vec3 scaling(1, 1, 1);
	std::string geom_path = "../resources/meshes/gem.fbx";
	std::string mat_path = "../resources/materials/default.slmtl";
	//if(player == 0) mat_path = "../data/materials/bright_stone.slmtl";
	//if(player == 1) mat_path = "../data/materials/dark_stone.slmtl";
	mat_path = "../resources/materials/default.slmtl";
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
	message_fifo.pop();
	message_counter--;

	return msg;
}

bool MessageReceiver::checkQueue()
{
	if(message_counter > 0) return true;
	else return false;
}
