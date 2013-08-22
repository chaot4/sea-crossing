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
	
	Board board;
	RandomAIPlayer player1("Spongebob", board);
	RandomAIPlayer player2("Patrick", board);
	
	SimpleGUIGame<MessageReceiver> g(&player1, &player2, board, testReceiver);
	std::thread gameThread(&SimpleGUIGame<MessageReceiver>::start,&g);

	gameThread.join();
	renderThread.join();

}
