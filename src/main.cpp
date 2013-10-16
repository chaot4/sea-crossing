#include "conf.h"
#include "messageChannel.h"
#include "communicationHub.h"
#include "messages.h"
#include "engine\renderHub.h"

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
	CommunicationHub c_hub;
	TwoWayChannel game_channel;
	TwoWayChannel player_channel;
	TwoWayChannel::connect(game_channel, c_hub.getGameChannel());
	TwoWayChannel::connect(player_channel, c_hub.getPlayerChannel());
	std::thread c_hub_thread(&CommunicationHub::start, &c_hub);

	std::shared_ptr<Message> new_msg(new MsgGameRequestInput(1));
	std::shared_ptr<Message> rec_msg;
	game_channel.send(new_msg);
	while (!player_channel.receive(rec_msg)) {}
	std::shared_ptr<MsgPlayerRequestInput> cast_msg(
			std::static_pointer_cast<MsgPlayerRequestInput>(rec_msg));
	cout << cast_msg->player_id << endl;

	c_hub.stop();
	c_hub_thread.join();

	/*	Test renderHub channel */
	RenderHub r_hub;
	TwoWayChannel engine_channel;
	TwoWayChannel::connect(engine_channel, r_hub.getChannelAccesPoint());
	std::thread render_thread(&RenderHub::init, &r_hub);
	std::shared_ptr<Message> new_engine_msg(
		new MsgEngineCreate(42, glm::vec3(0.0, 0.0, 0.0), glm::quat(), glm::vec3(1.0),
		"../resources/meshes/board.fbx","../resources/materials/debugging.slmtl") );
	engine_channel.send(new_engine_msg);
	while (!engine_channel.receive(rec_msg)) {}
	std::shared_ptr<MsgEngineCreateFeedback> c_msg(
		std::static_pointer_cast<MsgEngineCreateFeedback>(rec_msg));
	cout << "Message id:" <<c_msg->msg_id <<"  Entity id:"<< c_msg->entity_id<< endl;

	render_thread.join();

	return 0;
}
