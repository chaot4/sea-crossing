#ifndef game_game_h
#define game_game_h

#include "defs.h"
#include "board.h"
#include "player.h"
#include "human_players.h"
#include "../ai/ai_players.h"

#include <string>
#include <vector>

class DebugGame{
	private:
		struct Move{
			std::string label;
			bool owner_id;
			bool is_gem;

			Move(std::string const& label, PlayerID owner_id, bool is_gem)
				:label(label), owner_id(owner_id), is_gem(is_gem){}
		};

		ConsolePlayer** player;
		Board& board;

		std::vector<Move> moves;
		std::vector<Move> reverted_moves;

		bool command_player(PlayerID player_id);
		bool command_marker_player(PlayerID player_id);
		void command_back();
		void command_forward();

		void placeGem(PlayerID player_id, NodeLabel label);
		void placeMarker(PlayerID player_id, FaceLabel label);
		void removeGem(Move const& move);
		void removeMarker(Move const& move);

	public:
		DebugGame(ConsolePlayer* player1, ConsolePlayer* player2, Board& board);
		void start();
};

class ConsoleGame{
	private:
		Player** player;
		Board& board;

		bool makeMove(PlayerID player_id);
		void placeGem(PlayerID player_id, NodeLabel label);

	public:
		ConsoleGame(Player* player1, Player* player2, Board& board);
		void start();
};

template <typename MessageReceiver>
class SimpleGUIGame{
	private:
		Player** player;
		Board& board;
		MessageReceiver* receiver;

		bool makeMove(PlayerID player_id);
		void placeGem(PlayerID player_id, NodeLabel label);

	public:
		SimpleGUIGame(Player* player1, Player* player2,
				Board& board, MessageReceiver* receiver);
		void start();
};


//SimpleGUIGame::SimpleGUIGame(ConsolePlayer const& player1, ConsolePlayer const& player2)
//	:player{player1, player2}{}
template <typename MessageReceiver>
SimpleGUIGame<MessageReceiver>::SimpleGUIGame(Player* player1, Player* player2, Board& board,
		MessageReceiver* receiver)
	:player(new Player*[2]), board(board), receiver(receiver)
{
	player[0] = player1;
	player[1] = player2;
}

template <typename MessageReceiver>
void SimpleGUIGame<MessageReceiver>::start()
{
	bool current_player(0);
	bool valid_move(false);

	std::cout << "==- START SIMPLE GUI GAME -==" << std::endl;

	while(!board.checkVictoryCondition(current_player)){

		std::cout << std::endl;

		if(valid_move){
			current_player = !current_player;
		}

		valid_move = makeMove(current_player);
	}

	std::cout << player[current_player]->getName() << " wins!" << std::endl;
	std::cout << std::endl << "==- END SIMPLE GUI GAME -==" << std::endl;
}

template <typename MessageReceiver>
bool SimpleGUIGame<MessageReceiver>::makeMove(PlayerID player_id)
{
	NodeLabel label;

	player[player_id]->getNextMove(label);

	if(board.isNodeLabel(label)){
		if(!board.nodeHasOwner(label)){
			placeGem(player_id, label);
		}
		else{
			std::cout << "ERROR: This node is already taken." << std::endl;
			return false;
		}
	}
	else{
		std::cout << "ERROR: The passed string is not a node label." << std::endl;
		return false;
	}

	return true;
}

template <typename MessageReceiver>
void SimpleGUIGame<MessageReceiver>::placeGem(PlayerID player_id, NodeLabel label)
{
	std::vector<FaceLabel> new_markers;

	board.placeGem(label, player_id, new_markers);
	receiver->pushCreateGemMessage(label, player_id);

	for(unsigned int i=0; i<new_markers.size(); i++){
		receiver->pushCreateMarkerMessage(new_markers[i], player_id);
	}
}

#endif
