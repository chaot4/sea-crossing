#include "human_players.h"

using namespace std;

void ConsolePlayer::getNextMove(NodeLabel& node_label)
{
	cout << name << ", place your gem: ";
	cin >> node_label;
}

void ConsolePlayer::getMarkerMove(FaceLabel& face_label)
{
	cout << name << ", place your marker: ";
	cin >> face_label;
}
