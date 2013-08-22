#include "messageReceiver.h"

MessageReceiver::MessageReceiver():message_counter(0)
{
	entity_info_map.insert(std::pair<std::string, EntityInfo>("A",
		EntityInfo(0, glm::vec3(0, 0.125, 0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("BNW",
		EntityInfo(1, glm::vec3(-2.5, 0.125, -2.5), glm::rotate(glm::quat(), 45.0, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("BNE",
		EntityInfo(2, glm::vec3(2.5, 0.125, -2.5), glm::rotate(glm::quat(), -45.0, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("BSE",
		EntityInfo(3, glm::vec3(2.5, 0.125, 2.5), glm::rotate(glm::quat(), 45.0, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("BSW",
		EntityInfo(4, glm::vec3(-2.5, 0.125, 2.5), glm::rotate(glm::quat(), -45.0, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("CNW",
		EntityInfo(5, glm::vec3(-5, 0.125, -5), glm::rotate(glm::quat(), 45.0, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("CN",
		EntityInfo(6, glm::vec3(0, 0.125, -6.25), glm::rotate(glm::quat(), 0, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("CNE",
		EntityInfo(7, glm::vec3(5, 0.125, -5), glm::rotate(glm::quat(), -45, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("CE",
		EntityInfo(8, glm::vec3(6.25, 0.125, 0), glm::rotate(glm::quat(), 90, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("CSE",
		EntityInfo(9, glm::vec3(5, 0.125, 5), glm::rotate(glm::quat(), 45, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("CS",
		EntityInfo(10, glm::vec3(0, 0.125, 6.25), glm::rotate(glm::quat(), 0, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("CSW",
		EntityInfo(11, glm::vec3(-5, 0.125, 5), glm::rotate(glm::quat(), 45, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("CW",
		EntityInfo(12, glm::vec3(-6.25, 0.125, 0), glm::rotate(glm::quat(), 90, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("DNW",
		EntityInfo(13, glm::vec3(-7.5, 0.125, -7.5), glm::rotate(glm::quat(), 45, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("DN-1",
		EntityInfo(14, glm::vec3(-2.5, 0.125, -8.75), glm::rotate(glm::quat(), 0, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("DN1",
		EntityInfo(15, glm::vec3(2.5, 0.125, -8.75), glm::rotate(glm::quat(), 0, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("DNE",
		EntityInfo(16, glm::vec3(7.5, 0.125, -7.5), glm::rotate(glm::quat(), -45, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("DE1",
		EntityInfo(17, glm::vec3(8.75, 0.125, -2.5), glm::rotate(glm::quat(), 90, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("DE-1",
		EntityInfo(18, glm::vec3(8.75, 0.125, 2.5), glm::rotate(glm::quat(), 90, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("DSE",
		EntityInfo(19, glm::vec3(7.5, 0.125, 7.5), glm::rotate(glm::quat(), 45, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("DS1",
		EntityInfo(20, glm::vec3(2.5, 0.125, 8.75), glm::rotate(glm::quat(), 0, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("DS-1",
		EntityInfo(21, glm::vec3(-2.5, 0.125, 8.75), glm::rotate(glm::quat(), 0, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("DSW",
		EntityInfo(22, glm::vec3(-7.5, 0.125, 7.5), glm::rotate(glm::quat(), -45, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("DW-1",
		EntityInfo(23, glm::vec3(-8.75, 0.125, 2.5), glm::rotate(glm::quat(), 90, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("DW1",
		EntityInfo(24, glm::vec3(-8.75, 0.125, -2.5), glm::rotate(glm::quat(), 90, glm::vec3(0, 1, 0)))));

	entity_info_map.insert(std::pair<std::string, EntityInfo>("ENW",
		EntityInfo(25, glm::vec3(-10.0, 0.125, -10.0), glm::rotate(glm::quat(), 45, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("EN-1",
		EntityInfo(26, glm::vec3(-5.0, 0.125, -11.25), glm::rotate(glm::quat(), 0, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("EN",
		EntityInfo(27, glm::vec3(0.0, 0.125, -11.25), glm::rotate(glm::quat(), 0, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("EN1",
		EntityInfo(28, glm::vec3(5.0, 0.125, -11.25), glm::rotate(glm::quat(), 0, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("ENE",
		EntityInfo(29, glm::vec3(10.0, 0.125, -10.0), glm::rotate(glm::quat(), -45, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("EE1",
		EntityInfo(30, glm::vec3(11.25, 0.125, -5.0), glm::rotate(glm::quat(), 90, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("EE",
		EntityInfo(31, glm::vec3(11.25, 0.125, 0.0), glm::rotate(glm::quat(), 90, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("EE-1",
		EntityInfo(32, glm::vec3(11.25, 0.125, 5.0), glm::rotate(glm::quat(), 90, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("ESE",
		EntityInfo(33, glm::vec3(10.0, 0.125, 10.0), glm::rotate(glm::quat(), 45, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("ES1",
		EntityInfo(34, glm::vec3(5.0, 0.125, 11.25), glm::rotate(glm::quat(), 0, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("ES",
		EntityInfo(35, glm::vec3(0.0, 0.125, 11.25), glm::rotate(glm::quat(), 0, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("ES-1",
		EntityInfo(36, glm::vec3(-5.0, 0.125, 11.25), glm::rotate(glm::quat(), 0, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("ESW",
		EntityInfo(37, glm::vec3(-10.0, 0.125, 10.0), glm::rotate(glm::quat(), -45, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("EW-1",
		EntityInfo(38, glm::vec3(-11.25, 0.125, 5.0), glm::rotate(glm::quat(), 90, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("EW",
		EntityInfo(39, glm::vec3(-11.25, 0.125, 0.0), glm::rotate(glm::quat(), 90, glm::vec3(0, 1, 0)))));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("EW1",
		EntityInfo(40, glm::vec3(-11.25, 0.125, -5.0), glm::rotate(glm::quat(), 90, glm::vec3(0, 1, 0)))));
	

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
