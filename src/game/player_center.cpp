#include "player_center.h"

using namespace std;

PlayerCenter::PlayerCenter(Board const& board)
	: run(true), sleep_time(5), board(board) {}

void PlayerCenter::start()
{
	shared_ptr<Message> msg;

        while(run) {
		processMessage(_hub_channel);
                sleep(sleep_time);

		for (unsigned int i(0); i<_player_channels.size(); i++) {
			if (_player_channels[i]) {
				processMessage(*_player_channels[i]);
				sleep(sleep_time);
			}
		}
        }
}

void PlayerCenter::processMessage(TwoWayChannel& channel)
{
        shared_ptr<Message> msg;
        if (!channel.receive(msg)) {
                return;
        }

        switch (msg->type) {
		case GAME_REQUEST_INPUT:
			process(static_pointer_cast<MsgGameRequestInput>(msg));
			break;
		case GAME_RETURN_INPUT:
			process(static_pointer_cast<MsgGameReturnInput>(msg));
			break;
		case GAME_CREATE_PLAYER:
			process(static_pointer_cast<MsgGameCreatePlayer>(msg));
			break;
		case PLAYER_REQUEST_INPUT:
			process(static_pointer_cast<MsgPlayerRequestInput>(msg));
			break;
		case PLAYER_RETURN_INPUT:
			process(static_pointer_cast<MsgPlayerReturnInput>(msg));
			break;
		case PLAYER_QUIT:
			process(static_pointer_cast<MsgPlayerQuit>(msg));
			break;
		case PLAYER_FINISHED:
			process(static_pointer_cast<MsgPlayerFinished>(msg));
			break;
		case QUIT:
//			quit();
			break;
                default:
                        cerr << "ERROR: Unexpected message type: " << toString(msg->type) << endl;
        }
}

void PlayerCenter::process(std::shared_ptr<MsgGameRequestInput> msg)
{
	if (_player_channels.size() > msg->player_id) {
		_player_channels[msg->player_id]->send(static_pointer_cast<Message>(msg));
	}
	else {
		cerr << "ERROR: Message to non-existing player id." << endl;
	}
}

void PlayerCenter::process(std::shared_ptr<MsgGameReturnInput> msg)
{
	_hub_channel.send(static_pointer_cast<Message>(msg));
}

void PlayerCenter::process(std::shared_ptr<MsgPlayerRequestInput> msg)
{
	_hub_channel.send(static_pointer_cast<Message>(msg));
}

void PlayerCenter::process(std::shared_ptr<MsgPlayerReturnInput> msg)
{
	if (_player_channels.size() > msg->player_id) {
		_player_channels[msg->player_id]->send(static_pointer_cast<Message>(msg));
	}
	else {
		cerr << "ERROR: Message to non-existing player id." << endl;
	}
}

void PlayerCenter::process(std::shared_ptr<MsgGameCreatePlayer> msg)
{
	createPlayer(msg->player_id, msg->player_type, msg->player_name);
}

void PlayerCenter::process(std::shared_ptr<MsgPlayerQuit> msg)
{
	if (_player_channels.size() > msg->player_id) {
		_player_channels[msg->player_id]->send(static_pointer_cast<Message>(msg));
	}
	else {
		cerr << "ERROR: Message to non-existing player id." << endl;
	}
}

void PlayerCenter::process(std::shared_ptr<MsgPlayerFinished> msg)
{
	PlayerID player_id(msg->player_id);

	_player_threads[player_id]->join();
	delete _players[player_id];
	delete _player_threads[player_id];
	delete _player_channels[player_id];
	_players[player_id] = 0;
	_player_threads[player_id] = 0;
	_player_channels[player_id] = 0;
}

void PlayerCenter::createPlayer(PlayerID player_id, PlayerType player_type, string const& name)
{
	/* Player Factory */
	switch (player_type) {
		case CONSOLE_PLAYER:
			_players.push_back(new ConsolePlayer(player_id, name, board));
			break;
		case GUI_PLAYER:
			// TODO
			break;
		case DEBUG_PLAYER:
			_players.push_back(new DebugPlayer(player_id, name, board));
			break;
		case RANDOM_AI:
			_players.push_back(new RandomAIPlayer(player_id, name, board));
			break;
		case SHORTEST_PATH_AI:
			_players.push_back(new ShortestPathAIPlayer
					<NaiveCost, EqualityRating>(player_id, name, board));
			break;
		default:
			cerr << "Unexpected player type passed to the Player Center." << endl;
	}

	_player_channels.push_back(new TwoWayChannel());
	TwoWayChannel::connect(*_player_channels.back(),
			_players.back()->getPlayerCenterChannel());

	_player_threads.push_back(new std::thread(&Player::start, _players.back()));
}

TwoWayChannel& PlayerCenter::getHubChannel()
{
	return _hub_channel;
}

//void PlayerCenter::quit()
//{
//	for (unsigned int i(0); i<_player_channels.size(); i++) {
//		std::shared_ptr<Message> msg(new MsgQuit());
//		_player_channels[i]->send(msg);
//	}
//}
