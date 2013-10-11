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
#else
// other
#endif

class CommunicationHub
{
	private:
		TwoWayChannel _engine_channel;
		TwoWayChannel _game_channel;
		TwoWayChannel _menu_channel;

		bool run;

		void processMessage(TwoWayChannel& channel);
		void process(std::shared_ptr<MsgEngineCreateFeedback> msg);
		void process(std::shared_ptr<MsgEngineUserInput> msg);
		void process(std::shared_ptr<MsgGameCreateGem> msg);
		void process(std::shared_ptr<MsgGameCreateMarker> msg);
		void process(std::shared_ptr<MsgGameRequestInput> msg);
	
	public:
		CommunicationHub();

		void start();
		TwoWayChannel& getEngineChannel();
		TwoWayChannel& getGameChannel();
		TwoWayChannel& getMenuChannel();
};

#endif
