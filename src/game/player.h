#ifndef game_player_h
#define game_player_h

#include "defs.h"
#include "board.h"
#include "../messageChannel.h"
#include "../messages.h"

#include <string>

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

class Player{
	protected:
		bool run;
		unsigned int sleep_time;
		Board const& board;
		TwoWayChannel _player_center_channel;

		void processMessage(TwoWayChannel& channel);
		void process(std::shared_ptr<MsgGameRequestInput>);
		void process(std::shared_ptr<MsgPlayerReturnInput>);
		void process(std::shared_ptr<MsgPlayerQuit>);
		void msgSendFinished();
		void msgSendGemMove(NodeID node_id);

		std::string name;
		PlayerID id;
	public:
		Player(PlayerID id, std::string const& name, Board const& board);
		virtual ~Player();

		void start();
		TwoWayChannel& getPlayerCenterChannel();

		virtual void initGemMove() = 0;
};

#endif
