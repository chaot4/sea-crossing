#include "human_players.h"

using namespace std;

void GUIPlayer::msgSendEngineRequestInput(PlayerID id)
{
	std::shared_ptr<Message> new_msg(new MsgPlayerRequestInput(id));
	_player_center_channel.send(new_msg);
}

void GUIPlayer::initGemMove()
{
	msgSendEngineRequestInput(id);
}

void ConsolePlayer::initGemMove()
{
	NodeLabel node_label;
	bool valid_input(false);

	while (!valid_input) {
		cout << name << ", place your gem: ";
		cin >> node_label;

		if (board.isNodeLabel(node_label)) {
			valid_input = true;
		}
		else {
			cerr << "ERROR: " << node_label << " is not a node label." << endl;
		}
	}

	msgSendGemMove(board.getNodeID(node_label));
}

void DebugPlayer::initMarkerMove()
{
	FaceLabel face_label;
	bool valid_input(false);

	while (!valid_input) {
		cout << name << ", place your marker: ";
		cin >> face_label;

		if (board.isFaceLabel(face_label)) {
			valid_input = true;
		}
		else {
			cerr << "ERROR: " << face_label << " is not a face label." << endl;
		}
	}

	msgSendMarkerMove(board.getFaceID(face_label));
}

void DebugPlayer::msgSendMarkerMove(FaceID face_id)
{
//	std::shared_ptr<Message> new_msg(new MsgGameReturnInput(marker_id));
//	_player_center_channel.send(new_msg);
//	TODO
}
