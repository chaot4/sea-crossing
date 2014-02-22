#include "player.h"

using namespace std;

Player::Player(PlayerID id, std::string const& name, Board const& board)
	: run(true), sleep_time(5), board(board), name(name), id(id)
{

}

Player::~Player()
{

}

void Player::start()
{
	cout << "==- PLAYER " << name << " CREATED -==" << endl;

	while (run) {
		processMessage(_player_center_channel);
		sleep(sleep_time);
	}

	cout << "==- PLAYER " << name << " FINISHED -==" << endl;
	msgSendFinished();
}

TwoWayChannel& Player::getPlayerCenterChannel()
{
	return _player_center_channel;
}

void Player::processMessage(TwoWayChannel& channel)
{
        shared_ptr<Message> msg;
        if (!channel.receive(msg)) {
                return;
        }

	switch (msg->type) {
		case GAME_REQUEST_INPUT:
			process(static_pointer_cast<MsgGameRequestInput>(msg));
			break;
		case PLAYER_RETURN_INPUT:
			process(static_pointer_cast<MsgPlayerReturnInput>(msg));
			break;
		case PLAYER_QUIT:
			process(static_pointer_cast<MsgPlayerQuit>(msg));
			break;
		default:
			cerr << "ERROR: Unexpected message type: " << toString(msg->type) << endl;
	}
}

void Player::process(std::shared_ptr<MsgGameRequestInput> msg)
{
	if (msg->player_id == id) {
		initGemMove();
	}
	else {
		cerr << "Player " << id << " received an input request that belongs"
			<< " to another id." << endl;
	}
}

void Player::process(std::shared_ptr<MsgPlayerReturnInput> msg)
{
	std::shared_ptr<Message> new_msg(new MsgGameReturnInput(msg->node_id));
	_player_center_channel.send(new_msg);
}

void Player::process(std::shared_ptr<MsgPlayerQuit> msg)
{
	if (msg->player_id == id) {
		run = false;
	}
	else {
		cerr << "Player " << id << " received a quit request that belongs"
			<< " to another id." << endl;
	}
}

void Player::msgSendGemMove(NodeID node_id)
{
	std::shared_ptr<Message> new_msg(new MsgGameReturnInput(node_id));
	_player_center_channel.send(new_msg);
}

void Player::msgSendFinished()
{
	std::shared_ptr<Message> msg(new MsgPlayerFinished(id));
	_player_center_channel.send(msg);
}
