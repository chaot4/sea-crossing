#ifndef player_center_h
#define player_center_h

#include "../messageChannel.h"
#include "../messages.h"
#include "human_players.h"
#include "../ai/ai_players.h"
#include "board.h"

#include <vector>
#include <string>
#include <thread>
#include <iostream>

#ifdef WIN_32
#include <windows.h>
#define sleep(x) Sleep(x)
#elif __linux__
#include <unistd.h>
#else
// other
#endif

class PlayerCenter
{
	private:
		bool run;
		unsigned int sleep_time;
		Board const& board;

		TwoWayChannel _hub_channel;

		std::vector<TwoWayChannel*> _player_channels;
		std::vector<Player*> _players;
		std::vector<std::thread*> _player_threads;
                void createPlayer(PlayerID player_id, PlayerType player_type,
				std::string const& name);

                void processMessage(TwoWayChannel& channel);
		void process(std::shared_ptr<MsgGameRequestInput> msg);
		void process(std::shared_ptr<MsgGameReturnInput> msg);
		void process(std::shared_ptr<MsgPlayerRequestInput> msg);
		void process(std::shared_ptr<MsgPlayerReturnInput> msg);
		void process(std::shared_ptr<MsgGameCreatePlayer> msg);
		void process(std::shared_ptr<MsgPlayerQuit> msg);
		void process(std::shared_ptr<MsgPlayerFinished> msg);

//		void quit();

	public:
		PlayerCenter(Board const& board);
		void start();

		TwoWayChannel& getHubChannel();
};

#endif
