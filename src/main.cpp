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
	ShortestPathAIPlayer<Cost, Rating> player2(conf.getGameConf().p2_name, board);
	
	SimpleGUIGame g(&player1, &player2, board, conf.getGameConf(), testReceiver);
	std::thread gameThread(&SimpleGUIGame::start,&g);

	gameThread.join();
	renderThread.join();
}
