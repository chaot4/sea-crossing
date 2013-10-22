#include "conf.h"
#include "communicationHub.h"
#include "engine/renderHub.h"
#include "game/game_center.h"
#include "game/player_center.h"

#include <thread>

#include <iostream>
#ifdef WIN_32
#include <windows.h>
#define sleep(x) Sleep(x)
#elif __linux__
#include <unistd.h>
#define sleep(x) usleep(x)
#else
// other
#endif

using namespace std;

int main(){
	Board board;
	Conf conf("config");
	conf.readFromFile();

	CommunicationHub c_hub;
	RenderHub r_hub;
	GameCenter game_center(conf.getGameConf(), board);
	PlayerCenter player_center(board);
	TwoWayChannel menu_channel;

	TwoWayChannel::connect(game_center.getHubChannel(), c_hub.getGameChannel());
	TwoWayChannel::connect(player_center.getHubChannel(), c_hub.getPlayerChannel());
	TwoWayChannel::connect(r_hub.getChannelAccesPoint(), c_hub.getEngineChannel());
	TwoWayChannel::connect(menu_channel, c_hub.getMenuChannel());
	std::thread game_center_thread(&GameCenter::start, &game_center);
	std::thread player_center_thread(&PlayerCenter::start, &player_center);
	std::thread render_thread(&RenderHub::init, &r_hub);
	std::thread c_hub_thread(&CommunicationHub::start, &c_hub);

	std::shared_ptr<Message> msg(new MsgGameCreate(GUI_GAME));
	menu_channel.send(msg);

//	/*	Test Game and Player channels channel */
//	std::shared_ptr<Message> new_msg(new MsgGameRequestInput(1));
//	std::shared_ptr<Message> rec_msg;
//	game_channel.send(new_msg);
//	while (!player_channel.receive(rec_msg)) {}
//	std::shared_ptr<MsgPlayerRequestInput> cast_msg(
//			std::static_pointer_cast<MsgPlayerRequestInput>(rec_msg));
//	cout << cast_msg->player_id << endl;
//
//	/*	Test renderHub channel */
//	std::shared_ptr<Message> new_engine_msg(
//		new MsgEngineCreate(42, glm::vec3(0.0, 0.0, 0.0), glm::quat(), glm::vec3(1.0),
//		"../resources/meshes/board.fbx","../resources/materials/debugging.slmtl") );
//	engine_channel.send(new_engine_msg);
//	while (!engine_channel.receive(rec_msg)) {}
//	std::shared_ptr<MsgEngineCreateFeedback> c_msg(
//		std::static_pointer_cast<MsgEngineCreateFeedback>(rec_msg));
//	cout << "Message id:" <<c_msg->msg_id <<"  Entity id:"<< c_msg->entity_id<< endl;
//

	game_center_thread.join();
	player_center_thread.join();
	render_thread.join();
	c_hub_thread.join();

	return 0;
}
