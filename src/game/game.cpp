#include "game.h"

using namespace std;


/* DEBUG GAME */


//DebugGame::DebugGame(ConsolePlayer const& player1, ConsolePlayer const& player2)
//	:player{player1, player2}, board(){}
//DebugGame::DebugGame(ConsolePlayer* player1, ConsolePlayer* player2, Board& board,
//		MessageReceiver* receiver)
//	:player(new ConsolePlayer*[2]), board(board), receiver(receiver)
//{
//	player[0] = player1;
//	player[1] = player2;
//}
//
//void DebugGame::start()
//{
//	string command("");
//	bool game_finished(false);
//
//	cout << "==- START DEBUG GAME -==" << endl << endl;
//	cout << "The possible commands are: player1 (p1), player2 (p2), marker_player1 (mp1),"
//		<< endl;
//	cout <<	"                           marker_player2 (mp2), back (b), forward (f), exit (e)."
//		<< endl;
//
//	while(!game_finished){
//		cout << endl << "Pass a command: ";
//		cin >> command;
//
//		if(command == "player1" || command == "p1"){
//			game_finished = command_player(0);
//		}
//		else if(command == "player2" || command == "p2"){
//			game_finished = command_player(1);
//		}
//		else if(command == "marker_player1" || command == "mp1"){
//			game_finished = command_marker_player(0);
//		}
//		else if(command == "marker_player2" || command == "mp2"){
//			game_finished = command_marker_player(1);
//		}
//		else if(command == "back" || command == "b"){
//			command_back();
//		}
//		else if(command == "forward" || command == "f"){
//			command_forward();
//		}
//		else if(command == "exit" || command == "e"){
//			game_finished = true;
//		}
//		else{
//			cout << "ERROR: The command you entered is not known." << endl;
//		}
//	}
//
//	cout << endl << "==- END DEBUG GAME -==" << endl;
//}
//
//bool DebugGame::command_player(PlayerID player_id)
//{
//	NodeLabel label;
//
//	player[player_id]->getNextMove(label);
//
//	if(board.isNodeLabel(label))
//		if(!board.nodeHasOwner(label)){
//			placeGem(player_id, label);
//			reverted_moves.clear();
//
//			if(board.checkVictoryCondition(player_id)){
//				cout << player[player_id]->getName() << " wins!" << endl;
//				return true;
//			}
//		}
//		else{
//			cout << "ERROR: This node is already taken." << endl;
//		}
//	else
//		cout << "ERROR: The passed string is not a node label." << endl;
//
//	return false;
//}
//
//void DebugGame::placeGem(PlayerID player_id, NodeLabel label)
//{
//	vector<FaceLabel> new_markers;
//
//	cout << player[player_id]->getName() << " placed a gem on " << label << "." << endl;
//	board.placeGem(label, player_id, new_markers);
//	moves.push_back(Move(label, player_id, true));
//
//	if(receiver){
//		receiver->pushCreateGemMessage(label, player_id);
//	}
//
//	for(unsigned int i=0; i<new_markers.size(); i++){
//		cout << "A new marker of " << player[player_id]->getName()
//			<< " has been placed on " << new_markers[i] << "."
//			<< endl;
//
//		if(receiver){
//			receiver->pushCreateMarkerMessage(new_markers[i], player_id);
//		}
//	}
//}
//
//bool DebugGame::command_marker_player(PlayerID player_id)
//{
//	FaceLabel label;
//
//	player[player_id]->getMarkerMove(label);
//
//	if(board.isFaceLabel(label)){
//		if(!board.faceHasOwner(label)){
//			placeMarker(player_id, label);
//			reverted_moves.clear();
//
//			if(board.checkVictoryCondition(player_id)){
//				cout << player[player_id]->getName() << " wins!" << endl;
//				return true;
//			}
//		}
//		else{
//			cout << "ERROR: This face is already taken." << endl;
//		}
//	}
//	else{
//		cout << "ERROR: The passed string is not a face label." << endl;
//	}
//
//	return false;
//}
//
//void DebugGame::placeMarker(PlayerID player_id, FaceLabel label)
//{
//	cout << player[player_id]->getName() << " placed a marker on " << label << "." << endl;
//	board.placeMarker(label, player_id);
//	moves.push_back(Move(label, player_id, false));
//
//	if(receiver){
//		receiver->pushCreateMarkerMessage(label, player_id);
//	}
//}
//
//void DebugGame::command_back()
//{
//	if(!moves.empty()){
//		Move const& last_move(moves.back());
//
//		if(last_move.is_gem){
//			removeGem(last_move);
//		}
//		else{
//			removeMarker(last_move);
//		}
//
//		reverted_moves.push_back(last_move);
//		moves.pop_back();
//	}
//	else{
//		cout << "ERROR: There exists no move that can be reverted." << endl;
//	}
//}
//
//void DebugGame::removeGem(Move const& move)
//{
//	vector<FaceLabel> removed_markers;
//
//	cout << "Removed the gem of " << player[move.owner_id]->getName()
//		<< " from " << move.label << "." << endl;
//	board.removeGem(move.label, removed_markers);
//
//	// TODO receiver
//
//	if(!removed_markers.empty()){
//		cout << "Also removed the following markers: ";
//
//		for(unsigned int i=0; i<removed_markers.size(); i++){
//			cout << removed_markers[i] << " ";
//			// TODO receiver
//		}
//		cout << endl;
//	}
//}
//	
//void DebugGame::removeMarker(Move const& move)
//{
//	cout << "Removed the marker of " << player[move.owner_id]->getName()
//		<< " from " << move.label << "." << endl;
//	board.removeMarker(move.label);
//
//	// TODO receiver
//}
//
//void DebugGame::command_forward()
//{
//	if(!reverted_moves.empty()){
//		Move const& last_undone_move(reverted_moves.back());
//
//		if(last_undone_move.is_gem){
//			placeGem(last_undone_move.owner_id, last_undone_move.label);
//		}
//		else{
//			placeMarker(last_undone_move.owner_id, last_undone_move.label);
//		}
//
//		reverted_moves.pop_back();
//	}
//	else{
//		cout << "ERROR: There exists no move that can be redone." << endl;
//	}
//}


