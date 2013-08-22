#include "conf.h"
#include "game/game.h"
#include "engine/renderHub.h"

#include <thread>

using namespace std;

int main(){

	Conf conf;
	getConfFromFile("config", conf);

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
	testReceiver->pushCreateMarkerMessage("BSE",0);
	testReceiver->pushCreateMarkerMessage("CN",0);
	testReceiver->pushCreateMarkerMessage("DE-1",0);
	testReceiver->pushCreateMarkerMessage("DW1",0);
	testReceiver->pushCreateMarkerMessage("EN-1",0);
	testReceiver->pushCreateMarkerMessage("EE1",0);
	testReceiver->pushCreateMarkerMessage("EW",0);
	
	Board board;
	ConsolePlayer player1("Spongebob");
	ConsolePlayer player2("Patrick");
	
	SimpleGUIGame<MessageReceiver> g(&player1, &player2, board, testReceiver);
	std::thread gameThread(&SimpleGUIGame<MessageReceiver>::start,&g);

	gameThread.join();
	renderThread.join();
}
