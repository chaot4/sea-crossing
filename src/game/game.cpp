#include "game.h"

using namespace std;

void DebugGame::start()
{
	string command("");
	bool game_finished(false);
	DebugGameData d(Board(), ConsolePlayer("Spongebob"), ConsolePlayer("Patrick"));

	cout << "==- START DEBUG GAME -==" << endl << endl;
	cout << "The possible commands are: player1 (p1), player2 (p2), marker_player1 (mp1),"
		<< endl;
	cout <<	"                           marker_player2 (mp2), back (b), forward (f), exit (e)."
		<< endl;

	while(!game_finished){
		cout << endl << "Pass a command: ";
		cin >> command;

		if(command == "player1" || command == "p1"){
			game_finished = command_player(d, 0);
		}
		else if(command == "player2" || command == "p2"){
			game_finished = command_player(d, 1);
		}
		else if(command == "marker_player1" || command == "mp1"){
			game_finished = command_marker_player(d, 0);
		}
		else if(command == "marker_player2" || command == "mp2"){
			game_finished = command_marker_player(d, 1);
		}
		else if(command == "back" || command == "b"){
			command_back();
		}
		else if(command == "forward" || command == "f"){
			command_forward();
		}
		else if(command == "exit" || command == "e"){
			goto end;
		}
		else{
			cout << "ERROR: The command you entered is not known." << endl;
		}
	}

	end:;
	cout << endl << "==- END DEBUG GAME -==" << endl;
}

bool DebugGame::command_player(DebugGameData& d, PlayerID player_id)
{
	// TODO set marker if necessary
	NodeLabel label;
	d.player[player_id].getNextMove(label);

	if(d.board.isNodeLabel(label))
		if(d.board.placeGem(label, player_id))
			cout << "Placed a gem on " << label << "." << endl;
		else
			cout << "ERROR: This node is already taken." << endl;
	else
		cout << "ERROR: The passed string is not a node label." << endl;

	return false;
}

bool DebugGame::command_marker_player(DebugGameData& d, PlayerID player_id)
{
	FaceLabel label;
	d.player[player_id].getMarkerMove(label);

	if(d.board.isFaceLabel(label)){
		if(d.board.placeMarker(label, player_id)){

			cout << "Placed a marker on " << label << "." << endl;
			if(d.board.checkVictoryCondition(player_id)){
				cout << d.player[player_id].getName() << " wins!" << endl;
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

void DebugGame::command_back()
{
	// TODO
}

void DebugGame::command_forward()
{
	// TODO
}
