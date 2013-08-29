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
		EntityInfo(11, glm::vec3(-5, 0.125, 5), glm::rotate(glm::quat(), -45, glm::vec3(0, 1, 0)))));
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
	entity_info_map.insert(std::pair<std::string, EntityInfo>("eSW",
		EntityInfo(41, glm::vec3(-12.5, 0.3, 12.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("eSE",
		EntityInfo(42, glm::vec3(12.5, 0.3, 12.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dS-3",
		EntityInfo(43, glm::vec3(-7.5, 0.3, 10.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dS-2",
		EntityInfo(44, glm::vec3(-5.0, 0.3, 10.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dS-1",
		EntityInfo(45, glm::vec3(-2.5, 0.3, 10.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dS",
		EntityInfo(46, glm::vec3(0, 0.3, 10.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dS1",
		EntityInfo(47, glm::vec3(2.5, 0.3, 10.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dS2",
		EntityInfo(48, glm::vec3(5.0, 0.3, 10.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dS3",
		EntityInfo(49, glm::vec3(7.5, 0.3, 10.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dW-3",
		EntityInfo(50, glm::vec3(-10.0, 0.3, 7.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dE-3",
		EntityInfo(51, glm::vec3(10.0, 0.3, 7.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("cS-2",
		EntityInfo(52, glm::vec3(-5.0, 0.3, 7.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("cS-1",
		EntityInfo(53, glm::vec3(-2.5, 0.3, 7.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("cS",
		EntityInfo(54, glm::vec3(0, 0.3, 7.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("cS1",
		EntityInfo(55, glm::vec3(2.5, 0.3, 7.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("cS2",
		EntityInfo(56, glm::vec3(5.0, 0.3, 7.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dW-2",
		EntityInfo(57, glm::vec3(-10.0, 0.3, 5.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("cW-2",
		EntityInfo(58, glm::vec3(-7.5, 0.3, 5.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("cE-2",
		EntityInfo(59, glm::vec3(7.5, 0.3, 5.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dE-2",
		EntityInfo(60, glm::vec3(10.0, 0.3, 5.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("bS-1",
		EntityInfo(61, glm::vec3(-2.5, 0.3, 5.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("bS",
		EntityInfo(62, glm::vec3(0, 0.3, 5.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("bS1",
		EntityInfo(63, glm::vec3(2.5, 0.3, 5.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dW-1",
		EntityInfo(64, glm::vec3(-10, 0.3, 2.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("cW-1",
		EntityInfo(65, glm::vec3(-7.5, 0.3, 2.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("bW-1",
		EntityInfo(66, glm::vec3(-5.0, 0.3, 2.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("bE-1",
		EntityInfo(67, glm::vec3(5.0, 0.3, 2.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("cE-1",
		EntityInfo(68, glm::vec3(7.5, 0.3, 2.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dE-1",
		EntityInfo(69, glm::vec3(10, 0.3, 2.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("aS",
		EntityInfo(70, glm::vec3(0, 0.3, 2.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dW",
		EntityInfo(71, glm::vec3(-10, 0.3, 0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("cW",
		EntityInfo(72, glm::vec3(-7.5, 0.3, 0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("bW",
		EntityInfo(73, glm::vec3(-5.0, 0.3, 0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("aW",
		EntityInfo(74, glm::vec3(-2.5, 0.3, 0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("0",
		EntityInfo(75, glm::vec3(0, 0.3, 0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("aE",
		EntityInfo(76, glm::vec3(2.5, 0.3, 0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("bE",
		EntityInfo(77, glm::vec3(5.0, 0.3, 0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("cE",
		EntityInfo(78, glm::vec3(7.5, 0.3, 0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dE",
		EntityInfo(79, glm::vec3(10, 0.3, 0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("aN",
		EntityInfo(80, glm::vec3(0, 0.3, -2.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dW1",
		EntityInfo(81, glm::vec3(-10, 0.3, -2.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("cW1",
		EntityInfo(82, glm::vec3(-7.5, 0.3, -2.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("bW1",
		EntityInfo(83, glm::vec3(-5.0, 0.3, -2.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("bE1",
		EntityInfo(84, glm::vec3(5.0, 0.3, -2.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("cE1",
		EntityInfo(85, glm::vec3(7.5, 0.3, -2.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dE1",
		EntityInfo(86, glm::vec3(10, 0.3, -2.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("bN-1",
		EntityInfo(87, glm::vec3(-2.5, 0.3, -5.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("bN",
		EntityInfo(88, glm::vec3(0, 0.3, -5.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("bN1",
		EntityInfo(89, glm::vec3(2.5, 0.3, -5.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dW2",
		EntityInfo(90, glm::vec3(-10.0, 0.3, -5.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("cW2",
		EntityInfo(91, glm::vec3(-7.5, 0.3, -5.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("cE2",
		EntityInfo(92, glm::vec3(7.5, 0.3, -5.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dE2",
		EntityInfo(93, glm::vec3(10.0, 0.3, -5.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("cN-2",
		EntityInfo(94, glm::vec3(-5.0, 0.3, -7.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("cN-1",
		EntityInfo(95, glm::vec3(-2.5, 0.3, -7.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("cN",
		EntityInfo(96, glm::vec3(0, 0.3, -7.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("cN1",
		EntityInfo(97, glm::vec3(2.5, 0.3, -7.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("cN2",
		EntityInfo(98, glm::vec3(5.0, 0.3, -7.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dW3",
		EntityInfo(99, glm::vec3(-10.0, 0.3, -7.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dE3",
		EntityInfo(100, glm::vec3(10.0, 0.3, -7.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dN-3",
		EntityInfo(101, glm::vec3(-7.5, 0.3, -10.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dN-2",
		EntityInfo(102, glm::vec3(-5.0, 0.3, -10.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dN-1",
		EntityInfo(103, glm::vec3(-2.5, 0.3, -10.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dN",
		EntityInfo(104, glm::vec3(0, 0.3, -10.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dN1",
		EntityInfo(105, glm::vec3(2.5, 0.3, -10.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dN2",
		EntityInfo(106, glm::vec3(5.0, 0.3, -10.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("dN3",
		EntityInfo(107, glm::vec3(7.5, 0.3, -10.0), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("eNW",
		EntityInfo(108, glm::vec3(-12.5, 0.3, -12.5), glm::quat())));
	entity_info_map.insert(std::pair<std::string, EntityInfo>("eNE",
		EntityInfo(109, glm::vec3(12.5, 0.3, -12.5), glm::quat())));
}

void MessageReceiver::pushLoadSceneMessages()
{
	Message newMsg(CREATE,100,glm::vec3(0.0,0.0,0.0),glm::quat(),glm::vec3(1.0),
		"../resources/meshes/board.fbx",
		"../resources/materials/debugging.slmtl");

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
	if(player == 0) mat_path = "../resources/materials/templates/silver.slmtl";
	if(player == 1) mat_path = "../resources/materials/templates/gold.slmtl";
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
	if(player == 0) mat_path = "../resources/materials/templates/silver.slmtl";
	if(player == 1) mat_path = "../resources/materials/templates/gold.slmtl";
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
