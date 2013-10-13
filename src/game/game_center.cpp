#include "game_center.h"

using namespace std;

GameCenter::GameCenter(GameConf const& game_conf,
		Board& board)
	: run(true), sleep_time(5), _game_channel(0),
	_current_game(0), board(board), game_conf(game_conf) {}

GameCenter::~GameCenter()
{
	if (_current_game) { delete _current_game; }
	if (_current_game_thread) { delete _current_game_thread; }
	if (_game_channel) { delete _game_channel; }
}

void GameCenter::start()
{
	shared_ptr<Message> msg;

	while(run) {
		processMessage(_hub_channel);
		sleep(sleep_time);
		processMessage(*_game_channel);
		sleep(sleep_time);
	}
}

void GameCenter::processMessage(TwoWayChannel& channel)
{
        shared_ptr<Message> msg;
        if (!channel.receive(msg)) {
                return;
        }

	switch (msg->type) {
		case GAME_CREATE_GEM:
			process(static_pointer_cast<MsgGameCreateGem>(msg));
			break;
		case GAME_CREATE_MARKER:
			process(static_pointer_cast<MsgGameCreateMarker>(msg));
			break;
		case GAME_CREATE_PLAYER:
			process(static_pointer_cast<MsgGameCreatePlayer>(msg));
			break;
		case GAME_QUIT:
			process(static_pointer_cast<MsgGameQuit>(msg));
			break;
		case GAME_FINISHED:
			process(static_pointer_cast<MsgGameFinished>(msg));
			break;
		case GAME_RETURN_INPUT:
			process(static_pointer_cast<MsgGameReturnInput>(msg));
			break;
		case GAME_REQUEST_INPUT:
			process(static_pointer_cast<MsgGameRequestInput>(msg));
			break;
		case GAME_SEND_WINNER:
			process(static_pointer_cast<MsgGameSendWinner>(msg));
			break;
		default:
			cerr << "ERROR: Unexpected message type." << endl;
	}
}

void GameCenter::process(std::shared_ptr<MsgGameCreatePlayer> msg)
{
	_hub_channel.send(msg);
}

void GameCenter::process(std::shared_ptr<MsgGameCreateGem> msg)
{
	_hub_channel.send(msg);
}

void GameCenter::process(std::shared_ptr<MsgGameCreateMarker> msg)
{
	_hub_channel.send(msg);
}

void GameCenter::process(std::shared_ptr<MsgGameQuit> msg)
{
	if (_game_channel) {
		_game_channel->send(msg);
	}
}

void GameCenter::process(std::shared_ptr<MsgGameFinished> msg)
{
	_current_game_thread->join();
	delete _current_game;
	delete _current_game_thread;
	delete _game_channel;
	_current_game = 0;
	_current_game_thread = 0;
	_game_channel = 0;
}

void GameCenter::process(std::shared_ptr<MsgGameReturnInput> msg)
{
	if (_game_channel) {
		_game_channel->send(msg);
	}
}

void GameCenter::process(std::shared_ptr<MsgGameRequestInput> msg)
{
	_hub_channel.send(msg);
}

void GameCenter::process(std::shared_ptr<MsgGameSendWinner> msg)
{
	_hub_channel.send(msg);
}

bool GameCenter::startGame(GameType game_type)
{
	if (_current_game || _current_game_thread || _game_channel) {
		return false;
	}

	/* Game Factory */
	switch (game_type) {
		case DEBUG_GAME:
			// TODO
			break;
		case CONSOLE_GAME:
			_current_game = new ConsoleGame(game_conf, board);
			break;
		case GUI_GAME:
			_current_game = new SimpleGUIGame(game_conf, board);
			break;
		default:
			cerr << "Unexpected game type passed to the Game Center." << endl;
			return false;
	}

	_game_channel = new TwoWayChannel();
	TwoWayChannel::connect(*_game_channel, _current_game->getGameCenterChannel());

	_current_game_thread = new std::thread(&Game::start, _current_game);

	return true;
}

TwoWayChannel& GameCenter::getHubChannel()
{
	return _hub_channel;
}
