#include "players.h"

using namespace std;

string Player::getName() const
{
	return name;
}

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
