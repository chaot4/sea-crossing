#include "game/game.h"
#include "engine/renderHub.h"

int main(){
	Board board;
	RandomAIPlayer player1("Spongebob", board);
	RandomAIPlayer player2("Patrick", board);

	ConsoleGame g(&player1, &player2, board);
	g.start();
}
