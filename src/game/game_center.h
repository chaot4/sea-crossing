#ifndef game_center_h
#define game_center_h

#include "../messageChannel.h"
#include "../messages.h"
#include "game.h"

#include <string>
#include <thread>
#include <iostream>

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

class GameCenter
{
	private:
		bool run;
		unsigned int sleep_time;

		TwoWayChannel _hub_channel;
		TwoWayChannel* _game_channel;

		Game* _current_game;
		std::thread* _current_game_thread;
		Board& board;
		GameConf const& game_conf;
		bool startGame(GameType game_type);

		void processMessage(TwoWayChannel& channel);
		void process(std::shared_ptr<MsgGameCreateGem> msg);
		void process(std::shared_ptr<MsgGameCreateMarker> msg);
		void process(std::shared_ptr<MsgGameCreatePlayer> msg);
		void process(std::shared_ptr<MsgGameQuit> msg);
		void process(std::shared_ptr<MsgGameFinished> msg);
		void process(std::shared_ptr<MsgGameReturnInput> msg);
		void process(std::shared_ptr<MsgGameRequestInput> msg);
		void process(std::shared_ptr<MsgGameSendWinner> msg);

	public:
		GameCenter(GameConf const& game_conf, Board& board);
		~GameCenter();
		void start();

		TwoWayChannel& getHubChannel();
};

#endif
