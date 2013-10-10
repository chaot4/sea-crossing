#include "conf.h"
#include "game/game.h"
#include "engine/renderHub.h"
#include "messageChannel.h"

#include <thread>
#include <vector>

using namespace std;

int main(){

	Conf conf("config");
	conf.readFromFile();

	// Test
	TwoWayChannel c1;
	TwoWayChannel c2;
	TwoWayChannel::connect(c1, c2);
	c1.send<int>(5);
	c2.send(6);
	c2.send(7);
	int msg1;
	int msg2;
	c2.receive<int>(msg1);
	cout << msg1 << endl;
	c1.receive(msg2);
	cout << msg2 << endl;
	c1.receive(msg2);
	cout << msg2 << endl;
	// Ende Test

	MessageReceiver *testReceiver;
	RenderHub testRenderer(testReceiver);
	//if(testRenderer.init())
	//{
	//	testRenderer.addScene();
	//	testRenderer.setActiveScene(0);
	//	testReceiver->pushLoadSceneMessages();
	//	std::thread renderThread(&RenderHub::run,&testRenderer);
	//}
	std::thread renderThread(&RenderHub::init,&testRenderer);
	testReceiver->pushLoadSceneMessages();
	
	Board board;
	RandomAIPlayer player1(conf.getGameConf().p1_name, board);
	RandomAIPlayer player2(conf.getGameConf().p2_name, board);
	
	SimpleGUIGame g(&player1, &player2, board, conf.getGameConf(), testReceiver);
	std::thread gameThread(&SimpleGUIGame::start,&g);

	gameThread.join();
	renderThread.join();
}
