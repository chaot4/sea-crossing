#ifndef communicationHub_h
#define communicationHub_h

#include "messageChannel.h"
#include "messages.h"

#include <iostream>
#ifdef WIN_32
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

		void processMessage(TwoWayChannel& channel);
		void process(std::shared_ptr<MsgEngineCreateFeedback> msg);
		void process(std::shared_ptr<MsgEngineUserInput> msg);
		void process(std::shared_ptr<MsgGameCreateGem> msg);
		void process(std::shared_ptr<MsgGameFinished> msg);
		void process(std::shared_ptr<MsgGameCreateMarker> msg);
		void process(std::shared_ptr<MsgGameRequestInput> msg);
		void process(std::shared_ptr<MsgPlayerReturnInput> msg);
	
	public:
		CommunicationHub();

		void start();
		void stop();
		TwoWayChannel& getEngineChannel();
		TwoWayChannel& getMenuChannel();
		TwoWayChannel& getGameChannel();
		TwoWayChannel& getPlayerChannel();
};

#endif
