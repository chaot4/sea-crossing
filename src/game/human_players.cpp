#include "human_players.h"

using namespace std;

void ConsolePlayer::initGemMove()
{
	NodeLabel node_label;

	cout << name << ", place your gem: ";
	cin >> node_label;
}

void DebugPlayer::initMarkerMove()
{
	FaceLabel face_label;

	cout << name << ", place your marker: ";
	cin >> face_label;
}
