#ifndef game_game_h
#define game_game_h

#include "defs.h"
#include "board.h"
#include "../conf.h"
#include "../messageChannel.h"
#include "../messages.h"

#include <string>
#include <vector>

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

//class DebugGame{
//	private:
//		struct Move
//		{
//			std::string label;
//			bool owner_id;
//			bool is_gem;
//
//			Move(std::string const& label, PlayerID owner_id, bool is_gem)
//				:label(label), owner_id(owner_id), is_gem(is_gem){}
//		};
//
//		ConsolePlayer** player;
//		Board& board;
//		MessageReceiver* receiver;
//
//		std::vector<Move> moves;
//		std::vector<Move> reverted_moves;
//
//		bool command_player(PlayerID player_id);
//		bool command_marker_player(PlayerID player_id);
//		void command_back();
//		void command_forward();
//
//		void placeGem(PlayerID player_id, NodeLabel label);
//		void placeMarker(PlayerID player_id, FaceLabel label);
//		void removeGem(Move const& move);
//		void removeMarker(Move const& move);
//
//	public:
//		DebugGame(ConsolePlayer* player1, ConsolePlayer* player2,
//				Board& board, MessageReceiver* receiver = 0);
//		void start();
//};

class Game{
	protected:
		bool run;
		unsigned int sleep_time;
		TwoWayChannel _game_center_channel;

		PlayerID current_player;
		Board& board;
		GameConf conf;

		void processMessage(TwoWayChannel& channel);
		void process(std::shared_ptr<MsgGameQuit> msg);
		void process(std::shared_ptr<MsgGameReturnInput> msg);
		void msgRequestInput(PlayerID player_id);
		void msgCreateGem(PlayerID player_id, NodeID node_id);
		void msgCreateMarker(PlayerID player_id, FaceID face_id);
		void msgCreatePlayer(PlayerID player_id, PlayerType player_type,
				std::string const& player_name);
		void msgSendWinner(PlayerID player_id);
		void msgSendFinished();

		bool makeMove(PlayerID player_id, NodeID node_id);
		virtual void placeGem(PlayerID player_id, NodeID node_id) = 0;

	public:
		Game(GameConf const& conf, Board& board);
		virtual ~Game();

		void start();
		TwoWayChannel& getGameCenterChannel();
};

class ConsoleGame : public Game{
	private:
		void placeGem(PlayerID player_id, NodeID node_id);

	public:
		ConsoleGame(GameConf const& conf, Board& board);
};

class SimpleGUIGame : public Game{
	private:
		void placeGem(PlayerID player_id, NodeID node_id);

	public:
		SimpleGUIGame(GameConf const& conf, Board& board);
};

#endif
