#include "player.h"

using namespace std;

string Player::getName() const
{
	return name;
}

void Player::setID(PlayerID id)
{
	this->id = id;
}
