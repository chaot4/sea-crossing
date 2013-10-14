#include "conf.h"
#include "messageChannel.h"
#include "communicationHub.h"
#include "messages.h"

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

	return 0;
}
