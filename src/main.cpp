#include "game/game.h"
#include "engine/renderHub.h"

int main(){
	Board board;
	ConsolePlayer player1("Spongebob");
	RandomAIPlayer player2("Patrick", board);

	ConsoleGame g(&player1, &player2, board);
	g.start();
}
