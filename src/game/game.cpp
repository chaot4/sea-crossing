#include "game.h"

using namespace std;


/* DEBUG GAME */


//DebugGame::DebugGame(ConsolePlayer const& player1, ConsolePlayer const& player2)
//	:player{player1, player2}, board(){}
DebugGame::DebugGame(ConsolePlayer* player1, ConsolePlayer* player2, Board& board)
	:player(new ConsolePlayer*[2]), board(board)
{
	player[0] = player1;
	player[1] = player2;
}

void DebugGame::start()
{
	string command("");
	bool game_finished(false);

	cout << "==- START DEBUG GAME -==" << endl << endl;
	cout << "The possible commands are: player1 (p1), player2 (p2), marker_player1 (mp1),"
		<< endl;
	cout <<	"                           marker_player2 (mp2), back (b), forward (f), exit (e)."
		<< endl;

	while(!game_finished){
		cout << endl << "Pass a command: ";
		cin >> command;

		if(command == "player1" || command == "p1"){
			game_finished = command_player(0);
		}
		else if(command == "player2" || command == "p2"){
			game_finished = command_player(1);
		}
		else if(command == "marker_player1" || command == "mp1"){
			game_finished = command_marker_player(0);
		}
		else if(command == "marker_player2" || command == "mp2"){
			game_finished = command_marker_player(1);
		}
		else if(command == "back" || command == "b"){
			command_back();
		}
		else if(command == "forward" || command == "f"){
			command_forward();
		}
		else if(command == "exit" || command == "e"){
			game_finished = true;
		}
		else{
			cout << "ERROR: The command you entered is not known." << endl;
		}
	}

	cout << endl << "==- END DEBUG GAME -==" << endl;
}

bool DebugGame::command_player(PlayerID player_id)
{
	NodeLabel label;

	player[player_id]->getNextMove(label);

	if(board.isNodeLabel(label))
		if(!board.nodeHasOwner(label)){
			placeGem(player_id, label);
			reverted_moves.clear();

			if(board.checkVictoryCondition(player_id)){
				cout << player[player_id]->getName() << " wins!" << endl;
				return true;
			}
		}
		else{
			cout << "ERROR: This node is already taken." << endl;
		}
	else
		cout << "ERROR: The passed string is not a node label." << endl;

	return false;
}

void DebugGame::placeGem(PlayerID player_id, NodeLabel label)
{
	vector<FaceLabel> new_markers;

	cout << player[player_id]->getName() << " placed a gem on " << label << "." << endl;
	board.placeGem(label, player_id, new_markers);
	moves.push_back(Move(label, player_id, true));

	for(unsigned int i=0; i<new_markers.size(); i++){
		cout << "A new marker of " << player[player_id]->getName()
			<< " has been placed on " << new_markers[i] << "."
			<< endl;
	}
}

bool DebugGame::command_marker_player(PlayerID player_id)
{
	FaceLabel label;

	player[player_id]->getMarkerMove(label);

	if(board.isFaceLabel(label)){
		if(!board.faceHasOwner(label)){
			placeMarker(player_id, label);
			reverted_moves.clear();

			if(board.checkVictoryCondition(player_id)){
				cout << player[player_id]->getName() << " wins!" << endl;
				return true;
			}
		}
		else{
			cout << "ERROR: This face is already taken." << endl;
		}
	}
	else{
		cout << "ERROR: The passed string is not a face label." << endl;
	}

	return false;
}

void DebugGame::placeMarker(PlayerID player_id, FaceLabel label)
{
	cout << player[player_id]->getName() << " placed a marker on " << label << "." << endl;
	board.placeMarker(label, player_id);
	moves.push_back(Move(label, player_id, false));
}

void DebugGame::command_back()
{
	if(!moves.empty()){
		Move const& last_move(moves.back());

		if(last_move.is_gem){
			removeGem(last_move);
		}
		else{
			removeMarker(last_move);
		}

		reverted_moves.push_back(last_move);
		moves.pop_back();
	}
	else{
		cout << "ERROR: There exists no move that can be reverted." << endl;
	}
}

