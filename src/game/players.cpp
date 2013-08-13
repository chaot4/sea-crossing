#include "players.h"

using namespace std;

Player::Player(std::string const& name):name(name){}

string Player::getName(){
	return name;
}

void ConsolePlayer::getNextMove(NodeLabel& node_label){
	cout << name << ", place your gem: ";
	cin >> node_label;
}

void ConsolePlayer::getMarkerMove(FaceLabel& face_label){
	cout << name << ", place your marker: ";
	cin >> face_label;
}
