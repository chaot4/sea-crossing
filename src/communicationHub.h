#ifndef communicationHub_h
#define communicationHub_h

#include "messageChannel.h"
#include "messages.h"
#include "conf.h"
#include "game/board.h"

#include <limits>

#include <iostream>
#ifdef _WIN32
	/*Fix call to windows macros instead of std::max*/
	#define NOMINMAX
	#include <windows.h>
	#define sleep(x) Sleep(x)
#elif __linux__
#include <unistd.h>
#define sleep(x) usleep(x)
#else
#define sleep(x)
#endif

class CommunicationHub
{
	private:
		TwoWayChannel _engine_channel;
		TwoWayChannel _menu_channel;
		TwoWayChannel _game_channel;
		TwoWayChannel _player_channel;

		bool run;
		GraphicsConf graphics_conf;
		Board const& board;

		int engine_msg_id;

		void processMessage(TwoWayChannel& channel);
		void process(std::shared_ptr<MsgEngineCreateFeedback> msg);
		void process(std::shared_ptr<MsgEngineUserInput> msg);
		void process(std::shared_ptr<MsgGameCreate> msg);
		void process(std::shared_ptr<MsgGameCreateGem> msg);
		void process(std::shared_ptr<MsgGameWinner> msg);
		void process(std::shared_ptr<MsgGameFinished> msg);
		void process(std::shared_ptr<MsgGameCreateMarker> msg);
		void process(std::shared_ptr<MsgGameCreatePlayer> msg);
		void process(std::shared_ptr<MsgGameRequestInput> msg);
		void process(std::shared_ptr<MsgGameReturnInput> msg);

		void sendQuit(TwoWayChannel& channel);

		int nextEngineMsgID();
	
	public:
		CommunicationHub(GraphicsConf const& graphics_conf, Board const& board);

		void start();
		void stop();
		TwoWayChannel& getEngineChannel();
		TwoWayChannel& getMenuChannel();
		TwoWayChannel& getGameChannel();
		TwoWayChannel& getPlayerChannel();
};

#endif