void DebugGame::removeGem(Move const& move)
{
	vector<FaceLabel> removed_markers;

	cout << "Removed the gem of " << player[move.owner_id]->getName()
		<< " from " << move.label << "." << endl;
	board.removeGem(move.label, removed_markers);

	if(!removed_markers.empty()){
		cout << "Also removed the following markers: ";

		for(unsigned int i=0; i<removed_markers.size(); i++){
			cout << removed_markers[i] << " ";
		}
		cout << endl;
	}
}
	
void DebugGame::removeMarker(Move const& move)
{
	cout << "Removed the marker of " << player[move.owner_id]->getName()
		<< " from " << move.label << "." << endl;
	board.removeMarker(move.label);
}

void DebugGame::command_forward()
{
	if(!reverted_moves.empty()){
		Move const& last_undone_move(reverted_moves.back());

		if(last_undone_move.is_gem){
			placeGem(last_undone_move.owner_id, last_undone_move.label);
		}
		else{
			placeMarker(last_undone_move.owner_id, last_undone_move.label);
		}

		reverted_moves.pop_back();
	}
	else{
		cout << "ERROR: There exists no move that can be redone." << endl;
	}
}


/* CONSOLE GAME */


//ConsoleGame::ConsoleGame(ConsolePlayer const& player1, ConsolePlayer const& player2)
//	:player{player1, player2}{}
ConsoleGame::ConsoleGame(Player* player1, Player* player2, Board& board)
	:player(new Player*[2]), board(board)
{
	player[0] = player1;
	player[1] = player2;
}

void ConsoleGame::start()
{
	bool current_player(0);
	bool valid_move(false);

	cout << "==- START CONSOLE GAME -==" << endl;

	while(!board.checkVictoryCondition(current_player)){

		cout << endl;

		if(valid_move){
			current_player = !current_player;
		}

		valid_move = makeMove(current_player);
	}

	cout << player[current_player]->getName() << " wins!" << endl;
	cout << endl << "==- END CONSOLE GAME -==" << endl;
}

bool ConsoleGame::makeMove(PlayerID player_id)
{
	NodeLabel label;

	player[player_id]->getNextMove(label);

	if(board.isNodeLabel(label)){
		if(!board.nodeHasOwner(label)){
			placeGem(player_id, label);
		}
		else{
			cout << "ERROR: This node is already taken." << endl;
			return false;
		}
	}
	else{
		cout << "ERROR: The passed string is not a node label." << endl;
		return false;
	}

	return true;
}

void ConsoleGame::placeGem(PlayerID player_id, NodeLabel label)
{
	vector<FaceLabel> new_markers;

	cout << player[player_id]->getName() << " placed a gem on " << label << "." << endl;
	board.placeGem(label, player_id, new_markers);

	for(unsigned int i=0; i<new_markers.size(); i++){
		cout << "A new marker of " << player[player_id]->getName()
			<< " has been placed on " << new_markers[i] << "."
			<< endl;
	}
}


/* GUI GAME */


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

	cout << "==- START SIMPLE GUI GAME -==" << endl;

	while(!board.checkVictoryCondition(current_player)){

		cout << endl;

		if(valid_move){
			current_player = !current_player;
		}

		valid_move = makeMove(current_player);
	}

	cout << player[current_player]->getName() << " wins!" << endl;
	cout << endl << "==- END SIMPLE GUI GAME -==" << endl;
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
			cout << "ERROR: This node is already taken." << endl;
			return false;
		}
	}
	else{
		cout << "ERROR: The passed string is not a node label." << endl;
		return false;
	}

	return true;
}

template <typename MessageReceiver>
void SimpleGUIGame<MessageReceiver>::placeGem(PlayerID player_id, NodeLabel label)
{
	vector<FaceLabel> new_markers;

	board.placeGem(label, player_id, new_markers);
	receiver->pushCreateGemMessage(label, player_id);

	for(unsigned int i=0; i<new_markers.size(); i++){
		receiver->pushCreateMarkerMessage(new_markers[i], player_id);
	}
}
