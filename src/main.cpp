//#include "conf.h"
#include "game/game.h"
#include "engine/renderHub.h"

#include <thread>

int main(){

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

	testReceiver->pushCreateMarkerMessage("BSE", 0);
	
//	Board board;
//	RandomAIPlayer player1("Spongebob", board);
//	RandomAIPlayer player2("Patrick", board);
//	
//	ConsoleGame g(&player1, &player2, board);
//	//g.start();
//	std::thread gameThread(&ConsoleGame::start,&g);
//
//	gameThread.join();
	renderThread.join();

}