/* GAME */


Game::Game(GameConf const& conf, Board& board)
	: run(true), sleep_time(5), current_player(0), board(board), conf(conf)
{
	msgCreatePlayer(0, conf.p1_type);
	msgCreatePlayer(1, conf.p2_type);
}

Game::~Game()
{

}

void Game::start()
{
	cout << "==- START GAME -==" << endl;

	// Init the game by sending the first input request.
	msgRequestInput(current_player);

	while (run) {
		processMessage(_game_center_channel);
		sleep(sleep_time);
	}

	cout << "==- END GAME -==" << endl;
	msgSendFinished();
}

TwoWayChannel& Game::getGameCenterChannel()
{
	return _game_center_channel;
}

void Game::processMessage(TwoWayChannel& channel)
{
        shared_ptr<Message> msg;
        if (!channel.receive(msg)) {
                return;
        }

	switch (msg->type) {
		case GAME_QUIT:
			process(static_pointer_cast<MsgGameQuit>(msg));
			break;
		case GAME_RETURN_INPUT:
			process(static_pointer_cast<MsgGameReturnInput>(msg));
			break;
		default:
			cerr << "ERROR: Unexpected message type." << endl;
	}
}

void Game::process(std::shared_ptr<MsgGameQuit> msg)
{
	run = false;
}

void Game::process(std::shared_ptr<MsgGameReturnInput> msg)
{
	if (makeMove(current_player, msg->node_id)) {

		if (board.checkVictoryCondition(current_player)) {
			PlayerID winner(current_player);
			cout << "Player " << winner << " wins!" << endl;
			msgSendWinner(winner);
			return;
		}

		current_player = !current_player;
	}

	msgRequestInput(current_player);
}

void Game::msgRequestInput(PlayerID player_id)
{
	std::shared_ptr<Message> msg(new MsgGameRequestInput(player_id));
	_game_center_channel.send(msg);
}

void Game::msgCreatePlayer(PlayerID player_id, PlayerType player_type)
{
	std::shared_ptr<Message> msg(new MsgGameCreatePlayer(player_id, player_type));
	_game_center_channel.send(msg);
}

void Game::msgCreateGem(PlayerID player_id, NodeID node_id)
{
	std::shared_ptr<Message> msg(new MsgGameCreateGem(player_id, node_id));
	_game_center_channel.send(msg);
}

void Game::msgCreateMarker(PlayerID player_id, FaceID face_id)
{
	std::shared_ptr<Message> msg(new MsgGameCreateMarker(player_id, face_id));
	_game_center_channel.send(msg);
}

void Game::msgSendWinner(PlayerID player_id)
{
	std::shared_ptr<Message> msg(new MsgGameSendWinner(player_id));
	_game_center_channel.send(msg);
}

void Game::msgSendFinished()
{
	std::shared_ptr<Message> msg(new MsgGameFinished());
	_game_center_channel.send(msg);
}

bool Game::makeMove(PlayerID player_id, NodeID node_id)
{
	if(board.isNodeID(node_id)){
		if(!board.nodeHasOwner(node_id)){
			placeGem(player_id, node_id);
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


/* CONSOLE GAME */


ConsoleGame::ConsoleGame(GameConf const& conf, Board& board)
	: Game(conf, board) {}

void ConsoleGame::placeGem(PlayerID player_id, NodeID node_id)
{
	vector<FaceID> new_markers;

	cout << "Player " << current_player << " placed a gem on " <<
		board.getNode(node_id).label << "." << endl;
	board.placeGem(node_id, player_id, new_markers);

	for(unsigned int i=0; i<new_markers.size(); i++){
		cout << "A new marker of player " << current_player
			<< " has been placed on " << new_markers[i] << "."
			<< endl;
	}
}


/* SIMPLE GUI GAME */


SimpleGUIGame::SimpleGUIGame(GameConf const& conf, Board& board)
	: Game(conf, board) {}

void SimpleGUIGame::placeGem(PlayerID player_id, NodeID node_id)
{
	std::vector<FaceID> new_markers;

	board.placeGem(node_id, player_id, new_markers);
	msgCreateGem(player_id, node_id);

	for(unsigned int i=0; i<new_markers.size(); i++){
		msgCreateGem(player_id, new_markers[i]);
	}
}
